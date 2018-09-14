#ifndef WINBOND_SPI_FLASH_H_INCLUDED
#define WINBOND_SPI_FLASH_H_INCLUDED


extern SPI_HandleTypeDef hspi1;



typedef struct{

    union{
        uint32_t StatusRegister_32;
        uint8_t StatusRegister[4];
    };

    uint8_t SecurityRegister1[256];
    uint8_t SecurityRegister2[256];
    uint8_t SecurityRegister3[256];

    struct{
        char BPx        :3;
        char TB         :1;
        char SEC        :1;
        char SRPx       :2;
        char QE         :1;
        char LBx        :3;
        char CMP        :1;
        char WPS        :1;
        char DRV        :2;
        char RST        :1;
    }Bit;

    uint8_t UID[10];
    uint8_t ManDeviceID[2];
}W25Qx_TypeDef;

extern W25Qx_TypeDef W25Qx_Flash;

void        W25Qx_Init(void);
void        W25Qx_ReadPage(uint8_t* pdata, uint16_t addr);
uint8_t     W25Qx_ReadByte(uint32_t addr);
uint16_t    W25Qx_ReadWord(uint32_t addr);
uint32_t    W25Qx_ReadDWord(uint32_t addr);
void        W25Qx_ReadData(uint8_t* pdata, uint32_t addr, uint32_t len);

void        W25Qx_WriteByte(uint8_t data, uint32_t addr);
void        W25Qx_WriteWord(uint16_t data, uint32_t addr);
void        W25Qx_WriteDWord(uint32_t data, uint32_t addr);
void        W25Qx_WritePage(uint8_t* pdata, uint32_t addr);
void        W25Qx_WriteData(uint8_t* pdata, uint32_t addr, uint32_t len);

void        W25Qx_ChipErase(void);
void        W25Qx_SectorErase(uint16_t addr);
void        W25Qx_Block32kErase(uint16_t bl);
void        W25Qx_Block64kErase(uint8_t bl);
void        W25Qx_BlockLock(uint16_t bl);
void        W25Qx_BlockUnLock(uint16_t bl);
void        W25Qx_ReadBlockLock(uint8_t* pdata, uint16_t bl);
void        W25Qx_AllBlocksLock(void);
void        W25Qx_AllBlocksUnLock(void);

void        W25Qx_ReadSFDPRegister(uint8_t* pdata, uint16_t addr, uint16_t len);
uint8_t     W25Qx_ReadSecurityRegister(uint8_t bank, uint8_t reg);
void        W25Qx_ReadSecurityRegisterBank(uint8_t bank);
void        W25Qx_ReadSecurityRegisters(void);
void        W25Qx_ResetDevice(void);
void        W25Qx_DisableReset(void);
void        W25Qx_EnableReset(void);
void        W25Qx_WriteDisable(void);
void        W25Qx_WriteEnable(void);



FlagStatus W25Qx_GetStatusWEL_Flag(void);
FlagStatus W25Qx_GetStatusBUSY_Flag(void);


#endif /* WINBOND_SPI_FLASH_H_INCLUDED */
