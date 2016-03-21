/**
 * @file	Battery.h
 * @brief	Battery sense
 */
 #include "stm32f4xx.h"
#ifndef BATTERY_BATTERY_H_
#define BATTERY_BATTERY_H_

extern void BattSense_init(void);
extern void BattSenseISR(void);

#endif /* BATTERY_BATTERY_H_ */
