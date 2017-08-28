#if defined(__XC16__)
    #include <xc.h>
#endif

#include "system.h"          /* variables/params used by system.c */
/* TODO Add clock switching code if appropriate.  An example stub is below.   */
void ConfigureOscillator(void)
{
//    CLKDIVbits.RCDIV = 0x4;                         // Set RCDIV to 100 (Clock Divider bits to 500 KHz)
 //   _FBS = 0x0f;
//    _FOSCSEL = 0x47;

//    _RTCCLK1 = 0;       // Set RTCC Clock Source to Internal 32kHz RC
//    _RTCCLK0 = 0;

#if 0

        /* Disable Watch Dog Timer */
//        RCONbits.SWDTEN = 0;

        /* When clock switch occurs switch to Prim Osc (HS, XT, EC)with PLL */
//        __builtin_write_OSCCONH(0x03);  /* Set OSCCONH for clock switch */
//        __builtin_write_OSCCONL(0x01);  /* Start clock switching */
//        while(OSCCONbits.COSC != 0b011);

        /* Wait for Clock switch to occur */
        /* Wait for PLL to lock, if PLL is used */
        /* while(OSCCONbits.LOCK != 1); */

#endif
        
}
//***************************************************************************************************************************************************************

void InitApp(void)                  // Setup analog functionality and port direction
{
    TRISA = 0x000C;                 // RA2 & 3 (analog 13 & 14) Set as Input, Data Direction 1 = input, 0 = Output
    TRISB = 0x0000;                 // Data Direction 1 = input, 0 = Output
    TRISC = 0x0000;                 // Data Direction 1 = input, 0 = Output
    
    ANSA =  0x000C;                 // AN13,14 (pins30,31)is Set as Analog. Analog or Digital 1 = Analog, 0 = Digital
    ANSB =  0x0000;                 // Analog or Digital 1 = Analog, 0 = Digital
    ANSC =  0x0000;                 // Analog or Digital 1 = Analog, 0 = Digital
    
    PORTA = 0x0000;                 // Power up state of the Port Pins(ie as a 1 or a 0)
    PORTB = 0x0000;
    PORTC = 0x0000;
}
//***************************************************************************************************************************************************************