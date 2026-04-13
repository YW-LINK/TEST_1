/*
 * sys.h
 *
 *  Created on: 2023Äê3ÔÂ26ÈÕ
 *      Author: Zhang.Xinbo
 */

#ifndef APP_INC_SYS_H_
#define APP_INC_SYS_H_

#include "main.h"

extern void Delay_us(uint16_t us);
extern void Delay_ms(uint16_t ms);
extern void configCPUTimer(uint32_t cpuTimer, float freq, float period);


#endif /* APP_INC_SYS_H_ */
