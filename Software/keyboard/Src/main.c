/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "HW_key.h"
#include "data.h"


#if USART_KEY==1
#include "usart.h"

#else
#include "usb_device.h"
#include "usbd_hid.h"
extern USBD_HandleTypeDef hUsbDeviceFS;

#endif


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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

#if USART_KEY==0
#define KEY_LIB key_code


uint8_t key_code[12]={KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9
											,KEY_0,KEY_Back,KEY_Enter};

uint8_t game_code[12]={KEY_A,KEY_Q,KEY_1,KEY_S,KEY_W,KEY_2,KEY_D,KEY_E,KEY_3
											,KEY_F,KEY_R,KEY_4};


void send_cmd(uint8_t key,uint8_t *lib)
{
	uint8_t cmd[8]={0x00};

	cmd[2]=lib[key-1];
	USBD_HID_SendReport(&hUsbDeviceFS,cmd,8);//发送报文
	cmd[2]=0x00;
	HAL_Delay(20);

	
}
#endif


enum{
	Key_idle,
	Key_click,
};



void Keyboard_send(uint8_t key,uint8_t mode)
{
	static char flag=Key_idle,temp_key;
	uint8_t cmd[8]={0x00};
	#if USART_KEY==1
	if(mode)
	{
		flag=Key_click;
		temp_key=key;
		HAL_Delay(10);
	}
	else
	{
		if(flag==Key_click)
		{
			flag=Key_idle;
			if(temp_key<10)
				printf("[%d]",temp_key);
			else if(temp_key==10) printf("[0]");
			else if(temp_key==11) printf("[D]");
			else if(temp_key==12) printf("[E]");
			HAL_Delay(10);
		}
	}
	
	#else
	if(mode)
		send_cmd(key,KEY_LIB);
	else
	{
		USBD_HID_SendReport(&hUsbDeviceFS,cmd,8);//清除按键
		HAL_Delay(20);
	}
	#endif
}



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	char key;
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

  
  /* USER CODE BEGIN 2 */
	#if USART_KEY==1
	MX_USART1_UART_Init();
	//printf("hello");
	
	#else
	MX_USB_DEVICE_Init();
	#endif


  /* USER CODE END 2 */
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		key=KEY_SCAN();
		if(key)
			Keyboard_send(key,1);
		else
			Keyboard_send(key,0);
//		if(key)
//		{
//			if(flag==Key_idle)
//			{
//				flag=Key_firstclick;
//				Keyboard_send(key);
//			}
//			else if(flag==Key_firstclick)
//			{
//				flag=Key_alway;
//				HAL_Delay(200);
//			}
//			else if(flag==Key_alway)
//			{
//				Keyboard_send(key);
//			}
//		}
//		else
//		{
//			flag=Key_idle;
//		}
		
		
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
