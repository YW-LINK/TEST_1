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
// GPIO23 - GPIO Settings
//
#define LED_RED_GPIO_PIN_CONFIG GPIO_23_GPIO23
//
// GPIO34 - GPIO Settings
//
#define LED_GREEN_GPIO_PIN_CONFIG GPIO_34_GPIO34
//
// GPIO7 - GPIO Settings
//
#define RLY_GPIO_PIN_CONFIG GPIO_7_GPIO7
//
// GPIO4 - GPIO Settings
//
#define I2C_A0_GPIO_PIN_CONFIG GPIO_4_GPIO4
//
// GPIO2 - GPIO Settings
//
#define I2C_A1_GPIO_PIN_CONFIG GPIO_2_GPIO2
//
// GPIO0 - GPIO Settings
//
#define I2C_A2_GPIO_PIN_CONFIG GPIO_0_GPIO0

//
// I2CA -> myI2C0 Pinmux
//
//
// I2CA_SDA - GPIO Settings
//
#define GPIO_PIN_I2CA_SDA 26
#define myI2C0_I2CSDA_GPIO 26
#define myI2C0_I2CSDA_PIN_CONFIG GPIO_26_I2CA_SDA
//
// I2CA_SCL - GPIO Settings
//
#define GPIO_PIN_I2CA_SCL 27
#define myI2C0_I2CSCL_GPIO 27
#define myI2C0_I2CSCL_PIN_CONFIG GPIO_27_I2CA_SCL

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
#define myADCA_TRIGGER_SOURCE_ADCA0 ADC_TRIGGER_SW_ONLY
#define myADCA_CHANNEL_ADCA0 ADC_CH_ADCIN8
#define myADCA_ADCA1 ADC_SOC_NUMBER1
#define myADCA_FORCE_ADCA1 ADC_FORCE_SOC1
#define myADCA_SAMPLE_WINDOW_ADCA1 400
#define myADCA_TRIGGER_SOURCE_ADCA1 ADC_TRIGGER_SW_ONLY
#define myADCA_CHANNEL_ADCA1 ADC_CH_ADCIN0
#define myADCA_ADCA2 ADC_SOC_NUMBER2
#define myADCA_FORCE_ADCA2 ADC_FORCE_SOC2
#define myADCA_SAMPLE_WINDOW_ADCA2 400
#define myADCA_TRIGGER_SOURCE_ADCA2 ADC_TRIGGER_EPWM1_SOCB
#define myADCA_CHANNEL_ADCA2 ADC_CH_ADCIN6
#define myADCA_ADCA3 ADC_SOC_NUMBER3
#define myADCA_FORCE_ADCA3 ADC_FORCE_SOC3
#define myADCA_SAMPLE_WINDOW_ADCA3 400
#define myADCA_TRIGGER_SOURCE_ADCA3 ADC_TRIGGER_SW_ONLY
#define myADCA_CHANNEL_ADCA3 ADC_CH_ADCIN3
#define myADCA_ADCA4 ADC_SOC_NUMBER4
#define myADCA_FORCE_ADCA4 ADC_FORCE_SOC4
#define myADCA_SAMPLE_WINDOW_ADCA4 400
#define myADCA_TRIGGER_SOURCE_ADCA4 ADC_TRIGGER_SW_ONLY
#define myADCA_CHANNEL_ADCA4 ADC_CH_ADCIN1
void myADCA_init();

#define myADCC_BASE ADCC_BASE
#define myADCC_RESULT_BASE ADCCRESULT_BASE
#define myADCC_ADCC0 ADC_SOC_NUMBER0
#define myADCC_FORCE_ADCC0 ADC_FORCE_SOC0
#define myADCC_SAMPLE_WINDOW_ADCC0 800
#define myADCC_TRIGGER_SOURCE_ADCC0 ADC_TRIGGER_SW_ONLY
#define myADCC_CHANNEL_ADCC0 ADC_CH_ADCIN5
#define myADCC_ADCC1 ADC_SOC_NUMBER1
#define myADCC_FORCE_ADCC1 ADC_FORCE_SOC1
#define myADCC_SAMPLE_WINDOW_ADCC1 400
#define myADCC_TRIGGER_SOURCE_ADCC1 ADC_TRIGGER_SW_ONLY
#define myADCC_CHANNEL_ADCC1 ADC_CH_ADCIN3
#define myADCC_ADCC2 ADC_SOC_NUMBER2
#define myADCC_FORCE_ADCC2 ADC_FORCE_SOC2
#define myADCC_SAMPLE_WINDOW_ADCC2 400
#define myADCC_TRIGGER_SOURCE_ADCC2 ADC_TRIGGER_SW_ONLY
#define myADCC_CHANNEL_ADCC2 ADC_CH_ADCIN4
#define myADCC_ADCC3 ADC_SOC_NUMBER3
#define myADCC_FORCE_ADCC3 ADC_FORCE_SOC3
#define myADCC_SAMPLE_WINDOW_ADCC3 400
#define myADCC_TRIGGER_SOURCE_ADCC3 ADC_TRIGGER_SW_ONLY
#define myADCC_CHANNEL_ADCC3 ADC_CH_ADCIN2
#define myADCC_ADCC4 ADC_SOC_NUMBER4
#define myADCC_FORCE_ADCC4 ADC_FORCE_SOC4
#define myADCC_SAMPLE_WINDOW_ADCC4 400
#define myADCC_TRIGGER_SOURCE_ADCC4 ADC_TRIGGER_SW_ONLY
#define myADCC_CHANNEL_ADCC4 ADC_CH_ADCIN0
void myADCC_init();

