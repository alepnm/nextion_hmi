
#include "stm32f0xx_hal.h"
#include "hwlib.h"


extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;


/*  */
uint8_t spi_tx( uint8_t spi, uint8_t* data, uint16_t len){

    SPI_HandleTypeDef* phspi = NULL;

    if(spi == 1) phspi = &hspi1;
    //else phspi = &hspi2;

    if(phspi == NULL) return 1;

    (void)HAL_SPI_Transmit(phspi, data, len, 100);
    while( phspi->State == HAL_SPI_STATE_BUSY );

    return 0;
}


/*  */
uint8_t spi_rx( uint8_t spi, uint8_t* data, uint16_t len){

    SPI_HandleTypeDef* phspi = NULL;

    if(spi == 1) phspi = &hspi1;
    //else phspi = &hspi2;

    if(phspi == NULL) return 1;

    (void)HAL_SPI_Receive(&hspi1, data, len, 100);
    while( phspi->State == HAL_SPI_STATE_BUSY );

    return 0;
}
