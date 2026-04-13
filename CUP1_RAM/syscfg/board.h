/*
 * Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef BOARD_H
#define BOARD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************

//
// EPWM1 -> myEPWM1 Pinmux
//
//
// EPWM1_A - GPIO Settings
//
#define GPIO_PIN_EPWM1_A 0
#define myEPWM1_EPWMA_GPIO 0
#define myEPWM1_EPWMA_PIN_CONFIG GPIO_0_EPWM1_A
//
// EPWM1_B - GPIO Settings
//
#define GPIO_PIN_EPWM1_B 1
#define myEPWM1_EPWMB_GPIO 1
#define myEPWM1_EPWMB_PIN_CONFIG GPIO_1_EPWM1_B

//
// EPWM2 -> myEPWM2 Pinmux
//
//
// EPWM2_A - GPIO Settings
//
#define GPIO_PIN_EPWM2_A 2
#define myEPWM2_EPWMA_GPIO 2
#define myEPWM2_EPWMA_PIN_CONFIG GPIO_2_EPWM2_A
//
// EPWM2_B - GPIO Settings
//
#define GPIO_PIN_EPWM2_B 3
#define myEPWM2_EPWMB_GPIO 3
#define myEPWM2_EPWMB_PIN_CONFIG GPIO_3_EPWM2_B

//
// EPWM3 -> myEPWM3 Pinmux
//
//
// EPWM3_A - GPIO Settings
//
#define GPIO_PIN_EPWM3_A 4
#define myEPWM3_EPWMA_GPIO 4
#define myEPWM3_EPWMA_PIN_CONFIG GPIO_4_EPWM3_A
//
// EPWM3_B - GPIO Settings
//
#define GPIO_PIN_EPWM3_B 5
#define myEPWM3_EPWMB_GPIO 5
#define myEPWM3_EPWMB_PIN_CONFIG GPIO_5_EPWM3_B

//
// EPWM4 -> myEPWM4 Pinmux
//
//
// EPWM4_A - GPIO Settings
//
#define GPIO_PIN_EPWM4_A 6
#define myEPWM4_EPWMA_GPIO 6
#define myEPWM4_EPWMA_PIN_CONFIG GPIO_6_EPWM4_A
//
// EPWM4_B - GPIO Settings
//
#define GPIO_PIN_EPWM4_B 7
#define myEPWM4_EPWMB_GPIO 7
#define myEPWM4_EPWMB_PIN_CONFIG GPIO_7_EPWM4_B
//
// GPIO23 - GPIO Settings
//
#define LED_RED_GPIO_PIN_CONFIG GPIO_23_GPIO23
//
// GPIO34 - GPIO Settings
//
#define LED_GREEN_GPIO_PIN_CONFIG GPIO_34_GPIO34
//
// GPIO13 - GPIO Settings
//
#define DRV_GPIO_PIN_CONFIG GPIO_13_GPIO13
//
// GPIO30 - GPIO Settings
//
#define TIME_WATCH1_GPIO_PIN_CONFIG GPIO_30_GPIO30
//
// GPIO39 - GPIO Settings
//
#define TIME_WATCH2_GPIO_PIN_CONFIG GPIO_39_GPIO39
//
// GPIO16 - GPIO Settings
//
#define DIS_GPIO_PIN_CONFIG GPIO_16_GPIO16

//
// SCIA -> mySCI0 Pinmux
//
//
// SCIA_RX - GPIO Settings
//
#define GPIO_PIN_SCIA_RX 28
#define mySCI0_SCIRX_GPIO 28
#define mySCI0_SCIRX_PIN_CONFIG GPIO_28_SCIA_RX
//
// SCIA_TX - GPIO Settings
//
#define GPIO_PIN_SCIA_TX 29
#define mySCI0_SCITX_GPIO 29
#define mySCI0_SCITX_PIN_CONFIG GPIO_29_SCIA_TX

//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
#define myADCA_BASE ADCA_BASE
#define myADCA_RESULT_BASE ADCARESULT_BASE
#define myADCA_ADCA0 ADC_SOC_NUMBER0
#define myADCA_FORCE_ADCA0 ADC_FORCE_SOC0
#define myADCA_SAMPLE_WINDOW_ADCA0 800
#define myADCA_TRIGGER_SOURCE_ADCA0 ADC_TRIGGER_EPWM1_SOCB
#define myADCA_CHANNEL_ADCA0 ADC_CH_ADCIN0
#define myADCA_ADCA1 ADC_SOC_NUMBER1
#define myADCA_FORCE_ADCA1 ADC_FORCE_SOC1
#define myADCA_SAMPLE_WINDOW_ADCA1 400
#define myADCA_TRIGGER_SOURCE_ADCA1 ADC_TRIGGER_EPWM1_SOCB
#define myADCA_CHANNEL_ADCA1 ADC_CH_ADCIN8
#define myADCA_ADCA2 ADC_SOC_NUMBER2
#define myADCA_FORCE_ADCA2 ADC_FORCE_SOC2
#define myADCA_SAMPLE_WINDOW_ADCA2 400
#define myADCA_TRIGGER_SOURCE_ADCA2 ADC_TRIGGER_EPWM1_SOCB
#define myADCA_CHANNEL_ADCA2 ADC_CH_ADCIN3
#define myADCA_ADCA3 ADC_SOC_NUMBER3
#define myADCA_FORCE_ADCA3 ADC_FORCE_SOC3
#define myADCA_SAMPLE_WINDOW_ADCA3 400
#define myADCA_TRIGGER_SOURCE_ADCA3 ADC_TRIGGER_EPWM1_SOCB
#define myADCA_CHANNEL_ADCA3 ADC_CH_ADCIN5
#define myADCA_ADCA4 ADC_SOC_NUMBER4
#define myADCA_FORCE_ADCA4 ADC_FORCE_SOC4
#define myADCA_SAMPLE_WINDOW_ADCA4 400
#define myADCA_TRIGGER_SOURCE_ADCA4 ADC_TRIGGER_EPWM1_SOCB
#define myADCA_CHANNEL_ADCA4 ADC_CH_ADCIN1
#define myADCA_ADCA5 ADC_SOC_NUMBER5
#define myADCA_FORCE_ADCA5 ADC_FORCE_SOC5
#define myADCA_SAMPLE_WINDOW_ADCA5 400
#define myADCA_TRIGGER_SOURCE_ADCA5 ADC_TRIGGER_EPWM1_SOCA
#define myADCA_CHANNEL_ADCA5 ADC_CH_ADCIN0
#define myADCA_ADCA6 ADC_SOC_NUMBER6
#define myADCA_FORCE_ADCA6 ADC_FORCE_SOC6
#define myADCA_SAMPLE_WINDOW_ADCA6 400
#define myADCA_TRIGGER_SOURCE_ADCA6 ADC_TRIGGER_EPWM1_SOCA
#define myADCA_CHANNEL_ADCA6 ADC_CH_ADCIN8
#define myADCA_SOC7 ADC_SOC_NUMBER7
#define myADCA_FORCE_SOC7 ADC_FORCE_SOC7
#define myADCA_SAMPLE_WINDOW_SOC7 400
#define myADCA_TRIGGER_SOURCE_SOC7 ADC_TRIGGER_EPWM1_SOCA
#define myADCA_CHANNEL_SOC7 ADC_CH_ADCIN3
#define myADCA_SOC8 ADC_SOC_NUMBER8
#define myADCA_FORCE_SOC8 ADC_FORCE_SOC8
#define myADCA_SAMPLE_WINDOW_SOC8 400
#define myADCA_TRIGGER_SOURCE_SOC8 ADC_TRIGGER_EPWM1_SOCA
#define myADCA_CHANNEL_SOC8 ADC_CH_ADCIN5
#define myADCA_SOC9 ADC_SOC_NUMBER9
#define myADCA_FORCE_SOC9 ADC_FORCE_SOC9
#define myADCA_SAMPLE_WINDOW_SOC9 400
#define myADCA_TRIGGER_SOURCE_SOC9 ADC_TRIGGER_EPWM1_SOCA
#define myADCA_CHANNEL_SOC9 ADC_CH_ADCIN1
void myADCA_init();

#define myADCC_BASE ADCC_BASE
#define myADCC_RESULT_BASE ADCCRESULT_BASE
#define myADCC_ADCC0 ADC_SOC_NUMBER0
#define myADCC_FORCE_ADCC0 ADC_FORCE_SOC0
#define myADCC_SAMPLE_WINDOW_ADCC0 800
#define myADCC_TRIGGER_SOURCE_ADCC0 ADC_TRIGGER_EPWM1_SOCB
#define myADCC_CHANNEL_ADCC0 ADC_CH_ADCIN5
#define myADCC_ADCC1 ADC_SOC_NUMBER1
#define myADCC_FORCE_ADCC1 ADC_FORCE_SOC1
#define myADCC_SAMPLE_WINDOW_ADCC1 400
#define myADCC_TRIGGER_SOURCE_ADCC1 ADC_TRIGGER_EPWM1_SOCB
#define myADCC_CHANNEL_ADCC1 ADC_CH_ADCIN4
#define myADCC_ADCC2 ADC_SOC_NUMBER2
#define myADCC_FORCE_ADCC2 ADC_FORCE_SOC2
#define myADCC_SAMPLE_WINDOW_ADCC2 400
#define myADCC_TRIGGER_SOURCE_ADCC2 ADC_TRIGGER_EPWM1_SOCB
#define myADCC_CHANNEL_ADCC2 ADC_CH_ADCIN2
#define myADCC_ADCC3 ADC_SOC_NUMBER3
#define myADCC_FORCE_ADCC3 ADC_FORCE_SOC3
#define myADCC_SAMPLE_WINDOW_ADCC3 400
#define myADCC_TRIGGER_SOURCE_ADCC3 ADC_TRIGGER_EPWM1_SOCB
#define myADCC_CHANNEL_ADCC3 ADC_CH_ADCIN1
#define myADCC_ADCC4 ADC_SOC_NUMBER4
#define myADCC_FORCE_ADCC4 ADC_FORCE_SOC4
#define myADCC_SAMPLE_WINDOW_ADCC4 400
#define myADCC_TRIGGER_SOURCE_ADCC4 ADC_TRIGGER_EPWM1_SOCA
#define myADCC_CHANNEL_ADCC4 ADC_CH_ADCIN5
#define myADCC_ADCC5 ADC_SOC_NUMBER5
#define myADCC_FORCE_ADCC5 ADC_FORCE_SOC5
#define myADCC_SAMPLE_WINDOW_ADCC5 400
#define myADCC_TRIGGER_SOURCE_ADCC5 ADC_TRIGGER_EPWM1_SOCA
#define myADCC_CHANNEL_ADCC5 ADC_CH_ADCIN4
#define myADCC_ADCC6 ADC_SOC_NUMBER6
#define myADCC_FORCE_ADCC6 ADC_FORCE_SOC6
#define myADCC_SAMPLE_WINDOW_ADCC6 400
#define myADCC_TRIGGER_SOURCE_ADCC6 ADC_TRIGGER_EPWM1_SOCA
#define myADCC_CHANNEL_ADCC6 ADC_CH_ADCIN2
#define myADCC_SOC7 ADC_SOC_NUMBER7
#define myADCC_FORCE_SOC7 ADC_FORCE_SOC7
#define myADCC_SAMPLE_WINDOW_SOC7 400
#define myADCC_TRIGGER_SOURCE_SOC7 ADC_TRIGGER_EPWM1_SOCA
#define myADCC_CHANNEL_SOC7 ADC_CH_ADCIN1
void myADCC_init();

#define myADCB_BASE ADCB_BASE
#define myADCB_RESULT_BASE ADCBRESULT_BASE
#define myADCB_ADCB0 ADC_SOC_NUMBER0
#define myADCB_FORCE_ADCB0 ADC_FORCE_SOC0
#define myADCB_SAMPLE_WINDOW_ADCB0 800
#define myADCB_TRIGGER_SOURCE_ADCB0 ADC_TRIGGER_EPWM1_SOCB
#define myADCB_CHANNEL_ADCB0 ADC_CH_ADCIN4
#define myADCB_ADCB1 ADC_SOC_NUMBER1
#define myADCB_FORCE_ADCB1 ADC_FORCE_SOC1
#define myADCB_SAMPLE_WINDOW_ADCB1 400
#define myADCB_TRIGGER_SOURCE_ADCB1 ADC_TRIGGER_EPWM1_SOCB
#define myADCB_CHANNEL_ADCB1 ADC_CH_ADCIN1
#define myADCB_ADCB2 ADC_SOC_NUMBER2
#define myADCB_FORCE_ADCB2 ADC_FORCE_SOC2
#define myADCB_SAMPLE_WINDOW_ADCB2 400
#define myADCB_TRIGGER_SOURCE_ADCB2 ADC_TRIGGER_EPWM1_SOCB
#define myADCB_CHANNEL_ADCB2 ADC_CH_ADCIN3
#define myADCB_ADCB3 ADC_SOC_NUMBER3
#define myADCB_FORCE_ADCB3 ADC_FORCE_SOC3
#define myADCB_SAMPLE_WINDOW_ADCB3 400
#define myADCB_TRIGGER_SOURCE_ADCB3 ADC_TRIGGER_EPWM1_SOCB
#define myADCB_CHANNEL_ADCB3 ADC_CH_ADCIN8
#define myADCB_ADCB4 ADC_SOC_NUMBER4
#define myADCB_FORCE_ADCB4 ADC_FORCE_SOC4
#define myADCB_SAMPLE_WINDOW_ADCB4 400
#define myADCB_TRIGGER_SOURCE_ADCB4 ADC_TRIGGER_EPWM1_SOCB
#define myADCB_CHANNEL_ADCB4 ADC_CH_ADCIN2
#define myADCB_ADCB5 ADC_SOC_NUMBER5
#define myADCB_FORCE_ADCB5 ADC_FORCE_SOC5
#define myADCB_SAMPLE_WINDOW_ADCB5 400
#define myADCB_TRIGGER_SOURCE_ADCB5 ADC_TRIGGER_EPWM1_SOCA
#define myADCB_CHANNEL_ADCB5 ADC_CH_ADCIN4
#define myADCB_ADCB6 ADC_SOC_NUMBER6
#define myADCB_FORCE_ADCB6 ADC_FORCE_SOC6
#define myADCB_SAMPLE_WINDOW_ADCB6 400
#define myADCB_TRIGGER_SOURCE_ADCB6 ADC_TRIGGER_EPWM1_SOCA
#define myADCB_CHANNEL_ADCB6 ADC_CH_ADCIN1
#define myADCB_SOC7 ADC_SOC_NUMBER7
#define myADCB_FORCE_SOC7 ADC_FORCE_SOC7
#define myADCB_SAMPLE_WINDOW_SOC7 400
#define myADCB_TRIGGER_SOURCE_SOC7 ADC_TRIGGER_EPWM1_SOCA
#define myADCB_CHANNEL_SOC7 ADC_CH_ADCIN3
#define myADCB_SOC8 ADC_SOC_NUMBER8
#define myADCB_FORCE_SOC8 ADC_FORCE_SOC8
#define myADCB_SAMPLE_WINDOW_SOC8 400
#define myADCB_TRIGGER_SOURCE_SOC8 ADC_TRIGGER_EPWM1_SOCA
#define myADCB_CHANNEL_SOC8 ADC_CH_ADCIN8
#define myADCB_SOC9 ADC_SOC_NUMBER9
#define myADCB_FORCE_SOC9 ADC_FORCE_SOC9
#define myADCB_SAMPLE_WINDOW_SOC9 400
#define myADCB_TRIGGER_SOURCE_SOC9 ADC_TRIGGER_EPWM1_SOCA
#define myADCB_CHANNEL_SOC9 ADC_CH_ADCIN2
void myADCB_init();


//*****************************************************************************
//
// ASYSCTL Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
#define myEPWM1_BASE EPWM1_BASE
#define myEPWM1_TBPRD 4999
#define myEPWM1_COUNTER_MODE EPWM_COUNTER_MODE_UP
#define myEPWM1_TBPHS 0
#define myEPWM1_CMPA 100
#define myEPWM1_CMPB 10
#define myEPWM1_CMPC 0
#define myEPWM1_CMPD 0
#define myEPWM1_DBRED 20
#define myEPWM1_DBFED 20
#define myEPWM1_TZA_ACTION EPWM_TZ_ACTION_LOW
#define myEPWM1_TZB_ACTION EPWM_TZ_ACTION_LOW
#define myEPWM1_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define myEPWM2_BASE EPWM2_BASE
#define myEPWM2_TBPRD 4999
#define myEPWM2_COUNTER_MODE EPWM_COUNTER_MODE_UP
#define myEPWM2_TBPHS 0
#define myEPWM2_CMPA 100
#define myEPWM2_CMPB 10
#define myEPWM2_CMPC 0
#define myEPWM2_CMPD 0
#define myEPWM2_DBRED 20
#define myEPWM2_DBFED 20
#define myEPWM2_TZA_ACTION EPWM_TZ_ACTION_LOW
#define myEPWM2_TZB_ACTION EPWM_TZ_ACTION_LOW
#define myEPWM2_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define myEPWM3_BASE EPWM3_BASE
#define myEPWM3_TBPRD 4999
#define myEPWM3_COUNTER_MODE EPWM_COUNTER_MODE_UP
#define myEPWM3_TBPHS 0
#define myEPWM3_CMPA 100
#define myEPWM3_CMPB 10
#define myEPWM3_CMPC 0
#define myEPWM3_CMPD 0
#define myEPWM3_DBRED 20
#define myEPWM3_DBFED 20
#define myEPWM3_TZA_ACTION EPWM_TZ_ACTION_LOW
#define myEPWM3_TZB_ACTION EPWM_TZ_ACTION_LOW
#define myEPWM3_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define myEPWM4_BASE EPWM4_BASE
#define myEPWM4_TBPRD 4999
#define myEPWM4_COUNTER_MODE EPWM_COUNTER_MODE_UP
#define myEPWM4_TBPHS 0
#define myEPWM4_CMPA 100
#define myEPWM4_CMPB 10
#define myEPWM4_CMPC 0
#define myEPWM4_CMPD 0
#define myEPWM4_DBRED 20
#define myEPWM4_DBFED 20
#define myEPWM4_TZA_ACTION EPWM_TZ_ACTION_LOW
#define myEPWM4_TZB_ACTION EPWM_TZ_ACTION_LOW
#define myEPWM4_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define LED_RED 23
void LED_RED_init();
#define LED_GREEN 34
void LED_GREEN_init();
#define DRV 13
void DRV_init();
#define TIME_WATCH1 30
void TIME_WATCH1_init();
#define TIME_WATCH2 39
void TIME_WATCH2_init();
#define DIS 16
void DIS_init();

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_timer2
// ISR need to be defined for the registered interrupts
#define INT_timer2 INT_TIMER2
extern __interrupt void portTICK_ISR(void);

// Interrupt Settings for INT_myADCA_1
// ISR need to be defined for the registered interrupts
#define INT_myADCA_1 INT_ADCA1
#define INT_myADCA_1_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP1
extern __interrupt void INT_myADCA_1_ISR(void);

// Interrupt Settings for INT_mySCI0_RX
// ISR need to be defined for the registered interrupts
#define INT_mySCI0_RX INT_SCIA_RX
#define INT_mySCI0_RX_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP9
extern __interrupt void INT_mySCI0_RX_ISR(void);

// Interrupt Settings for INT_mySCI0_TX
// ISR need to be defined for the registered interrupts
#define INT_mySCI0_TX INT_SCIA_TX
#define INT_mySCI0_TX_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP9
extern __interrupt void INT_mySCI0_TX_ISR(void);

//*****************************************************************************
//
// SCI Configurations
//
//*****************************************************************************
#define mySCI0_BASE SCIA_BASE
#define mySCI0_BAUDRATE 1000000
#define mySCI0_CONFIG_WLEN SCI_CONFIG_WLEN_8
#define mySCI0_CONFIG_STOP SCI_CONFIG_STOP_ONE
#define mySCI0_CONFIG_PAR SCI_CONFIG_PAR_NONE
#define mySCI0_FIFO_TX_LVL SCI_FIFO_TX0
#define mySCI0_FIFO_RX_LVL SCI_FIFO_RX1
void mySCI0_init();

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	ADC_init();
void	ASYSCTL_init();
void	CPUTIMER_init();
void	EPWM_init();
void	GPIO_init();
void	INTERRUPT_init();
void	SCI_init();
void	SYNC_init();
void	PinMux_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
