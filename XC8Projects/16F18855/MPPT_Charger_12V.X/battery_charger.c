#include "battery_charger.h"

uint8_t             batteryState[2];
uint16_t            IminCount[2];
int16_t             stateCounter[2];
int16_t             Imin[2];
int16_t             Iref[2];                                       // setpoint for current output
int16_t             Vref[2];                                       // setpoint for voltage output
int16_t             Iout;
int8_t              Imode[2]        =   1;
uint8_t             cc_cv[2]        =   0;
int8_t              VHoldMode[2]    =   0;
int16_t             voltage[4]      =   {0};                    // Store calculated Voltage values
int16_t             current[4]      =   {0};                    // Store Calculated Current Values




void Init_Battery_State_Machine(uint8_t z)
{
	batteryState[z] = PRECHARGE;                          // Set to PRECHARGE on a system Reset
	stateCounter[z] = PRECHARGE_TIME;                     // Set counter to PRECHARGE_TIME

	Iref[z]=ILIM_PRECHARGE;                        // SET_CURRENT to ILIM_PRECHARGE (ILIM_PRECHARGE is in lead-acid_agm.h)
	Vref[z]=CHARGING_VOLTAGE;                      // SET_VOLTAGE to CHARGING_VOLTAGE (CHARGING_VOLTAGE is in lead-acid_agm.h) SET_VOLTAGE sets Vref value

	Imin[z]=IFLOAT;                                      // Set Imin to the IFLOAT Current Limit (found in lead_acid_agm.h)
	IminCount[z] = IminUpdate;
}

void Battery_State_Machine(uint8_t z)
{
	if(batteryState[z]==PRECHARGE)
	{
		if(voltage[z]<CUTOFF_VOLTAGE)                    // If Battery Voltage is below CUTOFF_VOLTAGE
		{
			if(stateCounter[z]>0)                         // If stateCounter > 0
            {
                stateCounter[z]-=1;                       // decrement it
            }
            else
            {
                batteryState[z]=FAULT;                  // else, Set FAULT mode
			}
		} 
        else                                            // VSENSE is >= CUTOFF_VOLTAGE
		{
			batteryState[z]=CHARGE;                     // Set CHARGE mode
			Iref[z]=ILIM;                          // Set Current sets IRef value
		}
	}
    else if(batteryState[z]==CHARGE)
	{
		if(!Imode[z])                           // Mode is "Voltage Mode", not "Current Mode", So we are applying Topping current
		{
			if(current[z] < Imin[z])      // || ISENSE1 < Imin)
			{
                IminCount[z]-=2;
                if(IminCount[z]<10)                          // Current has been low for at least IminCount cycles (600 cycles, or about 10 minutes)
                {
                    batteryState[z] = FLOAT;              // Switch to Float Charging Mode  
                    IminCount[z]=10;
                }
			}
            else
			{
				if(IminCount[z]<IminUpdate)IminCount[z]+=1; // Keep us from going into Float because of sporadic sun
			}
		}
        else if(IminCount[z]<IminUpdate)IminCount[z]+=1; // Keep us from going into Float because of sporadic sun
	} 
    else if(batteryState[z] == FLOAT)
	{
        Vref[z]=FLOATING_VOLTAGE;
    	Iref[z]=IFLOAT;                            // Set Current sets IRef value
    }
	else
	if(batteryState[z] == FAULT)
	{
        LCDWriteStringXY(0,0,"BATTERY FAULT");
        Imode[z]=0;
//        Imode1=0;
        __delay_ms(2000);
//		SET_VOLTAGE(0);
//		SET_CURRENT(0);
//		STOP_CONVERTER();	
	}
}

void cc_cv_mode(uint8_t z)
{
	if(voltage[z]>Vref[z])                                  // Vref is set by SET_VOLTAGE()
	{
        if(VHoldMode[z]<12)VHoldMode[z]+=1;
        
		if(cc_cv[z])                                       // cc_cv is the number of slowLoop cycles to complete before switching to Voltage Mode
        {
            cc_cv[z]-=1;                                   // Decrement it by 1,
        }
        else
		{
			if(Imode[z])                                  // until it is zero, 
            {
                Imode[z]=0;                             // then, switch to "Voltage Mode"
            }
		}
	}
    else if(voltage[z]<Vref[z])
    {
        VHoldMode[z]-=1;
        if(VHoldMode[z]<(CURRENT_MODE*-1))
        {
            Imode[z]=1;                                 // switch to "Current Mode"
            cc_cv[z]=(CURRENT_MODE*2);                   // and, set the cc_cv to count "CURRENT_MODE" number of slowLoop iterations, before allowing a return to "VOLTAGE Mode"
            VHoldMode[z]=(CURRENT_MODE*-1);
        }
    }
    else VHoldMode[z]=VHoldMode[z];
    
    if(current[z]>Iref[z])                                  // Iref is set by "SET_CURRENT(some Value here)" Use this to come back out of FLOAT Mode
	{
		if(!Imode[z])                                     // If not "CURRENT Mode",
        {
            if(batteryState[z]==FLOAT)
            {
                batteryState[z]=CHARGE;                   // Set CHARGE mode
                Vref[z]=CHARGING_VOLTAGE;          // Set Vref back to CHARGING_VOLTAGE
                Iref[z]=ILIM;                      // Set Iref back to ILIM
                Imode[z]=1;                             // switch to "Current Mode"
                cc_cv[z]=CURRENT_MODE;                   // and, set the cc_cv to count "CURRENT_MODE" number of slowLoop iterations, before allowing a return to "VOLTAGE Mode"
            }
        }
	}
}

