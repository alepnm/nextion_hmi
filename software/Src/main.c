
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_hal.h"

/* USER CODE BEGIN Includes */
#include "lcd_commands.h"
#include "winbond_spi_flash.h"
#include "xpt_touch.h"


#define PULSE_WR_LOW()      HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_RESET);\
                            asm("nop");\
                            HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET);



/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
DispHandle_TypeDef LCD;

volatile uint32_t Timestamp = 0;

/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
                                    
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
                                

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
static void LCD_Init(void);
static void SystemUpdate(void);

static void LCD_Write_COM_DATA(unsigned char commmand, int data);
static void LCD_Write_COM(unsigned char vl);
static void LCD_Write_DATA(unsigned char vh, unsigned char vl);
static void LCD_Write_DATA_1(unsigned char vl);
static void LCD_Write_Bus(unsigned char vh, unsigned char vl);

static void LCD_FillScreen(unsigned int color);

static void _fast_fill_16(unsigned int ch, unsigned int cl, unsigned long pix);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
    uint32_t touch_to_counter = 10000;

    uint32_t delay = 0;
    uint8_t data[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x09};
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_TIM1_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

    if (HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }

    W25Qx_Init();
    W25Qx_ReadUID(data);

    LCD_Init();

    XPT_Init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {

        if( delay < Timestamp )
        {

            delay = Timestamp + 10;

            SystemUpdate();

            XPT_Process();

            if(LCD.Options.IsPressed == SET)
            {
                touch_to_counter = HAL_GetTick() + 10000;
                LCD.Display.Brightness = 100;
                LCD.Options.TouchTimeoutOver = RESET;
            }
            else
            {

                if(touch_to_counter < Timestamp)
                {

                    if(LCD.Display.Brightness > 10)
                    {
                        LCD.Display.Brightness--;
                    }

                    LCD.Options.TouchTimeoutOver = SET;
                }
            }
        }
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

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* SPI1 init function */
static void MX_SPI1_Init(void)
{

  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM1 init function */
static void MX_TIM1_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 100;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 50;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim1);

}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 38400;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, XPTIN_Pin|XPTCS_Pin|XPTCLK_Pin|W25QCS_Pin 
                          |LCD_RD_Pin|LCD_WR_Pin|LCD_RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_DB0_Pin|LCD_DB1_Pin|LCD_DB2_Pin|LCD_DB10_Pin 
                          |LCD_DB11_Pin|LCD_DB12_Pin|LCD_DB13_Pin|LCD_DB14_Pin 
                          |LCD_DB15_Pin|LCD_DB3_Pin|LCD_DB4_Pin|LCD_DB5_Pin 
                          |LCD_DB6_Pin|LCD_DB7_Pin|LCD_DB8_Pin|LCD_DB9_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, LCD_CS_Pin|LCD_RST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : XPTREQ_Pin */
  GPIO_InitStruct.Pin = XPTREQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(XPTREQ_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : XPTOUT_Pin */
  GPIO_InitStruct.Pin = XPTOUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(XPTOUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : XPTIN_Pin XPTCS_Pin XPTCLK_Pin W25QCS_Pin */
  GPIO_InitStruct.Pin = XPTIN_Pin|XPTCS_Pin|XPTCLK_Pin|W25QCS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_DB0_Pin LCD_DB1_Pin LCD_DB2_Pin LCD_DB10_Pin 
                           LCD_DB11_Pin LCD_DB12_Pin LCD_DB13_Pin LCD_DB14_Pin 
                           LCD_DB15_Pin LCD_DB3_Pin LCD_DB4_Pin LCD_DB5_Pin 
                           LCD_DB6_Pin LCD_DB7_Pin LCD_DB8_Pin LCD_DB9_Pin */
  GPIO_InitStruct.Pin = LCD_DB0_Pin|LCD_DB1_Pin|LCD_DB2_Pin|LCD_DB10_Pin 
                          |LCD_DB11_Pin|LCD_DB12_Pin|LCD_DB13_Pin|LCD_DB14_Pin 
                          |LCD_DB15_Pin|LCD_DB3_Pin|LCD_DB4_Pin|LCD_DB5_Pin 
                          |LCD_DB6_Pin|LCD_DB7_Pin|LCD_DB8_Pin|LCD_DB9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_RD_Pin LCD_WR_Pin LCD_RS_Pin */
  GPIO_InitStruct.Pin = LCD_RD_Pin|LCD_WR_Pin|LCD_RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_CS_Pin */
  GPIO_InitStruct.Pin = LCD_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LCD_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_RST_Pin */
  GPIO_InitStruct.Pin = LCD_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_RST_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
static void LCD_Init(void)
{
    LCD.Display.DisplaySizeX = 320;
    LCD.Display.DisplaySizeY = 480;
    LCD.Display.Brightness = 100;
    LCD.Display.Orient = LANDSCAPE;


    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);


    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(20);
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);

    HAL_Delay(10);

    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

    LCD_Write_COM(0x11);
    HAL_Delay(20);
    LCD_Write_COM(0xD0);
    LCD_Write_DATA_1(0x07);
    LCD_Write_DATA_1(0x42);
    LCD_Write_DATA_1(0x18);

    LCD_Write_COM(0xD1);
    LCD_Write_DATA_1(0x00);
    LCD_Write_DATA_1(0x07);
    LCD_Write_DATA_1(0x10);

    LCD_Write_COM(0xD2);
    LCD_Write_DATA_1(0x01);
    LCD_Write_DATA_1(0x02);

    LCD_Write_COM(0xC0);
    LCD_Write_DATA_1(0x10);
    LCD_Write_DATA_1(0x3B);
    LCD_Write_DATA_1(0x00);
    LCD_Write_DATA_1(0x02);
    LCD_Write_DATA_1(0x11);

    LCD_Write_COM(0xC5);
    LCD_Write_DATA_1(0x03);

    LCD_Write_COM(0xC8);
    LCD_Write_DATA_1(0x00);
    LCD_Write_DATA_1(0x32);
    LCD_Write_DATA_1(0x36);
    LCD_Write_DATA_1(0x45);
    LCD_Write_DATA_1(0x06);
    LCD_Write_DATA_1(0x16);
    LCD_Write_DATA_1(0x37);
    LCD_Write_DATA_1(0x75);
    LCD_Write_DATA_1(0x77);
    LCD_Write_DATA_1(0x54);
    LCD_Write_DATA_1(0x0C);
    LCD_Write_DATA_1(0x00);

    LCD_Write_COM(0x36);
    LCD_Write_DATA_1(0x0A);

    LCD_Write_COM(0x3A);
    LCD_Write_DATA_1(0x55);

    LCD_Write_COM(0x2A);
    LCD_Write_DATA_1(0x00);
    LCD_Write_DATA_1(0x00);
    LCD_Write_DATA_1(0x01);
    LCD_Write_DATA_1(0x3F);

    LCD_Write_COM(0x2B);
    LCD_Write_DATA_1(0x00);
    LCD_Write_DATA_1(0x00);
    LCD_Write_DATA_1(0x01);
    LCD_Write_DATA_1(0xE0);
    HAL_Delay(120);
    LCD_Write_COM(0x29);

    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);


    LCD_FillScreen(0xFFFF);

}


