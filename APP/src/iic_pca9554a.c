#include "iic_pca9554a.h"
/*
 * ======================== 文件总览 ========================
 * 本文件实现了 3 层结构：
 * 1) I2C 基础层：PCA9554A_I2C_Write / PCA9554A_I2C_WriteRead
 * 2) 寄存器层：PCA9554A_WriteReg / PCA9554A_ReadReg
 * 3) GPIO 业务层：Set/Get Pin/Port
 *
 * 这样分层的目的：
 * - I2C 时序细节集中在底层
 * - 寄存器协议集中在中层
 * - 业务逻辑写在上层，易读易维护
 */

/*
 * F28004x driverlib 的模式命名是 CONTROLLER_*。
 * 通过宏别名统一写法，便于阅读。
 */
#define PCA_I2C_SEND_MODE      I2C_CONTROLLER_SEND_MODE
#define PCA_I2C_RECV_MODE      I2C_CONTROLLER_RECEIVE_MODE

/* PCA9554A 寄存器地址 */
#define PCA9554A_REG_INPUT      (0x00U)  /* 输入寄存器：读 GPIO 当前电平 */
#define PCA9554A_REG_OUTPUT     (0x01U)  /* 输出寄存器：写 GPIO 输出电平 */
#define PCA9554A_REG_CONFIG     (0x03U)  /* 方向寄存器：1=输入，0=输出 */

/*
 * 新增：I2C 事务占用标志
 * 目的：防止定时器/主循环同时进入 I2C 访问，造成状态机冲突。
 */
static volatile bool g_pca9554aI2CBusy = false;

/* ------------------------ 内部工具函数（仅本文件可见） ------------------------ */

/* 检查 pin 是否在 0~7 范围内 */
static bool pca_is_valid_pin(uint8_t pin)
{
    return (pin < 8U);
}

/*
 * 等待 STOP 条件位清零。
 * 场景：上一次事务刚结束时，STP 位可能还没完全清掉。
 */
static PCA9554A_Status pca_wait_stop_clear(uint32_t i2cBase)
{
    uint32_t timeout = PCA9554A_TIMEOUT_TICKS; /* 超时保护，避免死循环 */

    while((I2C_getStopConditionStatus(i2cBase) == true) && (timeout > 0U))
    {
        timeout--;
    }

    if(timeout == 0U)
    {
        return PCA9554A_ERR_BUS;
    }

    return PCA9554A_OK;
}

/* 等待 I2C 总线空闲（BUS_BUSY 清零） */
static PCA9554A_Status pca_wait_bus_free(uint32_t i2cBase)
{
    uint32_t timeout = PCA9554A_TIMEOUT_TICKS;

    while((I2C_isBusBusy(i2cBase) == true) && (timeout > 0U))
    {
        timeout--;
    }

    if(timeout == 0U)
    {
        return PCA9554A_ERR_BUS;
    }

    return PCA9554A_OK;
}

/*
 * 检查 NACK（无应答）。
 * 若出现 NACK：清状态 + 发送 STOP 结束当前事务。
 */
static PCA9554A_Status pca_check_nack(uint32_t i2cBase)
{
    uint16_t sts = I2C_getStatus(i2cBase); /* 读取状态寄存器 */

    if((sts & I2C_STS_NO_ACK) != 0U)
    {
        I2C_clearStatus(i2cBase, I2C_STS_NO_ACK); /* 清 NACK 标志 */
        I2C_sendStopCondition(i2cBase);           /* 强制终止本次传输 */
        (void)pca_wait_stop_clear(i2cBase);       /* 等待 STOP 生效结束 */
        return PCA9554A_ERR_NACK;
    }

    return PCA9554A_OK;
}

/* 新增：尝试加锁（成功=true，已被占用=false） */
static bool pca_try_lock_i2c(void)
{
    if(g_pca9554aI2CBusy)
    {
        return false;
    }

    g_pca9554aI2CBusy = true;
    return true;
}

/* 新增：释放 I2C 占用标志 */
static void pca_unlock_i2c(void)
{
    g_pca9554aI2CBusy = false;
}

