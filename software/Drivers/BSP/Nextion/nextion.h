#ifndef NEXTION_H_INCLUDED
#define NEXTION_H_INCLUDED

#include <stdint.h>
#include "stm32f0xx_hal.h"

#define USED_SPI    1

/* LCD Display */
#define LCD_CS_LOW()        HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET)
#define LCD_CS_HIGH()       HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET)
#define LCD_RS_LOW()        HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET)
#define LCD_RS_HIGH()       HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET)

#define LCD_RST_LOW()       HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET)
#define LCD_RST_HIGH()      HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET)

#define LCD_RD_LOW()        HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_RESET)
#define LCD_RD_HIGH()       HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_SET)

#define LCD_WR_LOW()        HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_RESET)
#define LCD_WR_HIGH()       HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET)

#define PULSE_WR_LOW()      LCD_WR_LOW(); asm("nop"); LCD_WR_HIGH();


/* Touch Panel */
#define XPT_CS_LOW()        HAL_GPIO_WritePin(XPTCS_GPIO_Port, XPTCS_Pin, GPIO_PIN_RESET)
#define XPT_CS_HIGH()       HAL_GPIO_WritePin(XPTCS_GPIO_Port, XPTCS_Pin, GPIO_PIN_SET)

#define XPT_CLK_LOW()       HAL_GPIO_WritePin(XPTCLK_GPIO_Port, XPTCLK_Pin, GPIO_PIN_RESET)
#define XPT_CLK_HIGH()      HAL_GPIO_WritePin(XPTCLK_GPIO_Port, XPTCLK_Pin, GPIO_PIN_RESET)

/* SPI-Flash */
#define W25Q_CS_LOW()       asm("nop"); HAL_GPIO_WritePin(W25QCS_GPIO_Port, W25QCS_Pin, GPIO_PIN_RESET); asm("nop");
#define W25Q_CS_HIGH()      asm("nop"); HAL_GPIO_WritePin(W25QCS_GPIO_Port, W25QCS_Pin, GPIO_PIN_SET); asm("nop");

/* Micro SD Card */
#define SD_CS_LOW()         HAL_GPIO_WritePin(SDCS_GPIO_Port, SDCS_Pin, GPIO_PIN_RESET);
#define SD_CS_HIGH()    	HAL_GPIO_WritePin(SDCS_GPIO_Port, SDCS_Pin, GPIO_PIN_SET);


void Nextion_Init(void);



/* LCD */
void LCD_IO_Init(void);
void LCD_IO_BusAsInput(void);
void LCD_IO_BusAsOutput(void);

void LCD_IO_Write_COM(unsigned char vl);
void LCD_IO_Write_DATA(unsigned char vh, unsigned char vl);
void LCD_IO_Write_DATA_1(unsigned char vl);


void LCD_Delay(uint32_t Delay);
void LCD_SetBrightness(void);


void SoftSpiSend( char* data, uint8_t len);
void SoftSpiReceive( char* data, uint8_t len);
//void SoftSpi_SendByte(uint8_t d);
//uint8_t SoftSpi_ReadByte(void);


uint8_t SPIx_TX( uint8_t spi, uint8_t* data, uint16_t len);
uint8_t SPIx_RX( uint8_t spi, uint8_t* data, uint16_t len);

#endif /* NEXTION_H_INCLUDED */
