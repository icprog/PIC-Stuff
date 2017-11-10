// CONFIG1
#pragma config FEXTOSC  = OFF                   // External Oscillator mode selection bits->Oscillator not enabled
#pragma config RSTOSC   = HFINT1                // Power-up default value for COSC bits->HFINTOSC (1MHz)
#pragma config CLKOUTEN = OFF                   // Clock Out Enable bit->CLKOUT function is disabled; i/o or oscillator function on OSC2
#pragma config CSWEN    = ON                    // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config FCMEN    = ON                    // Fail-Safe Clock Monitor Enable bit->FSCM timer enabled

// CONFIG2
#pragma config MCLRE    = ON                    // Master Clear Enable bit->MCLR pin is Master Clear function
#pragma config PWRTE    = OFF                   // Power-up Timer Enable bit->PWRT disabled
#pragma config LPBOREN  = OFF                   // Low-Power BOR enable bit->ULPBOR disabled
#pragma config BOREN    = ON                    // Brown-out reset enable bits->Brown-out Reset Enabled, SBOREN bit is ignored
#pragma config BORV     = LO                    // Brown-out Reset Voltage Selection->Brown-out Reset Voltage (VBOR) set to 1.9V on LF, and 2.45V on F Devices
#pragma config ZCD      = ON                    // Zero-cross detect disable->Zero-cross detect circuit is always enabled
#pragma config PPS1WAY  = ON                    // Peripheral Pin Select one-way control->The PPSLOCK bit can be cleared and set only once in software
#pragma config STVREN   = ON                    // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a reset
//#pragma config DEBUG    = OFF                   // Background Debugger->Background Debugger disabled

// CONFIG3
#pragma config WDTCPS   = WDTCPS_31             // WDT Period Select bits->Divider ratio 1:65536; software control of WDTPS
#pragma config WDTE     = ON                    // WDT operating mode->WDT Disabled, SWDTEN is ignored
#pragma config WDTCWS   = WDTCWS_7              // WDT Window Select bits->window always open (100%); software control; keyed access not required
#pragma config WDTCCS   = SC                    // WDT input clock selector->Software Control

// CONFIG4
#pragma config WRT      = OFF                   // UserNVM self-write protection bits->Write protection off
#pragma config SCANE    = available             // Scanner Enable bit->Scanner module is available for use
#pragma config LVP      = ON                    // Low Voltage Programming Enable bit->Low Voltage programming enabled. MCLR/Vpp pin function is MCLR.

// CONFIG5
#pragma config CP       = OFF                   // UserNVM Program memory code protection bit->Program Memory code protection disabled
#pragma config CPD      = OFF                   // DataNVM code protection bit->Data EEPROM code protection disabled

#include "system.h"

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();                   // Set all I/O pin values
    OSCILLATOR_Initialize();                    // Initialize the Oscillator
    ADC_Initialize();                           // Initialize the ADC
    ZCD_Initialize();                           // Initialize the Zero Cross Detector
    LCD_Init();                                 // Initialize the Nokia 5110 Graphical LCD
    __delay_ms(75);                             // delay 75 ms
    LCD_Clear();                                // Clear the LCD
    INTERRUPT_GlobalInterruptEnable();          // Enable the Global Interrupts
    INTERRUPT_PeripheralInterruptEnable();      // Enable the Peripheral Interrupts
    PWM6_Initialize();                          // Init Pulse Width Modulation
    TMR2_Initialize();                          // Init Timer2, will control PWM Period
}

void OSCILLATOR_Initialize(void)
{
    OSCCON1 = 0x60;                             // NOSC HFINTOSC; NDIV 1; 

    OSCCON3 = 0x00;                             // CSWHOLD may proceed; SOSCPWR Low power; 

    OSCEN = 0x00;                               // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled; 

    OSCFRQ = 0x02;                              // HFFRQ 4_MHz; 

    OSCTUNE = 0x00;                             // HFTUN 0; 
}