/*
 * 新增：错误收尾函数
 * 目的：无论哪种失败，都尽量发 STOP 并等待退出，减少 SCL 卡低概率。
 */
static void pca_force_stop_cleanup(uint32_t i2cBase)
{
    I2C_sendStopCondition(i2cBase);
    (void)pca_wait_stop_clear(i2cBase);
    I2C_clearStatus(i2cBase, (I2C_STS_NO_ACK | I2C_STS_REG_ACCESS_RDY | I2C_STS_STOP_CONDITION));
}

/* ------------------------ 初始化接口 ------------------------ */

/* 初始化总线对象：当前只需要保存 I2C base */
void PCA9554A_BusInit(PCA9554A_Bus *bus, uint32_t i2cBase)
{
    if(bus == 0)
    {
        return;
    }

    bus->i2cBase = i2cBase;
}

/*
 * 初始化单个设备对象：
 * 把 A2A1A0 地址位转换为 7-bit 地址，并保存到 handle。
 */
PCA9554A_Status PCA9554A_DeviceInit(PCA9554A_Handle *dev,
                                    PCA9554A_Bus *bus,
                                    uint8_t pca9554aAddrBitsA2A1A0)
{
    if((dev == 0) || (bus == 0))
    {
        return PCA9554A_ERR_PARAM;
    }

    dev->bus = bus;

    /* A2A1A0 仅低 3 位有效，所以用 &0x07 限制范围 */
    dev->ioAddr = (uint8_t)(PCA9554A_BASE_ADDR + (pca9554aAddrBitsA2A1A0 & 0x07U));

    return PCA9554A_OK;
}

/* ------------------------ I2C 基础层 ------------------------ */

/*
 * I2C 写流程：
 * 1) 检查 STOP/总线状态
 * 2) 配置地址/长度/模式
 * 3) 写入 TX 数据并 START
 * 4) 轮询等待发送完成
 * 5) STOP 收尾
 */
PCA9554A_Status PCA9554A_I2C_Write(PCA9554A_Bus *bus,
                                   uint8_t slaveAddr,
                                   const uint8_t *txData,
                                   uint16_t txLen)
{
    uint16_t i;
    uint32_t timeout;
    PCA9554A_Status st;
    bool txnStarted = false;

    if((bus == 0) || (txData == 0) || (txLen == 0U))
    {
        return PCA9554A_ERR_PARAM;
    }

    /*
     * 新增（兼容增强）：
     * 防并发重入。若上一笔事务还未结束，直接返回总线忙。
     */
    if(!pca_try_lock_i2c())
    {
        return PCA9554A_ERR_BUS;
    }

    /* 先确保总线处于可用状态 */
    st = pca_wait_stop_clear(bus->i2cBase);
    if(st != PCA9554A_OK)
    {
        goto write_error_exit;
    }

    st = pca_wait_bus_free(bus->i2cBase);
    if(st != PCA9554A_OK)
    {
        goto write_error_exit;
    }

    /* 清理上一笔可能残留的状态位 */
    I2C_clearStatus(bus->i2cBase,
                    (I2C_STS_NO_ACK | I2C_STS_REG_ACCESS_RDY | I2C_STS_STOP_CONDITION));

    /* 设置本次事务参数 */
    I2C_setAddressMode(bus->i2cBase, I2C_ADDR_MODE_7BITS); /* 7-bit 地址模式 */
    I2C_setTargetAddress(bus->i2cBase, slaveAddr);         /* 目标从机地址 */
    I2C_setDataCount(bus->i2cBase, txLen);                 /* 发 txLen 字节 */
    I2C_setConfig(bus->i2cBase, PCA_I2C_SEND_MODE);        /* 主机发送模式 */

    /* 预装载 TX FIFO */
    for(i = 0U; i < txLen; i++)
    {
        I2C_putData(bus->i2cBase, txData[i]);
    }

    I2C_sendStartCondition(bus->i2cBase); /* 发 START 开始传输 */
    txnStarted = true;

    /* 等 TX FIFO 为空，期间持续检查 NACK */
    timeout = PCA9554A_TIMEOUT_TICKS;
    while((I2C_getTxFIFOStatus(bus->i2cBase) != I2C_FIFO_TXEMPTY) && (timeout > 0U))
    {
        st = pca_check_nack(bus->i2cBase);
        if(st != PCA9554A_OK)
        {
            goto write_error_exit;
        }
        timeout--;
    }

    if(timeout == 0U)
    {
        st = PCA9554A_ERR_TIMEOUT;
        goto write_error_exit;
    }

    I2C_sendStopCondition(bus->i2cBase); /* 发 STOP 结束本次事务 */

    st = pca_wait_stop_clear(bus->i2cBase);
    if(st != PCA9554A_OK)
    {
        goto write_error_exit;
    }

    st = pca_check_nack(bus->i2cBase);
    pca_unlock_i2c();
    return st;

write_error_exit:
    /*
     * 新增（兼容增强）：
     * 失败统一收尾，避免出现“异常返回后 SCL 卡低”。
     */
    if(txnStarted)
    {
        pca_force_stop_cleanup(bus->i2cBase);
    }
    pca_unlock_i2c();
    return st;
}

