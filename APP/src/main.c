

/**
 * main.c
 *
 *  Created on: Apr 1, 2026
 *      Author: Wang.Yiwen
 */
#include "main.h"


signed rxHigherPriorityTaskWoken;



void main(void)
{
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();

    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    Board_init();
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    Interrupt_enableGlobal();
    Interrupt_disable(INT_mySCI0_RX);
    GateDriverDisable();
    PwmDisable();
    SciRxPacketReset();
    Interrupt_disable(INT_myCPUTIMER0);
    Delay_ms(500);
    Init_bidirectional();
    LED_GREEN_TGL;
    Delay_ms(5000);
    mySCI0_init();
    LED_GREEN_TGL;
    Interrupt_enable(INT_mySCI0_RX);
    Interrupt_enable(INT_myCPUTIMER0);

    FreeRTOS_init();

}

__attribute__((ramfunc))
__interrupt void INT_myCPUTIMER0_ISR(void)
{
    volatile uint16_t tempPIEIER = HWREGH(PIECTRL_BASE + PIE_O_IER1);

    IER |= M_INT1;
    IER &= MINT1;
    HWREGH(PIECTRL_BASE + PIE_O_IER1) &= MG1_7;

    Interrupt_clearACKGroup(0xFFFFU);
    __asm("  NOP");
    EINT;

    ControlLoop();
    // 3. 清除PIE中断标志位
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

    DINT;
    HWREGH(PIECTRL_BASE + PIE_O_IER1) = tempPIEIER;
}


// __attribute__((ramfunc))
// __interrupt void INT_myADCA_1_ISR(void)
// {

//     volatile uint16_t tempPIEIER = HWREGH(PIECTRL_BASE + PIE_O_IER1);
// //
//     //
//     // Set the global and group priority to allow CPU interrupts
//     // with higher priority
//     //
//     IER |= M_INT1;
//     IER &= MINT1;
//     HWREGH(PIECTRL_BASE + PIE_O_IER1) &= MG1_1;

//     //
//     // Enable Interrupts
//     //
//     Interrupt_clearACKGroup(0xFFFFU);
//     __asm("  NOP");
//     EINT;

//     // ControlLoop();
//     ADC_clearInterruptStatus(myADCA_BASE, ADC_INT_NUMBER1);
//     Interrupt_clearACKGroup(INT_myADCA_1_INTERRUPT_ACK_GROUP);
//     //
//     // Disable interrupts and restore registers saved:
//     //
//     DINT;
//     HWREGH(PIECTRL_BASE + PIE_O_IER1) = tempPIEIER;




// }

__attribute__((ramfunc))
__interrupt void INT_mySCI0_RX_ISR()
{
    volatile uint16_t tempPIEIER = HWREGH(PIECTRL_BASE + PIE_O_IER9);
    //
    // Set the global and group priority to allow CPU interrupts
    // with higher priority
    //
    IER |= M_INT9;
    IER &= MINT9;
    HWREGH(PIECTRL_BASE + PIE_O_IER9) &= MG9_1;
    //
    // Enable Interrupts
    //
    Interrupt_clearACKGroup(0xFFFFU);
    __asm("  NOP");
    EINT;

    static uint16_t recive_word = 0;
    static uint16_t recove_turn = 0;
    static uint16_t error_turn = 0;
    uint16_t i = 0;
    uint16_t recive_len = SCI_getRxFIFOStatus(mySCI0_BASE);
    rxHigherPriorityTaskWoken = pdFALSE;

    if (SCI_getRxStatus(SCIA_BASE) & (SCI_RXST_FE | SCI_RXST_OE | SCI_RXST_PE)) {
            SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_RXERR);
            SCI_resetRxFIFO(SCIA_BASE);
            error_turn++;
    }

    for(i=0;i<recive_len;i++)
    {
        recove_turn++;
        if(recove_turn%2 == 0)
        {
            recove_turn = 0;
            recive_word += SCI_readCharBlockingFIFO(mySCI0_BASE)<<8;
            rxDecodeWord(recive_word);
        }
        else
        {
            recive_word = SCI_readCharBlockingFIFO(mySCI0_BASE);
        }

    }
    if(error_turn>0||RxPacketCtrl.ErrorTurn>10)
    {
        error_turn = 0;
        recove_turn = 0;
        RxPacketCtrl.ErrorTurn = 0;
    }
    SCI_clearInterruptStatus(mySCI0_BASE, SCI_INT_RXFF);
    Interrupt_clearACKGroup(INT_mySCI0_RX_INTERRUPT_ACK_GROUP);

    DINT;
    HWREGH(PIECTRL_BASE + PIE_O_IER9) = tempPIEIER;

}

__attribute__((ramfunc))
__interrupt void INT_mySCI0_TX_ISR()
{
    SCI_clearInterruptStatus(mySCI0_BASE, SCI_INT_TXFF);
    Interrupt_clearACKGroup(INT_mySCI0_TX_INTERRUPT_ACK_GROUP);
}

#pragma CODE_SECTION(daly_pack, ".TI.ramfunc");
void daly_pack(void * pvParameters )
{
    for(;;)
    {
        dalychose.add_daly.dalyfloat[0] = (uint16_t)cmp_1;
        dalychose.add_daly.dalyfloat[1] = (uint16_t)tbprd;
        dalychose.add_daly.dalyfloat[2] = (uint16_t)phs_2;
        dalychose.add_daly.dalyfloat[3] = (uint16_t)phs_3;
        dalychose.add_daly.dalyU16[0].status.driver_on = driver_status;
        dalychose.add_daly.dalyU16[0].status.pwm_on = pwm_status;
        dalychose.add_daly.dalyU16[0].status.reserve1 =sys_mode;
        dalychose.add_daly.dalyU16[1].int16 = (uint16_t)pwm_deadband;
        daly_data_pack(dalychose.add_daly);
        vTaskDelay(200);
    }
}

#pragma CODE_SECTION(send_charge, ".TI.ramfunc");
void send_charge(void * pvParameters )
{
    for(;;)
    {
        LED_RED_TGL;
        executaske();
        vTaskDelay(100);
    }
}

#pragma CODE_SECTION(recive_cmd, ".TI.ramfunc");
void recive_cmd(void * pvParameters )
{
    for(;;)
    {
        xSemaphoreTake(mySemaphore0Handle, portMAX_DELAY);
        rxCmdList();
        logdata_lock = 1;
        dalydata_lock = 1;
        tempdata_lock = 1;
        data_lock = 1;
        task_lock = 1;
    }
}


