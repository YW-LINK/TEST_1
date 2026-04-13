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

//
// Includes
//
#include "c2000_freertos.h"

uint8_t ucHeap[ 4096 ];
#pragma DATA_SECTION(ucHeap,   ".freertosHeap")
#pragma DATA_ALIGN ( ucHeap , portBYTE_ALIGNMENT )

StaticTask_t idleTaskTCBBuffer;
StackType_t idleTaskStack[IDLE_TASK_STACK_SIZE];
#pragma DATA_SECTION(idleTaskStack, ".freertosStaticStack")
#pragma DATA_ALIGN ( idleTaskStack , portBYTE_ALIGNMENT )

//
// Variables for dalypack TCB and stack
//
StaticTask_t dalypackTCBBuffer;
StackType_t dalypackStackBuffer[dalypack_STACK_SIZE];
#pragma DATA_SECTION(dalypackStackBuffer, ".freertosStaticStack")
#pragma DATA_ALIGN ( dalypackStackBuffer , portBYTE_ALIGNMENT )

//
// Task Handle for dalypack
//
TaskHandle_t dalypackHandle = NULL;

//
// Variables for sendcharge TCB and stack
//
StaticTask_t sendchargeTCBBuffer;
StackType_t sendchargeStackBuffer[sendcharge_STACK_SIZE];
#pragma DATA_SECTION(sendchargeStackBuffer, ".freertosStaticStack")
#pragma DATA_ALIGN ( sendchargeStackBuffer , portBYTE_ALIGNMENT )

//
// Task Handle for sendcharge
//
TaskHandle_t sendchargeHandle = NULL;

//
// Variables for recivecmd TCB and stack
//
StaticTask_t recivecmdTCBBuffer;
StackType_t recivecmdStackBuffer[recivecmd_STACK_SIZE];
#pragma DATA_SECTION(recivecmdStackBuffer, ".freertosStaticStack")
#pragma DATA_ALIGN ( recivecmdStackBuffer , portBYTE_ALIGNMENT )

//
// Task Handle for recivecmd
//
TaskHandle_t recivecmdHandle = NULL;

//
// Declare a variable to hold the handle of the created semaphore.
//
SemaphoreHandle_t  mySemaphore0Handle = NULL;

//
// Declare a variable to hold data associated with the created static semaphore.
//
StaticSemaphore_t mySemaphore0Buffer;

//
// Declare a variable to hold the handle of the created semaphore.
//
SemaphoreHandle_t  mySemaphore1Handle = NULL;

//
// Declare a variable to hold data associated with the created static semaphore.
//
StaticSemaphore_t mySemaphore1Buffer;

//
// dalypack_init() - Initializes task dalypack
//
void dalypack_init() {
    //
    // Create the task with static memory allocation.
    //
    dalypackHandle =
    xTaskCreateStatic(daly_pack,          // Function that implements the task.
                      "dalypack",              // Text name for the task.
                      512,        // Number of indexes in the xStack array.
                      (void *) NULL,  // Parameter passed into the task.
                      10,         // Priority at which the task is created.
                      dalypackStackBuffer,      // Array to use as the task's stack.
                      &dalypackTCBBuffer );  // Variable to hold the task's TCB
}

//
// sendcharge_init() - Initializes task sendcharge
//
void sendcharge_init() {
    //
    // Create the task with static memory allocation.
    //
    sendchargeHandle =
    xTaskCreateStatic(send_charge,          // Function that implements the task.
                      "sendcharge",              // Text name for the task.
                      512,        // Number of indexes in the xStack array.
                      (void *) NULL,  // Parameter passed into the task.
                      1,         // Priority at which the task is created.
                      sendchargeStackBuffer,      // Array to use as the task's stack.
                      &sendchargeTCBBuffer );  // Variable to hold the task's TCB
}

//
// recivecmd_init() - Initializes task recivecmd
//
void recivecmd_init() {
    //
    // Create the task with static memory allocation.
    //
    recivecmdHandle =
    xTaskCreateStatic(recive_cmd,          // Function that implements the task.
                      "recivecmd",              // Text name for the task.
                      256,        // Number of indexes in the xStack array.
                      (void *) NULL,  // Parameter passed into the task.
                      5,         // Priority at which the task is created.
                      recivecmdStackBuffer,      // Array to use as the task's stack.
                      &recivecmdTCBBuffer );  // Variable to hold the task's TCB
}

//
// mySemaphore0_init() - Initializes semaphore mySemaphore0
//
void mySemaphore0_init() {
    //
    // Create the binary semaphore with static memory allocation.
    //
    mySemaphore0Handle =
    xSemaphoreCreateBinaryStatic(&mySemaphore0Buffer);

}

//
// mySemaphore1_init() - Initializes semaphore mySemaphore1
//
void mySemaphore1_init() {
    //
    // Create the binary semaphore with static memory allocation.
    //
    mySemaphore1Handle =
    xSemaphoreCreateBinaryStatic(&mySemaphore1Buffer);

}

//
// vApplicationGetIdleTaskMemory - Application must provide an implementation
// of vApplicationGetIdleTaskMemory() to provide the memory that is used by the
// Idle task if configUSE_STATIC_ALLOCATION is set to 1.
//
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
    /* If the buffers to be provided to the Idle task are declared inside this
    function then they must be declared static - otherwise they will be allocated on
    the stack and so not exists after this function exits. */

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &idleTaskTCBBuffer;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = idleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t, size is
    specified in words, not bytes. */
    *pulIdleTaskStackSize = IDLE_TASK_STACK_SIZE;
}




//
// FreeRTOS_init - Initializes added FreeRTOS constructs and starts the scheduler
//
void FreeRTOS_init(){
    dalypack_init();
    sendcharge_init();
    recivecmd_init();
    mySemaphore0_init();
    mySemaphore1_init();

    //
    // Start the scheduler
    //
    vTaskStartScheduler();
}