/*
 * I2C 写后读流程（重复起始）：
 * 1) 写寄存器地址（txData）
 * 2) 等 ARDY
 * 3) 切换到接收模式并重复起始
 * 4) 逐字节读取 rxData
 * 5) STOP 收尾
 */
PCA9554A_Status PCA9554A_I2C_WriteRead(PCA9554A_Bus *bus,
                                       uint8_t slaveAddr,
                                       const uint8_t *txData,
                                       uint16_t txLen,
                                       uint8_t *rxData,
                                       uint16_t rxLen)
{
    uint16_t i;
    uint32_t timeout;
    PCA9554A_Status st;
    bool txnStarted = false;

    if((bus == 0) || (txData == 0) || (rxData == 0) || (txLen == 0U) || (rxLen == 0U))
    {
        return PCA9554A_ERR_PARAM;
    }

    /* 新增：防并发重入 */
    if(!pca_try_lock_i2c())
    {
        return PCA9554A_ERR_BUS;
    }

    st = pca_wait_stop_clear(bus->i2cBase);
    if(st != PCA9554A_OK)
    {
        goto wr_error_exit;
    }

    st = pca_wait_bus_free(bus->i2cBase);
    if(st != PCA9554A_OK)
    {
        goto wr_error_exit;
    }

    I2C_setAddressMode(bus->i2cBase, I2C_ADDR_MODE_7BITS);
    I2C_setTargetAddress(bus->i2cBase, slaveAddr);

    /* 第一步：先写寄存器地址（通常 txLen=1） */
    I2C_setDataCount(bus->i2cBase, txLen);
    I2C_setConfig(bus->i2cBase, (PCA_I2C_SEND_MODE | I2C_REPEAT_MODE));

    for(i = 0U; i < txLen; i++)
    {
        I2C_putData(bus->i2cBase, txData[i]);
    }

    I2C_sendStartCondition(bus->i2cBase);
    txnStarted = true;

    /* 等 ARDY：表示第一阶段发送完，可进入重复起始 */
    timeout = PCA9554A_TIMEOUT_TICKS;
    while(((I2C_getStatus(bus->i2cBase) & I2C_STS_REG_ACCESS_RDY) == 0U) && (timeout > 0U))
    {
        st = pca_check_nack(bus->i2cBase);
        if(st != PCA9554A_OK)
        {
            goto wr_error_exit;
        }
        timeout--;
    }

    if(timeout == 0U)
    {
        st = PCA9554A_ERR_TIMEOUT;
        goto wr_error_exit;
    }

    I2C_clearStatus(bus->i2cBase, I2C_STS_REG_ACCESS_RDY);

    /* 第二步：切接收模式并读 rxLen 字节 */
    I2C_setDataCount(bus->i2cBase, rxLen);
    I2C_setConfig(bus->i2cBase, PCA_I2C_RECV_MODE);
    I2C_sendStartCondition(bus->i2cBase); /* 重复起始 */

    for(i = 0U; i < rxLen; i++)
    {
        timeout = PCA9554A_TIMEOUT_TICKS;

        /* 等待 RX 就绪 */
        while(((I2C_getStatus(bus->i2cBase) & I2C_STS_RX_DATA_RDY) == 0U) && (timeout > 0U))
        {
            st = pca_check_nack(bus->i2cBase);
            if(st != PCA9554A_OK)
            {
                goto wr_error_exit;
            }
            timeout--;
        }

        if(timeout == 0U)
        {
            st = PCA9554A_ERR_TIMEOUT;
            goto wr_error_exit;
        }

        rxData[i] = (uint8_t)I2C_getData(bus->i2cBase); /* 读 1 字节 */
    }

    I2C_sendStopCondition(bus->i2cBase);

    st = pca_wait_stop_clear(bus->i2cBase);
    if(st != PCA9554A_OK)
    {
        goto wr_error_exit;
    }

    st = pca_check_nack(bus->i2cBase);
    pca_unlock_i2c();
    return st;

wr_error_exit:
    if(txnStarted)
    {
        pca_force_stop_cleanup(bus->i2cBase);
    }
    pca_unlock_i2c();
    return st;
}

