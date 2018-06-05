/*****************************************************************************
*                           main.c
*
* Description: Main program loop
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

__CONFIG(0x39A4);
__CONFIG(0x1FFF);

void main()
{

	Init_Registers();

	Initialize_Hardware();

	Delay_ms(500);

	while(1)
	{
		if(T0IF)
		{

			T0IF = 0;
			if(but_cnt) but_cnt--;
			if(second) second--;
			
			read_ADC();

			if(battery_state > DONE)
		
			{
				cc_cv_mode();

				if(!cmode) pid(vout, vref); else
				pid(iout, iref);
			}
		}
		if(!but_cnt)
		{
			but_cnt = BUTTON_COUNT;

			if(!BUTTON & lbut)
			{
				if(battery_state == IDLE) Init_State_Machine(); else
				{
					battery_state = IDLE;
					SET_LED_BLINK(LED_OFF);
				}
			}
			lbut = BUTTON;

			led_blink();
		}
		if(!second)
		{
			second = SECOND_COUNT;

			Battery_State_Machine();
			
		}		
	}
}
