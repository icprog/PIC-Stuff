#include    "system.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <xc.h> /* XC8 General Include File */
//#include <stdint.h> /* For uint8_t definition */
//#include <stdbool.h> /* For true/false definition */
//#include "lcd.h"
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
    
    uint16_t count = 0;
    
    LCDInit(); //Init the LCD
    
    LCDClear();
    LCDBitmap(coffee);
    __delay_ms(3000);
    LCDClear();
    drawBox();
    
//    gotoXY(30,1);
    
    LCDWriteStringXY(30,1,"A N D ,");
    __delay_ms(1000);
    gotoXY(8,3);
    
    LCDWriteString("Layne Sucks COCK!!");
    gotoXY(8,4);
    LCDWriteString("and Likes it!!");
    
    LCDClear();
    while(1)
    {
        count +=1;
//        gotoXY(0,0);
//        LCDString("Count = ");
        LCDWriteIntXY(0,0,count,-1,0,0);
    //    __delay_ms(2000);
        
    }
    return (1);
}