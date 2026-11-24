/*
 * Advanced Hardware Engineering, Lab 05, Part C
 * Nexys A7-100T / MicroBlaze / FreeRTOS 10 / DDR2
 *
 * Build as the ONLY application source defining main() in a new FreeRTOS
 * Application Component named rtos_app. All hardware addresses below are
 * taken from the user's Vivado Address Editor (21 November 2026).
 *
 * GPIO0 CH1: 16 DIP switches (inputs); CH2: 16 LEDs (outputs).
 * GPIO1 CH1: seven-segment cathodes/DP (outputs, active-low);
 *       CH2: digit anodes (outputs, active-low).
 * UART Lite: 9600 baud, 8N1, with xil_printf routed to axi_uartlite_0.
 *
 * Lab extension: commands 'log clear' and 'monitor on/off' are supported.
 * Modified/created implementation for the user's Lab 05 Part C.
 */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "xil_io.h"
#include "xil_printf.h"
#include "xil_cache.h"
#include <string.h>

#define GPIO0_BASE          0x40000000u
#define GPIO1_BASE          0x40010000u
#define UART_BASE           0x40600000u

/* AXI GPIO register offsets: channel 1 DATA/TRI, channel 2 DATA/TRI. */
#define GPIO_DATA_CH1       0x00u
#define GPIO_TRI_CH1        0x04u
#define GPIO_DATA_CH2       0x08u
#define GPIO_TRI_CH2        0x0cu

/* AXI UART Lite register offsets and RX-valid bit. */
#define UART_RX_FIFO        0x00u
#define UART_STATUS         0x08u
#define UART_RX_VALID       0x01u

#define LOG_ENTRIES         65536u
#define LOG_QUEUE_LENGTH    32u
#define SHELL_LINE_LENGTH   64u

/* This is exactly 8 bytes, so 65536 entries occupy 512 KiB in DDR2. */
typedef struct {
    u32 tick;
    u32 switches;
} LogEvent;

static QueueHandle_t g_q;
static SemaphoreHandle_t g_print_mx;
static TimerHandle_t g_heartbeat_timer;
static TaskHandle_t g_input_h, g_display_h, g_logger_h;
static TaskHandle_t g_shell_h, g_monitor_h;

static LogEvent *g_ring;
static volatile u32 g_log_head = 0u;    /* next insertion index */
static volatile u32 g_log_count = 0u;   /* retained entries, maximum 65536 */
static volatile u32 g_log_total = 0u;   /* all events since last clear */
static volatile u16 g_switches = 0u;
static volatile u16 g_led = 0u;
static volatile u16 g_seg_value = 0x1234u;
static volatile BaseType_t g_mirror = pdTRUE;
static volatile BaseType_t g_monitor = pdFALSE;

/* The mutex protects complete xil_printf calls from task interleaving. */
#define PRINT(...) do {                                     \
    if (xSemaphoreTake(g_print_mx, portMAX_DELAY) == pdTRUE) { \
        xil_printf(__VA_ARGS__);                           \
        xSemaphoreGive(g_print_mx);                         \
    }                                                       \
} while (0)

/* Call only from tasks or the FreeRTOS software-timer callback, not an ISR. */
static void led_update(u16 mask, u16 value)
{
    taskENTER_CRITICAL();
    g_led = (u16)((g_led & (u16)~mask) | (value & mask));
    Xil_Out32(GPIO0_BASE + GPIO_DATA_CH2, (u32)g_led);
    taskEXIT_CRITICAL();
}

static void heartbeat_callback(TimerHandle_t timer)
{
    (void)timer;
    /* LED15 is reserved for the heartbeat. The other 15 LEDs are controllable. */
    led_update(0x8000u, (u16)(g_led ^ 0x8000u));
}

