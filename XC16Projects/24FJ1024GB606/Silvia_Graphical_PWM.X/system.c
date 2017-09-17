// PIC24FJ1024GB606 Configuration Bit Settings

// FSEC
#pragma config BWRP =       OFF             // Boot Segment Write-Protect bit (Boot Segment may be written)
#pragma config BSS =        OFF             // Boot Segment Code-Protect Level bits (No Protection (other than BWRP))
#pragma config BSEN =       OFF             // Boot Segment Control bit (No Boot Segment)
#pragma config GWRP =       OFF             // General Segment Write-Protect bit (General Segment may be written)
#pragma config GSS =        OFF             // General Segment Code-Protect Level bits (No Protection (other than GWRP))
#pragma config CWRP =       OFF             // Configuration Segment Write-Protect bit (Configuration Segment may be written)
#pragma config CSS =        DIS             // Configuration Segment Code-Protect Level bits (No Protection (other than CWRP))
#pragma config AIVTDIS =    DISABLE         // Alternate Interrupt Vector Table bit (Disabled AIVT)

// FBSLIM
#pragma config BSLIM =      0x1FFF          // Boot Segment Flash Page Address Limit bits (Boot Segment Flash page address  limit)

// FSIGN

// FOSCSEL
#pragma config FNOSC =      FRCPLL          // Oscillator Source Selection (Fast RC Oscillator with divide-by-N with PLL module (FRCPLL) )
#pragma config PLLMODE =    DISABLED        // PLL Mode Selection (No PLL used; PLLEN bit is not available)
#pragma config IESO =       ON              // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FOSC
#pragma config POSCMOD =    NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
#pragma config OSCIOFCN =   OFF             // OSC2 Pin Function bit (OSC2 is clock output)
#pragma config SOSCSEL =    ON              // SOSC Power Selection Configuration bits (SOSC is used in crystal (SOSCI/SOSCO) mode)
#pragma config PLLSS =      PLL_PRI         // PLL Secondary Selection Configuration bit (PLL is fed by the Primary oscillator)
#pragma config IOL1WAY =    ON              // Peripheral pin select configuration bit (Allow only one reconfiguration)
#pragma config FCKSM =      CSDCMD          // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPS =      PS32768         // Watchdog Timer Postscaler bits (1:32,768)
#pragma config FWPSA =      PR128           // Watchdog Timer Prescaler bit (1:128)
#pragma config FWDTEN =     OFF             // Watchdog Timer Enable bits (WDT and SWDTEN disabled)
#pragma config WINDIS =     OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config WDTWIN =     PS25_0          // Watchdog Timer Window Select bits (WDT Window is 25% of WDT period)
#pragma config WDTCMX =     WDTCLK          // WDT MUX Source Select bits (WDT clock source is determined by the WDTCLK Configuration bits)
#pragma config WDTCLK =     LPRC            // WDT Clock Source Select bits (WDT uses LPRC)

// FPOR
#pragma config BOREN =      ON              // Brown Out Enable bit (Brown Out Enable Bit)
#pragma config LPCFG =      OFF             // Low power regulator control (No Retention Sleep)
#pragma config DNVPEN =     ENABLE          // Downside Voltage Protection Enable bit (Downside protection enabled using ZPBOR when BOR is inactive)

// FICD
#pragma config ICS =        PGx1            // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
#pragma config JTAGEN =     OFF             // JTAG Enable bit (JTAG is disabled)
#pragma config BTSWP =      OFF             // BOOTSWP Disable (BOOTSWP instruction disabled)

// FDEVOPT1
#pragma config ALTCMPI =    DISABLE         // Alternate Comparator Input Enable bit (C1INC, C2INC, and C3INC are on their standard pin locations)
#pragma config TMPRPIN =    OFF             // Tamper Pin Enable bit (TMPRN pin function is disabled)
#pragma config SOSCHP =     ON              // SOSC High Power Enable bit (valid only when SOSCSEL = 1 (Enable SOSC high power mode (default))
#pragma config ALTVREF =    ALTVREFDIS      // Alternate Voltage Reference Location Enable bit (VREF+ and CVREF+ on RA10, VREF- and CVREF- on RA9)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.



#include "system.h"

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    ADCInit();
    INTERRUPT_Initialize();
    init_lcd();
    __delay_ms(100);
    cls();
}

void OSCILLATOR_Initialize(void)
{
    __builtin_write_OSCCONL((uint8_t) (0x0102 & 0x00FF)); // CF no clock failure; NOSC FRCPLL; SOSCEN enabled; POSCEN disabled; CLKLOCK unlocked; OSWEN Switch is Complete; IOLOCK not-active; 

    CLKDIV      = 0x3020;   // CPDIV 1:1; PLLEN enabled; DOZE 1:8; RCDIV FRC; DOZEN disabled; ROI disabled; 

    OSCTUN      = 0x0000;   // STOR disabled; STORPOL Interrupt when STOR is 1; STSIDL disabled; STLPOL Interrupt when STLOCK is 1; STLOCK disabled; STSRC SOSC; STEN disabled; TUN Center frequency; 

    REFOCONL    = 0x0000;   // ROEN disabled; ROSEL FOSC; ROSIDL disabled; ROSWEN disabled; ROOUT disabled; ROSLP disabled; 

    REFOCONH    = 0x0000;   // RODIV 0; 

    REFOTRIML   = 0x0000;   // ROTRIM 0; 

    DCOTUN      = 0x0000;   // DCOTUN 0; 

    DCOCON      = 0x0700;   // DCOFSEL 8; DCOEN disabled; 

    OSCDIV      = 0x0000;   // DIV 0; 

    OSCFDIV     = 0x0000;   // TRIM 0; 
}