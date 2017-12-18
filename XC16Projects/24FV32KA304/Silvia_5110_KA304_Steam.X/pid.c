// **************** Includes ***********\****************************************    
#include "pid.h"

// **************** Variables available to all Functions in Program ************ 
int internalKp[]                = {   50,   50,  50}; // Controller Gain      (inverse of Proportional Band)
int internalKi[]                = {   15,   15,  15}; // Controller Integral Reset/Unit Time, determined by how often PID is calculated
int internalKd[]                = {   25,   25,  25}; // Controller Derivative (or Rate))
long pidIntegrated[3]           = {    0,    0,   0};
long pidPrevError[3]            = {    0,    0,   0};
long pidPrevInput[3]            = {    0,    0,   0};
int controllerMinOutput[3]      = {    0,    0,   0};
int integralMinOutput[3]        = { -100,  -50,  -1};   
int pidMinOutput[3]             = { -500,- 400, -10}; // Minimum output limit of Controller
int pidMaxOutput[3]             = { 7811, 7812, 200}; // Maximum output limit of Controller
extern char tuning;                                   // Set to a 1 when tuning    

void Init_PID(int8_t controller, int pidKp, int pidKi, int pidKd)
{
    internalKp[controller]              = pidKp;
    internalKi[controller]              = pidKi;
    internalKd[controller]              = pidKd;
    pidIntegrated[controller]           = 0;
    pidPrevInput[controller]            = 0;
}

// *************** PID_Calculate Runs faster if called more often **************    
int PID_Calculate(unsigned char controller, unsigned int setpoint, unsigned int temp)
{
    int result;
    long  error, errorValue;
    long derivativeValue;
        
// **************** Calculate Gain *********************************************    
    error = (long)setpoint - temp;                                // error calculation
 
    errorValue  = (long)error * internalKp[controller];                           // Calculate proportional value
    
// **************** Calculate Integral *****************************************    
    pidIntegrated[controller] += ((long)error * internalKi[controller]);       // Calculate integral value

    if (pidIntegrated[controller]< integralMinOutput[controller])               // limit output minimum value
    {
        pidIntegrated[controller]= integralMinOutput[controller];
    }
    
    if (pidIntegrated[controller]> pidMaxOutput[controller])                        // limit output maximum value 
    {
        pidIntegrated[controller]= pidMaxOutput[controller];
    }
    
// *************** Calculate Derivative **************************************** 
        derivativeValue=((long)error-pidPrevError[controller])*internalKd[controller];

       if(error<15 && error>-15)
        {
            derivativeValue*=10;
        }

       else
        {
            derivativeValue*=5;
        }

       
        if(derivativeValue>pidMaxOutput[controller])
        {
            derivativeValue=pidMaxOutput[controller];
        }
        
        if(derivativeValue<pidMinOutput[controller])
       {
            derivativeValue=pidMinOutput[controller];
        }

        pidPrevError[controller] = (long)error;
        
  
// *************** Calculate Final Output **************************************    
    result = (int)errorValue + (int)pidIntegrated[controller] + (int)derivativeValue;   // Calculate total to send to Output
    
    if (result < controllerMinOutput[controller])                              // limit output minimum value
    {
        result = controllerMinOutput[controller];
    }
    
    if (result > pidMaxOutput[controller])                              // limit output maximum value 
    {
        result = pidMaxOutput[controller];
    }
    
    if(tuning==1)
    {
        LCDWriteStringXY(0,0,"ERR");
        LCDWriteIntXY(16,0,error,4,0,0);
        LCDWriteCharacter(' ');
        LCDWriteStringXY(40,0,"EV")
        LCDWriteIntXY(52,0,errorValue,5,0,0);
        LCDWriteCharacter(' ');
        LCDWriteStringXY(0,2,"PID I")
        LCDWriteIntXY(0,3,pidIntegrated[controller],5,0,0);            
        LCDWriteCharacter(' ');
        LCDWriteStringXY(32,2,"PID D")
        LCDWriteIntXY(32,3,derivativeValue,5,0,0);
        LCDWriteCharacter(' ');
        LCDWriteStringXY(58,2,"result")
        LCDWriteIntXY(58,3,result,5,0,0); 
    }
    return (result);
}