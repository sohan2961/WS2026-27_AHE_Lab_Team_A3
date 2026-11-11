
/*
 * Advanced Hardware Engineering - Lab 03
 * MicroBlaze GPIO + 7-Segment + PWM
 *
 * Board: Nexys A7-100T
 * Tools: Vivado / Vitis 2025.1
 *
 * Functions:
 * 1. Read 16 switches
 * 2. Mirror switch states on 16 LEDs
 * 3. Display switch values in hexadecimal
 * 4. Control RGB LED using custom PWM IP
 */

#include "xil_io.h"
#include "xil_types.h"
#include "sleep.h"

/* =====================================
 * AXI BASE ADDRESSES
 * From Vivado Address Editor
 * ===================================== */

#define GPIO0_BASE  0x40000000U
#define GPIO1_BASE  0x40010000U
#define PWM_BASE    0x44A00000U

/* =====================================
 * AXI GPIO REGISTER OFFSETS
 * ===================================== */

/* GPIO 0: Switches and LEDs */
#define GPIO_SW       0x00U
#define GPIO_SW_TRI   0x04U
#define GPIO_LED      0x08U
#define GPIO_LED_TRI  0x0CU

/* GPIO 1: 7-segment display */
#define SEG_REG       0x00U
#define SEG_TRI       0x04U
#define AN_REG        0x08U
#define AN_TRI        0x0CU

/* =====================================
 * CUSTOM PWM REGISTER OFFSETS
 * ===================================== */

#define PWM_CTRL  0x00U
#define PWM_R     0x04U
#define PWM_G     0x08U
#define PWM_B     0x0CU

/* =====================================
 * 7-SEGMENT HEX PATTERN TABLE
 *
 * Common-anode, active-low segments
 * 0 = segment ON
 * 1 = segment OFF
 * ===================================== */

static const u8 seg[16] = {
    0xC0,  // 0
    0xF9,  // 1
    0xA4,  // 2
    0xB0,  // 3
    0x99,  // 4
    0x92,  // 5
    0x82,  // 6
    0xF8,  // 7
    0x80,  // 8
    0x90,  // 9
    0x88,  // A
    0x83,  // B
    0xC6,  // C
    0xA1,  // D
    0x86,  // E
    0x8E   // F
};

/* =====================================
 * DISPLAY 16-BIT HEX VALUE
 * On rightmost four digits
 * ===================================== */

void show_hex(u16 value)
{
    for (int d = 0; d < 4; d++)
    {
        // Extract one hexadecimal digit
        u32 nib = (value >> (4 * d)) & 0xFU;

        // Disable all digits
        Xil_Out32(GPIO1_BASE + AN_REG, 0xFFU);

        // Set the segment pattern
        Xil_Out32(GPIO1_BASE + SEG_REG, seg[nib]);

        // Enable only the selected digit
        Xil_Out32(GPIO1_BASE + AN_REG,
                  (~(1U << d)) & 0xFFU);

        // Display digit for 1 millisecond
        usleep(1000);
    }

    // Turn off digits until next refresh
    Xil_Out32(GPIO1_BASE + AN_REG, 0xFFU);
}

/* =====================================
 * MAIN PROGRAM
 * ===================================== */

int main(void)
{
    u32 sw;

    /* Configure GPIO 0 */
    // Channel 1: 16 switch inputs
    Xil_Out32(GPIO0_BASE + GPIO_SW_TRI, 0xFFFFU);

    // Channel 2: 16 LED outputs
    Xil_Out32(GPIO0_BASE + GPIO_LED_TRI, 0x0000U);

    /* Configure GPIO 1 */

    // Initially turn off all display segments
    // and digit enables
    Xil_Out32(GPIO1_BASE + SEG_REG, 0xFFU);
    Xil_Out32(GPIO1_BASE + AN_REG, 0xFFU);

    // Both channels are outputs
    Xil_Out32(GPIO1_BASE + SEG_TRI, 0x00U);
    Xil_Out32(GPIO1_BASE + AN_TRI, 0x00U);

    /* Enable custom PWM */
    Xil_Out32(PWM_BASE + PWM_CTRL, 1U);

    /* Main application loop */
    while (1)
    {
        // 1. Read all 16 switches
        sw = Xil_In32(GPIO0_BASE + GPIO_SW)
             & 0xFFFFU;

        // 2. Mirror switches on LEDs
        Xil_Out32(GPIO0_BASE + GPIO_LED, sw);

        // 3. Set RGB PWM brightness
        // Each 4-bit value is scaled to 8 bits

        // SW3..SW0 controls RED
        Xil_Out32(PWM_BASE + PWM_R,
                  ((sw >> 0) & 0xFU) * 17U);

        // SW7..SW4 controls GREEN
        Xil_Out32(PWM_BASE + PWM_G,
                  ((sw >> 4) & 0xFU) * 17U);

        // SW11..SW8 controls BLUE
        Xil_Out32(PWM_BASE + PWM_B,
                  ((sw >> 8) & 0xFU) * 17U);

        // 4. Display switch value in HEX
        show_hex((u16)sw);
    }

    return 0;
}
