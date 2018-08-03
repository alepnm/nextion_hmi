#ifndef WINBOND_SPI_FLASH_H_INCLUDED
#define WINBOND_SPI_FLASH_H_INCLUDED



typedef enum{
    W25Q_STATUS_BUSY                 = 0x000001, //RO
    W25Q_STATUS_WEL                  = 0x000002, //RO
    W25Q_STATUS_BP0                  = 0x000004,
    W25Q_STATUS_BP1                  = 0x000008,
    W25Q_STATUS_BP2                  = 0x000010,
    W25Q_STATUS_TB                   = 0x000020,
    W25Q_STATUS_SEC                  = 0x000040,
    W25Q_STATUS_SRP0                 = 0x000080,
    W25Q_STATUS_SRP1                 = 0x000100,
    W25Q_STATUS_QE                   = 0x000200,
    //RESERVED                  = 0x000400, //RO
    W25Q_STATUS_LB1                  = 0x000800,
    W25Q_STATUS_LB2                  = 0x001000,
    W25Q_STATUS_LB3                  = 0x002000,
    W25Q_STATUS_CMP                  = 0x004000,
    W25Q_STATUS_SUS                  = 0x008000,  //RO
    //RESERVED                  = 0x010000, //RO
    //RESERVED                  = 0x020000, //RO
    W25Q_STATUS_WPS                  = 0x040000,
    //RESERVED                  = 0x080000, //RO
    //RESERVED                  = 0x100000, //RO
    W25Q_STATUS_DRV0                 = 0x200000,
    W25Q_STATUS_DRV1                 = 0x400000,
    W25Q_STATUS_RST                  = 0x800000
}W25Qx_StatusReg_TypeDef;


typedef enum {
    CMD_WRITE_STATUS_REG1       = 0x01,
    CMD_READ_DATA               = 0x03,
    CMD_WRITE_DISABLE           = 0x04,
    CMD_READ_STATUS_REG1        = 0x05,
    CMD_WRITE_ENABLE            = 0x06,
    CMD_WRITE_STATUS_REG3       = 0x11,
    CMD_READ_STATUS_REG3        = 0x15,
    CMD_WRITE_STATUS_REG2       = 0x31,
    CMD_READ_STATUS_REG2        = 0x35,
    CMD_READ_UID                = 0x4B,
    CMD_READ_DEVID              = 0x90,
    CMD_READ_DEVID_DUALIO       = 0x92,
    CMD_READ_DEVID_QUADIO       = 0x94,
    CMD_RESET_DEV               = 0x99,
    CMD_READ_JEDECID            = 0x9F,
    CMD_CHIP_ERASE              = 0xC7
}W25Qx_Commands_TypeDef;


void W25Qx_Init(void);
void W25Qx_ReadData(uint8_t* pdata, uint32_t addr, uint32_t len);

void W25Qx_ReadUID(uint8_t* pdata);
void W25Qx_ReadManDevID(uint8_t* pdata);
void W25Qx_ResetDevice(void);
void W25Qx_WriteDisable(void);
void W25Qx_WriteEnable(void);

FlagStatus W25Qx_GetStatusWEL_Flag(void);
FlagStatus W25Qx_GetStatusBUSY_Flag(void);


#endif /* WINBOND_SPI_FLASH_H_INCLUDED */
