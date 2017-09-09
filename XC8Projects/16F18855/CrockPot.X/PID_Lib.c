#include "PID_Lib.h"

float PID_Kp, PID_Ki;
float PID_Kd;
float PID_Integrated;
float PID_Prev_Input = 0;
int PID_MinOutput = 0, PID_MaxOutput = 1023;
unsigned char PID_First_Time = 1;

// *****************************************************************************    
void Init_PID(void)
{
  PID_Kp         = Kp;
  PID_Ki         = Ki;
  PID_Kd         = Kd;
  PID_MinOutput  = MinimumOutput;
  PID_MaxOutput  = MaximumOutput;
  PID_Integrated = 0;
  PID_Prev_Input = 0;
  PID_First_Time = 1;
}

// *****************************************************************************    
float PID_Calculate(int const setpoint, float temp)
{
    float Err, ErrValue, DerivativeValue, Result;
        
    Err = setpoint - temp;                                      // Error calculation
    
    ErrValue  = Err * PID_Kp;                                   // Calculate proportional value

    PID_Integrated = PID_Integrated + (Err * PID_Ki);           // Calculate integral value

    if (PID_Integrated < PID_MinOutput)                         // limit output minimum value
    {
        PID_Integrated = PID_MinOutput;
    }
    
    if (PID_Integrated > PID_MaxOutput)                         // limit output maximum value 
    {
        PID_Integrated = PID_MaxOutput;
    }


    if (PID_First_Time)                                         // Calculate derivative value
    {
        PID_First_Time = 0;                                     // to avoid a huge DerivativeValue the first time (PID_Prev_Input = 0)
        PID_Prev_Input = temp;
    }
  
    if(temp == PID_Prev_Input)                                  // If temp hasn't changed, Hold output due to Derivative action
    {
        DerivativeValue = DerivativeValue;
    }
    else
    {
        DerivativeValue = (temp - PID_Prev_Input) * PID_Kd;
        PID_Prev_Input = temp;
    }
    
    if(temp>=setpoint)
    {
        ErrValue = 0;
        PID_Integrated = 0;
    }
  
    Result = ErrValue + PID_Integrated - DerivativeValue;       // Calculate total to send to Output
    
    if (Result < PID_MinOutput)                                 // limit output minimum value
    {
        Result = PID_MinOutput;
    }
    
    if (Result > PID_MaxOutput)                                 // limit output maximum value 
    {
        Result = PID_MaxOutput;
    }
 
    return (Result);
}