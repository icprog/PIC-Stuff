
#if defined(__XC)
    #include <xc.h>                      // XC8 General Include File
#elif defined(HI_TECH_C)
    #include <htc.h>                     // HiTech General Include File
#endif

#include "system.h"
#include "user.h"




void ADCInit()
{
        ADCON1 = 0x10;                   // Set ADC conversion clock FOSC/8 See Page 80
}

//*****************************************************************************************
// ADCRead Function
//*****************************************************************************************

unsigned char ADCRead(unsigned char ch){ //Function to Read given 8 bit ADC channel (0-14)

    ADCON0=0x00;                         // Set ADCON0 to all zero's
    ADCON0=(ch<<2);                      // Select ADC Channel (write the decimal value of ch, Left shifted two places, writing to Bits 5,4,3 and 2)
    ADON=1;                              // Enable the ADC module (on selected channel)
    delay_us(200);                       // Delay 200 us to allow the ADC cap to charge
    GO_nDONE=1;                          // Start conversion
    while(GO_nDONE);                     // Wait for the conversion to finish
    ADON=0;                              // Disable the ADC
    return ADRES;                        // Return the 8 bit digital form of Analog value (0 - 255))
}


//*****************************************************************************************
// Median Function (Variables are local to function)
//*****************************************************************************************
unsigned char Median(unsigned char a, unsigned char c, unsigned char e)
{
    unsigned char b, d, f;

    if (c > e){
        b = c;
    }
    else{
        b = e;
    }

    if(e > a){
        d = e;
    }
    else{
        d = a;
    }

    if(b < d){
        f = b;
    }
    else{
        f = d;
    }

    return f;
}
//*****************************************************************************************