/* 新增：提供给上层的“总线恢复”API */
PCA9554A_Status PCA9554A_I2C_RecoverBus(PCA9554A_Bus *bus)
{
    if(bus == 0)
    {
        return PCA9554A_ERR_PARAM;
    }

    /*
     * 方案：先做一次强制 STOP 收尾，再软复位 I2C 外设模块。
     * 说明：不改原有业务接口，遇到异常时可手动调用本函数恢复。
     */
    pca_force_stop_cleanup(bus->i2cBase);

    I2C_disableModule(bus->i2cBase);
    DEVICE_DELAY_US(10U);
    I2C_enableModule(bus->i2cBase);
    DEVICE_DELAY_US(10U);

    I2C_clearStatus(bus->i2cBase, (I2C_STS_NO_ACK | I2C_STS_REG_ACCESS_RDY | I2C_STS_STOP_CONDITION));

    if((pca_wait_stop_clear(bus->i2cBase) != PCA9554A_OK) ||
       (pca_wait_bus_free(bus->i2cBase) != PCA9554A_OK))
    {
        return PCA9554A_ERR_BUS;
    }

    return PCA9554A_OK;
}

/* 新增：供调试查看当前是否有事务在执行 */
bool PCA9554A_I2C_IsBusy(void)
{
    return g_pca9554aI2CBusy;
}

/* ------------------------ 寄存器层 ------------------------ */

/* 写寄存器：发送两个字节 [reg, value] */
PCA9554A_Status PCA9554A_WriteReg(PCA9554A_Handle *dev, uint8_t reg, uint8_t value)
{
    uint8_t tx[2];

    if((dev == 0) || (dev->bus == 0))
    {
        return PCA9554A_ERR_PARAM;
    }

    tx[0] = reg;   /* 第 1 字节：寄存器地址 */
    tx[1] = value; /* 第 2 字节：寄存器数据 */

    return PCA9554A_I2C_Write(dev->bus, dev->ioAddr, tx, 2U);
}

/* 读寄存器：先写 reg，再读 1 字节 */
PCA9554A_Status PCA9554A_ReadReg(PCA9554A_Handle *dev, uint8_t reg, uint8_t *value)
{
    if((dev == 0) || (dev->bus == 0) || (value == 0))
    {
        return PCA9554A_ERR_PARAM;
    }

    return PCA9554A_I2C_WriteRead(dev->bus, dev->ioAddr, &reg, 1U, value, 1U);
}

/* ------------------------ GPIO 业务层（pin 级） ------------------------ */

/*
 * 把 pin 设为输出：
 * CONFIG 位定义：1=输入，0=输出。
 * 所以要把目标 bit 清零。
 */
