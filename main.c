#include "include.h"



void GPIO_Configuration(void);


int main(void)
{
	GPIO_Configuration();
  MotorDir_GPIO_Configuration();
	TIM_PWM_Configuration();
	BattSense_init();
	BuzzerInit();
	PWMControl(MOTOR_A,1,90);
	PWMControl(MOTOR_B,1,50);
	PWMControl(MOTOR_C,0,0);
	BuzzerSetSound(999);  // test Buzzer
	


  while (1)
  {
		BattSenseISR();

		
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

