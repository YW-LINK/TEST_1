#ifndef SCI_CMD_H
#define SCI_CMD_H

#define CMD_PWM_EN      0x02
extern void PwmEnable();

#define CMD_PWM_DIS     0x03
extern void PwmDisable();

#define CMD_DRV_EN      0x04
extern void GateDriverEnable();

#define CMD_DRV_DIS     0x05
extern void GateDriverDisable();

#define CMD_CMPPHS_SET     0x08
extern void PrdSet(float *data);

#define CMD_TRIGGER     0x30
extern void Trigger();

enum VALUE_CHOSE
{
    NONE_VALUE=0,
    FLOAT_INPUT_VOLTAGE,
    FLOAT_INPUT_CURRENT,
    FLOAT_INDUCTOR_CURRENT,
    FLOAT_CIRCULATING_CURRENT,
    FLOAT_TEST_SIN,
    FLOAT_TEST_COS,
    FLOAT_TEST_CON,
    STATUE_MASTER1,
    STATUE_MASTER2
};

#define VAL_ADDER_LONG 37
extern float * val_adder[VAL_ADDER_LONG];
extern Uint16 val_adder_chose[4];

extern volatile void rxCmdList(void);
extern void Init_val_adder(void);
#endif // SCI_CMD_H

