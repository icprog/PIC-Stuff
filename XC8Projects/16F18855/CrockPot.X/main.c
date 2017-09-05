#include <xc.h>
#include "system.h"

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
        LCDWriteStringXY(0,0,"HELLO!");
        __delay_ms(1000);
        RA0 = 1;
        LCD_Clear();
        __delay_ms(1000);
        RA0 = 0;
        PWM1_LoadDutyValue(0x01FF);
        PWM2_LoadDutyValue(0x01FF);
        PWM3_LoadDutyValue(0x01FF);
    }
}