#define myADCB_BASE ADCB_BASE
#define myADCB_RESULT_BASE ADCBRESULT_BASE
#define myADCB_ADCB0 ADC_SOC_NUMBER0
#define myADCB_FORCE_ADCB0 ADC_FORCE_SOC0
#define myADCB_SAMPLE_WINDOW_ADCB0 800
#define myADCB_TRIGGER_SOURCE_ADCB0 ADC_TRIGGER_SW_ONLY
#define myADCB_CHANNEL_ADCB0 ADC_CH_ADCIN4
#define myADCB_ADCB1 ADC_SOC_NUMBER1
#define myADCB_FORCE_ADCB1 ADC_FORCE_SOC1
#define myADCB_SAMPLE_WINDOW_ADCB1 400
#define myADCB_TRIGGER_SOURCE_ADCB1 ADC_TRIGGER_SW_ONLY
#define myADCB_CHANNEL_ADCB1 ADC_CH_ADCIN0
#define myADCB_ADCB2 ADC_SOC_NUMBER2
#define myADCB_FORCE_ADCB2 ADC_FORCE_SOC2
#define myADCB_SAMPLE_WINDOW_ADCB2 400
#define myADCB_TRIGGER_SOURCE_ADCB2 ADC_TRIGGER_SW_ONLY
#define myADCB_CHANNEL_ADCB2 ADC_CH_ADCIN6
#define myADCB_ADCB3 ADC_SOC_NUMBER3
#define myADCB_FORCE_ADCB3 ADC_FORCE_SOC3
#define myADCB_SAMPLE_WINDOW_ADCB3 400
#define myADCB_TRIGGER_SOURCE_ADCB3 ADC_TRIGGER_SW_ONLY
#define myADCB_CHANNEL_ADCB3 ADC_CH_ADCIN2
#define myADCB_ADCB4 ADC_SOC_NUMBER4
#define myADCB_FORCE_ADCB4 ADC_FORCE_SOC4
#define myADCB_SAMPLE_WINDOW_ADCB4 400
#define myADCB_TRIGGER_SOURCE_ADCB4 ADC_TRIGGER_SW_ONLY
#define myADCB_CHANNEL_ADCB4 ADC_CH_ADCIN3
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
#define myCPUTIMER0_BASE CPUTIMER0_BASE
void myCPUTIMER0_init();

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define LED_RED 23
void LED_RED_init();
#define LED_GREEN 34
void LED_GREEN_init();
#define RLY 7
void RLY_init();
#define I2C_A0 4
void I2C_A0_init();
#define I2C_A1 2
void I2C_A1_init();
#define I2C_A2 0
void I2C_A2_init();

//*****************************************************************************
//
// I2C Configurations
//
//*****************************************************************************
#define myI2C0_BASE I2CA_BASE
#define myI2C0_BITRATE 100000
#define myI2C0_TARGET_ADDRESS 57
#define myI2C0_OWN_ADDRESS 0
#define myI2C0_MODULE_CLOCK_FREQUENCY 10000000
void myI2C0_init();

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_timer2
// ISR need to be defined for the registered interrupts
#define INT_timer2 INT_TIMER2
extern __interrupt void portTICK_ISR(void);

// Interrupt Settings for INT_myCPUTIMER0
// ISR need to be defined for the registered interrupts
#define INT_myCPUTIMER0 INT_TIMER0
#define INT_myCPUTIMER0_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP1
extern __interrupt void INT_myCPUTIMER0_ISR(void);

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
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	ADC_init();
void	ASYSCTL_init();
void	CPUTIMER_init();
void	GPIO_init();
void	I2C_init();
void	INTERRUPT_init();
void	SCI_init();
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
