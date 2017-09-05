#ifndef SYSTEM_H
#define	SYSTEM_H

#include <xc.h>
#include "pin_manager.h"
#include <stdint.h>
#include <stdbool.h>
#include "tmr2.h"
#include "pwm1.h"
#include "pwm2.h"
#include "pwm3.h"
#include "lcd.h"

#define _XTAL_FREQ  250000



void SYSTEM_Initialize(void);


void OSCILLATOR_Initialize(void);



#endif