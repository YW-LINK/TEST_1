#ifndef IIC_PCA9554A_H
#define IIC_PCA9554A_H

#include "main.h"

/*
 * 文件作用：
 * 1) 定义 PCA9554A 驱动的数据结构与接口
 * 2) 给上层应用提供“按 pin”和“按 port”两种操作方式
 *
 * 适用场景：
 * - F280049C 作为 I2C 主机
 * - PCA9554A 直挂在同一条 I2C 总线上（无 MUX）
 */


#ifdef __cplusplus
extern "C" {
#endif
/* ------------------------ 宏定义 ------------------------ */

/* 你的系统里直挂了 5 片 PCA9554A */
#define PCA9554A_DEVICE_COUNT          (5U)

/* PCA9554A 的 7-bit 基地址，实际地址 = 0x38 + A2A1A0 */
#define PCA9554A_BASE_ADDR             (0x38U)

/* I2C 等待循环的超时计数，防止死等 */
#define PCA9554A_TIMEOUT_TICKS         (100000U)

/* ------------------------ 返回值定义 ------------------------ */

typedef enum
{
    PCA9554A_OK = 0,       /* 成功 */
    PCA9554A_ERR_PARAM,    /* 参数错误（空指针/越界等） */
    PCA9554A_ERR_BUS,      /* 总线忙或 STOP 状态异常 */
    PCA9554A_ERR_NACK,     /* 从机未应答 */
    PCA9554A_ERR_TIMEOUT   /* 轮询超时 */
} PCA9554A_Status;

/* ------------------------ 对象定义 ------------------------ */

/*
 * 总线对象：
 * - 只保存 I2C 外设 base
 * - 典型值：I2CA_BASE
 */
typedef struct
{
    uint32_t i2cBase;
} PCA9554A_Bus;

/*
 * 设备对象：
 * - bus: 挂在哪条 I2C 总线上
 * - ioAddr: 该设备的 7-bit I2C 地址
 */
typedef struct
{
    PCA9554A_Bus *bus;
    uint8_t ioAddr;
} PCA9554A_Handle;

/*
 * ======================== 调用关系总览 ========================
 * 建议按这个顺序理解代码：
 *
 * 1) I2C 基础层
 *    PCA9554A_I2C_Write / PCA9554A_I2C_WriteRead
 *
 * 2) 寄存器层
 *    PCA9554A_WriteReg / PCA9554A_ReadReg
 *
 * 3) GPIO 业务层
 *    pin 级：SetPinAsOutput / SetPinAsInput / SetPinOutputLevel / GetPinLevel
 *    port 级：SetPortDirection / SetPortOutput / GetPortInput
 *
 * pin 级 vs port 级的意义：
 * - pin 级：对业务代码友好，按单个引脚操作更直观。
 * - port 级：一次处理 8 位，适合初始化或批量更新。
 */

/* ------------------------ 初始化接口 ------------------------ */

/* 初始化总线对象（仅绑定 I2C base） */
void PCA9554A_BusInit(PCA9554A_Bus *bus, uint32_t i2cBase);

/*
 * 初始化设备对象
 * 参数 pca9554aAddrBitsA2A1A0: 0~7，对应地址位 A2A1A0
 * 例：A2A1A0=001 -> 7-bit 地址 0x39
 */
PCA9554A_Status PCA9554A_DeviceInit(PCA9554A_Handle *dev,
                                    PCA9554A_Bus *bus,
                                    uint8_t pca9554aAddrBitsA2A1A0);

/* ------------------------ I2C 基础接口 ------------------------ */

/* 纯写：START + 地址(W) + 数据 + STOP */
PCA9554A_Status PCA9554A_I2C_Write(PCA9554A_Bus *bus,
                                   uint8_t slaveAddr,
                                   const uint8_t *txData,
                                   uint16_t txLen);

/* 先写后读（重复起始）：常用于“先写寄存器地址，再读寄存器数据” */
PCA9554A_Status PCA9554A_I2C_WriteRead(PCA9554A_Bus *bus,
                                       uint8_t slaveAddr,
                                       const uint8_t *txData,
                                       uint16_t txLen,
                                       uint8_t *rxData,
                                       uint16_t rxLen);

/* ------------------------ 寄存器接口 ------------------------ */

/* 写 1 个寄存器：发送 [reg, value] */
PCA9554A_Status PCA9554A_WriteReg(PCA9554A_Handle *dev, uint8_t reg, uint8_t value);

/* 读 1 个寄存器：先写 reg，再读 1 字节 */
PCA9554A_Status PCA9554A_ReadReg(PCA9554A_Handle *dev, uint8_t reg, uint8_t *value);

/* ------------------------ GPIO 接口（pin 级） ------------------------ */

/* 把 pin 配置为输出：CONFIG 对应 bit 清零 */
extern PCA9554A_Status PCA9554A_SetPinAsOutput(PCA9554A_Handle *dev, uint8_t pin);

/* 把 pin 配置为输入：CONFIG 对应 bit 置位 */
extern PCA9554A_Status PCA9554A_SetPinAsInput(PCA9554A_Handle *dev, uint8_t pin);

/* 设置输出电平：OUTPUT 对应 bit = 1/0 */
extern PCA9554A_Status PCA9554A_SetPinOutputLevel(PCA9554A_Handle *dev, uint8_t pin, bool high);

/* 读取输入电平：读取 INPUT 后提取对应 bit */
extern PCA9554A_Status PCA9554A_GetPinLevel(PCA9554A_Handle *dev, uint8_t pin, bool *level);

/* ------------------------ GPIO 接口（port 级） ------------------------ */

/* 一次写整个 CONFIG 寄存器（bit=1 输入，bit=0 输出） */
extern PCA9554A_Status PCA9554A_SetPortDirection(PCA9554A_Handle *dev, uint8_t directionRegValue);

/* 一次写整个 OUTPUT 寄存器（bit=1 高，bit=0 低） */
extern PCA9554A_Status PCA9554A_SetPortOutput(PCA9554A_Handle *dev, uint8_t outputRegValue);

/* 一次读整个 INPUT 寄存器 */
extern PCA9554A_Status PCA9554A_GetPortInput(PCA9554A_Handle *dev, uint8_t *inputRegValue);

#ifdef __cplusplus
}
#endif

#endif
