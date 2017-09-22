#include "rtcc.h"

static void RTCC_Lock(void);
static bool rtccTimeInitialized;
static bool RTCCTimeInitialized(void);
static uint8_t ConvertHexToBCD(uint8_t hexvalue);
static uint8_t ConvertBCDToHex(uint8_t bcdvalue);

/**
// Section: Driver Interface Function Definitions
*/

void RTCC_Initialize(void)
{

   RTCCON1Lbits.RTCEN = 0;
   
   __builtin_write_RTCC_WRLOCK();
   
   
   if(!RTCCTimeInitialized())
   {
       // set 2017-09-22 11-09-15
       DATEH = 0x1709;    // Year/Month
       DATEL = 0x2205;    // Date/Wday
       TIMEH = 0x1109;    // hours/minutes
       TIMEL = 0x1500;    // seconds
   }

   // PWCPS 1:1; PS 1:1; CLKSEL SOSC; FDIV 0; 
   RTCCON2L = 0x0000;
   // DIV 16383; 
   RTCCON2H = 0x3FFF;
   // PWCSTAB 0; PWCSAMP 0; 
   RTCCON3L = 0x0000;

   // RTCEN enabled; OUTSEL Alarm Event; PWCPOE disabled; PWCEN disabled; WRLOCK disabled; PWCPOL disabled; TSAEN disabled; RTCOE disabled; 
   RTCCON1L = 0x8000; 
   
   RTCC_Lock();

}

static void RTCC_Lock(void)
{
    asm volatile("DISI #6");
    asm volatile("MOV #NVMKEY, W1");
    asm volatile("MOV #0x55, W2");
    asm volatile("MOV W2, [W1]");
    asm volatile("MOV #0xAA, W3");
    asm volatile("MOV W3, [W1]");
    asm volatile("BSET RTCCON1L, #11");
}

bool RTCC_TimeGet(struct RTCTime *currentTime)
{
    uint16_t register_value;
    if(RTCSTATLbits.SYNC){
        return false;
    }

 
    __builtin_write_RTCC_WRLOCK();
 
    register_value = DATEH;
    currentTime->time.year = ConvertBCDToHex((register_value & 0xFF00) >> 8);
    currentTime->time.month = ConvertBCDToHex(register_value & 0x00FF);
    
    register_value = DATEL;
    currentTime->time.monthday = ConvertBCDToHex((register_value & 0xFF00) >> 8);
    currentTime->time.weekday = ConvertBCDToHex(register_value & 0x00FF);
    
    register_value = TIMEH;
    currentTime->time.hour = ConvertBCDToHex((register_value & 0xFF00) >> 8);
    currentTime->time.minute = ConvertBCDToHex(register_value & 0x00FF);
    
    register_value = TIMEL;
    currentTime->time.second = ConvertBCDToHex((register_value & 0xFF00) >> 8);
   
    RTCC_Lock();

    return true;
}

void RTCC_TimeSet(struct RTCTime *initialTime)
{

  __builtin_write_RTCC_WRLOCK();

   RTCCON1Lbits.RTCEN = 0;
   

   // set RTCC initial time
   DATEH = (ConvertHexToBCD(initialTime->time.year) << 8) | ConvertHexToBCD(initialTime->time.month) ;  // YEAR/MONTH-1
   DATEL = (ConvertHexToBCD(initialTime->time.monthday) << 8) | ConvertHexToBCD(initialTime->time.weekday) ;  // /DAY-1/WEEKDAY
   TIMEH = (ConvertHexToBCD(initialTime->time.hour) << 8)  | ConvertHexToBCD(initialTime->time.minute); // /HOURS/MINUTES
   TIMEL = (ConvertHexToBCD(initialTime->time.second) << 8) ;   // SECOND
           
   // Enable RTCC, clear RTCWREN         
   RTCCON1Lbits.RTCEN = 1;  
   RTCC_Lock();

}

bool RTCC_BCDTimeGet(RTCTime *currentTime)
{
    uint16_t register_value;
    if(RTCSTATLbits.SYNC){
        return false;
    }


    __builtin_write_RTCC_WRLOCK();
   
    register_value = DATEH;
    currentTime->time.year = (register_value & 0xFF00) >> 8;
    currentTime->time.month = register_value & 0x00FF;
    
    register_value = DATEL;
    currentTime->time.monthday = (register_value & 0xFF00) >> 8;
    currentTime->time.weekday = register_value & 0x00FF;
    
    register_value = TIMEH;
    currentTime->time.hour = (register_value & 0xFF00) >> 8;
    currentTime->time.minute = register_value & 0x00FF;
   
    register_value = TIMEL;
    currentTime->time.second = (register_value & 0xFF00) >> 8;
   
    RTCC_Lock();

    return true;
}

