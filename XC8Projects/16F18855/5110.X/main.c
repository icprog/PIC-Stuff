#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

int main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

//    led_counter=0;
  //  spk_bit=0;
    //led_bit=0;

    LCDInit();
    LCDClear();
//    gotoXY(1,1);
  //  LCDString("PIC 16F18855");
    
    while(1)
    {
        RC2 = 1;
        __delay_ms(1000);
        RC2 = 0;
        __delay_ms(1000);
//        gotoXY(1,1);
  //      LCDString("PIC 16F18855");

    }
    return(1);

}

