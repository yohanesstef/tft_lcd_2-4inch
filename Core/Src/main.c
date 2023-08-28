/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd_module.h"
#include "server.h"
#include "lora.h"
#include "gps_M8N.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t flag;

//LCD_TouchPoint p;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint32_t test_tick;
uint8_t callback;
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
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_USART6_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim1);

  server_init(&huart6);
  lora_init(&huart1);
  Ringbuf_init();

//  flag = 1;
//  ID = readID();
//  HAL_Delay(100);
//  flag = 2;
//
//  tft_init(ID);
//  flag = 3;
//  setRotation(0);
//
//  fillScreen(BLACK);
//
//  fillScreen(BLACK);
//
//  setRotation(0);
//  testFillScreen();
////  testLines(CYAN);
////  testFastLines(RED, BLUE);
////  testFilledCircles(10, MAGENTA);
////  testCircles(10, WHITE);
////  scrollup(100);
////  invertDisplay(1);
//  fillScreen(WHITE);
//  printnewtstr(100, RED, &mono9x7bold, 3, "HELLO");
////  fillRect(10, 10, 100, 200, WHITE);
//  flag = 4;
//
//  LCD_Touch_Init(&hadc1, ADC_CHANNEL_7, &hadc1, ADC_CHANNEL_8);
//  LCD_SetMode(LCD_MODE_TOUCH);
//
//  flag = 5;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//	  LCD_SetMode(LCD_MODE_TOUCH);
//	  if (LCD_Touch_Read(&p) == LCD_TOUCH_READ_SUCCESS) {
////		  LCD_Touch_Draw_ConnectLastPoint(&p);
////		  LCD_Touch_Draw_PrintInfo();
//		  flag++;
//	  }
//	  if ((p.x < 200) & (p.x > 150) & (p.y < 200) & (p.y > 150)){
//		  p.x = 0;
//		  p.y = 0;
//		  LCD_SetMode(LCD_MODE_DRAW);
//		  testLines(CYAN);
//	  }
//	  server_transmit_routine();
//	  lora_receive_routine();
	  lora_wireless_transmit_routine();
	  gps_GGA_routine();
	  flag++;
//	  HAL_Delay(100);
//	  server_receive_restart();
//	  LCD_Touch_Draw_Update();
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 168;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
//delay untuk lcd
void delay (uint32_t time){
	/* change your code here for the delay in microseconds */
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	while ((__HAL_TIM_GET_COUNTER(&htim1))<time);
}

//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//  if (GPIO_Pin == GPIO_PIN_3 && (HAL_GetTick() - previousTick > 600))
//  {
//    txBuffer[dataIndex]=charValue;
//    dataBuffer[dataIndex++]=charValue;
//    txBuffer[dataIndex]=13;
//    HAL_UART_Transmit_IT(&huart1,(uint8_t *)txBuffer,dataIndex+1);
//    previousTick = HAL_GetTick();
//  }
//  else if (GPIO_Pin == GPIO_PIN_1 && (HAL_GetTick() - previousTick > 600))
//  {
//    dataIndex--;
//    dataBuffer[dataIndex]=0;
//    txBuffer[dataIndex]=13;
//    HAL_UART_Transmit_IT(&huart1,(uint8_t *)txBuffer,dataIndex+1);
//    SSD1306_Clear();
//    previousTick = HAL_GetTick();
//  }
//}
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
	callback++;
	server_receive_callback(huart);
}
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
