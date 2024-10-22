/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "pwm.h"
#include "delay.h"
#include "ultrasonic.h"
#include "I2C_lcd.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

#ifdef __GNUC__
  /* With GCC, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHARPROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFF);

  return ch;
}

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t rxData;
uint8_t rxData1;

uint8_t Forward_arr[] = "FOWARD\n";
uint8_t Backward_arr[] = "BACKWARD\n";
uint8_t Right_arr[] = "RIGHT\n";
uint8_t Left_arr[] = "LEFT\n";
uint8_t Pause_arr[] = "PAUSE\n";

uint16_t IC_VALUE1 = 0;
uint16_t IC_VALUE2 = 0;
uint16_t echoTime = 0;
uint8_t captureFlag = 0;
uint16_t distance = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart )
{
	if(huart->Instance == USART2)
	{
		HAL_UART_Receive_IT(&huart2, &rxData, sizeof(rxData));
		HAL_UART_Transmit_IT(&huart6, &rxData, sizeof(rxData));
	}

	if(huart->Instance == USART6)
	{
		HAL_UART_Receive_IT(&huart6, &rxData1, sizeof(rxData1));
		//FORWARD
		if(rxData1 == 'W')
		{
			HAL_UART_Transmit_IT(&huart2, Forward_arr, sizeof(Forward_arr));
			Motor_Forward();
			move_cursor(1, 4);
			lcd_string("FORWARD ");
		}
		//RIGHT
		else if(rxData1 == 'D')
		{
			HAL_UART_Transmit_IT(&huart2, Right_arr, sizeof(Right_arr));
			Motor_Right();
			move_cursor(1, 4);
			lcd_string("RIGHT    ");
		}
		//LEFT
		else if(rxData1 == 'A')
		{
			HAL_UART_Transmit_IT(&huart2, Left_arr, sizeof(Left_arr));
			Motor_Left();
			move_cursor(1, 4);
			lcd_string("LEFT    ");
		}
		//BACKWARD
		else if(rxData1 == 'S')
		{
			HAL_UART_Transmit_IT(&huart2, Backward_arr, sizeof(Backward_arr));
			Motor_Backward();
			move_cursor(1, 4);
			lcd_string("BACKWARD");
		}
		//PAUSE
		else //if(rxData1 == 'P')
		{
			HAL_UART_Transmit_IT(&huart2, Pause_arr, sizeof(Pause_arr));
			Motor_Stop();
			move_cursor(1, 4);
			lcd_string("STOP    ");
		}
	}
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_USART6_UART_Init();
  MX_TIM4_Init();
  MX_TIM10_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  // PWM motor
  HAL_UART_Receive_IT(&huart2, &rxData, sizeof(rxData));
  HAL_UART_Receive_IT(&huart6, &rxData1, sizeof(rxData1));

  pwmInit();

  //ULTRASONIC
  UltrasonicInit();

  HAL_TIM_Base_Start(&htim10);	// for delay func
  HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);		// for ultrasonic

  // LCD
  i2c_lcd_init();

  move_cursor(0, 4);
  lcd_string("WELCOME");

  // BUZZER
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
   while (1)
  {
  	 HCSR04_read();
  	 if(distance <= 15)
  	 {
  		 Motor_Stop();
  		 move_cursor(1, 4);
  		 lcd_string("!!STOP!!");
  	 }
  	 HAL_Delay(500);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */