/*
 * main.h
 *
 *  Created on: Apr 1, 2026
 *      Author: Wang.Yiwen
 */

#ifndef APP_INC_MAIN_H_
#define APP_INC_MAIN_H_


#include "board.h"
#include "c2000ware_libraries.h"
#include "c2000_freertos.h"
#include "sw_prioritized_isr_levels.h"
#include "sys.h"
#include "sci_cmd.h"
#include "sci_fifo.h"
#include "tddb_control.h"
#include "iic_pca9554a.h"

//#include "powercycling_control_loop.h"
//#include "iic_fifo.h"
//#include "iic_mlx906.h"

#define ERRO 0
#define SUCCESS 1

#define LED_RED_ON      GPIO_writePin(LED_RED, 0)
#define LED_RED_OFF     GPIO_writePin(LED_RED, 1)
#define LED_RED_TGL     GPIO_togglePin(LED_RED)

#define LED_GREEN_ON    GPIO_writePin(LED_GREEN, 0)
#define LED_GREEN_OFF   GPIO_writePin(LED_GREEN, 1)
#define LED_GREEN_TGL   GPIO_togglePin(LED_GREEN)

// #define DRV_EN          GPIO_writePin(DRV, 1)
// #define DRV_DIS         GPIO_writePin(DRV, 0)

#define RLY_EN   GPIO_writePin(RLY, 1)
#define RLY_DIS  GPIO_writePin(RLY, 0)
#define I2C_A0_EN   GPIO_writePin(I2C_A0, 1)
#define I2C_A0_DIS  GPIO_writePin(I2C_A0, 0)
#define I2C_A1_EN   GPIO_writePin(I2C_A1, 1)
#define I2C_A1_DIS  GPIO_writePin(I2C_A1, 0)
#define I2C_A2_EN   GPIO_writePin(I2C_A2, 1)
#define I2C_A2_DIS  GPIO_writePin(I2C_A2, 0)

extern signed rxHigherPriorityTaskWoken;
extern volatile Uint16 time_test_cmp1 ;
extern volatile Uint16 time_test_cmp2 ;
extern volatile Uint16 time_test_cmp3 ;
extern volatile Uint16 time_test_db ;
extern volatile Uint16 time_test_rest ;
//extern Uint16 test_cmp1;
//extern Uint16 test_cmp2;
//extern Uint16 test_cmp3;
//extern Uint16 test_db;
//extern void double_pulse(void);
#endif /* APP_INC_MAIN_H_ */
