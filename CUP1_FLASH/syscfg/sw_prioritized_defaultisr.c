//###########################################################################
//
// FILE:    sw_prioritized_defaultisr.c
//
// TITLE:   Default Software Prioritized Interrupt Service Routines.
//
//###########################################################################

//
// NOTE !!!!
// The application must define the ISR routines. The following functions can be
// used a reference.
// Any updates done to this file will be overwritten by the Syscfg tool
//

//
// Interrupts in the order of priority (Highest to Lowest) :
//      - ADCA Interrupt 1 (PIE Channel 1.1)             GlobalPriority = 1   GroupPriority = 1
//      - SCIA Receive Interrupt (PIE Channel 9.1)       GlobalPriority = 2   GroupPriority = 1
//      - SCIB Receive Interrupt (PIE Channel 9.3)       GlobalPriority = 2   GroupPriority = 2
//      - CPU Timer 2 Interrupt (INT14)                  GlobalPriority = 5   GroupPriority = 0
//

#include "sw_prioritized_isr_levels.h"


#ifdef TRACE_ISR_ENABLE

//
// This array will be used as a trace to check the order that the interrupts were serviced
//
uint16_t  traceISR[TRACE_SIZE];

//
// Index to update an element in the trace buffer
//
uint16_t  traceISRIndex = 0;

#endif


#if 0

//
//  ADCA Interrupt 1 (PIE Channel 1.1)
//
__interrupt void ADCA1_ISR(void)
{
    //
    // Save IER register on stack
    //
    volatile uint16_t tempPIEIER = HWREGH(PIECTRL_BASE + PIE_O_IER1);

    //
    // Set the global and group priority to allow CPU interrupts
    // with higher priority
    //
    IER |= M_INT1;
    IER &= MINT1;
    HWREGH(PIECTRL_BASE + PIE_O_IER1) &= MG1_1;

    //
    // Enable Interrupts
    //
    Interrupt_clearACKGroup(0xFFFFU);
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here ..
    //


    //
    // Disable interrupts and restore registers saved:
    //
    DINT;
    HWREGH(PIECTRL_BASE + PIE_O_IER1) = tempPIEIER;

    #ifdef TRACE_ISR_ENABLE
        //
        //  Add ISR to Trace
        //
        traceISR[traceISRIndex % TRACE_SIZE] = 0x0101;
        traceISRIndex++;
    #endif
}


//
//  SCIA Receive Interrupt (PIE Channel 9.1)
//
__interrupt void SCIA_RX_ISR(void)
{
    //
    // Save IER register on stack
    //
    volatile uint16_t tempPIEIER = HWREGH(PIECTRL_BASE + PIE_O_IER9);

    //
    // Set the global and group priority to allow CPU interrupts
    // with higher priority
    //
    IER |= M_INT9;
    IER &= MINT9;
    HWREGH(PIECTRL_BASE + PIE_O_IER9) &= MG9_1;

    //
    // Enable Interrupts
    //
    Interrupt_clearACKGroup(0xFFFFU);
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here ..
    //


    //
    // Disable interrupts and restore registers saved:
    //
    DINT;
    HWREGH(PIECTRL_BASE + PIE_O_IER9) = tempPIEIER;

    #ifdef TRACE_ISR_ENABLE
        //
        //  Add ISR to Trace
        //
        traceISR[traceISRIndex % TRACE_SIZE] = 0x0901;
        traceISRIndex++;
    #endif
}


//
//  SCIB Receive Interrupt (PIE Channel 9.3)
//
__interrupt void SCIB_RX_ISR(void)
{
    //
    // Save IER register on stack
    //
    volatile uint16_t tempPIEIER = HWREGH(PIECTRL_BASE + PIE_O_IER9);

    //
    // Set the global and group priority to allow CPU interrupts
    // with higher priority
    //
    IER |= M_INT9;
    IER &= MINT9;
    HWREGH(PIECTRL_BASE + PIE_O_IER9) &= MG9_3;

    //
    // Enable Interrupts
    //
    Interrupt_clearACKGroup(0xFFFFU);
    __asm("  NOP");
    EINT;

    //
    // Insert ISR Code here ..
    //


    //
    // Disable interrupts and restore registers saved:
    //
    DINT;
    HWREGH(PIECTRL_BASE + PIE_O_IER9) = tempPIEIER;

    #ifdef TRACE_ISR_ENABLE
        //
        //  Add ISR to Trace
        //
        traceISR[traceISRIndex % TRACE_SIZE] = 0x0903;
        traceISRIndex++;
    #endif
}


//
//  CPU Timer 2 Interrupt (INT14)
//
__interrupt void TIMER2_ISR(void)
{
    //
    // Set the global priority to allow CPU interrupts with higher priority
    //
    IER &= MINT14;
    EINT;

    //
    // Insert ISR Code here ..
    //

    //
    // Disable Interrupts
    //
    DINT;

    #ifdef TRACE_ISR_ENABLE
        //
        //  Add ISR to Trace
        //
        traceISR[traceISRIndex % TRACE_SIZE] = 0x1400;
        traceISRIndex++;
    #endif
}


#endif
