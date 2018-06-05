/*****************************************************************************
*                           BatteryCharger.c
*
* Description: Battery Charging Functions
*
* Hardware:  Synchronous Inverse SEPIC (Zeta) Converter + Battery Charging Library
*
* Resources: PICC 9.83 / MPLAB 8.80
*
* CODE OWNERSHIP AND DISCLAIMER OF LIABILITY
*
* Microchip Technology Incorporated ("Microchip") retains all ownership and
* intellectual property rights in the code accompanying this message and in
* all derivatives hereto.  You may use this code, and any derivatives created
* by any person or entity by or on your behalf, exclusively with Microchips
* proprietary products.  Your acceptance and/or use of this code constitutes
* agreement to the terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT
* LIMITED TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND
* FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH
* MICROCHIPS PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY
* APPLICATION.
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE,
* WHETHER IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF
* STATUTORY DUTY), STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE,
* FOR ANY INDIRECT, SPECIAL, PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL
* LOSS, DAMAGE, FOR COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
* CODE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
* POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWABLE
* BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS
* CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY
* TO HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and
* determining its suitability.  Microchip has no obligation to modify, test,
* certify, or support the code.
*
* Author            Date		Ver		Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Mihnea            Oct 2012 	1.00	Release
* Rosu-Hamzescu
******************************************************************************/

#include "BatteryCharger.h"

unsigned char battery_state;
unsigned char imin_db;
unsigned int iflat_db;
unsigned int state_counter;
unsigned int imin;

void Init_State_Machine()
{
	battery_state = PRECHARGE;	
	state_counter = PRECHARGE_TIME;
	SET_LED_BLINK(BLINK_05HZ);

	SET_CURRENT(ILIM_PRECHARGE);
	SET_VOLTAGE(CHARGING_VOLTAGE);

	imin = ILIM;
	imin_db = IMIN_UPDATE;
	iflat_db = IFLAT_COUNT;

	START_CONVERTER();
}

void Battery_State_Machine()
{
	if(battery_state == PRECHARGE)
	{
		SET_LED_BLINK(BLINK_05HZ);
		if(VSENSE < CUTOFF_VOLTAGE)
		{
			if(state_counter) state_counter--; else
				{
					battery_state = FAULT;
					SET_LED_BLINK(BLINK_05HZ);
				}
		} else
		{
			battery_state = CHARGE;
			SET_CURRENT(ILIM);
		}
	} else
	if(battery_state == CHARGE)
	{
		SET_LED_BLINK(BLINK_05HZ);
		if(CONSTANT_VOLTAGE)
		{
			if(ISENSE < imin)
			{
				if(imin_db) imin_db--; else
				{
					imin = ISENSE;
					imin_db = IMIN_UPDATE;
					iflat_db = IFLAT_COUNT;
				}
			} else
			{
				imin_db = IMIN_UPDATE;
				if(iflat_db) iflat_db--;
			}
		} else
		{
			imin_db = IMIN_UPDATE;
			iflat_db = IFLAT_COUNT;
			imin = ILIM;
		}
		if(imin < ISTOP || !iflat_db)
		{
			#ifdef	BATTERY_SLA
				battery_state = FLOAT;
				state_counter = FLOAT_TIME;

				SET_VOLTAGE(FLOATING_VOLTAGE);
			#else
				battery_state = DONE;
				if(imin < I_BAT_DETECT) battery_state = IDLE;
			#endif
		}
	} else
	if(battery_state == FLOAT)
	{
		SET_LED_BLINK(LED_ON);
		if(state_counter) state_counter--; else
		{
			battery_state = DONE;
		}
		#ifdef BATTERY_SLA
			if(state_counter < FLOAT_RELAX_TIME && ISENSE < I_BAT_DETECT)
			battery_state = IDLE;
		#endif
	} else
	if(battery_state == IDLE)
	{
		SET_LED_BLINK(LED_OFF);
		SET_VOLTAGE(0);
		SET_CURRENT(0);
		STOP_CONVERTER();
	} else
	if(battery_state == FAULT)
	{
		SET_LED_BLINK(BLINK_2HZ);
		SET_VOLTAGE(0);
		SET_CURRENT(0);
		STOP_CONVERTER();	
	} else
	if(battery_state == DONE)
	{
		SET_LED_BLINK(LED_ON);
		#ifdef BATTERY_STANDBY_MODE
			if(VSENSE < TOPPING_VOLTAGE && VSENSE > VBAT_DETECTION)
			{
				battery_state = CHARGE;

				SET_CURRENT(ILIM);
				SET_VOLTAGE(CHARGING_VOLTAGE);

				imin = ILIM;
				imin_db = IMIN_UPDATE;
				iflat_db = IFLAT_COUNT;

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