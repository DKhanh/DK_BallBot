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
extern void buzzer_init(void);
extern void buzzer_setsound(uint16_t CCR4_Val);
extern int buzzer_low_battery_notify();
extern int buzzer_low_battery_shutdown();
//extern void buzzer_on(uint32_t Freq, uint32_t msTime);

#endif /* BUZZER_BUZZER_H_ */