PCA9554A_Status PCA9554A_SetPinAsOutput(PCA9554A_Handle *dev, uint8_t pin)
{
    uint8_t cfg;
    PCA9554A_Status st;

    if((dev == 0) || (pca_is_valid_pin(pin) == false))
    {
        return PCA9554A_ERR_PARAM;
    }

    st = PCA9554A_ReadReg(dev, PCA9554A_REG_CONFIG, &cfg); /* 先读当前配置 */
    if(st != PCA9554A_OK)
    {
        return st;
    }

    cfg = (uint8_t)(cfg & (uint8_t)(~(1U << pin))); /* 清目标位 -> 输出 */
    return PCA9554A_WriteReg(dev, PCA9554A_REG_CONFIG, cfg); /* 写回 */
}

/* 把 pin 设为输入：把 CONFIG 对应 bit 置 1 */
PCA9554A_Status PCA9554A_SetPinAsInput(PCA9554A_Handle *dev, uint8_t pin)
{
    uint8_t cfg;
    PCA9554A_Status st;

    if((dev == 0) || (pca_is_valid_pin(pin) == false))
    {
        return PCA9554A_ERR_PARAM;
    }

    st = PCA9554A_ReadReg(dev, PCA9554A_REG_CONFIG, &cfg);
    if(st != PCA9554A_OK)
    {
        return st;
    }

    cfg = (uint8_t)(cfg | (uint8_t)(1U << pin)); /* 置目标位 -> 输入 */
    return PCA9554A_WriteReg(dev, PCA9554A_REG_CONFIG, cfg);
}

/*
 * 设置输出电平：
 * 先读 OUTPUT 再改 1 bit 再写回，避免影响其它 pin。
 */
PCA9554A_Status PCA9554A_SetPinOutputLevel(PCA9554A_Handle *dev, uint8_t pin, bool high)
{
    uint8_t out;
    PCA9554A_Status st;

    if((dev == 0) || (pca_is_valid_pin(pin) == false))
    {
        return PCA9554A_ERR_PARAM;
    }

    st = PCA9554A_ReadReg(dev, PCA9554A_REG_OUTPUT, &out);
    if(st != PCA9554A_OK)
    {
        return st;
    }

    if(high)
    {
        out = (uint8_t)(out | (uint8_t)(1U << pin));  /* 置位 -> 高电平 */
    }
    else
    {
        out = (uint8_t)(out & (uint8_t)(~(1U << pin))); /* 清位 -> 低电平 */
    }

    return PCA9554A_WriteReg(dev, PCA9554A_REG_OUTPUT, out);
}

/* 读取 pin 电平：读 INPUT 后提取目标位 */
PCA9554A_Status PCA9554A_GetPinLevel(PCA9554A_Handle *dev, uint8_t pin, bool *level)
{
    uint8_t inVal;
    PCA9554A_Status st;

    if((dev == 0) || (level == 0) || (pca_is_valid_pin(pin) == false))
    {
        return PCA9554A_ERR_PARAM;
    }

    st = PCA9554A_ReadReg(dev, PCA9554A_REG_INPUT, &inVal);
    if(st != PCA9554A_OK)
    {
        return st;
    }

    *level = ((inVal & (uint8_t)(1U << pin)) != 0U); /* bit=1 -> true */
    return PCA9554A_OK;
}

/* ------------------------ GPIO 业务层（port 级） ------------------------ */

/* 一次写整个方向寄存器 */
PCA9554A_Status PCA9554A_SetPortDirection(PCA9554A_Handle *dev, uint8_t directionRegValue)
{
    return PCA9554A_WriteReg(dev, PCA9554A_REG_CONFIG, directionRegValue);
}

/* 一次写整个输出寄存器 */
PCA9554A_Status PCA9554A_SetPortOutput(PCA9554A_Handle *dev, uint8_t outputRegValue)
{
    return PCA9554A_WriteReg(dev, PCA9554A_REG_OUTPUT, outputRegValue);
}

/* 一次读整个输入寄存器 */
PCA9554A_Status PCA9554A_GetPortInput(PCA9554A_Handle *dev, uint8_t *inputRegValue)
{
    return PCA9554A_ReadReg(dev, PCA9554A_REG_INPUT, inputRegValue);
}
