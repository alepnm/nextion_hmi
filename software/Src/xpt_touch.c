
#include "stm32f0xx_hal.h"
#include "xpt_touch.h"
#include "lcd.h"


#define  XPT_CS_LOW    HAL_GPIO_WritePin(XPTCS_GPIO_Port, XPTCS_Pin, GPIO_PIN_RESET)
#define  XPT_CS_HIGH   HAL_GPIO_WritePin(XPTCS_GPIO_Port, XPTCS_Pin, GPIO_PIN_SET)


XPT_TypeDef XPT;
extern volatile uint32_t Timestamp;


static uint16_t XPT_ReadADC_X(void);
static uint16_t XPT_ReadADC_Y(void);
static uint16_t XPT_ReadADC_N(void);
static uint16_t XPT_ReadTemperature(void);

static void     spi_sendbyte(char d);
static char     spi_readbyte(void);



void XPT_Init(void){

    HAL_GPIO_WritePin(XPTCS_GPIO_Port, XPTCS_Pin, GPIO_PIN_SET);

    XPT.OptionByte = START_BIT | PWDOWN_BETWEEN_CONV | CONV_MODE_8BIT | SELBIT_SEREF;

    XPT.Options.IsEnabled = ENABLE;
    XPT.Options.TouchTimeoutOver = RESET;

    SoftSpiSend( &XPT.OptionByte, 1);
}

void XPT_Process(void){

    if( XPT.Options.IsEnabled == DISABLE ) return;

    XPT.Options.IsPressed = !(FlagStatus)HAL_GPIO_ReadPin(XPTREQ_GPIO_Port, XPTREQ_Pin);

    if( XPT.Options.IsPressed == SET ){

        XPT.adc_x = XPT_ReadADC_X();
        XPT.adc_y = XPT_ReadADC_Y();
        XPT.adc_p = XPT_ReadADC_N();
    } else {

        XPT.temperature = XPT_ReadTemperature();
    }
}


static uint16_t XPT_ReadADC_X(void){

    char data[2];

    XPT_CS_LOW;

    XPT.OptionByte = ( XPT.OptionByte & (~CHANN_SEL_MASK) ) | CHANN_XP0;
    SoftSpiSend( &XPT.OptionByte, 1);

    SoftSpiReceive(data, 2);

    XPT_CS_HIGH;

    return (uint16_t)( data[0]<<8 | data[1]);
}


static uint16_t XPT_ReadADC_Y(void){

    char data[2];

    XPT_CS_LOW;

    XPT.OptionByte = ( XPT.OptionByte & (~CHANN_SEL_MASK) ) | CHANN_YP;
    SoftSpiSend( &XPT.OptionByte, 1);

    SoftSpiReceive(data, 2);

    XPT_CS_HIGH;

    return (uint16_t)( data[0]<<8 | data[1]);
}


static uint16_t XPT_ReadADC_N(void){

    char data[2];

    XPT_CS_LOW;

    XPT.OptionByte = ( XPT.OptionByte & (~CHANN_SEL_MASK) ) | CHANN_XP1;
    SoftSpiSend( &XPT.OptionByte, 1);

    SoftSpiReceive(data, 2);

    XPT_CS_HIGH;

    return (uint16_t)( data[0]<<8 | data[1]);
}


static uint16_t XPT_ReadTemperature(void){

    char data[2];

    XPT_CS_LOW;

    XPT.OptionByte = ( XPT.OptionByte & (~CHANN_SEL_MASK) ) | CHANN_TEMP1;
    SoftSpiSend( &XPT.OptionByte, 1);

    SoftSpiReceive(data, 2);

    XPT_CS_HIGH;

    return (uint16_t)( data[0]<<8 | data[1]);
}



void SoftSpiSend( char* data, uint8_t len){

    uint8_t i = 0;

    do {
        spi_sendbyte( *(data+i) );

    } while( ++i < len );
}


void SoftSpiReceive( char* data, uint8_t len){

    uint8_t i = 0;

    do {
        *(data+i) = spi_readbyte( );

    } while( ++i < len );
}


static void spi_sendbyte( char d ){

    uint8_t i;

    for(i=0; i<8; i++) {

        HAL_GPIO_WritePin( XPTIN_GPIO_Port, XPTIN_Pin, (GPIO_PinState)(d & 0x80) );

        HAL_GPIO_WritePin(XPTCLK_GPIO_Port, XPTCLK_Pin, GPIO_PIN_SET);
        d <<= 1;
        HAL_GPIO_WritePin(XPTCLK_GPIO_Port, XPTCLK_Pin, GPIO_PIN_RESET);
    }
}




static char spi_readbyte(void){

    uint8_t i, spiReadData = 0;

    for(i=0; i<8; i++) {

        spiReadData <<= 1;

        HAL_GPIO_WritePin(XPTCLK_GPIO_Port, XPTCLK_Pin, GPIO_PIN_SET);

        //delay - reikia palaukti

        if( HAL_GPIO_ReadPin(XPTOUT_GPIO_Port, XPTOUT_Pin) != GPIO_PIN_RESET) {
            spiReadData |= 0x01;
        }

        HAL_GPIO_WritePin(XPTCLK_GPIO_Port, XPTCLK_Pin, GPIO_PIN_RESET);

        //delay - reikia palaukti
    }

    return (char)spiReadData;
}


