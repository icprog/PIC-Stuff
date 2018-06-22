// <editor-fold defaultstate="collapsed" desc="Includes & Defines">

// *************** Includes ****************************************************    
#include "system.h"

#define VIn0            voltage[0]
#define VOut0           voltage[1]
#define VIn1            voltage[2]
#define VOut1           voltage[3]    


#define IIn0            analogs[4]
#define IOut0           analogs[5]
#define IIn1            analogs[6]
#define IOut1           analogs[7]
/*
#define VIn0            analogs[0]
#define VOut0           analogs[1]
#define VIn1            analogs[2]
#define VOut1           analogs[3]    


#define IIn0            analogs[4]
#define IOut0           analogs[5]
#define IIn1            analogs[6]
#define IOut1           analogs[7]
*/    
//#define		VIN1				RC7 // was RA2
//#define		IIN1        		RC6 // was RC2
//#define		VOUT1				RC5 // was RC3
//#define		IOUT1				RC4 // was RA1
//#define     VIN2                RC3
//#define     IIN2                RC2
//#define     VOUT2               RC1
//#define     IOUT2               RC0
    
#define     Fault       RB2
#define     PWM0        dutyCycle6
#define     PWM1        dutyCycle7

#define     power0In    VIn0*IIn0
#define     power0Out   VOut0*IOut0
#define     power1In    VIn1*IIn1
#define     power1Out   VOut1*IOut1

// *************** Externally available Variables ******************************    
//uint16_t samples[2][numSamples] = {0};
int16_t         analogs[8]      =   {0,0,0,0,0,0,0,0};

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc=" Variables declared in Main">
// *************** Main Routine ************************************************    


void main(void)
{
    int16_t         VIn0_Old        =   0;
    int16_t         VIn1_Old        =   0;
    int16_t         power0OutOld    =   0;
    int16_t         power1OutOld    =   0;
    
    uint16_t        dutyCycle6      =   126;                    // 126 is midpoint, allow adjusting up or down
    uint16_t        dutyCycle7      =   126;                    // 126 is midpoint, allow adjusting up or down
    
    int16_t         voltage[4]      =   {0};                    // Store calculated Voltage values

    uint8_t         j               =   0;

    uint8_t         fastLoop        =   0;
    uint8_t         slowLoop        =   200;
    extern int8_t   Imode;
    extern uint16_t Vref;                                       // setpoint for voltage output
    uint8_t         menuButton      =   0;                      // Holds value of which button is pressed

    
    SYSTEM_Initialize();
    
    LCDClear();
    // </editor-fold>
/*    
//    volatile unsigned char value = 0x09;
  //  unsigned char address = 0xE5;
    //eeprom_write(address, value);     // Writing value 0x9 to EEPROM address 0xE5        
    //value = eeprom_read (address);    // Reading the value from address 0xE5
    
//    eeprom_write(Kp_offset,10);
  //  eeprom_write(Ki_offset,4);
    //eeprom_write(Kd_offset,2);
  */  

    while (1)
    {
        for(j=0;j<8;j++) analogs[j]=readAnalog(j);          // Read analogs
        
        voltage[0]=analogs[0]/.20885;                       // Calculate VIn0
        
        voltage[1]=analogs[1]/.666;                         // Calculate VOut0

        voltage[2]=analogs[2]/.20885;                       // Calculate VIn1
        
        voltage[3]=analogs[3]/.666;                         // Calculate VOut1

        if(fastLoop>10)
        {
            if(Imode)
            {
                if(power0Out>power0OutOld)
                {
                    if(VIn0>VIn0_Old)
                    {
                        PWM0+=1;
                    }
                    else
                    {
                        PWM0-=1;
                    }
                }
                else
                {
                    if(VIn0>VIn0_Old)
                    {
                        PWM0-=1;
                    }
                    else
                    {
                        PWM0+=1;
                    }
                }
                power0OutOld=power0Out;
                VIn0_Old=VIn0;
                
                if(power1Out>power1OutOld)
                {
                    if(VIn1>VIn1_Old)
                    {
                        PWM1+=1;
                    }
                    else
                    {
                        PWM1-=1;
                    }
                }
                else
                {
                    if(VIn1>VIn1_Old)
                    {
                        PWM1-=1;
                    }
                    else
                    {
                        PWM1+=1;
                    }
                }
                power1OutOld=power1Out;
                VIn1_Old=VIn1;
            }
            else
            {
                if(VOut0>(int16_t)Vref)
                {
                    if(PWM0<252) PWM0+=1;
                }
                else
                {
                    if(PWM0>0) PWM0-=1;;
                }
 
                if(VOut1>(int16_t)Vref)
                {
                    if(PWM1<252) PWM1+=1;
                }
                else
                {
                    if(PWM1>0) PWM1-=1;;
                }
            }
            fastLoop=0;
            slowLoop+=1;
            PWM6_LoadDutyValue(PWM0);
            PWM7_LoadDutyValue(PWM1);
            menuButton = readButton();
            if(menuButton == Down) if(PWM0<252) PWM0+=1;
            if(menuButton == Up) if(PWM0>0) PWM0-=1;;
            if(menuButton == Enter)LCDInit();
        }
        fastLoop+=1;
        
        if(slowLoop>10)
        {
            LCDClear();
//            Battery_State_Machine();
//            LCDWriteIntXY(0,0,ADCRead(23),4,0,0);
  //          LCDWriteIntXY(20,0,ADCRead(22),4,0,0);
    //        LCDWriteIntXY(0,1,ADCRead(21),4,0,0);
      //      LCDWriteIntXY(20,1,ADCRead(20),4,0,0);
        //    LCDWriteIntXY(0,3,ADCRead(19),4,0,0);
          //  LCDWriteIntXY(20,3,ADCRead(18),4,0,0);
            //LCDWriteIntXY(0,4,ADCRead(17),4,0,0);
            //LCDWriteIntXY(20,4,ADCRead(16),4,0,0);

//            LCDWriteIntXY(0,2,ADCRead(22),4,0,0);
  //          LCDWriteIntXY(20,2,ADCRead(15),4,0,0);
            
            LCDWriteIntXY(0,0,analogs[1],4,0,0);
            LCDWriteIntXY(0,1,VIn0,4,2,0);
            LCDWriteCharacter('V');
            LCDWriteIntXY(28,1,IIn0-594,4,0,0);
            LCDWriteIntXY(48,1,ADCRead(11),4,0,0);
            LCDWriteIntXY(0,2,VOut0,4,2,0);
            LCDWriteCharacter('V');
            LCDWriteIntXY(28,2,IOut0-582,4,0,0);
            LCDWriteIntXY(48,2,Vref,4,0,0);
            LCDWriteIntXY(0,3,VIn1,4,2,0);
            LCDWriteCharacter('V');
            LCDWriteIntXY(28,3,IIn1,4,0,0);
            LCDWriteIntXY(0,4,VOut1,4,2,0);
            LCDWriteCharacter('V');
            LCDWriteIntXY(28,4,IOut1,4,0,0);
            LCDWriteIntXY(0,5,PWM0,3,0,0);
            LCDWriteIntXY(24,5,PWM1,3,0,0);
            
            LCDWriteIntXY(40,5,Fault,1,0,0);
            
            if(battery_state > FINISHED)
            {
            	cc_cv_mode();
            }
            slowLoop=0;
        }
    }
}