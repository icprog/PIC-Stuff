#include <xc.h>
#include "pin_manager.h"
#include "stdbool.h"


void PIN_MANAGER_Initialize(void)
{
    LATA = 0x00;    
    LATB = 0x00;    
    LATC = 0x00;    
   
    TRISA = 0xFE;
    TRISB = 0xC0;
    TRISC = 0xFF;

    ANSELC = 0x00;
    ANSELB = 0x00;
    ANSELA = 0x00;

    WPUE = 0x00;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;
    


   
    
    
    bool state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    T2AINPPSbits.T2AINPPS = 0x13;   //RC3->TMR2:T2IN;
    RC4PPS = 0x09;   //RC4->CCP1:CCP1;
    RC5PPS = 0x0A;   //RC5->CCP2:CCP2;
    RC6PPS = 0x0B;   //RC6->CCP3:CCP3;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS

    GIE = state;
}