void RTCC_BCDTimeSet(RTCTime *initialTime)
{

   __builtin_write_RTCC_WRLOCK();

   RTCCON1Lbits.RTCEN = 0;
   

   // set RTCC initial time
   DATEH = (initialTime->time.year << 8) | (initialTime->time.month) ;  // YEAR/MONTH-1
   DATEL = (initialTime->time.monthday << 8) | (initialTime->time.weekday) ;  // /DAY-1/WEEKDAY
   TIMEH = (initialTime->time.hour << 8) | (initialTime->time.minute); // /HOURS/MINUTES
   TIMEL = (initialTime->time.second << 8);   // SECONDS   
           
   // Enable RTCC, clear RTCWREN         
   RTCCON1Lbits.RTCEN = 1;  
   RTCC_Lock();

}

/**
 This function implements RTCC_TimeReset.This function is used to
 used by application to reset the RTCC value and reinitialize RTCC value.
*/
void RTCC_TimeReset(bool reset)
{
    rtccTimeInitialized = reset;
}

static bool RTCCTimeInitialized(void)
{
    return(rtccTimeInitialized);
}

void RTCC_TimestampAEventManualSet(void)
{
    RTCSTATLbits.TSAEVT = 1;
}

bool RTCC_TimestampADataGet(struct RTCTime *currentTime)
{
    uint16_t register_value;
    if(!RTCSTATLbits.TSAEVT){
        return false;
    }
  
    register_value = TSADATEH;
    currentTime->time.year = ConvertBCDToHex((register_value & 0xFF00) >> 8);
    currentTime->time.month = ConvertBCDToHex(register_value & 0x00FF);
    
    register_value = TSADATEL;
    currentTime->time.monthday = ConvertBCDToHex((register_value & 0xFF00) >> 8);
    currentTime->time.weekday = ConvertBCDToHex(register_value & 0x00FF);
    
    register_value = TSATIMEH;
    currentTime->time.hour = ConvertBCDToHex((register_value & 0xFF00) >> 8);
    currentTime->time.minute = ConvertBCDToHex(register_value & 0x00FF);
    
    register_value = TSATIMEL;
    currentTime->time.second = ConvertBCDToHex((register_value & 0xFF00) >> 8);
   
    RTCSTATLbits.TSAEVT = 0;

    return true;
}



bool RTCC_TimestampA_BCDDataGet(RTCTime *currentTime)
{
    uint16_t register_value;
    if(!RTCSTATLbits.TSAEVT){
        return false;
    }
  
    register_value = TSADATEH;
    currentTime->time.year = (register_value & 0xFF00) >> 8;
    currentTime->time.month = (register_value & 0x00FF);
    
    register_value = TSADATEL;
    currentTime->time.monthday = (register_value & 0xFF00) >> 8;
    currentTime->time.weekday = (register_value & 0x00FF);
    
    register_value = TSATIMEH;
    currentTime->time.hour = (register_value & 0xFF00) >> 8;
    currentTime->time.minute = (register_value & 0x00FF);
    
    register_value = TSATIMEL;
    currentTime->time.second = (register_value & 0xFF00) >> 8;
   
    RTCSTATLbits.TSAEVT = 0;

    return true;
}



static uint8_t ConvertHexToBCD(uint8_t hexvalue)
{
    uint8_t bcdvalue;
    bcdvalue = (hexvalue / 10) << 4;
    bcdvalue = bcdvalue | (hexvalue % 10);
    return (bcdvalue);
}

static uint8_t ConvertBCDToHex(uint8_t bcdvalue)
{
    uint8_t hexvalue;
    hexvalue = (((bcdvalue & 0xF0) >> 4)* 10) + (bcdvalue & 0x0F);
    return hexvalue;
}


/* Function:
    bool RTCC_Task(void)

  Summary:
    Status function which returns the RTCC interrupt flag status

  Description:
    This is the status function for the RTCC peripheral. 
*/
bool RTCC_Task(void)
{
    bool status;
    status = IFS3bits.RTCIF;
    if( IFS3bits.RTCIF)
    {
       IFS3bits.RTCIF = false;
    }
    return status;
}