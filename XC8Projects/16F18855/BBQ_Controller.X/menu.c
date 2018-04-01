#include    "menu.h"
#include    "lcd.h"

#define pitSetpoint             set
#define upKey                   RB0
#define downKey                 RB1
#define enterKey                RB2
#define delayNumber             30                              // Number of cycles for keypress delay at 200ms, before switch to 10ms delay

extern int set;

extern unsigned char loop;

char menuDelay                      =   0;
    
char delayCount                     =   0;


void checkKeys()
{
        if(upKey==1)
        {
            delayCount+=2;
            pitSetpoint+=1;
            if(pitSetpoint>2750)pitSetpoint=2750;
            LCDWriteIntXY(5,0,pitSetpoint,-1,1,0);
            menuDelay=255;
            if(delayCount<delayNumber)
            {
                __delay_ms(150);
            }
            
            if(delayCount>(delayNumber+10))delayCount=(delayNumber+10);
        }
        
        if(downKey==1)
        {
            delayCount+=2;
            pitSetpoint-=1;
            if(pitSetpoint<750)pitSetpoint=750;
            LCDWriteIntXY(5,0,pitSetpoint,-1,1,0);
            menuDelay=255;

            if(delayCount<delayNumber)
            {
                __delay_ms(150);
            }
            
            if(delayCount>(delayNumber+10))delayCount=(delayNumber+10);
        }
        
        if(delayCount>0)delayCount-=1;
        
        if(!(downKey || upKey))
        {
            if(menuDelay>0)
            {
                loop=0;
                menuDelay-=1;
            }
        }

    
}
