// **************** Includes ***********\****************************************    
#include "pid.h"

// **************** Variables available to all Functions in Program ************ 
int internalKp[]                = {  50,  50,  50}; // Controller Gain      (inverse of Proportional Band)
int internalKi[]                = {  15,  15,  15}; // Controller Integral Reset/Unit Time, determined by how often PID is calculated
int internalKd[]                = {  25,  25,  25}; // Controller Derivative (or Rate))
int pidIntegrated[3]            = {   0,   0,   0};
int pidPrevError[3]             = {   0,   0,   0};
int pidPrevInput[3]             = {   0,   0,   0};
int pidMinOutput[3]             = {   0,   0,   0}; // Minimum output limit of Controller
int pidMaxOutput[3]             = {7811,7812, 201}; // Maximum output limit of Controller
//extern int8_t choice;                                                                           // Not needed? FIX

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
    int error, errorValue, derivativeValue = 0, result;
        
// **************** Calculate Gain *********************************************    
    error = setpoint - temp;                                // error calculation

    errorValue  = error * internalKp[controller];                           // Calculate proportional value

// **************** Calculate Integral *****************************************    
    pidIntegrated[controller] = pidIntegrated[controller] + (error * internalKi[controller]);       // Calculate integral value

    if (pidIntegrated[controller]< pidMinOutput[controller])                        // limit output minimum value
    {
        pidIntegrated[controller]= pidMinOutput[controller];
    }
    
    if (pidIntegrated[controller]> pidMaxOutput[controller])                        // limit output maximum value 
    {
        pidIntegrated[controller]= pidMaxOutput[controller];
    }

// *************** Calculate Derivative ****************************************    
        derivativeValue=(error-pidPrevError[controller])*internalKd[controller];
        pidPrevError[controller] = error;
  
// *************** Calculate Final Output **************************************    
    result = errorValue + pidIntegrated[controller]- derivativeValue;   // Calculate total to send to Output
    
    if (result < pidMinOutput[controller])                              // limit output minimum value
    {
        result = pidMinOutput[controller];
    }
    
    if (result > pidMaxOutput[controller])                              // limit output maximum value 
    {
        result = pidMaxOutput[controller];
    }
 
    return (result);
}