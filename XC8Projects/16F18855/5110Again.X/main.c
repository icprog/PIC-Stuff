#include <stdio.h>
#include <stdlib.h>
#include <xc.h> /* XC8 General Include File */
#include <stdint.h> /* For uint8_t definition */
#include <stdbool.h> /* For true/false definition */
#include "5110lcd.h"
#include "coffee.h"


int main(void)
{
    LATA    =   0x00;
    LATB    =   0x00;
    LATC    =   0x00;
    
    TRISA   =   0x00;
    TRISB   =   0x00;
    TRISC   =   0x00;
    
    ANSELA  =   0x00;
    ANSELB  =   0x00;
    ANSELC  =   0x00;
    
    
    LCDInit(); //Init the LCD
    
    LCDClear();

    drawBox();
    
    gotoXY(65,4);
    
    LCDString("Hello World!");
    
    gotoXY(0,0);
    
    LCDString("Hello Again");
    
    LCDClear();
    
    LCDBitmap(coffee);
    
   // drawBox();
    
    while(1)
    {
        ;
    }
    return (EXIT_SUCCESS);
}