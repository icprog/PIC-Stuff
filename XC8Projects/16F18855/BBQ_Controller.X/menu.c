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

char key                            =   0;

char testKey                        =   0;


char readKey()
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

char menuChoice(void)
{
    while(enterKey != 1)
    {
        testKey = readKey();
                
        if(timer > 1000)
        {
            timer = 0;
            goto Exit;                                                  //This uses less memory than TestKey = KEY_ENTER
        }
        
        if(testKey==0)

        switch(testKey)
        {
            case 0:
            {
                
            }
                    break;

                    case KEY_LEFT:
                    {
                        choice -=1;
                            
                        if (choice < 0)
                        {
                            choice = 0;
                        }
                    }
                    break;
                        
                    case KEY_UP:
                    {
                        choice += 1;
                            
                        if(choice > 10)
                        {
                            choice = 10;
                        }
                    }
                    break;
                        
                    case KEY_RIGHT:
                    {
                        choice += 1;
                            
                        if(choice > 10)
                        {
                            choice = 10;
                        }
                    }
                    break;
                    
                    case KEY_RESET:
                    {
                        goto Exit;
                    }
                    break;
                        
                }

                if(timer < 2)
                {
                    LCD_Clear();
                }

                LCD_Set_Cursor(0,0);
                LCD_Write_String("Set Temperature for");
                LCD_Set_Cursor(1,0);
                LCD_Write_String(desc[choice]);
                LCDWriteStringXY(2,0,"Up/Dn Keys to change");
                LCDWriteStringXY(3,0,"Enter Key for Yes   ");
                
                heartBeat();                                                    // HeartBeat displays the HeartBeat on the LCD,
                                                                                // but, also increments mainTimer every second
                timer += 1;
            }
            
//            TestKey = 9;
            
            LCD_Clear();


            LCD_Set_Cursor(0,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(0,strlen(desc[choice]),"Set Tmp");
            eepromPutData(setpoint[choice], TempSetpoint(eepromGetData(setpoint[choice])));
            
            LCD_Set_Cursor(2,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(2,strlen(desc[choice]),"Set DB");
            eepromPutData(deadband[choice], SetDeadband(eepromGetData(deadband[choice])));            

            LCD_Clear();

            LCD_Set_Cursor(0,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(0,strlen(desc[choice]),"WrmBias");
            eepromPutData(BiasWarm[choice], SetBiasWarm(eepromGetData(BiasWarm[choice])));

            LCD_Set_Cursor(2,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(2,strlen(desc[choice]),"-5 Bias");
            eepromPutData(biasNeg5[choice], SetBiasNeg5(eepromGetData(biasNeg5[choice])));
            
            LCD_Clear();

            LCD_Set_Cursor(0,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(0,strlen(desc[choice]),"-15Bias");
            eepromPutData(biasNeg15[choice], SetBiasNeg15(eepromGetData(biasNeg15[choice])));

            LCD_Set_Cursor(2,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(2,strlen(desc[choice]),"-25Bias");
            eepromPutData(biasNeg25[choice], SetBiasNeg25(eepromGetData(biasNeg25[choice])));

            LCD_Clear();

            LCD_Set_Cursor(0,0);
            LCD_Write_String(desc[choice]);
            LCDWriteStringXY(0,strlen(desc[choice]),"Ext Run");
            eepromPutData(extendedRunEnable[choice], SetExtendedRunBit(eepromGetData(extendedRunEnable[choice])));
            
            Exit:
                        
            LCD_Clear();
        }

                
char checkKeys()
{
        
        if(upKey==1)
        {
            delayCount+=2;
            if(delayCount==2)
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

        if()
        LCDWriteStringXY(0,1,"   BackLight    ");
        
        
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

        return 0;
}
