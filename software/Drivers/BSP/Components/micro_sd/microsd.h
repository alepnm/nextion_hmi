#ifndef MICROSD_H_INCLUDED
#define MICROSD_H_INCLUDED



uint8_t SD_init(void);
uint8_t SD_ReadSector(uint32_t block, uint8_t *buff);
uint8_t SD_WriteSector(uint32_t block, uint8_t *buff);


/*  */
static inline uint8_t spi_tx (uint8_t spi, uint8_t* data, uint16_t len) {
    return SPIx_TX( spi, data, len);
}


/*  */
static inline uint8_t spi_rx (uint8_t spi, uint8_t* data, uint16_t len) {
    return SPIx_RX( spi, data, len);
}

#endif /* MICROSD_H_INCLUDED */
