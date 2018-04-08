#include "pin_manager.h"

void PIN_MANAGER_Initialize(void)
{
    // *************************************************************************
    // * Setting the Output Latch SFR(s)
    // *************************************************************************
    LATB = 0x0000;
    LATC = 0x0000;
    LATD = 0x0000;
    LATE = 0x0000;
    LATF = 0x0000;
    LATG = 0x0000;

    // *************************************************************************
    // * Setting the GPIO Direction SFR(s)
    // *************************************************************************
    TRISB = 0x1FC0;                         // Inputs 6,7,8,9,10,11,12
    TRISC = 0x0000;
    TRISD = 0x0000;
    TRISE = 0x0000;
    TRISF = 0x0000;
    TRISG = 0x0000;

    // *************************************************************************
    // * Setting the Weak Pull Up and Weak Pull Down SFR(s)
    // *************************************************************************
    IOCPDB = 0x0000;
    IOCPDC = 0x0000;
    IOCPDD = 0x0000;
    IOCPDE = 0x0000;
    IOCPDF = 0x0000;
    IOCPDG = 0x0000;
    IOCPUB = 0x0000;
    IOCPUC = 0x0000;
    IOCPUD = 0x0000;
    IOCPUE = 0x0000;
    IOCPUF = 0x0000;
    IOCPUG = 0x0000;

    //**************************************************************************
    // * Setting the Open Drain SFR(s)
    // *************************************************************************
    ODCB = 0x0000;
    ODCC = 0x0000;
    ODCD = 0x0000;
    ODCE = 0x0000;
    ODCF = 0x0000;
    ODCG = 0x0000;

    // *************************************************************************
    // * Setting the Analog/Digital Configuration SFR(s)
    // *************************************************************************
    ANSB = 0xDFC0;                          // AN 6,7,8,9,10,11,12,14,15 14 & 15 for Touch Interface
    ANSC = 0x0000;
    ANSD = 0x0000;
    ANSE = 0x0000;
    ANSG = 0x0000;
}
