/**
 * @file	speed control.c
 * @brief	speed control
 */




#include "include.h"
#include "SpeedControl.h"

extern void TIM_PWM_Configuration(void);
extern void PWM_Control(int Moter_x  ,int  Moter_dir , int Moter_speed);
extern void MotorDir_GPIO_Configuration(void);

TIM_TimeBaseInitTypeDef    PWM_TIM_TimeBaseStructure;
TIM_OCInitTypeDef          PWM_TIM_OCInitStructure;
GPIO_InitTypeDef           PWM_GPIO_InitStructure;
GPIO_InitTypeDef           MoterDir_GPIO_InitStructure;

/**
  * @brief  Control Motor A , B or C       
  * @param Motor_x  : where x can be 	A ( connected to Pin PA.2)
																			B ( connected to Pin PA.7)
																			C ( connected to Pin PB.9)
																			D ( connected to Pin PE.5)
	* @param Motor_dir : Direction of Motor can be 	1 Clock-wise     ( Affected to Pin PA.3 , PA.6 or PB.9 or PE.4)
																									0 AntiClock-wise
  * @param Motor_speed : DutyCycle of PWM Pulse
  * @retval None
  */

void PWM_Control(int Motor_x , int Motor_dir , int Motor_speed)
{
	/* pulse_length = ((TIM_Period + 1) * DutyCycle) / 100 – 1 */
	switch(Motor_x)
	{
	case MOTOR_A :
	{
		GPIO_WriteBit(GPIOB,GPIO_Pin_9,Motor_dir);
		GPIO_WriteBit(GPIOD,GPIO_Pin_12,Motor_dir);
		TIM2->CCR1 = Motor_speed * 99 / 100; 
		break;
	}		
	case MOTOR_B :
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_6,Motor_dir);
		GPIO_WriteBit(GPIOD,GPIO_Pin_13,Motor_dir);
	  TIM1->CCR2 = Motor_speed * 99 / 100;  
		break;
	}
	case MOTOR_C :
	{
		GPIO_WriteBit(GPIOB,GPIO_Pin_9,Motor_dir);
		GPIO_WriteBit(GPIOD,GPIO_Pin_14,Motor_dir);
		TIM4->CCR3 = Motor_speed * 99 / 100;  
		break;
	}
	}
}

void TIM_PWM_Configuration(void)
{ 
  RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOE , ENABLE);
  
  PWM_GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2  | GPIO_Pin_7  ;
  PWM_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  PWM_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  PWM_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  PWM_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &PWM_GPIO_InitStructure); 
  
  PWM_GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
  GPIO_Init(GPIOB, &PWM_GPIO_InitStructure);
	
	PWM_GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;
  GPIO_Init(GPIOE, &PWM_GPIO_InitStructure);
	

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);  // Motor_A_PA2
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM1);  // Motor_B_PA7
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_TIM4);  // Motor_C_PB9
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_TIM9); // Motor_D_PE10

  
  /* Time base configuration - Create 10KHz PWM Pulse  */
  PWM_TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock/2)/1000000)-1;//  Timer_tick_frequence = 1MHz
  PWM_TIM_TimeBaseStructure.TIM_Period = 0x63;   // TIM_Period = (Timer_tick_frequence/PWM_frequence )-1 = (1000000/10000)-1 = 99
  PWM_TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  PWM_TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM1, &PWM_TIM_TimeBaseStructure);
  TIM_TimeBaseInit(TIM2, &PWM_TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM4, &PWM_TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM9, &PWM_TIM_TimeBaseStructure);

  PWM_TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  PWM_TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
  PWM_TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  PWM_TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; 
  PWM_TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  PWM_TIM_OCInitStructure.TIM_Pulse = 0;
  //TIM_OCStructInit(&TIM_OCInitStructure);
  
  TIM_OC1Init(TIM2, &PWM_TIM_OCInitStructure);  
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

  TIM_OC2Init(TIM1, &PWM_TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

  TIM_OC3Init(TIM1, &PWM_TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_OC4Init(TIM9, &PWM_TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM9, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM1, ENABLE);
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_ARRPreloadConfig(TIM9, ENABLE);

  /* TIM1 enable counter */
  TIM_Cmd(TIM1, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM9, ENABLE);
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void MotorDir_GPIO_Configuration(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  
  MoterDir_GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_6;
  MoterDir_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  MoterDir_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  MoterDir_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  MoterDir_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &MoterDir_GPIO_InitStructure);
	
	MoterDir_GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
  GPIO_Init(GPIOB, &PWM_GPIO_InitStructure);
	
	MoterDir_GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
  GPIO_Init(GPIOE, &PWM_GPIO_InitStructure);
	
}

