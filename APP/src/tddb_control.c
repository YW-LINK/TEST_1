/*
 * acheating_control.c
 *
 *  Created on: Apr 1, 2026
 *      Author: Wang.Yiwen
 */

#include "tddb_control.h"

static PCA9554A_Bus gBus;                                /* 全局总线对象 */
static PCA9554A_Handle gDev[PCA9554A_DEVICE_COUNT];      /* 5 个设备对象 */

float cmp_1 = 2499.0f, tbprd = 4999.0f, phs_1= 4998.0f, phs_2= 0.0f, phs_3= 0.0f, phs_4= 0.0f;
float pwm_deadband = 20.0f;
uint16_t driver_status=0, pwm_status=0, message_effect_status=0,sys_mode=0;
float CH0_value_1X = 0.0f, CH0_value_10X = 0.0f, LDO_FB1 = 0.0f;
uint16_t time_turn=0;

float Igss = 0.0f, a_Igss = 222.49554271f, b_Igss = -2022.33216392f;
float Vgs = 0.0f;
// float a_Vgs = 0.00098121f, b_Vgs = -0.07473319f;  //100倍
float a_Vgs = 0.00019766f, b_Vgs = -0.06809569f;  //500倍

void Init_bidirectional();
void ControlLoop();
PCA9554A_Status PCA9554A_SetOutput8Level(uint8_t p0, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6, uint8_t p7);
PCA9554A_Status TDDB_ChannelSelect_Set(uint8_t channel);

void Init_bidirectional()
{
    I2C_A0_EN;
    I2C_A1_DIS;
    I2C_A2_DIS;
    GateDriverEnable();
    PCA9554A_Init();
}


void PCA9554A_Init(void)
{
    // PCA9554A_init(myI2C0_BASE, PCA9554A_I2C_ADDR);
    // PCA9554A_configDirection(0x00U);
    // PCA9554A_writeOutputs(0xE5U);

    uint16_t i;

    /*
     * 5 片 PCA9554A 的地址位 A2A1A0：001/010/011/100/101
     * 对应 7-bit 地址：0x39/0x3A/0x3B/0x3C/0x3D
     */
    const uint8_t addrBits[PCA9554A_DEVICE_COUNT] = {1U, 2U, 3U, 4U, 5U};

    /* 第一步：绑定 I2C 外设（这里使用 I2CA） */
    PCA9554A_BusInit(&gBus, myI2C0_BASE);

    /* 第二步：循环初始化 5 个设备句柄 */
    for(i = 0U; i < PCA9554A_DEVICE_COUNT; i++)
    {
        (void)PCA9554A_DeviceInit(&gDev[i], &gBus, addrBits[i]);
    }

    // for(i = 0U; i < PCA9554A_DEVICE_COUNT; i++)
    // {
    //     (void)PCA9554A_SetPortDirection(&gDev[i], DEMO_PORT_DIR_ALL_OUTPUT);
    // }

    (void)PCA9554A_SetPortDirection(&gDev[0], DEMO_PORT_DIR_ALL_OUTPUT);
    Delay_ms(10);
    (void)PCA9554A_SetOutput8Level(0U, 0U, 0U, 0U, 1U, 1U, 0U, 1U);
}

/*
 * 通过 8 个独立参数设置 P0~P7 输出电平（参数传 0/1 即可）：
 * p0 对应 P0，p1 对应 P1 ... p7 对应 P7
 *
 * 设计说明（解耦与易改）：
 * - 调用者不需要关心位移和位掩码，只传每个引脚的目标电平。
 * - 函数内部统一做“0/1标准化”，即使传入非0值也按1处理。
 */
PCA9554A_Status PCA9554A_SetOutput8Level(uint8_t p0, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4, uint8_t p5, uint8_t p6, uint8_t p7)
{
    uint8_t outRegValue;

    /* 把每个参数标准化为 0 或 1，再放到对应 bit 位 */
    outRegValue = (uint8_t)(
        ((p0 ? 1U : 0U) << 0U) |
        ((p1 ? 1U : 0U) << 1U) |
        ((p2 ? 1U : 0U) << 2U) |
        ((p3 ? 1U : 0U) << 3U) |
        ((p4 ? 1U : 0U) << 4U) |
        ((p5 ? 1U : 0U) << 5U) |
        ((p6 ? 1U : 0U) << 6U) |
        ((p7 ? 1U : 0U) << 7U)
    );

    /* 一次写 OUTPUT 寄存器，更新 P0~P7 全部输出电平 */
    return PCA9554A_SetPortOutput(&gDev[0], outRegValue);
}

