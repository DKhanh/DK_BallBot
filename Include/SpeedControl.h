/*
 * PWM.h
 *
 *  Created on: Mar 18, 2016
 *      Author: DKhanh
 */

#ifndef PWM_
#define PWM_

#include "stm32f4xx.h"

typedef enum
{
	MOTOR_A = 0,
	MOTOR_B,
	MOTOR_C = 3
} MOTOR ;

typedef struct
{
	 int Power;	
	 int Dir;
	 int Speed;
} MoterA;

typedef struct
{
	 int Power;	
	 int Dir;
	 int Speed;
} MoterC;

typedef struct
{
	 int Power;	
	 int Dir;
	 int Speed;
} MoterB;

extern void TIM_PWM_Configuration(void);
extern void PWMControl(int Moter_x  ,int  Moter_dir , int Moter_speed);
extern void MotorDir_GPIO_Configuration(void);
#endif /* PWM_ H*/
