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

#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules. 
// Call this function in your application if you wish to do all module 
// initialization.
// If you wish to not use some of the initializations, instead of the 
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
	EALLOW;

	PinMux_init();
	SYNC_init();
	ASYSCTL_init();
	ADC_init();
	CPUTIMER_init();
	EPWM_init();
	GPIO_init();
	SCI_init();
	INTERRUPT_init();

	EDIS;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
	//
	// PinMux for modules assigned to CPU1
	//
	
	//
	// EPWM1 -> myEPWM1 Pinmux
	//
	GPIO_setPinConfig(myEPWM1_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(myEPWM1_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myEPWM1_EPWMA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(myEPWM1_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(myEPWM1_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myEPWM1_EPWMB_GPIO, GPIO_QUAL_SYNC);

	//
	// EPWM2 -> myEPWM2 Pinmux
	//
	GPIO_setPinConfig(myEPWM2_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(myEPWM2_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myEPWM2_EPWMA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(myEPWM2_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(myEPWM2_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myEPWM2_EPWMB_GPIO, GPIO_QUAL_SYNC);

	//
	// EPWM3 -> myEPWM3 Pinmux
	//
	GPIO_setPinConfig(myEPWM3_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(myEPWM3_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myEPWM3_EPWMA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(myEPWM3_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(myEPWM3_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myEPWM3_EPWMB_GPIO, GPIO_QUAL_SYNC);

	//
	// EPWM4 -> myEPWM4 Pinmux
	//
	GPIO_setPinConfig(myEPWM4_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(myEPWM4_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myEPWM4_EPWMA_GPIO, GPIO_QUAL_SYNC);

	GPIO_setPinConfig(myEPWM4_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(myEPWM4_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myEPWM4_EPWMB_GPIO, GPIO_QUAL_SYNC);

	// GPIO23_VSW -> LED_RED Pinmux
	GPIO_setPinConfig(GPIO_23_GPIO23);
	// GPIO34 -> LED_GREEN Pinmux
	GPIO_setPinConfig(GPIO_34_GPIO34);
	// GPIO13 -> DRV Pinmux
	GPIO_setPinConfig(GPIO_13_GPIO13);
	// GPIO30 -> TIME_WATCH1 Pinmux
	GPIO_setPinConfig(GPIO_30_GPIO30);
	// GPIO39 -> TIME_WATCH2 Pinmux
	GPIO_setPinConfig(GPIO_39_GPIO39);
	// GPIO16 -> DIS Pinmux
	GPIO_setPinConfig(GPIO_16_GPIO16);
	//
	// SCIA -> mySCI0 Pinmux
	//
	GPIO_setPinConfig(mySCI0_SCIRX_PIN_CONFIG);
	GPIO_setPadConfig(mySCI0_SCIRX_GPIO, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(mySCI0_SCIRX_GPIO, GPIO_QUAL_ASYNC);

	GPIO_setPinConfig(mySCI0_SCITX_PIN_CONFIG);
	GPIO_setPadConfig(mySCI0_SCITX_GPIO, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(mySCI0_SCITX_GPIO, GPIO_QUAL_ASYNC);


}

//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
void ADC_init(){
	myADCA_init();
	myADCC_init();
	myADCB_init();
}

void myADCA_init(){
	//
	// ADC Initialization: Write ADC configurations and power up the ADC
	//
	// Set the analog voltage reference selection and ADC module's offset trims.
	// This function sets the analog voltage reference to internal (with the reference voltage of 1.65V or 2.5V) or external for ADC
	// which is same as ASysCtl APIs.
	//
	ADC_setVREF(myADCA_BASE, ADC_REFERENCE_EXTERNAL, ADC_REFERENCE_3_3V);
	//
	// Configures the analog-to-digital converter module prescaler.
	//
	ADC_setPrescaler(myADCA_BASE, ADC_CLK_DIV_2_0);
	//
	// Sets the timing of the end-of-conversion pulse
	//
	ADC_setInterruptPulseMode(myADCA_BASE, ADC_PULSE_END_OF_CONV);
	//
	// Powers up the analog-to-digital converter core.
	//
	ADC_enableConverter(myADCA_BASE);
	//
	// Delay for 1ms to allow ADC time to power up
	//
	DEVICE_DELAY_US(500);
	//
	// SOC Configuration: Setup ADC EPWM channel and trigger settings
	//
	// Disables SOC burst mode.
	//
	ADC_disableBurstMode(myADCA_BASE);
	//
	// Sets the priority mode of the SOCs.
	//
	ADC_setSOCPriority(myADCA_BASE, ADC_PRI_THRU_SOC8_HIPRI);
	//
	// Start of Conversion 0 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 0
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCB
	//	  	Channel			: ADC_CH_ADCIN0
	//	 	Sample Window	: 80 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCB, ADC_CH_ADCIN0, 80U);
	ADC_setInterruptSOCTrigger(myADCA_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 1 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 1
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCB
	//	  	Channel			: ADC_CH_ADCIN8
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCA_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM1_SOCB, ADC_CH_ADCIN8, 40U);
	ADC_setInterruptSOCTrigger(myADCA_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 2 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 2
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCB
	//	  	Channel			: ADC_CH_ADCIN3
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCA_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_EPWM1_SOCB, ADC_CH_ADCIN3, 40U);
	ADC_setInterruptSOCTrigger(myADCA_BASE, ADC_SOC_NUMBER2, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 3 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 3
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCB
	//	  	Channel			: ADC_CH_ADCIN5
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCA_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_EPWM1_SOCB, ADC_CH_ADCIN5, 40U);
	ADC_setInterruptSOCTrigger(myADCA_BASE, ADC_SOC_NUMBER3, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 4 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 4
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCB
	//	  	Channel			: ADC_CH_ADCIN1
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCA_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_EPWM1_SOCB, ADC_CH_ADCIN1, 40U);
	ADC_setInterruptSOCTrigger(myADCA_BASE, ADC_SOC_NUMBER4, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 5 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 5
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN0
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCA_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN0, 40U);
	ADC_setInterruptSOCTrigger(myADCA_BASE, ADC_SOC_NUMBER5, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 6 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 6
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN8
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCA_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN8, 40U);
	ADC_setInterruptSOCTrigger(myADCA_BASE, ADC_SOC_NUMBER6, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 7 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 7
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN3
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCA_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN3, 40U);
	ADC_setInterruptSOCTrigger(myADCA_BASE, ADC_SOC_NUMBER7, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 8 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 8
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN5
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCA_BASE, ADC_SOC_NUMBER8, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN5, 40U);
	ADC_setInterruptSOCTrigger(myADCA_BASE, ADC_SOC_NUMBER8, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 9 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 9
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN1
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCA_BASE, ADC_SOC_NUMBER9, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN1, 40U);
	ADC_setInterruptSOCTrigger(myADCA_BASE, ADC_SOC_NUMBER9, ADC_INT_SOC_TRIGGER_NONE);
	//
	// ADC Interrupt 1 Configuration
	// 		Source	: ADC_SOC_NUMBER9
	// 		Interrupt Source: enabled
	//		Continuous Mode	: enabled
	//
	//
	ADC_setInterruptSource(myADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER9);
	ADC_clearInterruptStatus(myADCA_BASE, ADC_INT_NUMBER1);
	ADC_enableContinuousMode(myADCA_BASE, ADC_INT_NUMBER1);
	ADC_enableInterrupt(myADCA_BASE, ADC_INT_NUMBER1);
}

void myADCC_init(){
	//
	// ADC Initialization: Write ADC configurations and power up the ADC
	//
	// Set the analog voltage reference selection and ADC module's offset trims.
	// This function sets the analog voltage reference to internal (with the reference voltage of 1.65V or 2.5V) or external for ADC
	// which is same as ASysCtl APIs.
	//
	ADC_setVREF(myADCC_BASE, ADC_REFERENCE_EXTERNAL, ADC_REFERENCE_3_3V);
	//
	// Configures the analog-to-digital converter module prescaler.
	//
	ADC_setPrescaler(myADCC_BASE, ADC_CLK_DIV_2_0);
	//
	// Sets the timing of the end-of-conversion pulse
	//
	ADC_setInterruptPulseMode(myADCC_BASE, ADC_PULSE_END_OF_ACQ_WIN);
	//
	// Sets the timing of early interrupt generation.
	//
	ADC_setInterruptCycleOffset(myADCC_BASE, 0U);
	//
	// Powers up the analog-to-digital converter core.
	//
	ADC_enableConverter(myADCC_BASE);
	//
	// Delay for 1ms to allow ADC time to power up
	//
	DEVICE_DELAY_US(500);
	//
	// SOC Configuration: Setup ADC EPWM channel and trigger settings
	//
	// Disables SOC burst mode.
	//
	ADC_disableBurstMode(myADCC_BASE);
	//
	// Sets the priority mode of the SOCs.
	//
	ADC_setSOCPriority(myADCC_BASE, ADC_PRI_THRU_SOC6_HIPRI);
	//
	// Start of Conversion 0 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 0
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCB
	//	  	Channel			: ADC_CH_ADCIN5
	//	 	Sample Window	: 80 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCC_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCB, ADC_CH_ADCIN5, 80U);
	ADC_setInterruptSOCTrigger(myADCC_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 1 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 1
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCB
	//	  	Channel			: ADC_CH_ADCIN4
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCC_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM1_SOCB, ADC_CH_ADCIN4, 40U);
	ADC_setInterruptSOCTrigger(myADCC_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 2 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 2
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCB
	//	  	Channel			: ADC_CH_ADCIN2
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCC_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_EPWM1_SOCB, ADC_CH_ADCIN2, 40U);
	ADC_setInterruptSOCTrigger(myADCC_BASE, ADC_SOC_NUMBER2, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 3 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 3
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCB
	//	  	Channel			: ADC_CH_ADCIN1
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCC_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_EPWM1_SOCB, ADC_CH_ADCIN1, 40U);
	ADC_setInterruptSOCTrigger(myADCC_BASE, ADC_SOC_NUMBER3, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 4 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 4
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN5
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCC_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN5, 40U);
	ADC_setInterruptSOCTrigger(myADCC_BASE, ADC_SOC_NUMBER4, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 5 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 5
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN4
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCC_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN4, 40U);
	ADC_setInterruptSOCTrigger(myADCC_BASE, ADC_SOC_NUMBER5, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 6 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 6
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN2
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCC_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN2, 40U);
	ADC_setInterruptSOCTrigger(myADCC_BASE, ADC_SOC_NUMBER6, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 7 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 7
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN1
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCC_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN1, 40U);
	ADC_setInterruptSOCTrigger(myADCC_BASE, ADC_SOC_NUMBER7, ADC_INT_SOC_TRIGGER_NONE);
}

void myADCB_init(){
	//
	// ADC Initialization: Write ADC configurations and power up the ADC
	//
	// Set the analog voltage reference selection and ADC module's offset trims.
	// This function sets the analog voltage reference to internal (with the reference voltage of 1.65V or 2.5V) or external for ADC
	// which is same as ASysCtl APIs.
	//
	ADC_setVREF(myADCB_BASE, ADC_REFERENCE_EXTERNAL, ADC_REFERENCE_3_3V);
	//
	// Configures the analog-to-digital converter module prescaler.
	//
	ADC_setPrescaler(myADCB_BASE, ADC_CLK_DIV_2_0);
	//
	// Sets the timing of the end-of-conversion pulse
	//
	ADC_setInterruptPulseMode(myADCB_BASE, ADC_PULSE_END_OF_ACQ_WIN);
	//
	// Sets the timing of early interrupt generation.
	//
	ADC_setInterruptCycleOffset(myADCB_BASE, 0U);
	//
	// Powers up the analog-to-digital converter core.
	//
	ADC_enableConverter(myADCB_BASE);
	//
	// Delay for 1ms to allow ADC time to power up
	//
	DEVICE_DELAY_US(500);
	//
	// SOC Configuration: Setup ADC EPWM channel and trigger settings
	//
	// Disables SOC burst mode.
	//
	ADC_disableBurstMode(myADCB_BASE);
	//
	// Sets the priority mode of the SOCs.
	//
	ADC_setSOCPriority(myADCB_BASE, ADC_PRI_THRU_SOC8_HIPRI);
	//
	// Start of Conversion 0 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 0
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCB
	//	  	Channel			: ADC_CH_ADCIN4
	//	 	Sample Window	: 80 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCB_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCB, ADC_CH_ADCIN4, 80U);
	ADC_setInterruptSOCTrigger(myADCB_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 1 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 1
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCB
	//	  	Channel			: ADC_CH_ADCIN1
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCB_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM1_SOCB, ADC_CH_ADCIN1, 40U);
	ADC_setInterruptSOCTrigger(myADCB_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 2 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 2
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCB
	//	  	Channel			: ADC_CH_ADCIN3
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCB_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_EPWM1_SOCB, ADC_CH_ADCIN3, 40U);
	ADC_setInterruptSOCTrigger(myADCB_BASE, ADC_SOC_NUMBER2, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 3 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 3
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCB
	//	  	Channel			: ADC_CH_ADCIN8
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCB_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_EPWM1_SOCB, ADC_CH_ADCIN8, 40U);
	ADC_setInterruptSOCTrigger(myADCB_BASE, ADC_SOC_NUMBER3, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 4 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 4
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCB
	//	  	Channel			: ADC_CH_ADCIN2
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCB_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_EPWM1_SOCB, ADC_CH_ADCIN2, 40U);
	ADC_setInterruptSOCTrigger(myADCB_BASE, ADC_SOC_NUMBER4, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 5 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 5
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN4
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCB_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN4, 40U);
	ADC_setInterruptSOCTrigger(myADCB_BASE, ADC_SOC_NUMBER5, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 6 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 6
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN1
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCB_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN1, 40U);
	ADC_setInterruptSOCTrigger(myADCB_BASE, ADC_SOC_NUMBER6, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 7 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 7
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN3
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCB_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN3, 40U);
	ADC_setInterruptSOCTrigger(myADCB_BASE, ADC_SOC_NUMBER7, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 8 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 8
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN8
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCB_BASE, ADC_SOC_NUMBER8, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN8, 40U);
	ADC_setInterruptSOCTrigger(myADCB_BASE, ADC_SOC_NUMBER8, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 9 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 9
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCA
	//	  	Channel			: ADC_CH_ADCIN2
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCB_BASE, ADC_SOC_NUMBER9, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN2, 40U);
	ADC_setInterruptSOCTrigger(myADCB_BASE, ADC_SOC_NUMBER9, ADC_INT_SOC_TRIGGER_NONE);
}


//*****************************************************************************
//
// ASYSCTL Configurations
//
//*****************************************************************************
void ASYSCTL_init(){
	//
	// asysctl initialization
	//
	// Disables the temperature sensor output to the ADC.
	//
	ASysCtl_disableTemperatureSensor();
	//
	// Set the analog voltage reference selection to external.
	//
	ASysCtl_setAnalogReferenceExternal( ASYSCTL_VREFHIA | ASYSCTL_VREFHIB | ASYSCTL_VREFHIC );
}

//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
void CPUTIMER_init(){
}


//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
void EPWM_init(){
    EPWM_setClockPrescaler(myEPWM1_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(myEPWM1_BASE, 4999);	
    EPWM_setupEPWMLinks(myEPWM1_BASE, EPWM_LINK_WITH_EPWM_1, EPWM_LINK_TBPRD);	
    EPWM_setTimeBaseCounter(myEPWM1_BASE, 0);	
    EPWM_setTimeBaseCounterMode(myEPWM1_BASE, EPWM_COUNTER_MODE_UP);	
    EPWM_disablePhaseShiftLoad(myEPWM1_BASE);	
    EPWM_setPhaseShift(myEPWM1_BASE, 0);	
    EPWM_forceSyncPulse(myEPWM1_BASE);	
    EPWM_setSyncOutPulseMode(myEPWM1_BASE, EPWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_B);	
    EPWM_setSyncPulseSource(myEPWM1_BASE, HRPWM_PWMSYNC_SOURCE_ZERO);	
    EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, 100);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_B, 10);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM1_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setDeadBandDelayPolarity(myEPWM1_BASE, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);	
    EPWM_setDeadBandDelayMode(myEPWM1_BASE, EPWM_DB_RED, true);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(myEPWM1_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(myEPWM1_BASE);	
    EPWM_setRisingEdgeDelayCount(myEPWM1_BASE, 20);	
    EPWM_setDeadBandDelayMode(myEPWM1_BASE, EPWM_DB_FED, true);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(myEPWM1_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(myEPWM1_BASE);	
    EPWM_setFallingEdgeDelayCount(myEPWM1_BASE, 20);	
    EPWM_setDeadBandOutputSwapMode(myEPWM1_BASE, EPWM_DB_OUTPUT_A, true);	
    EPWM_setDeadBandOutputSwapMode(myEPWM1_BASE, EPWM_DB_OUTPUT_B, true);	
    EPWM_setTripZoneAction(myEPWM1_BASE, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM1_BASE, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM1_BASE, EPWM_TZ_ACTION_EVENT_DCAEVT1, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM1_BASE, EPWM_TZ_ACTION_EVENT_DCAEVT2, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM1_BASE, EPWM_TZ_ACTION_EVENT_DCBEVT1, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM1_BASE, EPWM_TZ_ACTION_EVENT_DCBEVT2, EPWM_TZ_ACTION_LOW);	
    EPWM_enableADCTrigger(myEPWM1_BASE, EPWM_SOC_A);	
    EPWM_setADCTriggerSource(myEPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO);	
    EPWM_setADCTriggerEventPrescale(myEPWM1_BASE, EPWM_SOC_A, 1);	
    EPWM_enableADCTrigger(myEPWM1_BASE, EPWM_SOC_B);	
    EPWM_setADCTriggerSource(myEPWM1_BASE, EPWM_SOC_B, EPWM_SOC_TBCTR_PERIOD);	
    EPWM_setADCTriggerEventPrescale(myEPWM1_BASE, EPWM_SOC_B, 1);	
    EPWM_setClockPrescaler(myEPWM2_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(myEPWM2_BASE, 4999);	
    EPWM_setupEPWMLinks(myEPWM2_BASE, EPWM_LINK_WITH_EPWM_1, EPWM_LINK_TBPRD);	
    EPWM_setTimeBaseCounter(myEPWM2_BASE, 0);	
    EPWM_setTimeBaseCounterMode(myEPWM2_BASE, EPWM_COUNTER_MODE_UP);	
    EPWM_enablePhaseShiftLoad(myEPWM2_BASE);	
    EPWM_setPhaseShift(myEPWM2_BASE, 0);	
    EPWM_forceSyncPulse(myEPWM2_BASE);	
    EPWM_setSyncOutPulseMode(myEPWM2_BASE, EPWM_SYNC_OUT_PULSE_ON_EPWMxSYNCIN);	
    EPWM_setSyncPulseSource(myEPWM2_BASE, HRPWM_PWMSYNC_SOURCE_ZERO);	
    EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A, 100);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_B, 10);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM2_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setDeadBandDelayPolarity(myEPWM2_BASE, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);	
    EPWM_setDeadBandDelayMode(myEPWM2_BASE, EPWM_DB_RED, true);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(myEPWM2_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(myEPWM2_BASE);	
    EPWM_setRisingEdgeDelayCount(myEPWM2_BASE, 20);	
    EPWM_setDeadBandDelayMode(myEPWM2_BASE, EPWM_DB_FED, true);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(myEPWM2_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(myEPWM2_BASE);	
    EPWM_setFallingEdgeDelayCount(myEPWM2_BASE, 20);	
    EPWM_setTripZoneAction(myEPWM2_BASE, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM2_BASE, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM2_BASE, EPWM_TZ_ACTION_EVENT_DCAEVT1, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM2_BASE, EPWM_TZ_ACTION_EVENT_DCAEVT2, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM2_BASE, EPWM_TZ_ACTION_EVENT_DCBEVT1, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM2_BASE, EPWM_TZ_ACTION_EVENT_DCBEVT2, EPWM_TZ_ACTION_LOW);	
    EPWM_enableADCTrigger(myEPWM2_BASE, EPWM_SOC_A);	
    EPWM_setADCTriggerSource(myEPWM2_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO);	
    EPWM_setADCTriggerEventPrescale(myEPWM2_BASE, EPWM_SOC_A, 1);	
    EPWM_enableADCTrigger(myEPWM2_BASE, EPWM_SOC_B);	
    EPWM_setADCTriggerSource(myEPWM2_BASE, EPWM_SOC_B, EPWM_SOC_TBCTR_PERIOD);	
    EPWM_setADCTriggerEventPrescale(myEPWM2_BASE, EPWM_SOC_B, 1);	
    EPWM_setClockPrescaler(myEPWM3_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(myEPWM3_BASE, 4999);	
    EPWM_setupEPWMLinks(myEPWM3_BASE, EPWM_LINK_WITH_EPWM_1, EPWM_LINK_TBPRD);	
    EPWM_setTimeBaseCounter(myEPWM3_BASE, 0);	
    EPWM_setTimeBaseCounterMode(myEPWM3_BASE, EPWM_COUNTER_MODE_UP);	
    EPWM_enablePhaseShiftLoad(myEPWM3_BASE);	
    EPWM_setPhaseShift(myEPWM3_BASE, 0);	
    EPWM_forceSyncPulse(myEPWM3_BASE);	
    EPWM_setSyncOutPulseMode(myEPWM3_BASE, EPWM_SYNC_OUT_PULSE_ON_EPWMxSYNCIN);	
    EPWM_setSyncPulseSource(myEPWM3_BASE, HRPWM_PWMSYNC_SOURCE_ZERO);	
    EPWM_setCounterCompareValue(myEPWM3_BASE, EPWM_COUNTER_COMPARE_A, 100);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM3_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(myEPWM3_BASE, EPWM_COUNTER_COMPARE_B, 10);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM3_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setDeadBandDelayPolarity(myEPWM3_BASE, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);	
    EPWM_setDeadBandDelayMode(myEPWM3_BASE, EPWM_DB_RED, true);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(myEPWM3_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(myEPWM3_BASE);	
    EPWM_setRisingEdgeDelayCount(myEPWM3_BASE, 20);	
    EPWM_setDeadBandDelayMode(myEPWM3_BASE, EPWM_DB_FED, true);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(myEPWM3_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(myEPWM3_BASE);	
    EPWM_setFallingEdgeDelayCount(myEPWM3_BASE, 20);	
    EPWM_setDeadBandOutputSwapMode(myEPWM3_BASE, EPWM_DB_OUTPUT_A, true);	
    EPWM_setDeadBandOutputSwapMode(myEPWM3_BASE, EPWM_DB_OUTPUT_B, true);	
    EPWM_setTripZoneAction(myEPWM3_BASE, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM3_BASE, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM3_BASE, EPWM_TZ_ACTION_EVENT_DCAEVT1, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM3_BASE, EPWM_TZ_ACTION_EVENT_DCAEVT2, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM3_BASE, EPWM_TZ_ACTION_EVENT_DCBEVT1, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM3_BASE, EPWM_TZ_ACTION_EVENT_DCBEVT2, EPWM_TZ_ACTION_LOW);	
    EPWM_enableADCTrigger(myEPWM3_BASE, EPWM_SOC_A);	
    EPWM_setADCTriggerSource(myEPWM3_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO);	
    EPWM_setADCTriggerEventPrescale(myEPWM3_BASE, EPWM_SOC_A, 1);	
    EPWM_enableADCTrigger(myEPWM3_BASE, EPWM_SOC_B);	
    EPWM_setADCTriggerSource(myEPWM3_BASE, EPWM_SOC_B, EPWM_SOC_TBCTR_PERIOD);	
    EPWM_setADCTriggerEventPrescale(myEPWM3_BASE, EPWM_SOC_B, 1);	
    EPWM_setClockPrescaler(myEPWM4_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(myEPWM4_BASE, 4999);	
    EPWM_setupEPWMLinks(myEPWM4_BASE, EPWM_LINK_WITH_EPWM_1, EPWM_LINK_TBPRD);	
    EPWM_setTimeBaseCounter(myEPWM4_BASE, 0);	
    EPWM_setTimeBaseCounterMode(myEPWM4_BASE, EPWM_COUNTER_MODE_UP);	
    EPWM_enablePhaseShiftLoad(myEPWM4_BASE);	
    EPWM_setPhaseShift(myEPWM4_BASE, 0);	
    EPWM_forceSyncPulse(myEPWM4_BASE);	
    EPWM_setSyncOutPulseMode(myEPWM4_BASE, EPWM_SYNC_OUT_PULSE_ON_EPWMxSYNCIN);	
    EPWM_setSyncPulseSource(myEPWM4_BASE, HRPWM_PWMSYNC_SOURCE_ZERO);	
    EPWM_setCounterCompareValue(myEPWM4_BASE, EPWM_COUNTER_COMPARE_A, 100);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM4_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(myEPWM4_BASE, EPWM_COUNTER_COMPARE_B, 10);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM4_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setDeadBandDelayPolarity(myEPWM4_BASE, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);	
    EPWM_setDeadBandDelayMode(myEPWM4_BASE, EPWM_DB_RED, true);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(myEPWM4_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(myEPWM4_BASE);	
    EPWM_setRisingEdgeDelayCount(myEPWM4_BASE, 20);	
    EPWM_setDeadBandDelayMode(myEPWM4_BASE, EPWM_DB_FED, true);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(myEPWM4_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(myEPWM4_BASE);	
    EPWM_setFallingEdgeDelayCount(myEPWM4_BASE, 20);	
    EPWM_setTripZoneAction(myEPWM4_BASE, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM4_BASE, EPWM_TZ_ACTION_EVENT_TZB, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM4_BASE, EPWM_TZ_ACTION_EVENT_DCAEVT1, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM4_BASE, EPWM_TZ_ACTION_EVENT_DCAEVT2, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM4_BASE, EPWM_TZ_ACTION_EVENT_DCBEVT1, EPWM_TZ_ACTION_LOW);	
    EPWM_setTripZoneAction(myEPWM4_BASE, EPWM_TZ_ACTION_EVENT_DCBEVT2, EPWM_TZ_ACTION_LOW);	
    EPWM_enableADCTrigger(myEPWM4_BASE, EPWM_SOC_A);	
    EPWM_setADCTriggerSource(myEPWM4_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO);	
    EPWM_setADCTriggerEventPrescale(myEPWM4_BASE, EPWM_SOC_A, 1);	
    EPWM_enableADCTrigger(myEPWM4_BASE, EPWM_SOC_B);	
    EPWM_setADCTriggerSource(myEPWM4_BASE, EPWM_SOC_B, EPWM_SOC_TBCTR_PERIOD);	
    EPWM_setADCTriggerEventPrescale(myEPWM4_BASE, EPWM_SOC_B, 1);	
}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init(){
	LED_RED_init();
	LED_GREEN_init();
	DRV_init();
	TIME_WATCH1_init();
	TIME_WATCH2_init();
	DIS_init();
}

void LED_RED_init(){
	GPIO_writePin(LED_RED, 1);
	GPIO_setPadConfig(LED_RED, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(LED_RED, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(LED_RED, GPIO_DIR_MODE_OUT);
	GPIO_setControllerCore(LED_RED, GPIO_CORE_CPU1);
}
void LED_GREEN_init(){
	GPIO_setPadConfig(LED_GREEN, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(LED_GREEN, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(LED_GREEN, GPIO_DIR_MODE_OUT);
	GPIO_setControllerCore(LED_GREEN, GPIO_CORE_CPU1);
}
void DRV_init(){
	GPIO_writePin(DRV, 0);
	GPIO_setPadConfig(DRV, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(DRV, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(DRV, GPIO_DIR_MODE_OUT);
	GPIO_setControllerCore(DRV, GPIO_CORE_CPU1);
}
void TIME_WATCH1_init(){
	GPIO_writePin(TIME_WATCH1, 0);
	GPIO_setPadConfig(TIME_WATCH1, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(TIME_WATCH1, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(TIME_WATCH1, GPIO_DIR_MODE_OUT);
	GPIO_setControllerCore(TIME_WATCH1, GPIO_CORE_CPU1);
}
void TIME_WATCH2_init(){
	GPIO_writePin(TIME_WATCH2, 0);
	GPIO_setPadConfig(TIME_WATCH2, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(TIME_WATCH2, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(TIME_WATCH2, GPIO_DIR_MODE_OUT);
	GPIO_setControllerCore(TIME_WATCH2, GPIO_CORE_CPU1);
}
void DIS_init(){
	GPIO_writePin(DIS, 0);
	GPIO_setPadConfig(DIS, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(DIS, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(DIS, GPIO_DIR_MODE_OUT);
	GPIO_setControllerCore(DIS, GPIO_CORE_CPU1);
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init(){
	
	// Interrupt Settings for INT_timer2
	// ISR need to be defined for the registered interrupts
	Interrupt_register(INT_timer2, &portTICK_ISR);
	Interrupt_enable(INT_timer2);
	
	// Interrupt Settings for INT_myADCA_1
	// ISR need to be defined for the registered interrupts
	Interrupt_register(INT_myADCA_1, &INT_myADCA_1_ISR);
	Interrupt_enable(INT_myADCA_1);
	
	// Interrupt Settings for INT_mySCI0_RX
	// ISR need to be defined for the registered interrupts
	Interrupt_register(INT_mySCI0_RX, &INT_mySCI0_RX_ISR);
	Interrupt_enable(INT_mySCI0_RX);
	
	// Interrupt Settings for INT_mySCI0_TX
	// ISR need to be defined for the registered interrupts
	Interrupt_register(INT_mySCI0_TX, &INT_mySCI0_TX_ISR);
	Interrupt_disable(INT_mySCI0_TX);
}
//*****************************************************************************
//
// SCI Configurations
//
//*****************************************************************************
void SCI_init(){
	mySCI0_init();
}

void mySCI0_init(){
	SCI_clearInterruptStatus(mySCI0_BASE, SCI_INT_RXFF | SCI_INT_TXFF | SCI_INT_FE | SCI_INT_OE | SCI_INT_PE | SCI_INT_RXERR | SCI_INT_RXRDY_BRKDT | SCI_INT_TXRDY);
	SCI_clearOverflowStatus(mySCI0_BASE);
	SCI_resetTxFIFO(mySCI0_BASE);
	SCI_resetRxFIFO(mySCI0_BASE);
	SCI_resetChannels(mySCI0_BASE);
	SCI_setConfig(mySCI0_BASE, DEVICE_LSPCLK_FREQ, mySCI0_BAUDRATE, (SCI_CONFIG_WLEN_8|SCI_CONFIG_STOP_ONE|SCI_CONFIG_PAR_NONE));
	SCI_disableLoopback(mySCI0_BASE);
	SCI_performSoftwareReset(mySCI0_BASE);
	SCI_enableInterrupt(mySCI0_BASE, SCI_INT_RXFF);
	SCI_setFIFOInterruptLevel(mySCI0_BASE, SCI_FIFO_TX0, SCI_FIFO_RX1);
	SCI_enableFIFO(mySCI0_BASE);
	SCI_enableModule(mySCI0_BASE);
}

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************
void SYNC_init(){
	SysCtl_setSyncOutputConfig(SYSCTL_SYNC_OUT_SRC_EPWM1SYNCOUT);
	//
	// For EPWM1, the sync input is: SYSCTL_SYNC_IN_SRC_EXTSYNCIN1
	//
	SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_EPWM4, SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT);
	SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_EPWM7, SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT);
	SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_ECAP1, SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT);
	SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_ECAP4, SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT);
	SysCtl_setSyncInputConfig(SYSCTL_SYNC_IN_ECAP6, SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT);
	//
	// SOCA
	//
	SysCtl_enableExtADCSOCSource(0);
	//
	// SOCB
	//
	SysCtl_enableExtADCSOCSource(0);
}