/* input_task: priority 3, stack 256 words, period 20 ms. */
static void input_task(void *arg)
{
    TickType_t last_wake = xTaskGetTickCount();
    u16 previous = 0u;
    BaseType_t first = pdTRUE;
    (void)arg;

    for (;;) {
        u16 switches = (u16)(Xil_In32(GPIO0_BASE + GPIO_DATA_CH1) & 0xffffu);
        g_switches = switches;

        if (g_mirror == pdTRUE) {
            led_update(0x7fffu, (u16)(switches & 0x7fffu));
        }

        if (first == pdTRUE || switches != previous) {
            LogEvent event;
            event.tick = (u32)xTaskGetTickCount();
            event.switches = (u32)switches;
            /* Timeout 0 prevents switch sampling from stalling on a full queue. */
            (void)xQueueSend(g_q, &event, 0);
            previous = switches;
            first = pdFALSE;
        }
        vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(20));
    }
}

/* Standard active-low common-anode segment patterns, bit order dp-g-f-e-d-c-b-a. */
static const u8 g_hex_segments[16] = {
    0xc0u, 0xf9u, 0xa4u, 0xb0u, 0x99u, 0x92u, 0x82u, 0xf8u,
    0x80u, 0x90u, 0x88u, 0x83u, 0xc6u, 0xa1u, 0x86u, 0x8eu
};

/* display_task: priority 3, stack 256 words, one digit every 2 ms. */
static void display_task(void *arg)
{
    TickType_t last_wake = xTaskGetTickCount();
    u32 digit = 0u;
    (void)arg;

    for (;;) {
        u16 value = g_seg_value;
        u32 nibble = ((u32)value >> (4u * digit)) & 0x0fu;

        /* Disable all digits before changing cathodes to prevent ghosting. */
        Xil_Out32(GPIO1_BASE + GPIO_DATA_CH2, 0xffu);
        Xil_Out32(GPIO1_BASE + GPIO_DATA_CH1, (u32)g_hex_segments[nibble]);
        Xil_Out32(GPIO1_BASE + GPIO_DATA_CH2, (u32)(0xffu ^ (1u << digit)));

        digit = (digit + 1u) & 3u; /* Show four hexadecimal digits. */
        vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(2));
    }
}

/* logger_task: priority 2, stack 256 words, waits for switch events. */
static void logger_task(void *arg)
{
    LogEvent event;
    (void)arg;

    for (;;) {
        if (xQueueReceive(g_q, &event, portMAX_DELAY) == pdTRUE) {
            taskENTER_CRITICAL();
            g_ring[g_log_head & (LOG_ENTRIES - 1u)] = event;
            g_log_head++;
            if (g_log_count < LOG_ENTRIES) {
                g_log_count++;
            }
            g_log_total++;
            taskEXIT_CRITICAL();
        }
    }
}

static void print_stats(void)
{
    u32 count;
    taskENTER_CRITICAL();
    count = g_log_total;
    taskEXIT_CRITICAL();

    PRINT("uptime %u ticks, heap free %u bytes (minimum %u), log %u entries\r\n",
          (unsigned)xTaskGetTickCount(),
          (unsigned)xPortGetFreeHeapSize(),
          (unsigned)xPortGetMinimumEverFreeHeapSize(),
          (unsigned)count);

#if defined(INCLUDE_uxTaskGetStackHighWaterMark) && (INCLUDE_uxTaskGetStackHighWaterMark == 1)
    PRINT("stack free (words): input %u, display %u, logger %u, shell %u, monitor %u\r\n",
          (unsigned)uxTaskGetStackHighWaterMark(g_input_h),
          (unsigned)uxTaskGetStackHighWaterMark(g_display_h),
          (unsigned)uxTaskGetStackHighWaterMark(g_logger_h),
          (unsigned)uxTaskGetStackHighWaterMark(g_shell_h),
          (unsigned)uxTaskGetStackHighWaterMark(g_monitor_h));
#else
    PRINT("stack free (words): n/a (enable INCLUDE_uxTaskGetStackHighWaterMark in the BSP)\r\n");
#endif
}

