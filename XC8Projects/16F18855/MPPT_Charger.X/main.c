// <editor-fold defaultstate="collapsed" desc="Includes & Defines">

// *************** Includes ****************************************************    
#include "system.h"

#define VIn0            voltage[0]
#define VOut0           voltage[1]
#define VIn1            voltage[2]
#define VOut1           voltage[3]    


#define IIn0            current[0]
#define IOut0           current[1]
#define IIn1            current[2]
#define IOut1           current[3]

#define     Fault       !RB2
#define     PWM0        dutyCycle6
#define     PWM1        dutyCycle7
#define     PWM2        dutyCycle1

#define     power0In    VIn0/100*IIn0/10
#define     power0Out   VOut0/100*IOut0/10
#define     power1In    VIn1*IIn1
#define     power1Out   VOut1*IOut1



// *************** Externally available Variables ******************************    
int16_t         analogs[8]      =   {0,0,0,0,0,0,0,0};
extern int16_t  voltage[4];                    // Store calculated Voltage values
extern int16_t  current[4];                    // Store Calculated Current Values

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc=" Variables declared in Main">
// *************** Main Routine ************************************************    


void main(void)
{
    int16_t         MPPT0           =   3144;
    int16_t         MPPT1           =   3144;
    
    uint16_t        dutyCycle6      =   1023;                   // 126 is midpoint, allow adjusting up or down
    uint16_t        dutyCycle7      =   256;                    // 126 is midpoint, allow adjusting up or down
    uint16_t        dutyCycle1      =   60;                     // 30 is required for minimum speed
    int16_t         IOutTotal       =   0;

    uint8_t         j               =   0;

    uint8_t         fastLoop        =   0;
    uint8_t         slowLoop        =   200;
    uint8_t         displayRefresh  =   0;
    int16_t         batteryTemp     =   250;
    float           efficiency      =   0;
    extern int8_t   Imode0;
    extern int16_t  Vref;                                       // setpoint for voltage output
    extern int16_t  Iref;
    uint8_t         menuButton      =   0;                      // Holds value of which button is pressed
    uint8_t         faultReset      =   0;                      // Automatically Reset Current Fault latch
    
    SYSTEM_Initialize();
    
    LCDClear();
    
    void calculateCurrent0(void);
    void calculateCurrent1(void);
    void calculateCurrent2(void);
    void calculateCurrent3(void);
    
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
        for(j=0;j<8;j++) analogs[j]=readAnalog(j);              // Read analogs
        
        
        voltage[0]=(int16_t)(analogs[0]/.20885);                // Calculate VIn0
        
        voltage[1]=(int16_t)(analogs[1]/.54503);                // Calculate VOut0

//        voltage[2]=(int16_t)(analogs[2]/.20885);                // Calculate VIn1
        
  //      voltage[3]=(int16_t)(analogs[3]/.666);                  // Calculate VOut1
        
        calculateCurrent0();
//        current[0]=(analogs[4]-589)/1.3165;
        
        calculateCurrent1();
//        current[1]=(analogs[5]-578)/3.232;

        if(fastLoop>2)
        {
            if(Imode0)
            {
                if(VIn0<MPPT0)                             // 3164 is actual MPPT of Panel
                {
                    if(PWM0<1023)
                    {
                        PWM0+=1;
                    }
                }
                else if(PWM0>0)
                {
                    PWM0-=1;
                }
                
                if(VIn1<MPPT1)                             // 3164 is actual MPPT of Panel
                {
                    if(PWM1<252)
                    {
//                        PWM1+=1;
                    }
                }
                else if(PWM1>0)
                {
  //                  PWM1-=1;
                }
           }
            else
            {
                if(VOut0>(int16_t)Vref)
                {
                    if(PWM0<1023) PWM0+=1;
                }
                else
                {
                    if(PWM0>0) PWM0-=1;;
                }
 
                if(VOut1>(int16_t)Vref)
                {
//                    if(PWM1<1023) PWM1+=1;
                }
                else
                {
  //                  if(PWM1>0) PWM1-=1;;
                }

            }
            fastLoop=0;
            slowLoop+=1;

            PWM1_LoadDutyValue(PWM2);
            PWM6_LoadDutyValue(PWM0);
            PWM7_LoadDutyValue(PWM1);

            menuButton = readButton();
            if(menuButton == Down) if(MPPT0>2800)MPPT0-=10;
            if(menuButton == Up)if(MPPT0<3400)MPPT0+=10;
            if(menuButton == Enter)LCDInit();
        }
        fastLoop+=1;
        
        if(slowLoop>50)
        {
            
            IOutTotal=IOut0+IOut1;
            
            if(IOutTotal>20)
            {
                PWM2=(uint16_t)IOutTotal/2+10;
            }
            else
            {
                PWM2=0;
            }
            if(Fault==1)PWM2=55;                                                // Fault is the current sensors,can only be reset by resetting Processor
//            if(Fault==1)RESET();                                                // Fault is the current sensors,can only be reset by resetting Processor
                         
            displayRefresh+=1;
            if(displayRefresh>80)
            {
                LCDClear();
                displayRefresh=0;
                batteryTemp=tempCalc(ADCRead(9));                           // Read Thermistor on RB2
                faultReset+=1;
                if(faultReset>29)
                {
                    RESET();
                    faultReset=0;
                }
            }
            Battery_State_Machine();
            efficiency=(float)power0Out;
            efficiency/=(float)power0In;
            efficiency*=100;
            LCDWriteCharacter(' ');
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
            
            LCDWriteIntXY(0,0,batteryTemp,4,1,0);
  //          LCDWriteStringXY(24,0,"Eff:");
//            LCDWriteIntXY(60,0,(int16_t)efficiency,5,0,0);
            LCDWriteIntXY(28,0,analogs[4],4,0,0);
            LCDWriteIntXY(48,0,analogs[5],4,0,0);
            LCDWriteIntXY(0,1,VIn0,4,2,0);
            LCDWriteCharacter('V');
            LCDWriteIntXY(28,1,IIn0,3,1,0);
            LCDWriteCharacter('A');
//            LCDWriteIntXY(56,1,ADCRead(11),4,0,0);                              // Read Buttons
            LCDWriteIntXY(0,2,VOut0,4,2,0);
            LCDWriteCharacter('V');
            LCDWriteIntXY(28,2,IOut0,3,1,0);
            LCDWriteCharacter('A');
            LCDWriteIntXY(56,2,Vref,4,2,0);
            LCDWriteCharacter('V');
            
            LCDWriteIntXY(0,3,power0In,3,0,0);
            LCDWriteCharacter('W');
            LCDWriteIntXY(28,3,battery_state,1,0,0);
            LCDWriteIntXY(36,3,Imode0,1,0,0);
            LCDWriteIntXY(48,3,Iref,3,1,0);
            LCDWriteCharacter('A');
            
            LCDWriteIntXY(0,4,power0Out,3,0,0);
            LCDWriteCharacter('W');
//            LCDWriteIntXY(24,4,power0OutOld,3,0,0);
            LCDWriteCharacter('W');
            LCDWriteIntXY(48,4,MPPT0,4,0,0);
            
//            LCDWriteIntXY(0,3,VIn1,4,2,0);
  //          LCDWriteCharacter('V');
    //        LCDWriteIntXY(28,3,IIn1,4,0,0);
      //      LCDWriteIntXY(0,4,VOut1,4,2,0);
        //    LCDWriteCharacter('V');
          //  LCDWriteIntXY(28,4,IOut1,4,0,0);
            LCDWriteIntXY(0,5,PWM0,4,0,0);
            LCDWriteIntXY(24,5,PWM1,4,0,0);
            LCDWriteIntXY(48,5,PWM2,4,0,0);
            LCDWriteIntXY(74,5,Fault,1,0,0);

            if(battery_state > FINISHED)
            {
            	cc_cv_mode();
            }
            slowLoop=0;
        }
    }
}

void calculateCurrent0(void)
{
    if(analogs[4]-589<=0)
    {
        current[0]=0;
    }
    else
    {
        current[0]=(int16_t)((analogs[4]-589)/1.3165);
    }
}

void calculateCurrent1(void)
{
    if(analogs[5]-578<=0)
    {
        current[1]=0;
    }
    else
    {
        current[1]=(int16_t)((analogs[5]-578)/3.2323);
    }
}

void calculateCurrent2(void)
{
    if(analogs[6]-589<=0)
    {
        current[2]=0;
    }
    else
    {
        current[0]=(int16_t)((analogs[4]-589)/1.3165);
    }
}

void calculateCurrent3(void)
{
    if(analogs[7]-578<=0)
    {
        current[3]=0;
    }
    else
    {
        current[1]=(int16_t)((analogs[5]-578)/3.2323);
    }
}

