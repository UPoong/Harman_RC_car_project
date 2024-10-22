/*
 * ultrasonic.h
 *
 *  Created on: Aug 1, 2024
 *      Author: jsmok
 */

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "top.h"
#include "delay.h"
extern TIM_HandleTypeDef htim4;

#define TRIG_PORT		GPIOB
#define TRIG_PIN		GPIO_PIN_7

extern uint16_t IC_VALUE1;
extern uint16_t IC_VALUE2;
extern uint16_t echoTime;
extern uint8_t captureFlag;
extern uint16_t distance;

void UltrasonicInit(void);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void HCSR04_read(void);

#endif /* ULTRASONIC_H */
