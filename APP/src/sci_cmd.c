#include "main.h"

float *val_adder[VAL_ADDER_LONG];
Uint16 val_adder_chose[4];

void Init_val_adder(void);
volatile void rxCmdList(void);

void Init_val_adder(void)
{
    val_adder[0] = &cmp_1;
    val_adder[1] = &tbprd;
    val_adder[2] = &phs_1;
    val_adder[3] = &phs_2;
    val_adder[4] = &phs_3;
    val_adder[5] = &phs_4;

    val_adder_chose[0] = 1;
    val_adder_chose[1] = 2;
    val_adder_chose[2] = 3;
    val_adder_chose[3] = 4;

}

#pragma CODE_SECTION(rxCmdList, ".TI.ramfunc");
volatile void rxCmdList(void)
{
    switch(RxPacketCtrl.CtrlByte)
    {

        case CMD_PWM_EN:
        {
            PwmEnable();
            break;
        }
        case CMD_PWM_DIS:
        {
            PwmDisable();
            break;
        }
        case CMD_DRV_EN:
        {
            GateDriverEnable();
            break;
        }
        case CMD_DRV_DIS:
        {
            GateDriverDisable();
            break;
        }
        case CMD_CMPPHS_SET:
        {
            PrdSet(RxPacketBuffer.float32);
            break;
        }
        case CMD_TRIGGER:
        {
            Trigger();
            break;
        }
        default:
        {
            break;
        }
    }
}

void GateDriverEnable()
{
    RLY_EN;
    driver_status = 1;
}

void GateDriverDisable()
{
    RLY_DIS;
    driver_status = 0;
}

void PrdSet(float *data)
{
    float32 turn = 0;
    Interrupt_disable(INT_myCPUTIMER0);
    cmp_1 = data[0];
    tbprd = data[1];
    phs_1 = tbprd-1;
    phs_2 = data[2];
    phs_3 = data[3];
    phs_4 = data[4];
    turn = ADC_TIME_TICK/tbprd;
    if((Uint16)(turn+1)>15)turn = 14.0f;
    // EPWM_setADCTriggerEventPrescale(myEPWM1_BASE, EPWM_SOC_A, (Uint16)(turn+1));
    // EPWM_setADCTriggerEventPrescale(myEPWM1_BASE, EPWM_SOC_B, (Uint16)(turn+1));
    Interrupt_enable(INT_myCPUTIMER0);
}

void PwmEnable()
{
    // EPWM_clearTripZoneFlag(myEPWM1_BASE , EPWM_TZ_FLAG_OST);
    // EPWM_clearTripZoneFlag(myEPWM2_BASE , EPWM_TZ_FLAG_OST);
    // EPWM_clearTripZoneFlag(myEPWM3_BASE , EPWM_TZ_FLAG_OST);
    pwm_status = 1;
}

void PwmDisable()
{
    // EPWM_forceTripZoneEvent(myEPWM1_BASE, EPWM_TZ_FORCE_EVENT_OST);
    // EPWM_forceTripZoneEvent(myEPWM2_BASE, EPWM_TZ_FORCE_EVENT_OST);
    // EPWM_forceTripZoneEvent(myEPWM3_BASE, EPWM_TZ_FORCE_EVENT_OST);
    pwm_status = 0;
}


void Trigger()
{
    log_map.trigger.flag = 1;
}

