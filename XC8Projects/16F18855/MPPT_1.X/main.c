#include "system.h"
#include <math.h>

// *************** Defines *****************************************************    
//#define     numSamples  50                                              // Number of Temperature readings to Average

#define     PWM         dutyCycle7

#define     powerIn     PV_V*PV_I
#define     powerOut    Batt_V*Batt_I
//#define     powerInOld  PV_V_Old*PV_I_Old
//#define     powerOutOld Batt_V_Old*Batt_I_Old


// *************** Externally available Variables ******************************    
//uint16_t samples[2][numSamples] = {0};

bool    call    =   0;

// *************** Main Routine ************************************************    
void main(void)
{
    uint16_t    PV_V        =   0;
    uint16_t    PV_I        =   0;
    uint16_t    Batt_V      =   0;
    uint16_t    Batt_I      =   0;
//    uint16_t    PV_V_Old    =   0;
//    uint16_t    PV_I_Old    =   0;
    uint16_t    PV_V_Old  =   0;
//    uint16_t    Batt_I_Old  =   0;
    uint16_t    powerOutOld =   0;
    uint16_t    dutyCycle7  =   0;
    uint8_t     j           =   0;
    uint16_t    analogs[4]  =   {0,0,0,0};
    uint8_t     loopCount   =   0;
    
    SYSTEM_Initialize();
    
    while(1)
    {
        LCDWriteIntXY(0,0,loopCount,4,0,0);
        LCDWriteIntXY(0,1,PV_V,4,0,0);
        LCDWriteIntXY(0,2,PV_I,4,0,0);
        LCDWriteIntXY(0,3,Batt_V,4,0,0);
        LCDWriteIntXY(0,4,Batt_I,4,0,0);
        
        for(j=0;j<4;j++) analogs[j]=readAnalog(j);      // Read analogs

        if(loopCount>10)
        {
            if(call)                                    // Need IRQ to set call
            {
                if(powerOut>powerOutOld)
                {
                    if(PV_V>PV_V_Old)
                    {
                        PWM+=1;
                    }
                    else
                    {
                        PWM-=1;
                    }
                }
                else
                {
                    if(PV_V>PV_V_Old)
                    {
                        PWM-=1;
                    }
                    else
                    {
                        PWM+=1;
                    }
                }
                powerOutOld=powerOut;
                PV_V_Old=PV_V;
                PWM7_LoadDutyValue(PWM);
                call=0;
            }
        }
        loopCount+=1;
        if(loopCount>254)loopCount=11;
    }
}
   
/*    uint16_t solarInTemp, solarOutTemp;
    
    float R, steinhart, displayTemp, displayTemp2;                                    // Calculate R of Thermistor, and Temp using SteinHart/Hart equation
    
    static uint16_t sampleIndex0 = 0, sampleIndex1 = 0;

    int32_t totals[2] = {0};

    char count          = 11;
    
   LCDBitmap(&aloha[0], 0, 336);
   
 //                  LCDBitmap(&coffee[0], 0,504);           //Draw Splash Screen
   //             gotoXY(1,4);
     //           LCDWriteCharacter(' ');                 // Need to Write something to the screen to get it to Draw the Splash Screen  FIX

   
   __delay_ms(3000);
   
// *************** Read Temperature ********************************************    
    while (1)
    {
        if(count>10)
        {
            LCDWriteStringXY(0,4,"Input to Solar");
            LCDWriteIntXY(60,4,(int)displayTemp,-1,1,0);
//            LCDWriteCharacter(123);
            LCDWriteCharacter('F');
            LCDWriteCharacter(' ');
            
            LCDWriteStringXY(0,5,"Return to Pool");
            LCDWriteIntXY(60,5,(int)displayTemp2,-1,1,0);
  //          LCDWriteCharacter(123);
            LCDWriteCharacter('F');
            LCDWriteCharacter(' ');
            count=0;
        }

        solarInTemp = ADCRead(9);                                       // Assign the just read temperature to the location of the current oldest data
            
        totals[0] = totals[0] - samples[0][sampleIndex0];                         // Subtract the oldest sample data from the total

        samples[0][sampleIndex0] = solarInTemp;                         // Assign the just read temperature to the location of the current oldest data

        totals[0] = totals[0] + samples[0][sampleIndex0];                         // Add that new sample to the total
            
        sampleIndex0 += 1;                                               // and move to the next index location
            
        if(sampleIndex0 >= numSamples)
        {
            sampleIndex0 = 0;
        }
            
        solarInTemp = (uint16_t)(totals[0] / numSamples);                          // assign the average value of total to the readTemperature variable
        


        solarOutTemp = ADCRead(22);                                       // Assign the just read temperature to the location of the current oldest data
            
        totals[1] = totals[1] - samples[1][sampleIndex1];                         // Subtract the oldest sample data from the total

        samples[1][sampleIndex1] = solarOutTemp;                         // Assign the just read temperature to the location of the current oldest data

        totals[1] = totals[1] + samples[1][sampleIndex1];                         // Add that new sample to the total
            
        sampleIndex1 += 1;                                               // and move to the next index location
            
        if(sampleIndex1 >= numSamples)
        {
            sampleIndex1 = 0;
        }
            
        solarOutTemp = totals[1] / numSamples;                          // assign the average value of total to the readTemperature variable
        
// *************** Calculate & Display Temp ************************************    
        R = 10010/(1023/(float)solarInTemp - 1);                    // Resistance of Thermistor (R Reference/1023/readTemp -1)
        
        steinhart = R /10061;                                           // (R/Ro) R/R Standard (resistance of Thermistor at 25C)
        steinhart = log(steinhart);                                     // ln(R/Ro)
        steinhart /= 3995;                                              // 1/Beta * ln(R/Ro)
        steinhart += 1.0 / (25 + 273.15);                               // + (1/To, Temperature in degK @ 25C)
        steinhart = 1.0 / steinhart;                                    // Invert
        steinhart -= 273.15;                                            // convert to DegC

        displayTemp = steinhart*10;
        
            displayTemp = displayTemp*9/5+320;                          // Display Temperature in DegF
            

            
        R = 9975/(1023/(float)solarOutTemp - 1);                    // Resistance of Thermistor (R Reference/1023/readTemp -1)
        
        steinhart = R /10061;                                           // (R/Ro) R/R Standard (resistance of Thermistor at 25C)
        steinhart = log(steinhart);                                     // ln(R/Ro)
        steinhart /= 3995;                                              // 1/Beta * ln(R/Ro)
        steinhart += 1.0 / (25 + 273.15);                               // + (1/To, Temperature in degK @ 25C)
        steinhart = 1.0 / steinhart;                                    // Invert
        steinhart -= 273.15;                                            // convert to DegC
 

        displayTemp2 = steinhart*10;
        
            displayTemp2 = displayTemp2*9/5+320;                          // Display Temperature in DegF
            
        
        count+=1;
       }
  //  }
}
*/
/*
// <editor-fold defaultstate="collapsed" desc="Includes & Defines">

// *************** Includes ****************************************************    
#include "system.h"
// *************** Defines *****************************************************    
#define numOutSamples           40                              // Number of Output samples to be Averaged into Output
// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="Variables">
// *************** Main Routine ************************************************    
void main(void)
{
    SYSTEM_Initialize();
    LCDWriteStringXY(0,0,"Hello");
    
    while(1)
    {
//        LCDWriteStringXY(0,0,"Hello");
    }
}*/