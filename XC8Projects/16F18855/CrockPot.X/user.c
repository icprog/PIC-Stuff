#include "user.h"

#define downButton  RA3
#define upButton    RA4

char downCount = 0, upCount = 0;

int TempSetpoint(int b)
{
    int result = b;
    
    char TestKey;
    
    unsigned char timer = 0;
    
//    __delay_ms(500);
    
    TestKey = readButtons();
    
    while(TestKey != KEY_ENTER)
        {
        TestKey = MenuRead();
        
        timer += 1;
        
        __delay_ms(175);            // 175 mS delay to extend dead time to 150mS x number of counts below, before auto-exit of function
                    
        if(timer > 100)             // Number of counts multiplied by the delay value above to more or less set the time out delay
        {
            timer = 0;
            TestKey = KEY_ENTER;
        }
        
        LCDWriteStringXY(1,0,"Setpoint?");
        LCDWriteDecIntXY(1,11,result,3);

        heartBeat();
        
        
        switch(TestKey)
        {
            case KEY_DOWN:
            {
                result -=1;
                            
                if (result <= 50)
                    {
                        result = 50;
                    }
                }
            break;
                        
            case KEY_UP:
            {
                result += 1;
                            
                if(result >= 350)
                    {
                        result = 350;
                    }
                }
            break;
            }
        }
        
        TestKey = 9;            // Ensure TestKey is set to KEY_NONE before exiting
    
    return (result);
}

char readButtons(void)
{
    if(RA3 == 1)
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
    
    if(RA4 == 1)
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