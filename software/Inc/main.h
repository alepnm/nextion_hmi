/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V.
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include <stdint.h>
#include "stm32f0xx.h"

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define SD_RST_Pin GPIO_PIN_13
#define SD_RST_GPIO_Port GPIOC
#define XPTREQ_Pin GPIO_PIN_14
#define XPTREQ_GPIO_Port GPIOC
#define SD_DETECT_Pin GPIO_PIN_15
#define SD_DETECT_GPIO_Port GPIOC
#define XPTOUT_Pin GPIO_PIN_0
#define XPTOUT_GPIO_Port GPIOA
#define XPTIN_Pin GPIO_PIN_1
#define XPTIN_GPIO_Port GPIOA
#define XPTCS_Pin GPIO_PIN_2
#define XPTCS_GPIO_Port GPIOA
#define XPTCLK_Pin GPIO_PIN_3
#define XPTCLK_GPIO_Port GPIOA
#define W25QCS_Pin GPIO_PIN_4
#define W25QCS_GPIO_Port GPIOA
#define LCD_DB0_Pin GPIO_PIN_0
#define LCD_DB0_GPIO_Port GPIOB
#define LCD_DB1_Pin GPIO_PIN_1
#define LCD_DB1_GPIO_Port GPIOB
#define LCD_DB2_Pin GPIO_PIN_2
#define LCD_DB2_GPIO_Port GPIOB
#define LCD_DB10_Pin GPIO_PIN_10
#define LCD_DB10_GPIO_Port GPIOB
#define LCD_DB11_Pin GPIO_PIN_11
#define LCD_DB11_GPIO_Port GPIOB
#define LCD_DB12_Pin GPIO_PIN_12
#define LCD_DB12_GPIO_Port GPIOB
#define LCD_DB13_Pin GPIO_PIN_13
#define LCD_DB13_GPIO_Port GPIOB
#define LCD_DB14_Pin GPIO_PIN_14
#define LCD_DB14_GPIO_Port GPIOB
#define LCD_DB15_Pin GPIO_PIN_15
#define LCD_DB15_GPIO_Port GPIOB
#define DISPLAY_LED_Pin GPIO_PIN_8
#define DISPLAY_LED_GPIO_Port GPIOA
#define LCD_RD_Pin GPIO_PIN_11
#define LCD_RD_GPIO_Port GPIOA
#define LCD_WR_Pin GPIO_PIN_12
#define LCD_WR_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_6
#define LCD_CS_GPIO_Port GPIOF
#define LCD_RST_Pin GPIO_PIN_7
#define LCD_RST_GPIO_Port GPIOF
#define LCD_RS_Pin GPIO_PIN_15
#define LCD_RS_GPIO_Port GPIOA
#define LCD_DB3_Pin GPIO_PIN_3
#define LCD_DB3_GPIO_Port GPIOB
#define LCD_DB4_Pin GPIO_PIN_4
#define LCD_DB4_GPIO_Port GPIOB
#define LCD_DB5_Pin GPIO_PIN_5
#define LCD_DB5_GPIO_Port GPIOB
#define LCD_DB6_Pin GPIO_PIN_6
#define LCD_DB6_GPIO_Port GPIOB
#define LCD_DB7_Pin GPIO_PIN_7
#define LCD_DB7_GPIO_Port GPIOB
#define LCD_DB8_Pin GPIO_PIN_8
#define LCD_DB8_GPIO_Port GPIOB
#define LCD_DB9_Pin GPIO_PIN_9
#define LCD_DB9_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */
#define swap(type, i, j) { type t = i; i = j; j = t; }

 typedef struct {
     const uint16_t *data;
     uint16_t width;
     uint16_t height;
     uint8_t dataSize;
} tImage;

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