static void LCD_Write_COM_DATA(unsigned char commmand, int data)
{
    LCD_Write_COM(commmand);
    LCD_Write_DATA(data >> 8, data);
}

static void LCD_Write_COM(unsigned char vl)
{
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
    LCD_Write_Bus(0x00, vl);
}


static void LCD_Write_DATA(unsigned char vh, unsigned char vl)
{
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
    LCD_Write_Bus(vh, vl);
}


static void LCD_Write_DATA_1(unsigned char vl)
{
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
    LCD_Write_Bus(0x00, vl);
}


static void LCD_Write_Bus(unsigned char vh, unsigned char vl)
{
    GPIOB->ODR = ( vh<<8 | vl );

    //asm("nop");
    PULSE_WR_LOW()
    //asm("nop");
}


static void LCD_FillScreen(unsigned int color)
{
    unsigned char ch = (unsigned char)(color >> 8);
    unsigned char cl = (unsigned char)(color & 0xFF);

    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

    LCD_Write_COM(0x2a);
    LCD_Write_DATA_1(0>>8);
    //LCD_Write_DATA_1(0);
    LCD_Write_DATA_1(LCD.Display.DisplaySizeX>>8);
    //LCD_Write_DATA_1(LCD.Display.DisplaySizeX);
    LCD_Write_COM(0x2b);
    LCD_Write_DATA_1(0>>8);
    //LCD_Write_DATA_1(0);
    LCD_Write_DATA_1(LCD.Display.DisplaySizeY>>8);
    //LCD_Write_DATA_1(LCD.Display.DisplaySizeY);
    LCD_Write_COM(0x2c);


    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);

    _fast_fill_16(ch, cl, LCD.Display.DisplaySizeY * LCD.Display.DisplaySizeX);

    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}


static void _fast_fill_16(unsigned int ch, unsigned int cl, unsigned long pix)
{
    unsigned long blocks;
    unsigned int i;

    GPIOB->ODR = ( ch<<8 | cl );

    blocks = pix / 16;

    for (i = 0; i < blocks; i++)
    {
        PULSE_WR_LOW();
        PULSE_WR_LOW();
        PULSE_WR_LOW();
        PULSE_WR_LOW();
        PULSE_WR_LOW();
        PULSE_WR_LOW();
        PULSE_WR_LOW();
        PULSE_WR_LOW();
        PULSE_WR_LOW();
        PULSE_WR_LOW();
        PULSE_WR_LOW();
        PULSE_WR_LOW();
        PULSE_WR_LOW();
        PULSE_WR_LOW();
        PULSE_WR_LOW();
        PULSE_WR_LOW();
    }

    if ((pix % 16) != 0)
    {
        for (i = 0; i < (pix % 16) + 1; i++)
        {
            PULSE_WR_LOW();
        }
    }
}


static void SystemUpdate(void)
{

    __HAL_TIM_SET_COMPARE( &htim1, TIM_CHANNEL_1, LCD.Display.Brightness);

}



void HAL_SYSTICK_Callback(void)
{
    Timestamp = HAL_GetTick();

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
