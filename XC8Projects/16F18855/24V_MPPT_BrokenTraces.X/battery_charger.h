#include "system.h"
#include "lead_acid.h"

#define		CURRENT_MODE		9                          // Number of slowLoop cycles Voltage is over Vref before we drop back to "Voltage Mode" from "Current Mode"
#define 	IminUpdate			600

#ifndef BATTERY_CHARGER_H
	#define BATTERY_CHARGER_H
	enum charge_states { IDLE = 0, FAULT = 1, FINISHED = 2, PRECHARGE = 3, CHARGE = 4, FLOAT = 5 };
#endif
    

extern uint8_t  battery_state[2];

void Init_Battery_State_Machine(uint8_t z);
void Battery_State_Machine(uint8_t z);
void cc_cv_mode(uint8_t z);