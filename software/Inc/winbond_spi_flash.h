#ifndef WINBOND_SPI_FLASH_H_INCLUDED
#define WINBOND_SPI_FLASH_H_INCLUDED


extern SPI_HandleTypeDef hspi1;

inline void spi_tx( uint8_t* data, uint16_t len){
    (void)HAL_SPI_Transmit(&hspi1, data, len, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );
}

inline void spi_rx( uint8_t* data, uint16_t len){
    (void)HAL_SPI_Receive(&hspi1, data, len, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );
}


void        W25Qx_Init(void);
void        W25Qx_ReadData(uint8_t* pdata, uint32_t addr, uint32_t len);
void        W25Qx_ReadPage(uint8_t* pdata, uint32_t page);
uint8_t     W25Qx_ReadByte(uint32_t addr);
uint16_t    W25Qx_ReadWord(uint32_t addr);
uint32_t    W25Qx_ReadDWord(uint32_t addr);
void        W25Qx_WritePage(uint8_t* pdata, uint16_t page);
void        W25Qx_WriteByte(uint8_t* pdata, uint16_t addr);
void        W25Qx_WriteData(uint8_t* pdata, uint16_t addr, uint16_t len);

void        W25Qx_ChipErase(void);
void        W25Qx_SectorErase(uint16_t bl);
void        W25Qx_Block32kErase(uint16_t bl);
void        W25Qx_Block64kErase(uint8_t bl);
void        W25Qx_BlockLock(uint16_t bl);
void        W25Qx_BlockUnLock(uint16_t bl);
void        W25Qx_ReadBlockLock(uint16_t bl, uint8_t* pdata);
void        W25Qx_AllBlocksLock(void);
void        W25Qx_AllBlocksUnLock(void);

void        W25Qx_ReadUID(uint8_t* pdata);
void        W25Qx_ReadManDevID(uint8_t* pdata);
void        W25Qx_ReadSFDPRegister(uint8_t* pdata, uint16_t addr, uint16_t len);
void        W25Qx_ResetDevice(void);
void        W25Qx_DisableReset(void);
void        W25Qx_EnableReset(void);
void        W25Qx_WriteDisable(void);
void        W25Qx_WriteEnable(void);



FlagStatus W25Qx_GetStatusWEL_Flag(void);
FlagStatus W25Qx_GetStatusBUSY_Flag(void);


#endif /* WINBOND_SPI_FLASH_H_INCLUDED */
