/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI4_15_IRQn
#define led_1_Pin GPIO_PIN_0
#define led_1_GPIO_Port GPIOC
#define led_2_Pin GPIO_PIN_1
#define led_2_GPIO_Port GPIOC
#define led_3_Pin GPIO_PIN_2
#define led_3_GPIO_Port GPIOC
#define led_4_Pin GPIO_PIN_3
#define led_4_GPIO_Port GPIOC
#define key_1_Pin GPIO_PIN_0
#define key_1_GPIO_Port GPIOA
#define key_1_EXTI_IRQn EXTI0_1_IRQn
#define key_2_Pin GPIO_PIN_1
#define key_2_GPIO_Port GPIOA
#define key_2_EXTI_IRQn EXTI0_1_IRQn
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define key_4_Pin GPIO_PIN_5
#define key_4_GPIO_Port GPIOC
#define key_4_EXTI_IRQn EXTI4_15_IRQn
#define led_5_Pin GPIO_PIN_0
#define led_5_GPIO_Port GPIOB
#define DHT11_Pin GPIO_PIN_11
#define DHT11_GPIO_Port GPIOA
#define DHT22_Pin GPIO_PIN_12
#define DHT22_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define key_3_Pin GPIO_PIN_3
#define key_3_GPIO_Port GPIOB
#define key_3_EXTI_IRQn EXTI2_3_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
