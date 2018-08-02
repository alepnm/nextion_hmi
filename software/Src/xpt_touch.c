
#include "stm32f0xx_hal.h"
#include "xpt_touch.h"


#define  XPT_CS_LOW    HAL_GPIO_WritePin(XPTCS_GPIO_Port, XPTCS_Pin, GPIO_PIN_RESET)
#define  XPT_CS_HIGH   HAL_GPIO_WritePin(XPTCS_GPIO_Port, XPTCS_Pin, GPIO_PIN_SET)


static FlagStatus IsTouchEnabled = RESET;
static FlagStatus TouchIsPresset = RESET;
static volatile uint16_t adc_x, adc_y;


static uint16_t XPT_ReadADC_X (void);
static uint16_t XPT_ReadADC_Y (void);

static void spi_sendbyte(unsigned char d);
static uint8_t spi_readbyte(void);



void XPT_Process(void) {

    if( IsTouchEnabled == RESET ) return;

    TouchIsPresset = (FlagStatus)HAL_GPIO_ReadPin(XPTREQ_GPIO_Port, XPTREQ_Pin);

    if( TouchIsPresset == RESET ) {

        adc_x = XPT_ReadADC_X();
        adc_y = XPT_ReadADC_Y();

    } else {


    }
}


static uint16_t XPT_ReadADC_X(void) {


    return 0;

//	uint8_t c, b;
//	uint16_t i = 0, a;
//	// nCS := 0
//	CS ( );
//
//	// Wait 100 ns
////	delay_ms ( 1 ); //задержка 1мС
//	for ( i_delay = 0; i_delay < 0x00008000; i_delay ++ );
//
//	spi2_sendByte ( 0xB8 ); // 0xB8 = 1011 1000: xxpt2046.pdf, page 22
//							//  7: S = 1;
//							//  6..4: A2..0 = 011 - Channel select (Table 1, p.15) - Ch
//							//  3: 1 - Mode
//							//  2: SER/nDRF = 0
//							//  1..0: 00 - Power down mode
//	c = spi2_sendByte ( 0 );  // Читаем Z1 и Z2 их сумма не должна быть меньше 5
//	// SPI3_WR(0xC8); // нахрена я не знаю, но мне кажется это связано с
//	spi2_sendByte ( 0xC8 );		// 0xC8 = 1100 1000 - Channel 100
//	b = spi2_sendByte ( 0 );  // ошибками чтения
//	a = c + b;		 //
//	if ( a >= 5)
//	{
//		for ( a = 0; a < 8; a ++ )
//		{ // 8 раз читаем значение Х и вычисляем среднее
//			// SPI3_WR(0x90); //команда на чтение координат Х
//			spi2_sendByte ( 0x90 );		// 0x90 = 1001 0000 - Channel 001
//			i += RD_t ( );
//		} // for
//	} // if
//
//	// nCS := 1
//	D_CS();
//
//	i >>= 3;
//	return i;
}


static uint16_t XPT_ReadADC_Y(void) {


    return 0;

//	uint8_t c, b;
//	uint16_t i = 0, a;
//	// nCS := 0
//	CS();
//
//	// Wait 100 ns
////	delay_ms ( 1 ); //задержка 1мС
//	for ( i_delay = 0; i_delay < 0x00008000; i_delay ++ );
//
//	spi2_sendByte ( 0xB8 ); // 0xB8 = 1011 1000: xxpt2046.pdf, page 22
//							//  7: S = 1;
//							//  6..4: A2..0 = 011 - Channel select (Table 1, p.15) - Ch
//							//  3: 1 - Mode
//							//  2: SER/nDRF = 0
//							//  1..0: 00 - Power down mode
//	c = spi2_sendByte ( 0 );  // Читаем Z1 и Z2 их сумма не должна быть меньше 5
//	// SPI3_WR(0xC8); // нахрена я не знаю, но мне кажется это связано с
//	spi2_sendByte ( 0xC8 );		// 0xC8 = 1100 1000 - Channel 100
//	b = spi2_sendByte ( 0 );  // ошибками чтения
//	a = c + b;		 //
//	if ( a >= 5 )
//	{
//		for ( a = 0; a < 8; a ++ )
//		{
//			// SPI3_WR ( 0xD0 ); //команда на чтение координат Y
//								// 0xD0 = 1101 0000 - Ch 101
//			spi2_sendByte ( 0xD0 );
//			i += RD_t ( );
//		} // for
//	} // if
//
//	// nCS := 1
//	D_CS ( );
//
//	i >>= 3;
//	return i;
}



static int RD_t(void) {



    return 0;

//	uint16_t a, b, temp; //данные из сенсора мы получаем 12 разрядные
//	a = spi2_sendByte ( 0 );
//	b = spi2_sendByte ( 0 );
//	temp = ((a << 4) | (b >> 4));
//	return temp;
}



void SoftSpiSend( uint8_t* data, uint8_t len) {

    uint8_t i = 0;

    XPT_CS_LOW;

    do {
        spi_sendbyte( *(data+i) );

    } while( ++i < len );


    XPT_CS_HIGH;
}


void SoftSpiReceive( uint8_t* data, uint8_t len) {

    uint8_t i = 0;

    XPT_CS_LOW;

    do {
        *(data+i) = spi_readbyte( );

    } while( ++i < len );

    XPT_CS_HIGH;
}


static void spi_sendbyte( unsigned char d ) {

    uint8_t i;

    for(i=0; i<8; i++) {

        HAL_GPIO_WritePin( XPTIN_GPIO_Port, XPTIN_Pin, (GPIO_PinState)(d & 0x80) );

        HAL_GPIO_WritePin(XPTCLK_GPIO_Port, XPTCLK_Pin, GPIO_PIN_SET);
        d <<= 1;
        HAL_GPIO_WritePin(XPTCLK_GPIO_Port, XPTCLK_Pin, GPIO_PIN_RESET);
    }
}




static uint8_t spi_readbyte(void) {

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

    return spiReadData;
}


