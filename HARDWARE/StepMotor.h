#ifndef _STEPMOTOR_H_
#define _STEPMOTOR_H_

#include "stm32f10x_gpio.h"
#include "sys.h"

#define PUL GPIO_Pin_0             //脉冲
#define DIR GPIO_Pin_1             //方向
#define ENA GPIO_Pin_2             //使能
#define MOTOR_PORT       GPIOA

#define PUL_HIGH      GPIO_Setbits(MOTOR_PORT,PUL);
#define PUL_LOW       GPIO_ResetBits(MOTOR_PORT,PUL);

#define DIR_HIGH      GPIO_Setbits(MOTOR_PORT,DIR);
#define DIR_LOW       GPIO_ResetBits(MOTOR_PORT,DIR);

#define ENA_HIGH      GPIO_Setbits(MOTOR_PORT,ENA);
#define ENA_LOW       GPIO_ResetBits(MOTOR_PORT,ENA);

void StepMotor_Config(u16 Period , u16 Prescaler);

void StepMotor_Init(void);


#endif