static void print_log(void)
{
    LogEvent recent[10];
    u32 n, count, total, head;

    taskENTER_CRITICAL();
    count = g_log_count;
    total = g_log_total;
    head = g_log_head;
    n = count < 10u ? count : 10u;
    for (u32 i = 0u; i < n; ++i) {
        recent[i] = g_ring[(head - 1u - i) & (LOG_ENTRIES - 1u)];
    }
    taskEXIT_CRITICAL();

    for (u32 i = 0u; i < n; ++i) {
        PRINT("tick %u: switches %04x\r\n",
              (unsigned)recent[i].tick,
              (unsigned)(recent[i].switches & 0xffffu));
    }
    PRINT("%u entries in total\r\n", (unsigned)total);
}

/* Parse one to four hexadecimal digits, optionally preceded by '0x'. */
static BaseType_t parse_hex16(const char *s, u16 *out)
{
    u32 value = 0u;
    u32 digits = 0u;

    while (*s == ' ') ++s;
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) s += 2;

    while (*s != '\0' && *s != ' ') {
        char c = *s++;
        u32 digit;
        if (c >= '0' && c <= '9') digit = (u32)(c - '0');
        else if (c >= 'a' && c <= 'f') digit = (u32)(c - 'a' + 10);
        else if (c >= 'A' && c <= 'F') digit = (u32)(c - 'A' + 10);
        else return pdFALSE;
        if (++digits > 4u) return pdFALSE;
        value = (value << 4u) | digit;
    }
    while (*s == ' ') ++s;
    if (digits == 0u || *s != '\0') return pdFALSE;
    *out = (u16)value;
    return pdTRUE;
}

static void execute_command(const char *line)
{
    u16 value;

    if (strcmp(line, "help") == 0) {
        PRINT("help | led <hex> | sw | seg <hex> | mirror on/off | log [clear] | stats | monitor on/off\r\n");
    } else if (strcmp(line, "sw") == 0) {
        PRINT("switches: %04x\r\n", (unsigned)g_switches);
    } else if (strncmp(line, "led ", 4) == 0) {
        if (parse_hex16(line + 4, &value) == pdTRUE) {
            g_mirror = pdFALSE;
            led_update(0x7fffu, (u16)(value & 0x7fffu));
            PRINT("LEDs 0..14: %04x (mirror off)\r\n", (unsigned)(value & 0x7fffu));
        } else {
            PRINT("usage: led <hex>, e.g. led 00ff\r\n");
        }
    } else if (strncmp(line, "seg ", 4) == 0) {
        if (parse_hex16(line + 4, &value) == pdTRUE) {
            g_seg_value = value;
            PRINT("display: %04x\r\n", (unsigned)value);
        } else {
            PRINT("usage: seg <hex>, e.g. seg 1234\r\n");
        }
    } else if (strcmp(line, "mirror on") == 0) {
        g_mirror = pdTRUE;
        led_update(0x7fffu, (u16)(g_switches & 0x7fffu));
        PRINT("mirror on\r\n");
    } else if (strcmp(line, "mirror off") == 0) {
        g_mirror = pdFALSE;
        PRINT("mirror off\r\n");
    } else if (strcmp(line, "log") == 0) {
        print_log();
    } else if (strcmp(line, "log clear") == 0) {
        taskENTER_CRITICAL();
        g_log_head = 0u;
        g_log_count = 0u;
        g_log_total = 0u;
        taskEXIT_CRITICAL();
        PRINT("log cleared\r\n");
    } else if (strcmp(line, "stats") == 0) {
        print_stats();
    } else if (strcmp(line, "monitor on") == 0) {
        g_monitor = pdTRUE;
        PRINT("monitor on (every 5 seconds)\r\n");
    } else if (strcmp(line, "monitor off") == 0) {
        g_monitor = pdFALSE;
        PRINT("monitor off\r\n");
    } else if (line[0] != '\0') {
        PRINT("unknown command: %s (type help)\r\n", line);
    }
}

