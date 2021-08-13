/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_TX_Pin GPIO_PIN_2
#define LED_TX_GPIO_Port GPIOE
#define LED_ACT_Pin GPIO_PIN_3
#define LED_ACT_GPIO_Port GPIOE
#define LED_CH1_Pin GPIO_PIN_4
#define LED_CH1_GPIO_Port GPIOE
#define LED_CH2_Pin GPIO_PIN_5
#define LED_CH2_GPIO_Port GPIOE
#define SYNC_OUT_TEST_Pin GPIO_PIN_13
#define SYNC_OUT_TEST_GPIO_Port GPIOC
#define CMX7032_IRQ_Pin GPIO_PIN_0
#define CMX7032_IRQ_GPIO_Port GPIOC
#define CMX7032_IRQ_EXTI_IRQn EXTI0_IRQn
#define GPS_PPS_Pin GPIO_PIN_1
#define GPS_PPS_GPIO_Port GPIOC
#define GPS_PPS_EXTI_IRQn EXTI1_IRQn
#define CMX_PWR_CTRL_Pin GPIO_PIN_0
#define CMX_PWR_CTRL_GPIO_Port GPIOA
#define GPS_EXTINT_Pin GPIO_PIN_1
#define GPS_EXTINT_GPIO_Port GPIOA
#define CBUS_CSN_Pin GPIO_PIN_4
#define CBUS_CSN_GPIO_Port GPIOA
#define CBUS_SCK_Pin GPIO_PIN_5
#define CBUS_SCK_GPIO_Port GPIOA
#define CBUS_RDATA_Pin GPIO_PIN_6
#define CBUS_RDATA_GPIO_Port GPIOA
#define CBUS_CDATA_Pin GPIO_PIN_7
#define CBUS_CDATA_GPIO_Port GPIOA
#define GPIO_C4_Pin GPIO_PIN_4
#define GPIO_C4_GPIO_Port GPIOC
#define GPIO_C5_Pin GPIO_PIN_5
#define GPIO_C5_GPIO_Port GPIOC
#define SLOT_CLK_Pin GPIO_PIN_0
#define SLOT_CLK_GPIO_Port GPIOB
#define GPIO_B1_Pin GPIO_PIN_1
#define GPIO_B1_GPIO_Port GPIOB
#define GPIO_B2_Pin GPIO_PIN_2
#define GPIO_B2_GPIO_Port GPIOB
#define TX_VCO_EN_Pin GPIO_PIN_9
#define TX_VCO_EN_GPIO_Port GPIOE
#define FLASH_RST_Pin GPIO_PIN_10
#define FLASH_RST_GPIO_Port GPIOE
#define FLASH_NSS_Pin GPIO_PIN_11
#define FLASH_NSS_GPIO_Port GPIOE
#define FLASH_SCK_Pin GPIO_PIN_12
#define FLASH_SCK_GPIO_Port GPIOE
#define FLASH_MISO_Pin GPIO_PIN_13
#define FLASH_MISO_GPIO_Port GPIOE
#define FLASH_MOSI_Pin GPIO_PIN_14
#define FLASH_MOSI_GPIO_Port GPIOE
#define FLASH_WP_Pin GPIO_PIN_15
#define FLASH_WP_GPIO_Port GPIOE
#define LOCK_DET_RXB_Pin GPIO_PIN_10
#define LOCK_DET_RXB_GPIO_Port GPIOB
#define LOCK_DET_RXA_Pin GPIO_PIN_12
#define LOCK_DET_RXA_GPIO_Port GPIOB
#define PA_TEST_EN_Pin GPIO_PIN_10
#define PA_TEST_EN_GPIO_Port GPIOC
#define SPI_SSEL1_Pin GPIO_PIN_0
#define SPI_SSEL1_GPIO_Port GPIOD
#define SPI_SSEL2_Pin GPIO_PIN_1
#define SPI_SSEL2_GPIO_Port GPIOD
#define RX_ON_Pin GPIO_PIN_5
#define RX_ON_GPIO_Port GPIOB
#define GPS_RST_Pin GPIO_PIN_7
#define GPS_RST_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
