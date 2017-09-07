#include "user.h"
#include "lcd.h"

#define downButton  RA3
#define upButton    RA4

uint8_t downCount = 0, upCount = 0, oldSetpoint;
extern uint8_t setpoint;


void tempSetpoint(void)
{
    uint8_t counter = 0;
    
    oldSetpoint = setpoint;
    
    while(downCount >= 5)
    {
        counter+=1;
        if(counter<=1)
        {
            LCD_Clear();
        }
        setpoint-=1;
        LCDWriteStringXY(0,0,"Setpoint?");
        LCDWriteIntXY(1,0,setpoint,3,0,0);
        LCD_Write_Char(0);
        LCD_Write_Char('C');
        LCD_Write_Char(' ');
        __delay_ms(350);
        readButtons();
//        CLRWDT();
    }
    
    while(upCount >= 5)
    {
        counter+=1;
        if(counter<=1)
        {
            LCD_Clear();
        }
        setpoint+=1;
        LCDWriteStringXY(0,0,"Setpoint?");
        LCDWriteIntXY(1,0,setpoint,3,0,0);
        LCD_Write_Char(0);
        LCD_Write_Char('C');
        LCD_Write_Char(' ');
        __delay_ms(350);
        readButtons();
//        CLRWDT();
    }
    
    counter = 0;
    
    if(oldSetpoint!=setpoint)
    {
        __delay_ms(3000);
        LCD_Clear();
    }
}
    

void readButtons(void)
{
    if(RA3 == 0)
    {
        downCount +=1;
        if(downCount>5)
        {
            downCount = 5;
        }
    }
    else 
    {
        downCount = 0;
    }
    
    if(RA4 == 0)
    {
        upCount +=1;
        if(upCount>5)
        {
            upCount = 5;
        }
    }
    else 
    {
        upCount = 0;
    }
}