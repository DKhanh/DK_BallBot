/**
 * @file	Buzzer.h
 * @brief	Battery sense
 */


#ifndef BUZZER_BUZZER_H_
#define BUZZER_BUZZER_H_
/*
typedef struct
{
	uint32_t Freq;
	uint32_t msTime;
} BUZZER_PULSE;
*/
extern void BuzzerInit(void);
extern void BuzzerSetSound(uint16_t CCR4_Val);
extern int BuzzerLowBattery_notify();
extern int BuzzerLowBattery_shutdown();
//extern void buzzer_on(uint32_t Freq, uint32_t msTime);

#endif /* BUZZER_BUZZER_H_ */
