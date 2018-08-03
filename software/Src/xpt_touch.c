
#include "stm32f0xx_hal.h"
#include "xpt_touch.h"


#define  XPT_CS_LOW    HAL_GPIO_WritePin(XPTCS_GPIO_Port, XPTCS_Pin, GPIO_PIN_RESET)
#define  XPT_CS_HIGH   HAL_GPIO_WritePin(XPTCS_GPIO_Port, XPTCS_Pin, GPIO_PIN_SET)


extern DispHandle_TypeDef LCD;
extern volatile uint32_t Timestamp;


static uint16_t XPT_ReadADC_X(void);
static uint16_t XPT_ReadADC_Y(void);
static uint16_t XPT_ReadADC_N(void);
static uint16_t XPT_ReadTemperature(void);

static void     spi_sendbyte(char d);
static char  spi_readbyte(void);



void XPT_Init(void){

    HAL_GPIO_WritePin(XPTCS_GPIO_Port, XPTCS_Pin, GPIO_PIN_SET);

    LCD.XPT.OptionByte = START_BIT | PWDOWN_BETWEEN_CONV | CONV_MODE_8BIT | SELBIT_SEREF;

    LCD.Options.IsEnabled = ENABLE;
    LCD.Options.TouchTimeoutOver = RESET;

    SoftSpiSend( &LCD.XPT.OptionByte, 1);

    LCD.Options.AdcX_Min = 1500;
    LCD.Options.AdcX_Max = 32768;

    LCD.Options.AdcY_Min = 2500;
    LCD.Options.AdcY_Max = 32768;

    LCD.Display.DisplaySizeX_Ratio = LCD.Options.AdcX_Max / LCD.Display.DisplaySizeX;
    LCD.Display.DisplaySizeY_Ratio = LCD.Options.AdcY_Max / LCD.Display.DisplaySizeY;
}

void XPT_Process(void){

    if( LCD.Options.IsEnabled == DISABLE ) return;

    LCD.Options.IsPressed = !(FlagStatus)HAL_GPIO_ReadPin(XPTREQ_GPIO_Port, XPTREQ_Pin);

    if( LCD.Options.IsPressed == SET ){

        LCD.XPT.adc_x = XPT_ReadADC_X();

        LCD.Display.PositionX = (float)LCD.XPT.adc_x / LCD.Display.DisplaySizeX_Ratio;

        LCD.XPT.adc_y = XPT_ReadADC_Y();

        LCD.Display.PositionY = (float)LCD.XPT.adc_y / LCD.Display.DisplaySizeY_Ratio;

        LCD.XPT.adc_p = XPT_ReadADC_N();
    } else {

        LCD.XPT.temperature = XPT_ReadTemperature();
    }
}


static uint16_t XPT_ReadADC_X(void){

    char data[2];

    XPT_CS_LOW;

    LCD.XPT.OptionByte = ( LCD.XPT.OptionByte & (~CHANN_SEL_MASK) ) | CHANN_XP0;
    SoftSpiSend( &LCD.XPT.OptionByte, 1);

    SoftSpiReceive(data, 2);

    XPT_CS_HIGH;

    return (uint16_t)( data[0]<<8 | data[1]);
}


static uint16_t XPT_ReadADC_Y(void){

    char data[2];

    XPT_CS_LOW;

    LCD.XPT.OptionByte = ( LCD.XPT.OptionByte & (~CHANN_SEL_MASK) ) | CHANN_YP;
    SoftSpiSend( &LCD.XPT.OptionByte, 1);

    SoftSpiReceive(data, 2);

    XPT_CS_HIGH;

    return (uint16_t)( data[0]<<8 | data[1]);
}


static uint16_t XPT_ReadADC_N(void){

    char data[2];

    XPT_CS_LOW;

    LCD.XPT.OptionByte = ( LCD.XPT.OptionByte & (~CHANN_SEL_MASK) ) | CHANN_XP1;
    SoftSpiSend( &LCD.XPT.OptionByte, 1);

    SoftSpiReceive(data, 2);

    XPT_CS_HIGH;

    return (uint16_t)( data[0]<<8 | data[1]);
}


static uint16_t XPT_ReadTemperature(void){

    char data[2];

    XPT_CS_LOW;

    LCD.XPT.OptionByte = ( LCD.XPT.OptionByte & (~CHANN_SEL_MASK) ) | CHANN_TEMP1;
    SoftSpiSend( &LCD.XPT.OptionByte, 1);

    SoftSpiReceive(data, 2);

    XPT_CS_HIGH;

    return (uint16_t)( data[0]<<8 | data[1]);
}



static int RD_t(void){



    return 0;

//	uint16_t a, b, temp; //данные из сенсора мы получаем 12 разрядные
//	a = spi2_sendByte ( 0 );
//	b = spi2_sendByte ( 0 );
//	temp = ((a << 4) | (b >> 4));
//	return temp;
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


