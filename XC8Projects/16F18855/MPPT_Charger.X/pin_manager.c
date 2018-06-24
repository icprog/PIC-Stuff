#include <xc.h>
#include "system.h"
#include "pin_manager.h"

void PIN_MANAGER_Initialize(void)
{
    LATA = 0x20;                    // LATA5 Must be turned on to provide power to Current Sensors                  
    LATB = 0x00;                       
    LATC = 0x00;                    

    WPUA = 0x00;
    WPUB = 0x00;
    WPUC = 0x00;
    WPUE = 0x8;

    TRISA = 0x00;
    TRISB = 0x0F;                   // RB0, 1, 2, and 3 as Input
    TRISC = 0xFF;                   // Port C as Input

    ANSELA = 0x00;
    ANSELB = 0x0B;                  // RB0, 1, and 3 as Analog Input
    ANSELC = 0xFF;                  // Port C as Analog Input
    

    PIE0bits.IOCIE = 0;                 // interrupts-on-change are globally disabled
    int8_t state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00;       // unlock PPS

    RA6PPS = 0x000E;                    //RA6->PWM6:PWM6OUT;
    RA7PPS = 0x000F;                    //RC4->PWM7:PWM7OUT;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    GIE = state;
}