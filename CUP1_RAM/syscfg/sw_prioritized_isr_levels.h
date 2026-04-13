//###########################################################################
//
// FILE:    sw_prioritized_isr_levels.h
//
// TITLE:   Software Prioritized Interrupt Service Routine Level
//          definitions.
//
//#############################################################################
#ifndef SW_PRIORITZIED_ISR_LEVELS_H
#define SW_PRIORITZIED_ISR_LEVELS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define TRACE_SIZE 50

#ifdef TRACE_ISR_ENABLE
extern uint16_t  traceISR[TRACE_SIZE];
extern uint16_t  traceISRIndex;
#endif


//
// Mask for interrupt groups
//
#define M_INT1      0x0001  // INT1 Mask
#define M_INT2      0x0002  // INT2 Mask
#define M_INT3      0x0004  // INT3 Mask
#define M_INT4      0x0008  // INT4 Mask
#define M_INT5      0x0010  // INT5 Mask
#define M_INT6      0x0020  // INT6 Mask
#define M_INT7      0x0040  // INT7 Mask
#define M_INT8      0x0080  // INT8 Mask
#define M_INT9      0x0100  // INT9 Mask
#define M_INT10     0x0200  // INT10 Mask
#define M_INT11     0x0400  // INT11 Mask
#define M_INT12     0x0800  // INT12 Mask
#define M_INT13     0x1000  // INT13 Mask
#define M_INT14     0x2000  // INT14 Mask
#define M_DLOG      0x4000  // DLOGINT Mask
#define M_RTOS      0x8000  // RTOSINT Mask

//
// Interrupt Enable Register Allocation:
// Interrupts can be enabled/disabled using the CPU interrupt enable register
// (IER) and the PIE interrupt enable registers (PIEIER1 to PIEIER12).
//

//
// Set "Global" Interrupt Priority Level (IER register):
//
// The user must set the appropriate priority level for each of the CPU
// interrupts. This is termed as the "global" priority. The priority level
// must be a number between 1 (highest) to 16 (lowest). A value of 0 must
// be entered for reserved interrupts or interrupts that are not used.
//
// Note: The priority levels below are used to calculate the IER register
//       interrupt masks MINT1 to MINT16.
//
// 0  = not used
// 1  = highest priority
// ...
// 16 = lowest priority
//
#define INT1PL  1   // Global Priority for Group 1 interrupts
#define INT2PL  0   // Global Priority for Group 2 interrupts
#define INT3PL  0   // Global Priority for Group 3 interrupts
#define INT4PL  0   // Global Priority for Group 4 interrupts
#define INT5PL  0   // Global Priority for Group 5 interrupts
#define INT6PL  0   // Global Priority for Group 6 interrupts
#define INT7PL  0   // Global Priority for Group 7 interrupts
#define INT8PL  0   // Global Priority for Group 8 interrupts
#define INT9PL  2   // Global Priority for Group 9 interrupts
#define INT10PL  0   // Global Priority for Group 10 interrupts
#define INT11PL  0   // Global Priority for Group 11 interrupts
#define INT12PL  0   // Global Priority for Group 12 interrupts
#define INT13PL  0   // Global Priority for INT13 (Timer 1 Interrupt)
#define INT14PL  5   // Global Priority for INT14 (Timer 2 Interrupt)
#define INT15PL  0   // Global Priority for DATALOG
#define INT16PL  0   // Global Priority for RTOSINT


//
// Set "Group" Interrupt Priority Level (PIEIER1 to PIEIER12 registers):
//
// The user must set the appropriate priority level for each of the PIE
// interrupts. This is termed as the "group" priority. The priority level
// must be a number between 1 (highest) to 16 (lowest). A value of 0 must
// be entered for reserved interrupts or interrupts that are not used.
//
// Note: The priority levels below are used to calculate the following
//       PIEIER register interrupt masks:
//       MG1_1 to MG1_16
//       MG2_1 to MG2_16
//       MG3_1 to MG3_16
//       MG4_1 to MG4_16
//       MG5_1 to MG5_16
//       MG6_1 to MG6_16
//       MG7_1 to MG7_16
//       MG8_1 to MG8_16
//       MG9_1 to MG9_16
//       MG10_1 to MG10_16
//       MG11_1 to MG11_16
//       MG12_1 to MG12_16
//
// 0  = not used
// 1  = highest priority
// ...
// 16  = lowest priority
//
#define G1_1PL         1  // ADCA Interrupt 1
#define G1_2PL         0  // ADCB Interrupt 1
#define G1_3PL         0  // ADCC Interrupt 1
#define G1_4PL         0  // XINT1 Interrupt
#define G1_5PL         0  // XINT2 Interrupt
#define G1_6PL         0  // Reserved
#define G1_7PL         0  // Timer 0 Interrupt
#define G1_8PL         0  // Halt Wakeup/Watchdog Interrupt
#define G1_9PL         0  // Reserved
#define G1_10PL        0  // Reserved
#define G1_11PL        0  // Reserved
#define G1_12PL        0  // Reserved
#define G1_13PL        0  // Reserved
#define G1_14PL        0  // Reserved
#define G1_15PL        0  // Reserved
#define G1_16PL        0  // Reserved

