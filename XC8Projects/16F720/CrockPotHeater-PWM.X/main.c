#include <xc.h>
#include "system.h"
#include "user.h"
#include "interupts.h"
// #include "hd44780.h"
#include "lcd.h"
#include <stdio.h>

unsigned char OutCurrent = 255;

void main()
{
    char s[16];

    Init(); 

    delay_ms(250);
    
    LCD_Init();
    
    LCD_Clear();

    PORTCbits.RC0 = 1;

    
    extern unsigned char OutCurrent;
    unsigned char setpoint, ReadCurrent;
    unsigned char x;
        

    while(1)                                                                    // Infinite loop
    {
        
        for(x = 0; x < 255 ; x++)
        {
            ReadCurrent = (ReadCurrent + ADCRead(3))/2;
        }
        
                
        for(x = 0 ; x < 255 ; x++)
        {
            setpoint = (setpoint + ADCRead(2))/2;
        }
        
        delay_ms(1000);
        

        if(setpoint >= ReadCurrent + 2)
        {
            if(OutCurrent < 255)
            {
                OutCurrent+=1;
            }
            else
            {
                OutCurrent = 255;
            }
        }
        

        if(setpoint <= ReadCurrent - 2)
        {
            
            
            if(OutCurrent > 0)
            {
                OutCurrent-=1;
            }
            else
            {
                OutCurrent = 0;
            }
        }
        

        LCD_Clear();
    

sprintf(s, "CCPR1L      = %d", CCPR1L );
LCD_Set_Cursor(0,0);
LCD_Write_String(s);

sprintf(s, "OutCurrent  = %d", OutCurrent );
LCD_Set_Cursor(1,0);
LCD_Write_String(s);

sprintf(s, "Setpoint    = %d", setpoint );
LCDWriteStringXY(2,0,s);

sprintf(s, "ReadCurrent = %d", ReadCurrent );
LCDWriteStringXY(3,0,s);

// delay_ms(1000);

                
//        LCDWriteIntXY(0,0,CCPR1L,3);
  //      LCDWriteIntXY(0,1,OutCurrent,3);
    //    LCDWriteIntXY(4,0,setpoint,3);
      //  LCDWriteIntXY(4,1,ReadCurrent,3);
    }
}
