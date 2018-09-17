
#include "stm32f0xx_hal.h"
#include "nextion.h"
#include "ili9841.h"
#include "xpt2046.h"
#include "w25qx.h"

extern TIM_HandleTypeDef htim1;
extern SPI_HandleTypeDef hspi1;


void Nextion_Init(void) {

    LCD.API->Init();

    LCD.Brightnes = 100;
    LCD.fnt_color = VGA_GREEN;
    LCD.bg_color = VGA_BLACK;

    LCD_SetBrightness();

    XPT_Init();

    W25Qx_Init();
}


static void LCD_IO_Write_Bus(unsigned char vh, unsigned char vl);



/********************************* LINK LCD ***********************************/
/*  */
void LCD_IO_Init(void) {

}


/* patikrinta */
void LCD_IO_Write_COM(unsigned char vl) {
    LCD_RS_LOW();
    LCD_IO_Write_Bus(0x00, vl);
}


/* patikrinta */
void LCD_IO_Write_DATA(unsigned char vh, unsigned char vl) {
    LCD_RS_HIGH();
    LCD_IO_Write_Bus(vh, vl);
}

/* patikrinta */
void LCD_IO_Write_DATA_1(unsigned char vl) {
    LCD_RS_HIGH();
    LCD_IO_Write_Bus(0x00, vl);
}

/* patikrinta */
static void LCD_IO_Write_Bus(unsigned char vh, unsigned char vl) {
    GPIOB->ODR = (uint16_t)( vh<<8 | vl );
    PULSE_WR_LOW()
}

/*  */
void LCD_IO_BusAsInput(void) {

    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = LCD_DB0_Pin|LCD_DB1_Pin|LCD_DB2_Pin|LCD_DB10_Pin
                          |LCD_DB11_Pin|LCD_DB12_Pin|LCD_DB13_Pin|LCD_DB14_Pin
                          |LCD_DB15_Pin|LCD_DB3_Pin|LCD_DB4_Pin|LCD_DB5_Pin
                          |LCD_DB6_Pin|LCD_DB7_Pin|LCD_DB8_Pin|LCD_DB9_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/*  */
void LCD_IO_BusAsOutput(void) {

    GPIO_InitTypeDef GPIO_InitStruct;

    HAL_GPIO_WritePin(GPIOB, LCD_DB0_Pin|LCD_DB1_Pin|LCD_DB2_Pin|LCD_DB10_Pin
                      |LCD_DB11_Pin|LCD_DB12_Pin|LCD_DB13_Pin|LCD_DB14_Pin
                      |LCD_DB15_Pin|LCD_DB3_Pin|LCD_DB4_Pin|LCD_DB5_Pin
                      |LCD_DB6_Pin|LCD_DB7_Pin|LCD_DB8_Pin|LCD_DB9_Pin, GPIO_PIN_RESET);


    GPIO_InitStruct.Pin = LCD_DB0_Pin|LCD_DB1_Pin|LCD_DB2_Pin|LCD_DB10_Pin
                          |LCD_DB11_Pin|LCD_DB12_Pin|LCD_DB13_Pin|LCD_DB14_Pin
                          |LCD_DB15_Pin|LCD_DB3_Pin|LCD_DB4_Pin|LCD_DB5_Pin
                          |LCD_DB6_Pin|LCD_DB7_Pin|LCD_DB8_Pin|LCD_DB9_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/*  */
void LCD_Delay(uint32_t Delay) {
    HAL_Delay(Delay);
}


void LCD_SetBrightness(void){
    __HAL_TIM_SET_COMPARE( &htim1, TIM_CHANNEL_1, LCD.Brightnes);
}


/*  */
void SoftSpi_SendByte( char d ){

    uint8_t i;

    for(i=0; i<8; i++) {

        HAL_GPIO_WritePin( XPTIN_GPIO_Port, XPTIN_Pin, (GPIO_PinState)(d & 0x80) );

        XPT_CLK_HIGH();
        d <<= 1;
        XPT_CLK_LOW();
    }
}

/*  */
char SoftSpi_ReadByte(void){

    uint8_t i, spiReadData = 0;

    for(i=0; i<8; i++) {

        spiReadData <<= 1;

        XPT_CLK_HIGH();

        //delay - reikia palaukti

        if( HAL_GPIO_ReadPin(XPTOUT_GPIO_Port, XPTOUT_Pin) != GPIO_PIN_RESET) {
            spiReadData |= 0x01;
        }

        XPT_CLK_LOW();

        //delay - reikia palaukti
    }

    return (char)spiReadData;
}



/*  */
uint8_t SPIx_TX( uint8_t spi, uint8_t* data, uint16_t len ){

    SPI_HandleTypeDef* phspi = NULL;

    if(spi == 1) phspi = &hspi1;
    //else phspi = &hspi2;

    if(phspi == NULL) return 1;

    (void)HAL_SPI_Transmit(phspi, data, len, 100);
    while( phspi->State == HAL_SPI_STATE_BUSY );

    return 0;
}


/*  */
uint8_t SPIx_RX( uint8_t spi, uint8_t* data, uint16_t len ){

    SPI_HandleTypeDef* phspi = NULL;

    if(spi == 1) phspi = &hspi1;
    //else phspi = &hspi2;

    if(phspi == NULL) return 1;

    (void)HAL_SPI_Receive(&hspi1, data, len, 100);
    while( phspi->State == HAL_SPI_STATE_BUSY );

    return 0;
}
