/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32f0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "bluetooth.h"
#include "melody_control.h"
#include "car_direction.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
volatile uint8_t count_10sec=0;
volatile uint32_t timer6_tick;
volatile uint32_t timer7_tick;
volatile uint8_t song_number = Song_off;
volatile uint32_t ADC_value[4];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM6 global and DAC channel underrun error interrupts.
  */
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */
	timer6_tick++;
	TIM6->SR &= ~0x1ul;
  /* USER CODE END TIM6_DAC_IRQn 0 */
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
  * @brief This function handles TIM7 global interrupt.
  */
void TIM7_IRQHandler(void)
{
  /* USER CODE BEGIN TIM7_IRQn 0 */
	timer7_tick++;
	if((ADC1->ISR & 0x1ul) == 1){
		ADC1->CR |= 0x1ul<<2;
		for(int i=0;i<4;i++){
			while((ADC1->ISR & (0x1ul<<2)) ==0){};
				ADC_value[i]=ADC1->DR;
			
		}
		if(ADC_value[0]>500 || ADC_value[1]>500 || ADC_value[2]>500 || ADC_value[3]>500){
			car_direction(Car_stop);
		}
	}
	TIM7->SR &= ~0x1ul;
  /* USER CODE END TIM7_IRQn 0 */
  /* USER CODE BEGIN TIM7_IRQn 1 */

  /* USER CODE END TIM7_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
	uint8_t rxData;
	
	if(USART1->ISR & (0x1ul<<5)){
		rxData = USART1->RDR;
		printf("bt cmd = %c \n\r",rxData);
		switch(rxData) {
			case Song_1_cmd:
				song_number=Song_1;
				break;
			case Song_2_cmd:
				song_number=Song_2;
				break;
			case Song_3_cmd:
				song_number=Song_3;
				break;
			case Song_4_cmd:
				song_number=Song_4;
				break;
			case Song_5_cmd:
				song_number=Song_5;
				break;
			case Song_6_cmd:
				song_number=Song_6;
				break;
			case Song_7_cmd:
				song_number=Song_7;
				break;
			case Song_off_cmd:
				song_number=Song_off;
				break;
			
			case Car_forward_cmd:
				car_direction(Car_forward);
				break;
			
			case Car_left_cmd:
				car_direction(Car_left);
				break;
			
			case Car_right_cmd:
				car_direction(Car_right);
				break;
			
			case Car_backward_cmd:
				car_direction(Car_backward);
				break;
			
			case Car_stop_cmd:
				car_direction(Car_stop);
				break;
		}
	}
  /* USER CODE END USART1_IRQn 0 */
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART3 and USART4 global interrupts.
  */
void USART3_4_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_4_IRQn 0 */
	uint8_t rxData;
	
	if(USART3->ISR & (0x1ul<<5)){
		rxData = USART3->RDR;
		printf("wifi cmd = %c \n\r",rxData);
		switch(rxData) {
			case Song_1_cmd:
				song_number=Song_1;
				break;
			case Song_2_cmd:
				song_number=Song_2;
				break;
			case Song_3_cmd:
				song_number=Song_3;
				break;
			case Song_4_cmd:
				song_number=Song_4;
				break;
			case Song_5_cmd:
				song_number=Song_5;
				break;
			case Song_6_cmd:
				song_number=Song_6;
				break;
			case Song_7_cmd:
				song_number=Song_7;
				break;
			case Song_off_cmd:
				song_number=Song_off;
				break;
			
			case Car_forward_cmd:
				car_direction(Car_forward);
				break;
			
			case Car_left_cmd:
				car_direction(Car_left);
				break;
			
			case Car_right_cmd:
				car_direction(Car_right);
				break;
			
			case Car_backward_cmd:
				car_direction(Car_backward);
				break;
			
			case Car_stop_cmd:
				car_direction(Car_stop);
				break;
		}
	}
  /* USER CODE END USART3_4_IRQn 0 */
  /* USER CODE BEGIN USART3_4_IRQn 1 */

  /* USER CODE END USART3_4_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
