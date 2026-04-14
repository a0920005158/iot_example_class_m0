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
#include "relay_control.h"
#include <stdbool.h>
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
volatile bool flag_relay1 = false;
volatile bool flag_relay2 = false;
volatile bool flag_relay3 = false;
volatile bool flag_relay4 = false;

volatile uint32_t timer6_tick;
volatile uint32_t timer7_tick;

volatile uint32_t sensor1_counter;
volatile bool sensor1_flag=false;
volatile uint32_t body_counter;
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
  * @brief This function handles EXTI line 0 and 1 interrupts.
  */
void EXTI0_1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_1_IRQn 0 */
	uint32_t pr_value;
	pr_value = EXTI->PR;
	if ( (pr_value & 0x1ul) ) {
		printf("Pa.0 int \n\r");
		if (flag_relay1){
			relay1_off();
			flag_relay1=false;
		}else{
			relay1_on();
			flag_relay1=true;
		}
		EXTI->PR |= 0x1ul;
	} else {
		if ( (pr_value & (0x1ul << 1)) ) {
			printf("PA.1 int\n\r");
			if (flag_relay2){
				relay2_off();
				flag_relay2=false;
			}else{
				relay2_on();
				flag_relay2=true;
			}
			EXTI->PR |= (0x1ul<<1);
		}
	}
	
  /* USER CODE END EXTI0_1_IRQn 0 */
  /* USER CODE BEGIN EXTI0_1_IRQn 1 */

  /* USER CODE END EXTI0_1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line 2 and 3 interrupts.
  */
void EXTI2_3_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI2_3_IRQn 0 */
	if( EXTI->PR & (0x1ul<<2) ){
		HAL_Delay(50);
		if( (GPIOB->IDR & (0x1ul<<2)) == 0){
			sensor1_counter = timer7_tick;
			sensor1_flag = true;
			GPIOC->ODR |= 0x1ul<<9;
			printf("PB.2 sensor 1 int \n\r");
		}
		EXTI->PR |= 0x1ul<<2;
		
	}
	
	if( EXTI->PR & (0x1ul<<3) ){
		printf("PB.3 int \n\r");
		if (flag_relay3){
			relay3_off();
			flag_relay3=false;
		}else{
			relay3_on();
			flag_relay3=true;
		}
		EXTI->PR |= 0x1ul<<3;
	}
	
  /* USER CODE END EXTI2_3_IRQn 0 */
  /* USER CODE BEGIN EXTI2_3_IRQn 1 */

  /* USER CODE END EXTI2_3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line 4 to 15 interrupts.
  */
void EXTI4_15_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_15_IRQn 0 */
	if(EXTI->PR & (0x1ul<<4)) {
		HAL_Delay(10);
		if( GPIOC->IDR & (0x1ul<<4) ){
			printf("PC.4 body sensor start\n\r");
			GPIOC->ODR |= 0x1ul<<8;
			body_counter = timer7_tick;
		} else if((GPIOC->IDR & (0x1ul<<4)) == 0){
			GPIOC->ODR &= ~(0x1ul<<8);
			float time = (timer7_tick - body_counter) *0.1;
			printf("PC.4 body sensor end time = %f\n\r",time);
		}
		
		EXTI->PR |= 0x1ul <<4;
	}
	
	if( EXTI->PR & (0x1ul<<6) ){
		HAL_Delay(50);
		if((GPIOC->IDR & (0x1ul<<6)) == 0) {
			printf("PC.6 sensor 2 int\n\r");
		}
		EXTI->PR |= 0x1UL<<6;
	
	}
	
	if(EXTI->PR & (0x1ul<<5)){
		printf("PB.5 int \n\r");
		if (flag_relay4){
			relay4_off();
			flag_relay4=false;
		}else{
			relay4_on();
			flag_relay4=true;
		}
		EXTI->PR |= 0x1ul<<5;
	}
  /* USER CODE END EXTI4_15_IRQn 0 */
  /* USER CODE BEGIN EXTI4_15_IRQn 1 */

  /* USER CODE END EXTI4_15_IRQn 1 */
}

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
	if(sensor1_flag && (timer7_tick - sensor1_counter) >=50){
		GPIOC->ODR &= ~(0x1ul<<9);
		sensor1_flag = false;
		printf("sensor 1 led off \n\r");
	}
//	printf("timer 7\n\r");
	TIM7->SR &= ~0x1ul;

  /* USER CODE END TIM7_IRQn 0 */
  /* USER CODE BEGIN TIM7_IRQn 1 */

  /* USER CODE END TIM7_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
