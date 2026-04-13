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
	ASYSCTL_init();
	ADC_init();
	CPUTIMER_init();
	GPIO_init();
	I2C_init();
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
	
	// GPIO23_VSW -> LED_RED Pinmux
	GPIO_setPinConfig(GPIO_23_GPIO23);
	// GPIO34 -> LED_GREEN Pinmux
	GPIO_setPinConfig(GPIO_34_GPIO34);
	// GPIO7 -> RLY Pinmux
	GPIO_setPinConfig(GPIO_7_GPIO7);
	// GPIO4 -> I2C_A0 Pinmux
	GPIO_setPinConfig(GPIO_4_GPIO4);
	// GPIO2 -> I2C_A1 Pinmux
	GPIO_setPinConfig(GPIO_2_GPIO2);
	// GPIO0 -> I2C_A2 Pinmux
	GPIO_setPinConfig(GPIO_0_GPIO0);
	//
	// I2CA -> myI2C0 Pinmux
	//
	GPIO_setPinConfig(myI2C0_I2CSDA_PIN_CONFIG);
	GPIO_setPadConfig(myI2C0_I2CSDA_GPIO, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(myI2C0_I2CSDA_GPIO, GPIO_QUAL_ASYNC);

	GPIO_setPinConfig(myI2C0_I2CSCL_PIN_CONFIG);
	GPIO_setPadConfig(myI2C0_I2CSCL_GPIO, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(myI2C0_I2CSCL_GPIO, GPIO_QUAL_ASYNC);

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
	ADC_setSOCPriority(myADCA_BASE, ADC_PRI_THRU_SOC4_HIPRI);
	//
	// Start of Conversion 0 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 0
	//	  	Trigger			: ADC_TRIGGER_SW_ONLY
	//	  	Channel			: ADC_CH_ADCIN8
	//	 	Sample Window	: 80 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN8, 80U);
	ADC_setInterruptSOCTrigger(myADCA_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 1 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 1
	//	  	Trigger			: ADC_TRIGGER_SW_ONLY
	//	  	Channel			: ADC_CH_ADCIN0
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCA_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 40U);
	ADC_setInterruptSOCTrigger(myADCA_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 2 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 2
	//	  	Trigger			: ADC_TRIGGER_EPWM1_SOCB
	//	  	Channel			: ADC_CH_ADCIN6
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCA_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_EPWM1_SOCB, ADC_CH_ADCIN6, 40U);
	ADC_setInterruptSOCTrigger(myADCA_BASE, ADC_SOC_NUMBER2, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 3 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 3
	//	  	Trigger			: ADC_TRIGGER_SW_ONLY
	//	  	Channel			: ADC_CH_ADCIN3
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCA_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 40U);
	ADC_setInterruptSOCTrigger(myADCA_BASE, ADC_SOC_NUMBER3, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 4 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 4
	//	  	Trigger			: ADC_TRIGGER_SW_ONLY
	//	  	Channel			: ADC_CH_ADCIN1
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCA_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, 40U);
	ADC_setInterruptSOCTrigger(myADCA_BASE, ADC_SOC_NUMBER4, ADC_INT_SOC_TRIGGER_NONE);
	//
	// ADC Interrupt 1 Configuration
	// 		Source	: ADC_SOC_NUMBER4
	// 		Interrupt Source: enabled
	// 		Continuous Mode	: disabled
	//
	//
	ADC_setInterruptSource(myADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER4);
	ADC_clearInterruptStatus(myADCA_BASE, ADC_INT_NUMBER1);
	ADC_disableContinuousMode(myADCA_BASE, ADC_INT_NUMBER1);
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
	ADC_setInterruptPulseMode(myADCC_BASE, ADC_PULSE_END_OF_CONV);
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
	ADC_setSOCPriority(myADCC_BASE, ADC_PRI_THRU_SOC4_HIPRI);
	//
	// Start of Conversion 0 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 0
	//	  	Trigger			: ADC_TRIGGER_SW_ONLY
	//	  	Channel			: ADC_CH_ADCIN5
	//	 	Sample Window	: 80 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCC_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN5, 80U);
	ADC_setInterruptSOCTrigger(myADCC_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 1 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 1
	//	  	Trigger			: ADC_TRIGGER_SW_ONLY
	//	  	Channel			: ADC_CH_ADCIN3
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCC_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 40U);
	ADC_setInterruptSOCTrigger(myADCC_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 2 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 2
	//	  	Trigger			: ADC_TRIGGER_SW_ONLY
	//	  	Channel			: ADC_CH_ADCIN4
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCC_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, 40U);
	ADC_setInterruptSOCTrigger(myADCC_BASE, ADC_SOC_NUMBER2, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 3 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 3
	//	  	Trigger			: ADC_TRIGGER_SW_ONLY
	//	  	Channel			: ADC_CH_ADCIN2
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCC_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, 40U);
	ADC_setInterruptSOCTrigger(myADCC_BASE, ADC_SOC_NUMBER3, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 4 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 4
	//	  	Trigger			: ADC_TRIGGER_SW_ONLY
	//	  	Channel			: ADC_CH_ADCIN0
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCC_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 40U);
	ADC_setInterruptSOCTrigger(myADCC_BASE, ADC_SOC_NUMBER4, ADC_INT_SOC_TRIGGER_NONE);
	//
	// ADC Interrupt 1 Configuration
	// 		Source	: ADC_SOC_NUMBER4
	// 		Interrupt Source: enabled
	// 		Continuous Mode	: disabled
	//
	//
	ADC_setInterruptSource(myADCC_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER4);
	ADC_clearInterruptStatus(myADCC_BASE, ADC_INT_NUMBER1);
	ADC_disableContinuousMode(myADCC_BASE, ADC_INT_NUMBER1);
	ADC_enableInterrupt(myADCC_BASE, ADC_INT_NUMBER1);
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
	ADC_setInterruptPulseMode(myADCB_BASE, ADC_PULSE_END_OF_CONV);
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
	ADC_setSOCPriority(myADCB_BASE, ADC_PRI_THRU_SOC4_HIPRI);
	//
	// Start of Conversion 0 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 0
	//	  	Trigger			: ADC_TRIGGER_SW_ONLY
	//	  	Channel			: ADC_CH_ADCIN4
	//	 	Sample Window	: 80 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCB_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN4, 80U);
	ADC_setInterruptSOCTrigger(myADCB_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 1 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 1
	//	  	Trigger			: ADC_TRIGGER_SW_ONLY
	//	  	Channel			: ADC_CH_ADCIN0
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCB_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 40U);
	ADC_setInterruptSOCTrigger(myADCB_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 2 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 2
	//	  	Trigger			: ADC_TRIGGER_SW_ONLY
	//	  	Channel			: ADC_CH_ADCIN6
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCB_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN6, 40U);
	ADC_setInterruptSOCTrigger(myADCB_BASE, ADC_SOC_NUMBER2, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 3 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 3
	//	  	Trigger			: ADC_TRIGGER_SW_ONLY
	//	  	Channel			: ADC_CH_ADCIN2
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCB_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN2, 40U);
	ADC_setInterruptSOCTrigger(myADCB_BASE, ADC_SOC_NUMBER3, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 4 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 4
	//	  	Trigger			: ADC_TRIGGER_SW_ONLY
	//	  	Channel			: ADC_CH_ADCIN3
	//	 	Sample Window	: 40 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADCB_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN3, 40U);
	ADC_setInterruptSOCTrigger(myADCB_BASE, ADC_SOC_NUMBER4, ADC_INT_SOC_TRIGGER_NONE);
	//
	// ADC Interrupt 1 Configuration
	// 		Source	: ADC_SOC_NUMBER4
	// 		Interrupt Source: enabled
	// 		Continuous Mode	: disabled
	//
	//
	ADC_setInterruptSource(myADCB_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER4);
	ADC_clearInterruptStatus(myADCB_BASE, ADC_INT_NUMBER1);
	ADC_disableContinuousMode(myADCB_BASE, ADC_INT_NUMBER1);
	ADC_enableInterrupt(myADCB_BASE, ADC_INT_NUMBER1);
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
	myCPUTIMER0_init();
}

void myCPUTIMER0_init(){
	CPUTimer_setEmulationMode(myCPUTIMER0_BASE, CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
	CPUTimer_setPreScaler(myCPUTIMER0_BASE, 0U);
	CPUTimer_setPeriod(myCPUTIMER0_BASE, 9999U);
	CPUTimer_enableInterrupt(myCPUTIMER0_BASE);
	CPUTimer_stopTimer(myCPUTIMER0_BASE);

	CPUTimer_reloadTimerCounter(myCPUTIMER0_BASE);
	CPUTimer_startTimer(myCPUTIMER0_BASE);
}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init(){
	LED_RED_init();
	LED_GREEN_init();
	RLY_init();
	I2C_A0_init();
	I2C_A1_init();
	I2C_A2_init();
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
void RLY_init(){
	GPIO_writePin(RLY, 0);
	GPIO_setPadConfig(RLY, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(RLY, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(RLY, GPIO_DIR_MODE_OUT);
	GPIO_setControllerCore(RLY, GPIO_CORE_CPU1);
}
void I2C_A0_init(){
	GPIO_writePin(I2C_A0, 0);
	GPIO_setPadConfig(I2C_A0, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(I2C_A0, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(I2C_A0, GPIO_DIR_MODE_OUT);
	GPIO_setControllerCore(I2C_A0, GPIO_CORE_CPU1);
}
void I2C_A1_init(){
	GPIO_writePin(I2C_A1, 0);
	GPIO_setPadConfig(I2C_A1, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(I2C_A1, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(I2C_A1, GPIO_DIR_MODE_OUT);
	GPIO_setControllerCore(I2C_A1, GPIO_CORE_CPU1);
}
void I2C_A2_init(){
	GPIO_writePin(I2C_A2, 1);
	GPIO_setPadConfig(I2C_A2, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(I2C_A2, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(I2C_A2, GPIO_DIR_MODE_OUT);
	GPIO_setControllerCore(I2C_A2, GPIO_CORE_CPU1);
}

//*****************************************************************************
//
// I2C Configurations
//
//*****************************************************************************
void I2C_init(){
	myI2C0_init();
}

void myI2C0_init(){
	I2C_disableModule(myI2C0_BASE);
	I2C_initController(myI2C0_BASE, DEVICE_SYSCLK_FREQ, myI2C0_BITRATE, I2C_DUTYCYCLE_50);
	I2C_setConfig(myI2C0_BASE, I2C_CONTROLLER_SEND_MODE);
	I2C_disableLoopback(myI2C0_BASE);
	I2C_setOwnAddress(myI2C0_BASE, myI2C0_OWN_ADDRESS);
	I2C_setTargetAddress(myI2C0_BASE, myI2C0_TARGET_ADDRESS);
	I2C_setBitCount(myI2C0_BASE, I2C_BITCOUNT_8);
	I2C_setDataCount(myI2C0_BASE, 1);
	I2C_setAddressMode(myI2C0_BASE, I2C_ADDR_MODE_7BITS);
	I2C_enableFIFO(myI2C0_BASE);
	I2C_setEmulationMode(myI2C0_BASE, I2C_EMULATION_FREE_RUN);
	I2C_enableModule(myI2C0_BASE);
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
	
	// Interrupt Settings for INT_myCPUTIMER0
	// ISR need to be defined for the registered interrupts
	Interrupt_register(INT_myCPUTIMER0, &INT_myCPUTIMER0_ISR);
	Interrupt_enable(INT_myCPUTIMER0);
	
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