/* shell_task: priority 2, stack 768 words, polls UART every 10 ms. */
static void shell_task(void *arg)
{
    char line[SHELL_LINE_LENGTH];
    u32 used = 0u;
    (void)arg;

    PRINT("\r\nFreeRTOS I/O controller\r\n> ");
    for (;;) {
        while ((Xil_In32(UART_BASE + UART_STATUS) & UART_RX_VALID) != 0u) {
            char ch = (char)(Xil_In32(UART_BASE + UART_RX_FIFO) & 0xffu);
            if (ch == '\r' || ch == '\n') {
                if (used != 0u) {
                    line[used] = '\0';
                    PRINT("\r\n");
                    execute_command(line);
                    used = 0u;
                    PRINT("> ");
                }
            } else if (ch == '\b' || (unsigned char)ch == 127u) {
                if (used != 0u) {
                    --used;
                    PRINT("\b \b");
                }
            } else if (ch >= 32 && ch <= 126) {
                if (used < (SHELL_LINE_LENGTH - 1u)) {
                    line[used++] = ch;
                    PRINT("%c", ch); /* terminal local echo should be off */
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

/* monitor_task: priority 1, stack 512 words, period 5 seconds. */
static void monitor_task(void *arg)
{
    TickType_t last_wake = xTaskGetTickCount();
    (void)arg;

    for (;;) {
        vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(5000));
        if (g_monitor == pdTRUE) {
            PRINT("[monitor] ");
            print_stats();
        }
    }
}

void vApplicationMallocFailedHook(void)
{
    xil_printf("malloc failed\r\n");
    for (;;) { }
}

void vApplicationStackOverflowHook(TaskHandle_t task, char *name)
{
    (void)task;
    xil_printf("stack overflow in %s\r\n", name);
    for (;;) { }
}

int main(void)
{
    BaseType_t ok = pdPASS;

    Xil_ICacheEnable();
    Xil_DCacheEnable();

    /* AXI GPIO TRI: 1=input, 0=output. Disable all anodes initially. */
    Xil_Out32(GPIO0_BASE + GPIO_TRI_CH1, 0xffffu);
    Xil_Out32(GPIO0_BASE + GPIO_TRI_CH2, 0x0000u);
    Xil_Out32(GPIO1_BASE + GPIO_TRI_CH1, 0x0000u);
    Xil_Out32(GPIO1_BASE + GPIO_TRI_CH2, 0x0000u);
    Xil_Out32(GPIO0_BASE + GPIO_DATA_CH2, 0x0000u);
    Xil_Out32(GPIO1_BASE + GPIO_DATA_CH2, 0x00ffu);
    Xil_Out32(GPIO1_BASE + GPIO_DATA_CH1, 0x00ffu);

    g_ring = (LogEvent *)pvPortMalloc(LOG_ENTRIES * sizeof(LogEvent));
    g_q = xQueueCreate(LOG_QUEUE_LENGTH, sizeof(LogEvent));
    g_print_mx = xSemaphoreCreateMutex();
    if (g_ring == NULL || g_q == NULL || g_print_mx == NULL) {
        xil_printf("allocation failed - check FreeRTOS 2 MiB heap\r\n");
        for (;;) { }
    }

    g_heartbeat_timer = xTimerCreate("heartbeat", pdMS_TO_TICKS(500),
                                     pdTRUE, NULL, heartbeat_callback);
    if (g_heartbeat_timer == NULL) {
        xil_printf("heartbeat timer allocation failed\r\n");
        for (;;) { }
    }

    ok &= xTaskCreate(input_task,   "input",   256, NULL, 3, &g_input_h);
    ok &= xTaskCreate(display_task, "display", 256, NULL, 3, &g_display_h);
    ok &= xTaskCreate(logger_task,  "logger",  256, NULL, 2, &g_logger_h);
    ok &= xTaskCreate(shell_task,   "shell",   768, NULL, 2, &g_shell_h);
    ok &= xTaskCreate(monitor_task, "monitor", 512, NULL, 1, &g_monitor_h);

    if (ok != pdPASS || xTimerStart(g_heartbeat_timer, 0) != pdPASS) {
        xil_printf("task/timer creation failed\r\n");
        for (;;) { }
    }

    vTaskStartScheduler();
    xil_printf("scheduler failed to start\r\n");
    for (;;) { }
}
