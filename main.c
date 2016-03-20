#include "include.h"



void GPIO_Configuration(void);


int main(void)
{
	GPIO_Configuration();
  MotorDir_GPIO_Configuration();
	TIM_PWM_Configuration();
	BattSense_init();
	


  while (1)
  {
		PWM_Control(MOTOR_A,1,999);
		PWM_Control(MOTOR_B,0,500);
		PWM_Control(MOTOR_C,1,0);
		buzzer_setsound(500);  // test Buzzer
		
  }
}



void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

