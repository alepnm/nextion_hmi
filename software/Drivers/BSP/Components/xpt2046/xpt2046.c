
#include "nextion.h"
#include "xpt2046.h"


XPT_TypeDef XPT;
extern volatile uint32_t Timestamp;


static uint16_t XPT_ReadADC_X(void);
static uint16_t XPT_ReadADC_Y(void);
static uint16_t XPT_ReadADC_N(void);
static uint16_t XPT_ReadTemperature(void);

/*  */
void XPT_Init(void){

    XPT_CS_HIGH();

    XPT.OptionByte = START_BIT | PWDOWN_BETWEEN_CONV | CONV_MODE_8BIT | SELBIT_SEREF;

    XPT.Options.IsEnabled = ENABLE;
    XPT.Options.TouchTimeoutOver = RESET;

    SoftSpiSend( &XPT.OptionByte, 1);
}

/*  */
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

/*  */
static uint16_t XPT_ReadADC_X(void){

    char data[2];

    XPT_CS_LOW();

    XPT.OptionByte = ( XPT.OptionByte & (~CHANN_SEL_MASK) ) | CHANN_XP0;
    SoftSpiSend( &XPT.OptionByte, 1);

    SoftSpiReceive(data, 2);

    XPT_CS_HIGH();

    return (uint16_t)( data[0]<<8 | data[1]);
}

/*  */
static uint16_t XPT_ReadADC_Y(void){

    char data[2];

    XPT_CS_LOW();

    XPT.OptionByte = ( XPT.OptionByte & (~CHANN_SEL_MASK) ) | CHANN_YP;
    SoftSpiSend( &XPT.OptionByte, 1);

    SoftSpiReceive(data, 2);

    XPT_CS_HIGH();

    return (uint16_t)( data[0]<<8 | data[1]);
}

/*  */
static uint16_t XPT_ReadADC_N(void){

    char data[2];

    XPT_CS_LOW();

    XPT.OptionByte = ( XPT.OptionByte & (~CHANN_SEL_MASK) ) | CHANN_XP1;
    SoftSpiSend( &XPT.OptionByte, 1);

    SoftSpiReceive(data, 2);

    XPT_CS_HIGH();

    return (uint16_t)( data[0]<<8 | data[1]);
}

/*  */
static uint16_t XPT_ReadTemperature(void){

    char data[2];

    XPT_CS_LOW();

    XPT.OptionByte = ( XPT.OptionByte & (~CHANN_SEL_MASK) ) | CHANN_TEMP1;
    SoftSpiSend( &XPT.OptionByte, 1);

    SoftSpiReceive(data, 2);

    XPT_CS_HIGH();

    return (uint16_t)( data[0]<<8 | data[1]);
}