#define G2_1PL         0  // ePWM1 Trip Zone Interrupt
#define G2_2PL         0  // ePWM2 Trip Zone Interrupt
#define G2_3PL         0  // ePWM3 Trip Zone Interrupt
#define G2_4PL         0  // ePWM4 Trip Zone Interrupt
#define G2_5PL         0  // ePWM5 Trip Zone Interrupt
#define G2_6PL         0  // ePWM6 Trip Zone Interrupt
#define G2_7PL         0  // ePWM7 Trip Zone Interrupt
#define G2_8PL         0  // ePWM8 Trip Zone Interrupt
#define G2_9PL         0  // Reserved
#define G2_10PL        0  // Reserved
#define G2_11PL        0  // Reserved
#define G2_12PL        0  // Reserved
#define G2_13PL        0  // Reserved
#define G2_14PL        0  // Reserved
#define G2_15PL        0  // Reserved
#define G2_16PL        0  // Reserved

#define G3_1PL         0  // ePWM1 Interrupt
#define G3_2PL         0  // ePWM2 Interrupt
#define G3_3PL         0  // ePWM3 Interrupt
#define G3_4PL         0  // ePWM4 Interrupt
#define G3_5PL         0  // ePWM5 Interrupt
#define G3_6PL         0  // ePWM6 Interrupt
#define G3_7PL         0  // ePWM7 Interrupt
#define G3_8PL         0  // ePWM8 Interrupt
#define G3_9PL         0  // Reserved
#define G3_10PL        0  // Reserved
#define G3_11PL        0  // Reserved
#define G3_12PL        0  // Reserved
#define G3_13PL        0  // Reserved
#define G3_14PL        0  // Reserved
#define G3_15PL        0  // Reserved
#define G3_16PL        0  // Reserved

#define G4_1PL         0  // eCAP1 Interrupt
#define G4_2PL         0  // eCAP2 Interrupt
#define G4_3PL         0  // eCAP3 Interrupt
#define G4_4PL         0  // eCAP4 Interrupt
#define G4_5PL         0  // eCAP5 Interrupt
#define G4_6PL         0  // eCAP6 Interrupt
#define G4_7PL         0  // eCAP7 Interrupt
#define G4_8PL         0  // Reserved
#define G4_9PL         0  // Reserved
#define G4_10PL        0  // Reserved
#define G4_11PL        0  // Reserved
#define G4_12PL        0  // Reserved
#define G4_13PL        0  // Reserved
#define G4_14PL        0  // eCAP6_2 Interrupt
#define G4_15PL        0  // eCAP7_2 Interrupt
#define G4_16PL        0  // Reserved

#define G5_1PL         0  // eQEP1 Interrupt
#define G5_2PL         0  // eQEP2 Interrupt
#define G5_3PL         0  // Reserved
#define G5_4PL         0  // Reserved
#define G5_5PL         0  // CLB1 (Reconfigurable Logic) Interrupt
#define G5_6PL         0  // CLB2 (Reconfigurable Logic) Interrupt
#define G5_7PL         0  // CLB3 (Reconfigurable Logic) Interrupt
#define G5_8PL         0  // CLB4 (Reconfigurable Logic) Interrupt
#define G5_9PL         0  // SDFM1 Interrupt
#define G5_10PL        0  // Reserved
#define G5_11PL        0  // Reserved
#define G5_12PL        0  // Reserved
#define G5_13PL        0  // SDFM1DR1 Interrupt
#define G5_14PL        0  // SDFM1DR2 Interrupt
#define G5_15PL        0  // SDFM1DR3 Interrupt
#define G5_16PL        0  // SDFM1DR4 Interrupt

#define G6_1PL         0  // SPIA Receive Interrupt
#define G6_2PL         0  // SPIA Transmit Interrupt
#define G6_3PL         0  // SPIB Receive Interrupt
#define G6_4PL         0  // SPIB Transmit Interrupt
#define G6_5PL         0  // Reserved
#define G6_6PL         0  // Reserved
#define G6_7PL         0  // Reserved
#define G6_8PL         0  // Reserved
#define G6_9PL         0  // Reserved
#define G6_10PL        0  // Reserved
#define G6_11PL        0  // Reserved
#define G6_12PL        0  // Reserved
#define G6_13PL        0  // Reserved
#define G6_14PL        0  // Reserved
#define G6_15PL        0  // Reserved
#define G6_16PL        0  // Reserved

