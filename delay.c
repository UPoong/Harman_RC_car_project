/*
 * delay.c
 *
 *  Created on: Jul 30, 2024
 *      Author: jsmok
 */

#include "delay.h"

void delay_us(uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim10, 0);		// 호출하면 0부터 시작(초기화)
	while((__HAL_TIM_GET_COUNTER(&htim10)) < us);		// us보다 작으면 while안에서 머물고, 그렇지 않으면 밖으로 나옴
}
