// **************** Includes ***************************************************    
#include "pid.h"

// **************** Variables available to all Functions in Program ************ 
int16_t error, errorValue, derivativeValue = 0, Result;
char count              = 0;

int Kp                = 1;    // Controller Gain      (inverse of Proportional Band)
int Ki                = 1;    // Controller Integral Reset/Unit Time, determined by how often PID is calculated
int Kd                = 1;    // Controller Derivative (or Rate))
int16_t pidIntegrated     = 0;
int16_t pidPrevError      = 0;
//float pidPrevInput      = 0;
int pidMinOutput        = 0;     // Minimum output limit of Controller
int pidMaxOutput        = 4095;  // Maximum output limit of Controller
//extern int8_t choice;
/*
void Init_PID(int pidKp, int pidKi, int pidKd)
{
    Kp         = pidKp;
    Ki         = pidKi;
    Kd         = pidKd;
    pidIntegrated = 0;
    pidPrevInput = 0;
}
*/

// *************** Calculate PID Runs faster if called more often **************    
float PID_Calculate(int16_t setpoint, int16_t temp)
{
    count+=1;
//    float error, errorValue, derivativeValue = 0, Result;
        
// **************** Calculate Gain *********************************************    
    error = setpoint - temp;                                // error calculation

    errorValue  = error * Kp;                           // Calculate proportional value

// **************** Calculate Integral *****************************************  
    if(count>59)
    {
        pidIntegrated = pidIntegrated + (error * Ki);       // Calculate integral value

        if (pidIntegrated< pidMinOutput)                        // limit output minimum value
        {
            pidIntegrated= pidMinOutput;
        }
    
        if (pidIntegrated> pidMaxOutput)                        // limit output maximum value 
        {
            pidIntegrated= pidMaxOutput;
        }
        count = 0;
    }

// *************** Calculate Derivative ****************************************    
        derivativeValue=(error-pidPrevError)*Kd;
        pidPrevError = error;
  
// *************** Calculate Final Output **************************************    
    Result = errorValue + pidIntegrated+ derivativeValue;   // Calculate total to send to Output
    
    if (Result < pidMinOutput)                              // limit output minimum value
    {
        Result = pidMinOutput;
    }
    
    if (Result > pidMaxOutput)                              // limit output maximum value 
    {
        Result = pidMaxOutput;
    }
 
    return (Result);
}