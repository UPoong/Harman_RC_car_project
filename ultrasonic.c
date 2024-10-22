/*
 * ultrasonic.c
 *
 *  Created on: Aug 1, 2024
 *      Author: jsmok
 */

#include "ultrasonic.h"

void UltrasonicInit(void)
{
	HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_1);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		if (captureFlag == 0)
		{
			IC_VALUE1 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_1);
			captureFlag = 1;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim4, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
		}
		else if (captureFlag == 1)
		{
			IC_VALUE2 = HAL_TIM_ReadCapturedValue(&htim4, TIM_CHANNEL_1);
			__HAL_TIM_SET_COUNTER(&htim4, 0);

			if (IC_VALUE2 > IC_VALUE1)
			{
				echoTime = IC_VALUE2 - IC_VALUE1;
			}
			else
			{
				echoTime = (0xffff - IC_VALUE1) + IC_VALUE2;
			}

			distance = echoTime / 58;
//			//////////////
//			if(distance > 200)
//			{
//				distance = 200;
//			}

			captureFlag = 0;
			__HAL_TIM_SET_CAPTUREPOLARITY(&htim4, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
			__HAL_TIM_DISABLE_IT(&htim4, TIM_IT_CC1);
		}
	}
}


void HCSR04_read(void)
{
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, 1);
	delay_us(10);
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, 0);

	__HAL_TIM_ENABLE_IT(&htim4, TIM_IT_CC1); // 초음파 센서용 타이머 채널
}

