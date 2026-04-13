/*
 * acheating_control.h
 *
 *  Created on: Apr 1, 2026
 *      Author: Wang.Yiwen
 */

#ifndef TDDB_CONTROL_H_
#define TDDB_CONTROL_H_
#include "main.h"


#define ADC_TIME_TICK 2250.0f
#define DEMO_PORT_DIR_ALL_OUTPUT                (0x00U)

extern uint16_t driver_status, pwm_status, message_effect_status,sys_mode;
extern float cmp_1, tbprd, phs_1, phs_2, phs_3, phs_4;
extern float pwm_deadband;


extern void Init_bidirectional();
extern void ControlLoop();


#endif /* APP_INC_BIDIRECTIONAL_TEST_H_ */
