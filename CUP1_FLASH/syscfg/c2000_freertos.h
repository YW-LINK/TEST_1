/*
 * Copyright (C) 2021 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef C2000_FREERTOS_H
#define C2000_FREERTOS_H

//
// Includes
//
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "timers.h"
#include "event_groups.h"
#include "driverlib.h"

extern uint8_t ucHeap[ 4096 ];

//
// Idle task specific macros
//
#define IDLE_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

//
// Idle task specific variables
//
extern StaticTask_t idleTaskTCBBuffer;
extern StackType_t idleTaskStack[IDLE_TASK_STACK_SIZE];

//
// Macro for task stack size
//
#define dalypack_STACK_SIZE 512

//
// Variables for Task TCB and stack
//
extern StaticTask_t dalypackTCBBuffer;
extern StackType_t dalypackStackBuffer[dalypack_STACK_SIZE];

//
// Task Handle for task dalypack
//
extern TaskHandle_t dalypackHandle;

//
// Macro for task stack size
//
#define sendcharge_STACK_SIZE 512

//
// Variables for Task TCB and stack
//
extern StaticTask_t sendchargeTCBBuffer;
extern StackType_t sendchargeStackBuffer[sendcharge_STACK_SIZE];

//
// Task Handle for task sendcharge
//
extern TaskHandle_t sendchargeHandle;

//
// Macro for task stack size
//
#define recivecmd_STACK_SIZE 256

//
// Variables for Task TCB and stack
//
extern StaticTask_t recivecmdTCBBuffer;
extern StackType_t recivecmdStackBuffer[recivecmd_STACK_SIZE];

//
// Task Handle for task recivecmd
//
extern TaskHandle_t recivecmdHandle;

//
// Declare a variable to hold the handle of the created semaphore.
//
extern SemaphoreHandle_t  mySemaphore0Handle;

//
// Declare a variable to hold data associated with the created static semaphore.
//
extern StaticSemaphore_t mySemaphore0Buffer;

//
// Declare a variable to hold the handle of the created semaphore.
//
extern SemaphoreHandle_t  mySemaphore1Handle;

//
// Declare a variable to hold data associated with the created static semaphore.
//
extern StaticSemaphore_t mySemaphore1Buffer;


//
// Declaration for dalypack task function. Application needs to implement this.
//
extern void daly_pack( void * pvParameters );

//
// Declaration for sendcharge task function. Application needs to implement this.
//
extern void send_charge( void * pvParameters );

//
// Declaration for recivecmd task function. Application needs to implement this.
//
extern void recive_cmd( void * pvParameters );

//
// Init Functions
//
void dalypack_init();
void sendcharge_init();
void recivecmd_init();
void mySemaphore0_init();
void mySemaphore1_init();
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize );
void vApplicationSetupTimerInterrupt( void );
void FreeRTOS_init();

#endif /* C2000_FREERTOS_H */