/*
 * 关闭所有通道（COM 与 CH0~CH15 全断开）
 * 原理：两片 74HC4051 的 E# 都置为高电平（禁用）
 */
PCA9554A_Status TDDB_ChannelSelect_DisableAll(void)
{
    return PCA9554A_SetOutput8Level(
        0U, 0U, 0U, 0U,
        1U, /* EN1=1 */
        1U, /* EN2=1 */
        0U, 0U
    );
}

/*
 * 核心函数：按通道号选择 CH0~CH15 到 COM
 *
 * 参数：
 * channel: 0~15
 *
 * 返回：
 * PCA9554A_OK           选择成功
 * PCA9554A_ERR_PARAM    通道号非法（不在 0~15）
 * 其它错误码            I2C 或器件访问失败
 */
PCA9554A_Status TDDB_ChannelSelect_Set(uint8_t channel)
{
    uint8_t a0;
    uint8_t a1;
    uint8_t a2;
    uint8_t en1;
    uint8_t en2;
    uint8_t sel;
    uint8_t led2;
    uint8_t led1;

    if(channel > 15U)
    {
        return PCA9554A_ERR_PARAM;
    }

    if(channel < 8U)
    {
        /* CH0~CH7: 使能 U1，关闭 U4 */
        sel = channel;
        en1 = 0U; /* E# 低有效 -> 使能 */
        en2 = 1U; /* 关闭 */
        led2 = 1U;
        led1 = 0U;
    }
    else
    {
        /* CH8~CH15: 关闭 U1，使能 U4 */
        sel = (uint8_t)(channel - 8U);
        en1 = 1U; /* 关闭 */
        en2 = 0U; /* 使能 */
        led2 = 0U;
        led1 = 1U;
    }

    /* 拆出地址位 A2/A1/A0 */
    a0 = (uint8_t)((sel >> 0U) & 0x01U);
    a1 = (uint8_t)((sel >> 1U) & 0x01U);
    a2 = (uint8_t)((sel >> 2U) & 0x01U);

    /*
     * 写到 PCA9554A：
     * P0=A0, P1=A1, P2=A2, P4=EN1, P5=EN2
     */
    return PCA9554A_SetOutput8Level(
        a0,  /* P0 */
        a1,  /* P1 */
        a2,  /* P2 */
        0U,  /* P3 unused */
        en1, /* P4 -> EN1 */
        en2, /* P5 -> EN2 */
        led2,  /* P6 -> led2 */
        led1   /* P7 -> led1 */
    );
}

#pragma CODE_SECTION(ControlLoop, ".TI.ramfunc");
void ControlLoop()
{
    // time_turn++;
    // if(time_turn <= 500)
    // {
    //     PCA9554A_SetOutput8Level(1U, 1U, 1U, 0U, 0U, 1U, 1U, 0U);
    // }
    // else if(time_turn <= 1000)
    // {
    //     PCA9554A_SetOutput8Level(1U, 1U, 1U, 0U, 0U, 1U, 0U, 1U);
    // }
    // else time_turn = 0;
    
    TDDB_ChannelSelect_Set(0U);
    Delay_us(5);

    ADC_forceMultipleSOC(myADCA_BASE, (ADC_FORCE_SOC0|ADC_FORCE_SOC1|ADC_FORCE_SOC2|ADC_FORCE_SOC3|ADC_FORCE_SOC4));
    ADC_forceMultipleSOC(myADCB_BASE, (ADC_FORCE_SOC0|ADC_FORCE_SOC1|ADC_FORCE_SOC2|ADC_FORCE_SOC3|ADC_FORCE_SOC4));
    ADC_forceMultipleSOC(myADCC_BASE, (ADC_FORCE_SOC0|ADC_FORCE_SOC1|ADC_FORCE_SOC2|ADC_FORCE_SOC3|ADC_FORCE_SOC4));
    while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1) == false)
    {
    }
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

    while(ADC_getInterruptStatus(ADCB_BASE, ADC_INT_NUMBER1)== false)
    {
    }
    ADC_clearInterruptStatus(ADCB_BASE, ADC_INT_NUMBER1);

    while(ADC_getInterruptStatus(ADCC_BASE, ADC_INT_NUMBER1) == false)
    {
    }
    ADC_clearInterruptStatus(ADCC_BASE, ADC_INT_NUMBER1);

    CH0_value_1X = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
    CH0_value_10X = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER1);
    Vgs = CH0_value_10X * a_Vgs + b_Vgs;
    Igss = Vgs * 1e6 / 40.33f;

    LDO_FB1 = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER0);

}

