#ifndef PID_H
#define	PID_H
#include "system.h"

void Init_PID(int8_t controller, int pidKp, int pidKi, int pidKd);

// **************** Calculate PID (Call more often for fast loops) *************
// *** Output will update every time this is called, so, Reset & derivative ****
// ** actions happen more often, same as if Overall Loop Gain were increased! **
// ******* So, Temperature, poll less often, Flow or pressure more often. ******
// ** This algorithm is a non-interactive PID as opposed to Classic PID, so, ***
// ****** Tuning is handled differently, specifically, Gain is Stanalone. ******
int PID_Calculate(unsigned char controller, unsigned int setpoint, unsigned int temp);

#endif