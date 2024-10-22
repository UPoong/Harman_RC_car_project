/*
 * pwm.c
 *
 *  Created on: Jul 31, 2024
 *      Author: jsmok
 */


#include "pwm.h"

void pwmInit(void)
{
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start_IT(&htim3, TIM_CHANNEL_4);
}

void PWM_SetDutyCycle(uint32_t channel, uint16_t dutyCycle)
{
	__HAL_TIM_SET_COMPARE(&htim3, channel, dutyCycle);
}

void Motor_Forward(void)
{
	// 위쪽 모터
	PWM_SetDutyCycle(TIM_CHANNEL_3, 1000);
	PWM_SetDutyCycle(TIM_CHANNEL_4, 1000);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

	// 아래쪽 모터
	PWM_SetDutyCycle(TIM_CHANNEL_1, 1000);
	PWM_SetDutyCycle(TIM_CHANNEL_2, 1000);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
}

void Motor_Backward(void)
{
	// 위쪽 모터
	PWM_SetDutyCycle(TIM_CHANNEL_3, 1000);
	PWM_SetDutyCycle(TIM_CHANNEL_4, 1000);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);

	// 아래쪽 모터
	PWM_SetDutyCycle(TIM_CHANNEL_1, 1000);
	PWM_SetDutyCycle(TIM_CHANNEL_2, 1000);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
}

void Motor_Right(void)
{
	// 위쪽 모터
	PWM_SetDutyCycle(TIM_CHANNEL_3, 1000);
	PWM_SetDutyCycle(TIM_CHANNEL_4, 1000);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

	// 아래쪽 모터
	PWM_SetDutyCycle(TIM_CHANNEL_1, 1000);
	PWM_SetDutyCycle(TIM_CHANNEL_2, 1000);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
}

void Motor_Left(void)
{
	// 위쪽 모터
	PWM_SetDutyCycle(TIM_CHANNEL_3, 1000);
	PWM_SetDutyCycle(TIM_CHANNEL_4, 1000);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

	// 아래쪽 모터
	PWM_SetDutyCycle(TIM_CHANNEL_1, 1000);
	PWM_SetDutyCycle(TIM_CHANNEL_2, 1000);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
}

void Motor_Stop(void)
{
	// 위쪽 모터
	PWM_SetDutyCycle(TIM_CHANNEL_3, 1000);
	PWM_SetDutyCycle(TIM_CHANNEL_4, 1000);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

	// 아래쪽 모터
	PWM_SetDutyCycle(TIM_CHANNEL_1, 1000);
	PWM_SetDutyCycle(TIM_CHANNEL_2, 1000);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);

}





