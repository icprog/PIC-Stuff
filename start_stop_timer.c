#include "start_stop_timer.h"
#include "menu4.h"


int const startHour[]   =   {40,42,44,46,48,50,52};

int const startMinute[] =   {54,56,58,60,62,64,66};

int const stopHour[]    =   {68,70,72,74,76,78,80};

int const stopMinute[]  =   {82,84,86,88,90,92,94};

signed char choice;

//unsigned int timer = 0;                                                         // Used to return to operation if user does not finish!


extern char *WeekDay[7];
//char *dayOfWeek[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

unsigned char TestKey = None;

char sel = 0;
    
char done = 0;

//  extern char call;

//***************************************************************************************************************************************************************
char runTimer(int weekday, int hour, int minute)
{
    static char run;
    
    if(hour == eepromGetData(startHour[weekday]) && minute == eepromGetData(startMinute[weekday]))
    {
        run = 1;
    }
    
    if(hour == eepromGetData(stopHour[weekday]) && minute == eepromGetData(stopMinute[weekday]))
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
        TestKey = menuRead();
        
        if(timer > 1500)
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
        }

        if(timer < 3)
        {
            LCDClear();
        }

        LCDBitmap(&menu4[0], 5,84);              //Draw Menu2
        
        LCDWriteStringXY(2,5,"Start/Stop");
        LCDWriteStringXY(2,16,"for ");
        LCDWriteString(WeekDay[choice]);
        LCDWriteStringXY(3,5,"Up/Dn Keys");
        LCDWriteStringXY(3,16,"to change.");
        LCDWriteStringXY(4,5,"Enter Key f");
        LCDWriteStringXY(4,16,"or Yes");
                                                                                // but, also increments mainTimer every second
        timer += 1;
    }
    
    LCDClear();
    eepromPutData(startHour[choice], setStartHour(eepromGetData(startHour[choice])));
    eepromPutData(startMinute[choice], setStartMinute(eepromGetData(startMinute[choice])));
    eepromPutData(stopHour[choice], setStopHour(eepromGetData(stopHour[choice])));
    eepromPutData(stopMinute[choice], setStopMinute(eepromGetData(stopMinute[choice])));

    Exit:
    LCDClear();
    timer = 0;
}

char setStartHour(char b)
{
    uint16_t timer = 0;                                                         // Used to return to operation if user does not finish!
    
    int8_t result = b;
    
    int8_t TestKey = None;

    TestKey = readButton();
    
    while(TestKey != Enter)
        {
        TestKey = readButton();
        
        timer += 1;
        
        __delay_ms(15);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
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
    uint16_t timer = 0;                                                         // Used to return to operation if user does not finish!
    
    int8_t result = b;
    
    int8_t TestKey = None;

    TestKey = readButton();
    
    while(TestKey != Enter)
        {
        TestKey = readButton();
        
        timer += 1;
        
        __delay_ms(15);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
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
    uint16_t timer = 0;                                                         // Used to return to operation if user does not finish!
    
    int8_t result = b;
    
    int8_t TestKey = None;

    TestKey = readButton();
    
    while(TestKey != Enter)
        {
        TestKey = readButton();
        
        timer += 1;
        
       __delay_ms(15);            // 15 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
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
    uint16_t timer = 0;                                                         // Used to return to operation if user does not finish!
    
    int8_t result = b;
    
    int8_t TestKey = None;

    TestKey = readButton();
    
    while(TestKey != Enter)
        {
        TestKey = readButton();
        
        timer += 1;
        
        __delay_ms(15);             // 15 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
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
/*
 char setStartHour(char b)
{
//    call = 1;
    
    unsigned int timer = 0;                                                         // Used to return to operation if user does not finish!
    
    char result = b;
    
    char TestKey = KEY_NONE;

    TestKey = menuRead();
    
    while(TestKey != KEY_3)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(75);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 1500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            TestKey = KEY_3;
        }
        
        
        LCDWriteStringXY(1,2,"Start Hour =");
        LCDWriteIntXY(1,16,result,2,0,0);

        switch(TestKey)
        {
            case KEY_2:
            {
                result -= 1;
                            
                if (result < 0)
                {
                    result = 23;
                }
            }
            break;
                        
            case KEY_1:
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
        
//    call = 0;
    
    return (result);
}


//***************************************************************************************************************************************************************
char setStartMinute(char b)
{
//    call = 1;
    
    unsigned int timer = 0;                                                         // Used to return to operation if user does not finish!
    
    char result = b;
    
    char TestKey = KEY_NONE;

    TestKey = menuRead();
    
    while(TestKey != KEY_3)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(75);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 1500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            TestKey = KEY_3;
        }
        
        
        LCDWriteStringXY(2,2,"Start Minute =");
        LCDWriteIntXY(2,16,result,2,0,0);


        switch(TestKey)
        {
            case KEY_2:
            {
                result -= 5;
                            
                if (result < 0)
                {
                    result = 55;
                }
            }
            break;
                        
            case KEY_1:
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
        
//    call = 0;
    
    return (result);
}

//***************************************************************************************************************************************************************
char setStopHour(char b)
{
//    call = 1;
    
    unsigned int timer = 0;                                                         // Used to return to operation if user does not finish!
    
    char result = b;
    
    char TestKey = KEY_NONE;

    TestKey = menuRead();
    
    while(TestKey != KEY_3)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(75);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 1500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            TestKey = KEY_3;
        }
        
        
        LCDWriteStringXY(3,2,"Stop Hour =");
        LCDWriteIntXY(3,16,result,2,0,0);

//        heartBeat();
        

        switch(TestKey)
        {
            case KEY_2:
            {
                result -= 1;
                            
                if (result < 0)
                {
                    result = 23;
                }
            }
            break;
                        
            case KEY_1:
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
        
//    call = 0;
    
    return (result);
}


//***************************************************************************************************************************************************************
char setStopMinute(char b)
{
//    call = 1;
    
    unsigned int timer = 0;                                                         // Used to return to operation if user does not finish!
    
    char result = b;
    
    char TestKey = KEY_NONE;

    TestKey = menuRead();
    
    while(TestKey != KEY_3)
        {
        TestKey = menuRead();
        
        timer += 1;
        
        __delay_ms(75);            // 175 delay to extend dead time to delay x number of counts below, before auto-exit of function
                    
        if(timer > 1500)             // Number of counts multiplied by the delay value above to more or less set the time out delay in non-pressed key time
        {
            timer = 0;
            TestKey = KEY_3;
        }
        
        
        LCDWriteStringXY(4,2,"Stop Minute =");
        LCDWriteIntXY(4,16,result,2,0,0);

//        heartBeat();
        

        switch(TestKey)
        {
            case KEY_2:
            {
                result -= 5;
                            
                if (result < 0)
                {
                    result = 55;
                }
            }
            break;
                        
            case KEY_1:
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
        
//    call = 0;
    
    return (result);
}
 */
//***************************************************************************************************************************************************************