#define G7_1PL         0  // DMA Channel 1 Interrupt
#define G7_2PL         0  // DMA Channel 2 Interrupt
#define G7_3PL         0  // DMA Channel 3 Interrupt
#define G7_4PL         0  // DMA Channel 4 Interrupt
#define G7_5PL         0  // DMA Channel 5 Interrupt
#define G7_6PL         0  // DMA Channel 6 Interrupt
#define G7_7PL         0  // Reserved
#define G7_8PL         0  // Reserved
#define G7_9PL         0  // Reserved
#define G7_10PL        0  // Reserved
#define G7_11PL        0  // FSITXA_INT1 Interrupt
#define G7_12PL        0  // FSITXA_INT2 Interrupt
#define G7_13PL        0  // FSIRXA_INT1 Interrupt
#define G7_14PL        0  // FSIRXA_INT2 Interrupt
#define G7_15PL        0  // CLA1PROMCRC Interrupt
#define G7_16PL        0  // DCC Interrupt

#define G8_1PL         0  // I2CA Interrupt 1
#define G8_2PL         0  // I2CA Interrupt 2
#define G8_3PL         0  // Reserved
#define G8_4PL         0  // Reserved
#define G8_5PL         0  // Reserved
#define G8_6PL         0  // Reserved
#define G8_7PL         0  // Reserved
#define G8_8PL         0  // Reserved
#define G8_9PL         0  // LINA Interrupt0
#define G8_10PL        0  // LINA Interrupt1
#define G8_11PL        0  // Reserved
#define G8_12PL        0  // Reserved
#define G8_13PL        0  // PMBUSA Interrupt
#define G8_14PL        0  // Reserved
#define G8_15PL        0  // Reserved
#define G8_16PL        0  // Reserved

#define G9_1PL         1  // SCIA Receive Interrupt
#define G9_2PL         0  // SCIA Transmit Interrupt
#define G9_3PL         2  // SCIB Receive Interrupt
#define G9_4PL         0  // SCIB Transmit Interrupt
#define G9_5PL         0  // CANA Interrupt 0
#define G9_6PL         0  // CANA Interrupt 1
#define G9_7PL         0  // CANB Interrupt 0
#define G9_8PL         0  // CANB Interrupt 1
#define G9_9PL         0  // Reserved
#define G9_10PL        0  // Reserved
#define G9_11PL        0  // Reserved
#define G9_12PL        0  // Reserved
#define G9_13PL        0  // Reserved
#define G9_14PL        0  // Reserved
#define G9_15PL        0  // Reserved
#define G9_16PL        0  // Reserved

#define G10_1PL        0  // ADCA Event Interrupt
#define G10_2PL        0  // ADCA Interrupt 2
#define G10_3PL        0  // ADCA Interrupt 3
#define G10_4PL        0  // ADCA Interrupt 4
#define G10_5PL        0  // ADCB Event Interrupt
#define G10_6PL        0  // ADCB Interrupt 2
#define G10_7PL        0  // ADCB Interrupt 3
#define G10_8PL        0  // ADCB Interrupt 4
#define G10_9PL        0  // ADCC Event Interrupt
#define G10_10PL       0  // ADCC Interrupt 2
#define G10_11PL       0  // ADCC Interrupt 3
#define G10_12PL       0  // ADCC Interrupt 4
#define G10_13PL       0  // Reserved
#define G10_14PL       0  // Reserved
#define G10_15PL       0  // Reserved
#define G10_16PL       0  // Reserved

#define G11_1PL        0  // CLA1 Interrupt 1
#define G11_2PL        0  // CLA1 Interrupt 2
#define G11_3PL        0  // CLA1 Interrupt 3
#define G11_4PL        0  // CLA1 Interrupt 4
#define G11_5PL        0  // CLA1 Interrupt 5
#define G11_6PL        0  // CLA1 Interrupt 6
#define G11_7PL        0  // CLA1 Interrupt 7
#define G11_8PL        0  // CLA1 Interrupt 8
#define G11_9PL        0  // Reserved
#define G11_10PL       0  // Reserved
#define G11_11PL       0  // Reserved
#define G11_12PL       0  // Reserved
#define G11_13PL       0  // Reserved
#define G11_14PL       0  // Reserved
#define G11_15PL       0  // Reserved
#define G11_16PL       0  // Reserved

#define G12_1PL        0  // XINT3 Interrupt
#define G12_2PL        0  // XINT4 Interrupt
#define G12_3PL        0  // XINT5 Interrupt
#define G12_4PL        0  // PBIST Interrupt
#define G12_5PL        0  // Flash Wrapper Operation Done Interrupt
#define G12_6PL        0  // Reserved
#define G12_7PL        0  // FPU Overflow Interrupt
#define G12_8PL        0  // FPU Underflow Interrupt
#define G12_9PL        0  // Reserved
#define G12_10PL       0  // RAM Correctable Error Interrupt
#define G12_11PL       0  // Flash Correctable Error Interrupt
#define G12_12PL       0  // RAM Access Violation Interrupt
#define G12_13PL       0  // System PLL Slip Interrupt
#define G12_14PL       0  // Reserved
#define G12_15PL       0  // CLA Overflow Interrupt
#define G12_16PL       0  // CLA Underflow Interrupt


//
// Include the header file with software interrupt prioritization logic
//
#include "device_support/f28004x/common/include/sw_interrupt_prioritization_logic.h"

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif // eof

//
// End of file
//

