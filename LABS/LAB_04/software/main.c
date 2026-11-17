
#include "xil_io.h"
#include "xil_printf.h"
#include "sleep.h"

/* AXI GPIO base address from Vivado Address Editor */
#define GPIO_BASE 0x40000000U

/* AXI GPIO register offsets */
#define DIN       0x00U  /* Channel 1: output to RM */
#define DOUT      0x08U  /* Channel 2: input from RM */

static const char *identify(void)
{
    Xil_Out32(GPIO_BASE + DIN, 0x0001U);
    usleep(100);

    u32 r = Xil_In32(GPIO_BASE + DOUT) & 0xFFFFU;

    if (r == 0x0001U)
        return "RM A (pass-through)";

    if (r == 0xFFFEU)
        return "RM B (invert)";

    if (r == 0x0100U)
        return "RM C (swap bytes)";

    return "unknown";
}

int main(void)
{
    u16 cnt = 0;

    xil_printf("\r\nLab 04 - MicroBlaze Partial Reconfiguration\r\n");

    while (1) {
        const char *name = identify();

        Xil_Out32(GPIO_BASE + DIN, cnt);
        usleep(1000);

        u32 out = Xil_In32(GPIO_BASE + DOUT) & 0xFFFFU;

        xil_printf("loaded: %s   in=%04x out=%04x\r\n",
                   name,
                   (unsigned int)cnt,
                   (unsigned int)out);

        cnt++;
        usleep(250000);
    }
}
