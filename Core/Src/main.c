/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "../../header.h"
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
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t UART2_outputbuffer[255] = {0};
uint8_t funBuffer[1000] = {0};
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the huart2 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1,0xFFFF);
	//HAL_UART_Transmit_IT(&huart2, (uint8_t *)&ch, 1);
  return ch;
}

/*bool getchar(uint8_t * ch)
{
       // check for overflow and clear
	if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_ORE))
		__HAL_UART_CLEAR_FLAG(&huart1, UART_FLAG_ORE);

	if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE))
	{
		*ch = huart1.Instance->RDR & 0x1FF;
		return true;
	}

	return false;
}*/

void printhexlikeshellcode(size_t l,unsigned char* thing){
	for(size_t i=0;i<l;i++){
		printf("\\x%x",thing[i]);
		//putchar(thing[i]);
	}
}
size_t funBufferIndex=0;
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_StatusTypeDef x;
  HAL_UART_Receive_DMA(&huart2, (uint8_t *)funBuffer, 4);
  uint buttonPressed1Counter=0;
  uint buttonPressed2Counter=0;
  HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
  uint button1pressed=0;
  uint button1pressednext=0;
  uint button2pressed=0;
  uint button2pressednext=0;
  printf("program start\r\n");
  char prevchar=0;
  uint thechar=0;
  uint dings=0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //printf("huart2.RxXferSize=%u\r\n",huart2.RxXferSize);
	  //printf("hello wolrd\r\n");
	  button1pressednext=0;
	  if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)!=GPIO_PIN_SET){
		  button1pressednext=1;
	      if(button1pressed==0){
	      	  printf("button is pressed times: %u \r\n",++buttonPressed1Counter);
	      	HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
	      }
	      // printf("rust number:%u",test());
	  }/*
	  button2pressednext=0;
	  if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10)!=GPIO_PIN_RESET){
	  	button2pressednext=1;
	    if(button2pressed==0)
	      		printf("button2 is pressed times: %u \r\n",++buttonPressed2Counter);
	  }

	  button2pressednext=button2pressednext;*/
	  button1pressed=button1pressednext;
	  //huart2.pRxBuffPtr  = funBuffer;
	  /*while(funBuffer[funBufferIndex]){
		  //Do something with the character
		  //dings=0;
		  dings++;
		  /*if(funBuffer[funBufferIndex]<='9'&&funBuffer[funBufferIndex]>='0'){
			  dings=funBuffer[funBufferIndex]-'0';
		  }else if(funBuffer[funBufferIndex]<='z'&&funBuffer[funBufferIndex]>='a'){
			  dings=funBuffer[funBufferIndex]-'a'+10;

		  }
		  printf("digit:%u\r\n",dings);
		  HAL_GPIO_WritePin(GPIOA,LED_2_Pin,(dings)&1);
		  HAL_GPIO_WritePin(GPIOA,bled2_Pin,((dings)>>1)&1);
		  HAL_GPIO_WritePin(GPIOA,bled3_Pin,((dings)>>2)&1);
		  HAL_GPIO_WritePin(GPIOB,bled4_Pin,((dings)>>3)&1);
		  HAL_GPIO_WritePin(bled5_GPIO_Port,bled5_Pin,((dings)>>4)&1);
		  HAL_GPIO_WritePin(GPIOA,bled6_Pin,((dings)>>5)&1);
		  HAL_GPIO_WritePin(GPIOA,bled7_Pin,((dings)>>6)&1);
		  HAL_GPIO_WritePin(GPIOB,bled8_Pin,((dings)>>7)&1);
		  HAL_GPIO_WritePin(GPIOB,bled9_Pin,((dings)>>8)&1);
		  funBufferIndex++;
	  }*/
	  while(funBuffer[funBufferIndex]){
		  //printf("pressed, funBufferIndex:%u\r\n",funBufferIndex);
		  dings=0;

		  if(funBuffer[funBufferIndex]<='9'&&funBuffer[funBufferIndex]>='0'){
		  			  dings=funBuffer[funBufferIndex]-'0';
		  }else if(funBuffer[funBufferIndex]<='z'&&funBuffer[funBufferIndex]>='a'){
			  dings=funBuffer[funBufferIndex]-'a'+10;
		  }
		  if(prevchar){
			  thechar|=dings;
			  printf("thechar:%u\r\n",thechar);
			  dings=thechar;
			  HAL_GPIO_WritePin(GPIOA,LED_2_Pin,(dings)&1);
			  HAL_GPIO_WritePin(GPIOA,bled2_Pin,((dings)>>1)&1);
			  HAL_GPIO_WritePin(GPIOA,bled3_Pin,((dings)>>2)&1);
			  HAL_GPIO_WritePin(GPIOB,bled4_Pin,((dings)>>3)&1);
			  HAL_GPIO_WritePin(bled5_GPIO_Port,bled5_Pin,((dings)>>4)&1);
			  HAL_GPIO_WritePin(GPIOA,bled6_Pin,((dings)>>5)&1);
			  HAL_GPIO_WritePin(GPIOA,bled7_Pin,((dings)>>6)&1);
			  HAL_GPIO_WritePin(GPIOB,bled8_Pin,((dings)>>7)&1);
			  HAL_GPIO_WritePin(GPIOB,bled9_Pin,((dings)>>8)&1);
		  }else{
			  thechar=dings<<4;
		  }
		  prevchar=!prevchar;
		  funBufferIndex++;
	  }
	  //printf("length of char %d",sizeof(char));
	  //printhexlikeshellcode(10,funBuffer);
	  //printf("buff:%s\r\n",funBuffer);
	  //memset(funBuffer, 0, sizeof(funBuffer));
	  //HAL_UART_Transmit(&huart2, '\n', 1,0xFFFF);
	 // for(uint i=0;i<2;i++)
	  //printf("%c",huart2.Instance->RDR);
	  //printf("\r\n");
	  //printf("     \r                                                                       ");
	  //char lel[3];
	  //sprintf(lel,"yo");
	  //printf("before transmit\n");
	  //HAL_UART_Transmit(&huart2,(uint8_t *)lel, 3,0xFFFF);
	  //printf("after transmit");
	  //putchar('x');
	  //printf("\r\n");
	  fflush(stdout);
	  //printf("huart2.RxXferCount=%u\r\n",huart2.RxXferCount);
	  //huart2.RxXferCount=1000;
	  //huart2.Instance->TDR='d';
	  if (huart2.Instance->ISR>>3&1||huart2.Instance->CR1==13){
		  printf("I can't receive data anymore\r\n");
		//  printf("huart2.instance->ISR=%u\r\n",huart2.Instance->ISR);
		  printf("huart2.instance->RDR=%c\r\n",huart2.Instance->RDR);
		  //attempt to fix
		 // huart2.Instance->ISR&=(~(1<<3));
		 // huart2.Instance->CR1=301;
		 huart2.RxState = HAL_UART_STATE_READY;
		 printf("HAL REPLY:%u\r\n",HAL_UART_Receive_DMA(&huart2, (uint8_t *)funBuffer, 10));
	  }//else{*/
	  //printf("huart2.RxXferSize=%u\r\n",huart2.RxXferSize);
	  //printf("huart2.instance->RDR=%c\r\n",huart2.Instance->RDR);
	  //printf("huart2.ErrorCode=%u\r\n",huart2.ErrorCode);
	  //printf("huart2.instance->ISR=%u\r\n",huart2.Instance->ISR);
	  //printf("huart2.instance->DR=%u\r\n",huart2.Instance->DR);
	  //printf("huart2.instance->TDR=%u\r\n",huart2.Instance->TDR);
	  //printf("huart2.instance->CR1=%u\r\n",huart2.Instance->CR1);
	  //printf("huart2.instance->CR2=%u\r\n",huart2.Instance->CR2);
	  //printf("huart2.instance->CR3=%u\r\n",huart2.Instance->CR3);
	 // }
	  //HAL_UART_Transmit(&huart2, funBuffer, 255, 100);

	 /* uint8_t Test[] = "Hello World !!!\r\n"; //Data to send
	  HAL_UART_Transmit(&huart2,Test,sizeof(Test),10);// Sending in normal mode
	  x=HAL_UART_Receive (&huart2, UART2_rxBuffer, 12, 5000);
	  HAL_UART_Transmit(&huart2, UART2_rxBuffer, 12, 100);
	  huart2.RxState=HAL_UART_STATE_READY;
	  printf("hello world :p\r\n");
	  sprintf((char*)funBuffer,"huart2.RxXferSize=%u\r\n",huart2.RxXferSize);
	  HAL_UART_Transmit(&huart2, funBuffer, 255, 100);
	  sprintf((char*)funBuffer,"huart2.RxXferCount=%u\r\n",huart2.RxXferCount);
	  HAL_UART_Transmit(&huart2, funBuffer, 255, 100);
	  sprintf((char*)funBuffer,"HAL_UART_Receive return=%u\r\n",x);
	  HAL_UART_Transmit(&huart2, funBuffer, 255, 100);
	  sprintf((char*)funBuffer,"huart2.instance->RDR=%c\r\n",huart2.Instance->RDR);
	  HAL_UART_Transmit(&huart2, funBuffer, 255, 100);
	  memset(UART2_rxBuffer, 0, sizeof(UART2_rxBuffer));
	  HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);*/
	 // HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
	  //HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_5);
	  //HAL_Delay(1000);


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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_2_Pin|bled2_Pin|bled3_Pin|bled7_Pin
                          |bled6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, bled8_Pin|bled9_Pin|bled4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(bled5_GPIO_Port, bled5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_2_Pin bled2_Pin bled3_Pin bled7_Pin
                           bled6_Pin */
  GPIO_InitStruct.Pin = LED_2_Pin|bled2_Pin|bled3_Pin|bled7_Pin
                          |bled6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : bled8_Pin bled9_Pin bled4_Pin */
  GPIO_InitStruct.Pin = bled8_Pin|bled9_Pin|bled4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : bled5_Pin */
  GPIO_InitStruct.Pin = bled5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(bled5_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
/**
  * @brief Rx Transfer completed callbacks
  * @param huart: uart handle
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_RxCpltCallback can be implemented in the user file
   */
    char recover=funBuffer[funBufferIndex];
    //printf("recovered character:%c\r\n",funBuffer[funBufferIndex]);
    //printf("Data has been uploaded!\r\n");
    funBufferIndex=0;
    memset(funBuffer, 0, sizeof(funBuffer));
    funBuffer[0]=recover;
    //funBuffer[1]=recover;
    HAL_UART_Receive_DMA(&huart2, (uint8_t *)(funBuffer+1), 999);

   // HAL_UART_Transmit_IT(&huart2, (uint8_t *)funBuffer, 1);
   // printf("I've been interrupted\r\n");
    //HAL_UART_Receive_IT(&huart2, (uint8_t *)funBuffer, 1);
    //memset(funBuffer, 0, sizeof(funBuffer));
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
	  printf("THERE HAS BEEN AN ERROR\r\n");
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
