#ifndef SYSTEM_H
#define	SYSTEM_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "pin_manager.h"
#include <stdint.h>
#include <stdbool.h>
#include "adc.h"
#include "lcd.h"
#include "interrupt_manager.h"
#include "tmr2.h"
#include "pwm6.h"
#include "zcd.h"

#define _XTAL_FREQ  4000000

void SYSTEM_Initialize(void);

void OSCILLATOR_Initialize(void);

#endif

