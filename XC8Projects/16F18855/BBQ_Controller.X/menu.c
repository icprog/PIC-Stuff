#include    "menu.h"
#include    "lcd.h"

#define pitSetpoint             setpoint[0]
#define backLightSetpoint       setpoint[1]
#define upKey                   RB0
#define downKey                 RB1
#define enterKey                RB2
#define delayNumber             30                              // Number of cycles for keypress delay at 200ms, before switch to 10ms delay

unsigned int lowRangeSet[2]     =   {750,0};               // lowrangeSet[0] is Pit Temp setpoint lower limit, lowrangeSet[1] is backlight intensity

unsigned int highRangeSet[2]    =   {2750,1023};           // highRangeSet[0] is Pit Temp setpoint upper limit, highRangeSet[1] is backlight intensity

int16_t setpoint[2]             =   {2250,523};            // default startup setpoints for Pit temp & backlight

char const *desc[]              =   {" Pit Temp:","BackLight:"};

//extern int set;

unsigned char loop                  =   64;

char menuDelay                      =   0;
    
char delayCount                     =   0;

char key                            =   0;

char choice                         =   0;

char testKey                        =   0;

int timer                           =   0;

char timer2                         =   0;



char readKey(void)
{
    if(downKey==1)
    {
        if(key>0)key-=1;
    }
    
    if(upKey==1)
    {
        if(key<1)key+=1;
    }
    
    return key;
}

void menuChoice(void)
{
    while(enterKey != 1)
    {
        choice = readKey();
                
        if(timer > 1000)
        {
            timer = 0;
            goto Exit;                                             
        }
        
        if(timer2>25)LCDWriteStringXY(0,0,"Up/Down to Alter")else LCDWriteStringXY(0,0,"Enter to Select ");
        
        LCDWriteStringXY(1,0,desc[choice]);
        
        if(timer2>49)timer2=0;
        
        timer+=1;
        timer2+=1;
    }
    timer=0;
    timer2=0;

    while(enterKey != 1)
    {
        if(timer > 1000)
        {
            timer = 0;
            goto Exit;                                             
        }
        
        timer+=1;
        
        if(upKey==1)
        {
            delayCount+=2;
//            if(delayCount==2)setpoint[choice]+=1;
            setpoint[choice]+=1;
            if(setpoint[choice]>highRangeSet[choice])setpoint[choice]=highRangeSet[choice];
            LCDWriteIntXY(5,0,setpoint[choice],-1,1,0);
            menuDelay=255;
            if(delayCount<delayNumber)
            {
                __delay_ms(150);
            }
            if(delayCount>(delayNumber+10))delayCount=(delayNumber+10);
            
            timer=0;
        }
        
        
        if(downKey==1)
        {
            delayCount+=2;
            setpoint[choice]-=1;
            if(setpoint[choice]<lowRangeSet[choice])setpoint[choice]=lowRangeSet[choice];
            LCDWriteIntXY(5,0,setpoint[choice],-1,1,0);
            menuDelay=255;

            if(delayCount<delayNumber)
            {
                __delay_ms(150);
            }
            
            if(delayCount>(delayNumber+10))delayCount=(delayNumber+10);
            
            timer=0;
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
    Exit:
    timer=0;
}