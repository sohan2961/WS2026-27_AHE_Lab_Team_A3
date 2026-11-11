
#include "xparameters.h"
#include "xgpio.h"
#include "xil_printf.h"
#include "xstatus.h"

#define GPIO_BASEADDR XPAR_XGPIO_0_BASEADDR

#define SWITCH_CHANNEL 1
#define LED_CHANNEL    2

int main(void)
{
    XGpio Gpio;
    int Status;
    u32 SwitchValue;
    u32 PreviousValue = 0xFFFFFFFFU;

    Status = XGpio_Initialize(&Gpio, GPIO_BASEADDR);

    if (Status != XST_SUCCESS) {
        xil_printf("GPIO initialization failed!\r\n");
        return XST_FAILURE;
    }

    // Channel 1: switches as inputs
    XGpio_SetDataDirection(&Gpio, SWITCH_CHANNEL, 0xF);

    // Channel 2: LEDs as outputs
    XGpio_SetDataDirection(&Gpio, LED_CHANNEL, 0x0);

    xil_printf("MicroBlaze GPIO Test Started\r\n");

    while (1) {
        // Read four switches
        SwitchValue = XGpio_DiscreteRead(
            &Gpio, SWITCH_CHANNEL
        ) & 0xF;

        // Copy switch states to LEDs
        XGpio_DiscreteWrite(
            &Gpio, LED_CHANNEL, SwitchValue
        );

        if (SwitchValue != PreviousValue) {
            xil_printf("Switch value: 0x%x\r\n",
                       SwitchValue);
            PreviousValue = SwitchValue;
        }
    }

    return 0;
}
