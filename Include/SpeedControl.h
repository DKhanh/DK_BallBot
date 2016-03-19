/*
 * PWM.h
 *
 *  Created on: Mar 18, 2016
 *      Author: DKhanh
 */

#ifndef PWM_
#define PWM_
/*
#define TURN_ON_IRD1()			ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0xff)
#define TURN_OFF_IRD1()			ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0x00)

#define TURN_ON_IRD2()			ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0xff)
#define TURN_OFF_IRD2()			ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0x00)

#define TURN_ON_IRD3()			ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0xff)
#define TURN_OFF_IRD3()			ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0x00)

#define TURN_ON_IRD4()			ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0xff)
#define TURN_OFF_IRD4()			ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0x00)

#define TURN_ON_IRD_ALL()		ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0xff);
#define TURN_OFF_IRD_ALL()		ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x00);

#define IR_LEFT 1
#define IR_RIGHT 2
#define IR_FRONT_LEFT 0
#define IR_FRONT_RIGHT 3
*/

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
extern void PWM_Control(int Moter_x  ,int  Moter_dir , int Moter_speed);
extern void MotorDir_GPIO_Configuration(void);
#endif /* PWM_ H*/
