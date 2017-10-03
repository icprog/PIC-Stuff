#include    "start_stop_timer.h"
#include    "menu4.h"

int startHour[]   =   { 8, 6, 6, 6, 6, 6, 8};

int startMinute[] =   {45,45,45,45,45,45,45};

int stopHour[]    =   {11, 7, 7, 7, 7, 7,11};

int stopMinute[]  =   {00,25,25,25,25,25,00};

signed char choice;

extern char *WeekDay[7];

unsigned char TestKey = None;

//char sel = 0;
    
//char done = 0;

//***************************************************************************************************************************************************************

int8_t runTimer(int16_t weekday, int16_t hour, int16_t minute)
{
    static uint8_t run;
    
    if(hour == startHour[weekday] && minute == startMinute[weekday])
    {
        run = 1;
    }
    
    if(hour == stopHour[weekday] && minute == stopMinute[weekday])
    {
        run = 0;
    }
    return run;
}

//***************************************************************************************************************************************************************
void writeStartStopTimes(void)
{
    unsigned int timer = 0;                                                     // Used to return to operation if user does not finish!
    
    TestKey = None;
    
    while(TestKey != Enter)
    {
        TestKey = readButton();
        
        if(timer > 3500)
        {
            goto Exit;                                                 
        }

        switch(TestKey)
        {
             case Down:
             {
                choice -=1;
                            
                if (choice < 0)
                {
                    choice = 0;
                }
            }
            break;
            
            case Up:
            {
                choice += 1;
                            
                if(choice > 6)
                {
                    choice = 6;
                }
            }
            break;
                    
//            case KEY_RESET:
  //          {
    //            LCDClear();
      //          goto Exit;
        //    }
          //  break;
        }

        if(timer < 3)
        {
            LCDClear();
            LCDBitmap(&menu4[0], 5, 84);                  //Draw Menu4
        }

//        LCDBitmap(&menu4[0], 1024,0);                  //Draw Menu4
        
        LCDWriteStringXY(0,0,"Start/Stop for ");
        LCDWriteString(WeekDay[choice]);
        LCDWriteStringXY(0,2,"Up/Dn Keys to choose");
        LCDWriteStringXY(0,3,"Enter Key to Set");
                                                                                // but, also increments mainTimer every second
        timer += 1;
    }
    
    LCDClear();
    LCDBitmap(&menu4[0], 5, 84);                  //Draw Menu4
    startHour[choice] = setStartHour(startHour[choice]);
    startMinute[choice] = setStartMinute(startMinute[choice]);
    stopHour[choice] = setStopHour(stopHour[choice]);
    stopMinute[choice] = setStopMinute(stopMinute[choice]);

    Exit:
    LCDClear();
    timer = 0;
}

//***************************************************************************************************************************************************************
char setStartHour(char b)
{
    unsigned int timer = 0;                                                         // Used to return to operation if user does not finish!
    
    char result = b;
    
    char TestKey = None;

    TestKey = readButton();
    
    while(TestKey != Enter)
        {
        TestKey = readButton();
        
        timer += 1;
        
        __delay_ms(75);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 1500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            TestKey = Enter;
        }
        
        
        LCDWriteStringXY(0,1,"Start Hour = ");
        LCDWriteIntXY(61,1,result,2,0,0);

        switch(TestKey)
        {
            case Down:
            {
                result -= 1;
                            
                if (result < 0)
                {
                    result = 23;
                }
            }
            break;
                        
            case Up:
            {
                result += 1;
                            
                if(result > 23)
                {
                    result = 0;
                }
            }
            break;
        }
    }
        
    timer = 0;
    
    return (result);
}


//***************************************************************************************************************************************************************
char setStartMinute(char b)
{
    unsigned int timer = 0;                                                         // Used to return to operation if user does not finish!
    
    char result = b;
    
    char TestKey = None;

    TestKey = readButton();
    
    while(TestKey != Enter)
        {
        TestKey = readButton();
        
        timer += 1;
        
        __delay_ms(75);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 1500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            TestKey = Enter;
        }
        
        
        LCDWriteStringXY(0,2,"Start Minute = ");
        LCDWriteIntXY(61,2,result,2,0,0);


        switch(TestKey)
        {
            case Down:
            {
                result -= 5;
                            
                if (result < 0)
                {
                    result = 55;
                }
            }
            break;
                        
            case Up:
            {
                result += 5;
                            
                if(result > 55)
                {
                    result = 0;
                }
            }
            break;
        }
    }
        
    timer = 0;
    
    return (result);
}

//***************************************************************************************************************************************************************
char setStopHour(char b)
{
    unsigned int timer = 0;                                                         // Used to return to operation if user does not finish!
    
    char result = b;
    
    char TestKey = None;

    TestKey = readButton();
    
    while(TestKey != Enter)
        {
        TestKey = readButton();
        
        timer += 1;
        
        __delay_ms(75);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 1500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            TestKey = Enter;
        }
        
        
        LCDWriteStringXY(0,3,"Stop Hour =");
        LCDWriteIntXY(61,3,result,2,0,0);

//        heartBeat();
        

        switch(TestKey)
        {
            case Down:
            {
                result -= 1;
                            
                if (result < 0)
                {
                    result = 23;
                }
            }
            break;
                        
            case Up:
            {
                result += 1;
                            
                if(result > 23)
                {
                    result = 0;
                }
            }
            break;
        }
    }
        
    timer = 0;

    return (result);
}


//***************************************************************************************************************************************************************
char setStopMinute(char b)
{
    unsigned int timer = 0;                                                         // Used to return to operation if user does not finish!
    
    char result = b;
    
    char TestKey = None;

    TestKey = readButton();
    
    while(TestKey != Enter)
        {
        TestKey = readButton();
        
        timer += 1;
        
        __delay_ms(75);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 1500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            TestKey = Enter;
        }
        
        
        LCDWriteStringXY(0,4,"Stop Minute =");
        LCDWriteIntXY(61,4,result,2,0,0);

//        heartBeat();
        

        switch(TestKey)
        {
            case Down:
            {
                result -= 5;
                            
                if (result < 0)
                {
                    result = 55;
                }
            }
            break;
                        
            case Up:
            {
                result += 5;
                            
                if(result > 55)
                {
                    result = 0;
                }
            }
            break;
        }
    }
        
    timer = 0;
    
    return (result);
}
//***************************************************************************************************************************************************************