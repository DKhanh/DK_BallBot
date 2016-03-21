/**
 * @file	Button.h
 * @brief	Push button driver
 */

#include "include.h"
#include "Buzzer.h"

//* Private function prototype ----------------------------------------------*/
//static void buzzer_lowbat_notify_handler(void);
//static void Buzzer_lowbat_shutdown_handler(void);
//static void buzzer_on_timeout_handler(void);
//static void buzzer_Stoptimeout(void);

extern void BuzzerInit(void);
extern void BuzzerSetSound(uint16_t CCR4_Val);
extern int BuzzerLowBattery_notify();
extern int BuzzerLowBattery_shutdown();

//* Function declaration ----------------------------------------------------*/
/**
 * @brief Buzzer init
 */
void BuzzerInit(void)
{
	GPIO_InitTypeDef BUZZER_GPIO_InitStructure;
	/* Setup the microcontroller system. Initialize the Embedded Flash Interface,  
	initialize the PLL and update the SystemFrequency variable. */
	//SystemInit();		// no need because SystemInit() is already called in start up code	

	/* TIM9 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);

	/* Enable GPIOE clocks */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);

	/* PCLK1 = HCLK/16 => 72MHz/16 = 4.5MHz */	
	RCC_PCLK1Config(RCC_HCLK_Div16);
	
	/* Buzzer GPIO Config*/
	

	/* Configuration PE5 pin:TIM9 Channe1 as alternate function push-pull */
	BUZZER_GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  BUZZER_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  BUZZER_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  BUZZER_GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  BUZZER_GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;

	GPIO_Init(GPIOE, &BUZZER_GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_TIM9);
	
}

/**
 * @brief Set buzzer frequency
 */
void BuzzerSetSound(uint16_t CCR4_Val )
{
	TIM_TimeBaseInitTypeDef  BUZZER_TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  BUZZER_TIM_OCInitStructure;
	/* ----------------------------------------------------------------------*/
	/* Time base configuration */
	BUZZER_TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock/2)/1000000)-1;
	BUZZER_TIM_TimeBaseStructure.TIM_Period = 9999;
	BUZZER_TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	BUZZER_TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM9, &BUZZER_TIM_TimeBaseStructure);

	/* PWM2 Mode configuration: Channe */
	BUZZER_TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	BUZZER_TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
  BUZZER_TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  BUZZER_TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; 
  BUZZER_TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  BUZZER_TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

	TIM_OC4Init(TIM9, &BUZZER_TIM_OCInitStructure);

	TIM_OC4PreloadConfig(TIM9, TIM_OCPreload_Enable);		

	TIM_ARRPreloadConfig(TIM9, ENABLE);

	/* TIM2 enable counter */
	TIM_Cmd(TIM9, ENABLE);
}


int BuzzerLowBattery_notify()
{
	BuzzerSetSound(500);
	
}

int BuzzerLowBattery_shutdown()
{
	BuzzerSetSound(500);
	if(1)
	{
	}
}