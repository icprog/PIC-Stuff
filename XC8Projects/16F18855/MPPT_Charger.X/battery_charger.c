#include "battery_charger.h"

uint8_t     battery_state;
uint8_t     Imin_db;
uint16_t    Iflat_db;
uint16_t    state_counter;
uint16_t    Imin;
uint16_t    Iref;                                       // setpoint for current output
uint16_t    Vref;                                       // setpoint for voltage output
uint16_t    warmup;
uint16_t    Iout;
uint16_t    Vout;
int8_t      Imode;
int16_t     increment;




void Init_Battery_State_Machine()
{
	battery_state = PRECHARGE;	
	state_counter = PRECHARGE_TIME;

	SET_CURRENT(ILIM_PRECHARGE);                        // SET_CURRENT is in Hardware.h    ILIM_PRECHARGE is in Lead-acid.h
	SET_VOLTAGE(CHARGING_VOLTAGE);                        //SET_VOLTAGE is in Hardware.h CHARGING_VOLTAGE  is in Lead-acid.h

	Imin = ILIM;
	Imin_db = IMIN_UPDATE;
	Iflat_db = IFLAT_COUNT;

	START_CONVERTER();
}

void Battery_State_Machine()
{
	if(battery_state == PRECHARGE)
	{
		if(VSENSE < CUTOFF_VOLTAGE)
		{
			if(state_counter) state_counter--; else
				{
					battery_state = FAULT;
				}
		} else
		{
			battery_state = CHARGE;
			SET_CURRENT(ILIM);
		}
	} else
	if(battery_state == CHARGE)
	{
		if(CONSTANT_VOLTAGE)
		{
			if(ISENSE < Imin)
			{
				if(Imin_db) Imin_db--; else
				{
					Imin = ISENSE;
					Imin_db = IMIN_UPDATE;
					Iflat_db = IFLAT_COUNT;
				}
			} else
			{
				Imin_db = IMIN_UPDATE;
				if(Iflat_db) Iflat_db--;
			}
		} else
		{
			Imin_db = IMIN_UPDATE;
			Iflat_db = IFLAT_COUNT;
			Imin = ILIM;
		}
		if(Imin < ISTOP || !Iflat_db)
		{
			#ifdef	BATTERY_SLA
				battery_state = FLOAT;
				state_counter = FLOAT_TIME;

				SET_VOLTAGE(FLOATING_VOLTAGE);
			#else
				battery_state = FINISHED;
				if(Imin < I_BAT_DETECT) battery_state = IDLE;
			#endif
		}
	} else
	if(battery_state == FLOAT)
	{
		if(state_counter) state_counter--; else
		{
			battery_state = FINISHED;
		}
		#ifdef BATTERY_SLA
			if(state_counter < FLOAT_RELAX_TIME && ISENSE < I_BAT_DETECT)
			battery_state = IDLE;
		#endif
	} else
	if(battery_state == IDLE)
	{
		SET_VOLTAGE(0);
		SET_CURRENT(0);
		STOP_CONVERTER();
	} else
	if(battery_state == FAULT)
	{
		SET_VOLTAGE(0);
		SET_CURRENT(0);
		STOP_CONVERTER();	
	} else
	if(battery_state == FINISHED)
	{
		#ifdef BATTERY_STANDBY_MODE
			if(VSENSE < TOPPING_VOLTAGE && VSENSE > VBAT_DETECTION)
			{
				battery_state = CHARGE;

				SET_CURRENT(ILIM);
				SET_VOLTAGE(CHARGING_VOLTAGE);

				Imin = ILIM;
				Imin_db = IMIN_UPDATE;
				Iflat_db = IFLAT_COUNT;

				START_CONVERTER();
			} else
			{
				SET_VOLTAGE(0);
				SET_CURRENT(0);
				STOP_CONVERTER();	
				if(VSENSE < VBAT_DETECTION) battery_state = IDLE;
			}
		#else
			battery_state = IDLE;	
		#endif
	}
}