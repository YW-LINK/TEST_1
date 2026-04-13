/*
 * sys.c
 *
 *  Created on: 2023Äê3ÔÂ26ÈÕ
 *      Author: Zhang.Xinbo
 */
#include "sys.h"



void Delay_us(uint16_t us);
void Delay_ms(uint16_t ms);
void configCPUTimer(uint32_t cpuTimer, float freq, float period);


void Delay_us(uint16_t us)
{
    DEVICE_DELAY_US(us);
}

void Delay_ms(uint16_t ms)
{
    uint16_t i =ms;
    for(;i>0;i--)
    {
        Delay_us(1000);
    }
}


void configCPUTimer(uint32_t cpuTimer, float freq, float period)
{
    uint32_t temp;
    //
    // Initialize timer period:
    //
    temp = (uint32_t)((freq / 1000000) * period);
    CPUTimer_setPeriod(cpuTimer, temp);
    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    CPUTimer_setPreScaler(cpuTimer, 0);
    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    //
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);

}
