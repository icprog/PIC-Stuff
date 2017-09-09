#ifndef PID_LIB_H
#define	PID_LIB_H

#include "lcd.h"
#include "eeprom.h"

#define Kp              5
#define Ki              15
#define Kd              300
#define MinimumOutput   0
#define MaximumOutput   1023


void Init_PID(void);

float PID_Calculate(int const setpoint, float temp);

#endif