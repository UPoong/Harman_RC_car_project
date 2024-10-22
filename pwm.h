/*
 * pwm.h
 *
 *  Created on: Jul 31, 2024
 *      Author: jsmok
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

#include "top.h"

extern TIM_HandleTypeDef htim3;

void pwmInit(void);
void Motor_Forward(void);
void Motor_Backward(void);
void Motor_Right(void);
void Motor_Left(void);
void Motor_Stop(void);

#endif /* INC_PWM_H_ */
