// *************** Includes ****************************************************    
#include "system.h"

// *************** Defines *****************************************************    
#define celcius         analogs[0]
#define farenheit       analogs[1]
#define down            analogs[2]
#define up              analogs[3]
#define solarInTemp     analogs[4]
#define solarOutTemp    analogs[5]

// *************** Main Routine ************************************************    
void main(void)
{
    SYSTEM_Initialize();
    
    uint16_t analogs[6]     =   {0};                    // array of analog readings (button presses and temperatures)
    
    float displayTemp, displayTemp2;                    // Calculate R of Thermistor, and Temp using SteinHart/Hart equation

    unsigned char x[8]      =   {0,64,2,0,0,0,0,10};       // looping var, cycle counter, tempDisplay, C or F autoDisplay, display intensity loop counter, startup delay, Reset delay to allow reset to occur before brightness adjustment occurs
    
    uint16_t dutyCycle      = 1023;                     // display back light brightness
    
    PWM6_LoadDutyValue(dutyCycle);

    __delay_ms(300);
   
    LCD_Clear();
    
    LCDWriteStringXY(2,1,"A");
    __delay_ms(200);
    LCDWriteStringXY(3,1,"L");
    __delay_ms(200);
    LCDWriteStringXY(4,1,"O");
    __delay_ms(200);
    LCDWriteStringXY(5,1,"H");
    __delay_ms(200);
    LCDWriteStringXY(6,1,"A");
    __delay_ms(200);
    LCDWriteStringXY(7,1," ");
    __delay_ms(200);
    LCDWriteStringXY(8,1,"D");
    __delay_ms(200);
    LCDWriteStringXY(9,1,"A");
    __delay_ms(200);
    LCDWriteStringXY(10,1,"V");
    __delay_ms(200);
    LCDWriteStringXY(11,1,"I");
    __delay_ms(200);
    LCDWriteStringXY(12,1,"D");
    __delay_ms(200);
    LCDWriteStringXY(13,1,"!");
    __delay_ms(5000);
    
    LCD_Clear();

    PWM6_LoadDutyValue(dutyCycle);
        

    while (1)
    {
//        LCDWriteIntXY(7,1,x[2],1,0,0);
        for(x[0]=0;x[0]<6;x[0]++) analogs[x[0]]=readAnalog(x[0]);
        
        if(analogs[0]<1020)x[7]+=1;
            
            
        if(analogs[1]<900)x[7]-=1;
            
        if(x[7]<1)
        {
            x[2]=1;
            x[7]=10;
        }
        
        if(x[7]>19)
        {
            x[2]=0;
            x[7]=10;
        }
        
        if(analogs[0]<1020&&analogs[1]<970)
        {
            x[2]=2;
            __delay_ms(200);
        }
        
        
        
        x[5]+=1;
        
        if(x[5]>254)
        {
            x[5]=254;
            
            if(down<900&&up<900)RESET();
            
            if(down<900)
            {
                x[6]+=1;
                
                if(x[6]>20)
                {
                    while(down<975)
                    {
                        down=ADCRead(4);
                        
                        if(x[4]<1)LCD_Clear();
                        x[4]+=1;

                        if(dutyCycle>0)dutyCycle-=1;
                
                        LCDWriteStringXY(0,0,"BackLight:");
                        LCD_Write_Int(dutyCycle/10,-1,0,0);
                        LCD_Write_Char('%');
                        LCD_Write_Char(' ');
                        PWM6_LoadDutyValue(dutyCycle);
                    }
                    x[4]=0;
                    __delay_ms(100);
                    LCD_Clear();
                    x[6]=0;
                }
            }

            if(up<900)
            {
                x[6]+=1;
                
                if(x[6]>20)
                {
                    while(up<975)
                    {
                        up=ADCRead(5);

                        if(x[4]<1)LCD_Clear();
                        x[4]+=1;

                        if(dutyCycle<1009)dutyCycle+=1;
                
                        LCDWriteStringXY(0,0,"BackLight:");
                        LCD_Write_Int(dutyCycle/10,-1,0,0);
                        LCD_Write_Char('%');
                        LCD_Write_Char(' ');
                        PWM6_LoadDutyValue(dutyCycle);
                    }
                    x[4]=0;
                    __delay_ms(100);
                    LCD_Clear();
                    x[6]=0;
                }
            }
        }

// *************** Calculate & Display Temp ************************************   
        
        displayTemp = tempCalc(solarInTemp);
        
        displayTemp2 = tempCalc(solarOutTemp);

        if(x[1]>127)
        {
            LCDWriteStringXY(0,0,"Solar In");
            LCDWriteStringXY(0,1,"Return");
  
            if(x[3]==0)
            {
                LCDWriteIntXY(9,0,(int)displayTemp,-1,1,0);
                LCD_Write_Char(0);
                LCD_Write_Char('C');
                LCD_Write_Char(' ');
            
                LCDWriteIntXY(9,1,(int)displayTemp2,-1,1,0);
                LCD_Write_Char(0);
                LCD_Write_Char('C');
                LCD_Write_Char(' ');
            }
            
            if(x[3]==1)
            {
                displayTemp = displayTemp*9/5+320;          // Display Temperature in DegF
                displayTemp2 = displayTemp2*9/5+320;        // Display Temperature in DegF

                LCDWriteIntXY(9,0,(int)displayTemp,-1,1,0);
                LCD_Write_Char(0);
                LCD_Write_Char('F');
                LCD_Write_Char(' ');
            
                LCDWriteIntXY(9,1,(int)displayTemp2,-1,1,0);
                LCD_Write_Char(0);
                LCD_Write_Char('F');
                LCD_Write_Char(' ');
            }
            
            
            if(x[2]==0)x[3]=0;

            if(x[2]==1)x[3]=1;

            if(x[2]==2)x[3]=1-x[3];
/*            LCDWriteIntXY(0,0,analogs[0],-1,0,0);
            LCD_Write_Char(' ');
            LCDWriteIntXY(6,0,analogs[1],-1,0,0);
            LCD_Write_Char(' ');
            LCDWriteIntXY(11,0,analogs[2],-1,0,0);
            LCD_Write_Char(' ');

            LCDWriteIntXY(0,1,analogs[3],-1,0,0);
            LCD_Write_Char(' ');
            LCDWriteIntXY(6,1,analogs[4],-1,0,0);
            LCD_Write_Char(' ');
            LCDWriteIntXY(11,1,analogs[5],-1,0,0);
            LCD_Write_Char(' ');
            
  */          
            x[1]=0;
        }
        x[1]+=1;
    }
}