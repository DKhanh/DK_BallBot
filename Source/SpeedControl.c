/**
 * @file	speed control.c
 * @brief	speed control
 */




#include "include.h"
#include "SpeedControl.h"

extern void TIM_PWM_Configuration(void);
extern void PWMControl(int Moter_x  ,int  Moter_dir , int Moter_speed);
extern void MotorDir_GPIO_Configuration(void);

TIM_TimeBaseInitTypeDef    PWM_TIM_TimeBaseStructure;
TIM_OCInitTypeDef          PWM_TIM_OCInitStructure;
GPIO_InitTypeDef           PWM_GPIO_InitStructure;
GPIO_InitTypeDef           MoterDir_GPIO_InitStructure;

/**
  * @brief  Control Motor A , B or C       
  * @param Motor_x  : where x can be 	A ( connected to Pin PB8)
																			B ( connected to Pin PA2)
																			C ( connected to Pin PA3)
																			D ( connected to Pin PE6)
	* @param Motor_dir : Direction of Motor can be 	1 Clock-wise     ( Affected to Pin PB9 , PA0 or PA1 or PE4)
																									0 AntiClock-wise
  * @param Motor_speed : DutyCycle of PWM Pulse
  * @retval None
  */

void PWMControl(int Motor_x , int Motor_dir , int Motor_speed)
{
	/* pulse_length = ((TIM_Period + 1) * DutyCycle) / 100 – 1 */
	switch(Motor_x)
	{
	case MOTOR_A :
	{
		GPIO_WriteBit(GPIOB,GPIO_Pin_9,Motor_dir);
		GPIO_WriteBit(GPIOD,GPIO_Pin_12,Motor_dir);
		TIM4->CCR1 = Motor_speed * (65535) / 100 ; 
		break;
	}		
	case MOTOR_B :
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Motor_dir);
		GPIO_WriteBit(GPIOD,GPIO_Pin_13,Motor_dir);
	  TIM2->CCR2 =   Motor_speed * (65535) / 100;  
		break;
	}
	case MOTOR_C :
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_1,Motor_dir);
		GPIO_WriteBit(GPIOD,GPIO_Pin_14,Motor_dir);
		TIM2->CCR3 = Motor_speed * (65535) / 100;  
		break;
	}
	}
}

void TIM_PWM_Configuration(void)
{ 
// RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOE , ENABLE);
  
  PWM_GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2  | GPIO_Pin_3  ;
  PWM_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  PWM_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  PWM_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  PWM_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &PWM_GPIO_InitStructure); 
  
  PWM_GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
  GPIO_Init(GPIOB, &PWM_GPIO_InitStructure);
	
	PWM_GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;
  GPIO_Init(GPIOE, &PWM_GPIO_InitStructure);
	

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM4);  // Motor_A_PB8
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);  // Motor_B_PA2
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM2);  // Motor_C_PA3
 // GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_TIM9); // Motor_D_PE6

  
  /* Time base configuration - Create 1KHz PWM Pulse  */
  PWM_TIM_TimeBaseStructure.TIM_Prescaler = 0;//  Timer_tick_frequence = 1MHz
  PWM_TIM_TimeBaseStructure.TIM_Period = 0xFFFF;   // TIM_Period = (Timer_tick_frequence/PWM_frequence )-1 = (48000000/1000)-1 = 
  PWM_TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  PWM_TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM4, &PWM_TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM2, &PWM_TIM_TimeBaseStructure);
//	TIM_TimeBaseInit(TIM9, &PWM_TIM_TimeBaseStructure);

  PWM_TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  PWM_TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
  PWM_TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  PWM_TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; 
  PWM_TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  PWM_TIM_OCInitStructure.TIM_Pulse = 0;
  //TIM_OCStructInit(&TIM_OCInitStructure);
  
  TIM_OC1Init(TIM4, &PWM_TIM_OCInitStructure);  
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

  TIM_OC2Init(TIM2, &PWM_TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

  TIM_OC3Init(TIM2, &PWM_TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
//TIM_OC4Init(TIM9, &PWM_TIM_OCInitStructure);
// TIM_OC4PreloadConfig(TIM9, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_ARRPreloadConfig(TIM4, ENABLE);
//	TIM_ARRPreloadConfig(TIM9, ENABLE);

  /* TIM1 enable counter */
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM9, ENABLE);
 // TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void MotorDir_GPIO_Configuration(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  MoterDir_GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
  MoterDir_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  MoterDir_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  MoterDir_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  MoterDir_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &MoterDir_GPIO_InitStructure);
	
	MoterDir_GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
  GPIO_Init(GPIOB, &MoterDir_GPIO_InitStructure);
	
	MoterDir_GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
  GPIO_Init(GPIOE, &MoterDir_GPIO_InitStructure);
	
}

