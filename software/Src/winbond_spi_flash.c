
#include <stdlib.h>
#include "stm32f0xx_hal.h"
#include "winbond_spi_flash.h"


#define  W25Q_CS_LOW    HAL_GPIO_WritePin(W25QCS_GPIO_Port, W25QCS_Pin, GPIO_PIN_RESET)
#define  W25Q_CS_HIGH   HAL_GPIO_WritePin(W25QCS_GPIO_Port, W25QCS_Pin, GPIO_PIN_SET)


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
    CMD_PAGE_PROGRAM            = 0x02,
    CMD_READ_DATA               = 0x03,
    CMD_WRITE_DISABLE           = 0x04,
    CMD_READ_STATUS_REG1        = 0x05,
    CMD_WRITE_ENABLE            = 0x06,
    CMD_WRITE_STATUS_REG3       = 0x11,
    CMD_READ_STATUS_REG3        = 0x15,
    CMD_SECTOR_ERASE            = 0x20,
    CMD_WRITE_STATUS_REG2       = 0x31,
    CMD_READ_STATUS_REG2        = 0x35,
    CMD_BLOCK_SECTOR_LOCK       = 0x36,
    CMD_BLOCK_SECTOR_UNLOCK     = 0x39,
    CMD_READ_BLOCK_SECTOR_LOCK  = 0x3D,
    CMD_READ_UID                = 0x4B,
    CMD_BLOCK32K_ERASE          = 0x52,
    CMD_READ_SFDP_REGISTER      = 0x5A,
    CMD_ENABLE_RESET            = 0x66,
    CMD_GLOBAL_BL_SEC_LOCK      = 0x7E,
    CMD_READ_DEVID              = 0x90,
    CMD_READ_DEVID_DUALIO       = 0x92,
    CMD_READ_DEVID_QUADIO       = 0x94,
    CMD_GLOBAL_BL_SEC_UNLOCK    = 0x98,
    CMD_RESET_DEV               = 0x99,
    CMD_READ_JEDECID            = 0x9F,
    CMD_CHIP_ERASE              = 0xC7,
    CMD_BLOCK64K_ERASE          = 0xD8
}W25Qx_Commands_TypeDef;


//extern SPI_HandleTypeDef hspi1;

extern inline void spi_tx( uint8_t* data, uint16_t len);
extern inline void spi_rx( uint8_t* data, uint16_t len);


static union{
    uint32_t SR_32BIT;
    struct{
        uint8_t reserv;
        uint8_t SR1;
        uint8_t SR2;
        uint8_t SR3;
    };
}StatusRegister;


static void W25Qx_ReadStatusRegisters(void);

static void W25Qx_WriteStatusReg1(void);
static void W25Qx_WriteStatusReg2(void);
static void W25Qx_WriteStatusReg3(void);


void W25Qx_Init(void){
    HAL_GPIO_WritePin(W25QCS_GPIO_Port, W25QCS_Pin, GPIO_PIN_SET);
}

/* tikrinti */
void W25Qx_ReadUID(uint8_t* pdata){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*5);
    cmd[0] = CMD_READ_UID;

    W25Q_CS_LOW;

    spi_tx( cmd, 5 );
    spi_rx( pdata, 8 );

    W25Q_CS_HIGH;

    free(cmd);
}

/* tikrinti */
void W25Qx_ReadManDevID(uint8_t* pdata){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);
    cmd[0] = CMD_READ_DEVID;

    W25Q_CS_LOW;

    spi_tx( cmd, 4 );
    spi_rx( pdata, 2 );

    W25Q_CS_HIGH;

    free(cmd);
}

/* tikrinti */
void W25Qx_ReadSFDPRegister(uint8_t* pdata, uint16_t addr, uint16_t len){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*5);
    cmd[0] = CMD_READ_SFDP_REGISTER;
    cmd[1] = (uint8_t)( addr & 0x000000FF );
    cmd[2] = (uint8_t)( ( addr & 0x0000FF00 )>>8 );
    cmd[3] = (uint8_t)( ( addr & 0x00FF0000 )>>16 );
    cmd[4] = 0x00;  //dummy byte

    W25Q_CS_LOW;

    spi_tx( cmd, 5 );
    spi_rx( pdata, len );

    W25Q_CS_HIGH;

    free(cmd);
}




/* tikrinti */
void W25Qx_ReadData(uint8_t* pdata, uint32_t addr, uint32_t len){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    cmd[0] = CMD_READ_DATA;
    cmd[1] = (uint8_t)( addr & 0x000000FF );
    cmd[2] = (uint8_t)( ( addr & 0x0000FF00 )>>8 );
    cmd[3] = (uint8_t)( ( addr & 0x00FF0000 )>>16 );

    W25Q_CS_LOW;

    spi_tx( cmd, 4 );
    spi_rx( pdata, len );

    W25Q_CS_HIGH;

    free(cmd);
}


void W25Qx_ReadPage(uint8_t* pdata, uint32_t page){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    cmd[0] = CMD_READ_DATA;
    cmd[1] = (uint8_t)( page & 0x00FF );
    cmd[2] = (uint8_t)( ( page & 0xFF00 )>>8 );
    cmd[3] = 0x00;

    W25Q_CS_LOW;

    spi_tx( cmd, 4 );
    spi_rx( pdata, 256 );

    W25Q_CS_HIGH;

    free(cmd);
}



/* tikrinti */
uint8_t W25Qx_ReadByte(uint32_t addr){

    uint8_t data = 0x00;

    W25Qx_ReadData(&data, addr, 1);

    return data;
}

/* tikrinti */
uint16_t W25Qx_ReadWord(uint32_t addr){

    uint8_t data[2] = {0x00, 0x00};

    W25Qx_ReadData(data, addr, 2);

    return ( data[0]<<8 | data[1] );
}

/* tikrinti */
uint32_t W25Qx_ReadDWord(uint32_t addr){

    uint8_t data[4] = {0x00, 0x00, 0x00, 0x00};

    W25Qx_ReadData(data, addr, 4);

    return ( data[0]<<24 | data[1]<<16 | data[2]<<8 | data[3] );
}


/* tikrinti *//* 65536 pages */
void W25Qx_WritePage(uint8_t* pdata, uint16_t page){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    cmd[0] = CMD_PAGE_PROGRAM;
    cmd[1] = (uint8_t)( page & 0x00FF );
    cmd[2] = (uint8_t)( ( page & 0xFF00 )>>8 );
    cmd[3] = 0x00;

    W25Qx_WriteEnable();

    W25Q_CS_LOW;

    spi_tx( cmd, 1 );
    spi_tx( pdata, 256 );   // siunciam duomenys

    W25Q_CS_HIGH;

    free(cmd);
}



void W25Qx_WriteByte(uint8_t* pdata, uint16_t addr){
/*
Logika:
1. nuskaitom vias peidza i buferi
2. istrinam ji
3. pakeiciam buferyje reikiama baita
4. iresom visa buferi atgal
*/

    uint8_t* buf = (uint8_t*)malloc(sizeof(uint8_t)*256);

    /* pirma - apskaiciuojam peidza */
    page = 1;

    W25Qx_ReadPage(buf, page);

    /* keiciam reikiama baita buferyje */
    ///............

    /* ar page galim istrinti? */


}


void W25Qx_WriteData(uint8_t* pdata, uint16_t addr, uint16_t len){



}




/* tikrinti */
static void W25Qx_ReadStatusRegisters(void){

    W25Qx_WriteStatusReg1();
    W25Qx_WriteStatusReg2();
    W25Qx_WriteStatusReg3();
}

/* tikrinti */
static void W25Qx_WriteStatusReg1(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_WRITE_STATUS_REG1;

    W25Qx_WriteEnable();

    W25Q_CS_LOW;

    spi_tx( cmd, 1 );
    spi_rx( &StatusRegister.SR1, 1 );

    W25Q_CS_HIGH;

    free(cmd);
}

/* tikrinti */
static void W25Qx_WriteStatusReg2(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_WRITE_STATUS_REG2;

    W25Qx_WriteEnable();

    W25Q_CS_LOW;

    spi_tx( cmd, 1 );
    spi_rx( &StatusRegister.SR2, 1 );

    W25Q_CS_HIGH;

    free(cmd);
}

/* tikrinti */
static void W25Qx_WriteStatusReg3(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_WRITE_STATUS_REG3;

    W25Qx_WriteEnable();

    W25Q_CS_LOW;

    spi_tx( cmd, 1 );
    spi_rx( &StatusRegister.SR3, 1 );

    W25Q_CS_HIGH;

    free(cmd);
}

/* tikrinti */
FlagStatus W25Qx_GetStatusWEL_Flag(void){

    W25Qx_ReadStatusRegisters();

    return (FlagStatus)( StatusRegister.SR_32BIT & W25Q_STATUS_WEL );
}

/* tikrinti */
FlagStatus W25Qx_GetStatusBUSY_Flag(void){

    W25Qx_ReadStatusRegisters();

    return (FlagStatus)( StatusRegister.SR_32BIT & W25Q_STATUS_BUSY );
}

/* tikrinti */
void W25Qx_ResetDevice(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_RESET_DEV;

    W25Q_CS_LOW;

    spi_tx( cmd, 1 );

    W25Q_CS_HIGH;

    free(cmd);

    HAL_Delay(1);   //reikia pauzes 30us
}


/* tikrinti */
void W25Qx_DisableReset(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_ENABLE_RESET;

    W25Q_CS_LOW;

    spi_tx( cmd, 1 );

    W25Q_CS_HIGH;

    *cmd = 0x00;            // disable RESET

    W25Q_CS_LOW;

    spi_tx( cmd, 1 );

    W25Q_CS_HIGH;

    free(cmd);
}


/* tikrinti */
void W25Qx_EnableReset(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_ENABLE_RESET;

    W25Q_CS_LOW;

    spi_tx( cmd, 1 );

    W25Q_CS_HIGH;

    *cmd = CMD_RESET_DEV;   // enable RESET

    W25Q_CS_LOW;

    spi_tx( cmd, 1 );

    W25Q_CS_HIGH;

    free(cmd);
}



/* tikrinti */
void W25Qx_WriteDisable(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_WRITE_DISABLE;

    W25Q_CS_LOW;

    spi_tx( cmd, 1 );

    W25Q_CS_HIGH;

    free(cmd);
}

/* tikrinti */
void W25Qx_WriteEnable(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_WRITE_ENABLE;

    W25Q_CS_LOW;

    spi_tx( cmd, 1 );

    W25Q_CS_HIGH;

    free(cmd);
}


/* tikrinti */
void W25Qx_ChipErase(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_CHIP_ERASE;

    W25Qx_WriteEnable();

    W25Q_CS_LOW;

    spi_tx( cmd, 1 );

    W25Q_CS_HIGH;

    free(cmd);

    while( W25Qx_GetStatusBUSY_Flag() != RESET );
}

/* tikrinti *//* 4096 sectors */
void W25Qx_SectorErase(uint16_t sec){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    cmd[0] = CMD_SECTOR_ERASE;
    cmd[1] = (uint8_t)( sec & 0x00FF );
    cmd[2] = (uint8_t)( ( sec & 0xFF00 )>>8 );
    cmd[3] = 0;

    W25Qx_WriteEnable();

    W25Q_CS_LOW;

    spi_tx( cmd, 4 );

    W25Q_CS_HIGH;

    free(cmd);

    while( W25Qx_GetStatusBUSY_Flag() != RESET );
}


/* tikrinti *//* 512 32k blocks  */
void W25Qx_Block32kErase(uint16_t bl){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    cmd[0] = CMD_BLOCK32K_ERASE;
    cmd[1] = (uint8_t)( bl & 0x000FF );
    cmd[2] = (uint8_t)( ( bl & 0xFF00 )>>8 );
    cmd[3] = 0;

    W25Qx_WriteEnable();

    W25Q_CS_LOW;

    spi_tx( cmd, 4 );

    W25Q_CS_HIGH;

    free(cmd);

    while( W25Qx_GetStatusBUSY_Flag() != RESET );
}

/* tikrinti *//* 256 64k blocks */
void W25Qx_Block64kErase(uint8_t bl){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    cmd[0] = CMD_BLOCK64K_ERASE;
    cmd[1] = bl;
    cmd[2] = 0;
    cmd[3] = 0;

    W25Qx_WriteEnable();

    W25Q_CS_LOW;

    spi_tx( cmd, 4 );

    W25Q_CS_HIGH;

    free(cmd);

    while( W25Qx_GetStatusBUSY_Flag() != RESET );
}

/* tikrinti */
void W25Qx_BlockLock(uint16_t bl){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    cmd[0] = CMD_BLOCK_SECTOR_LOCK;
    cmd[1] = (uint8_t)( bl & 0x000FF );
    cmd[2] = (uint8_t)( ( bl & 0xFF00 )>>8 );
    cmd[3] = 0;

    W25Qx_WriteEnable();

    W25Q_CS_LOW;

    spi_tx( cmd, 4 );

    W25Q_CS_HIGH;

    free(cmd);
}

/* tikrinti */
void W25Qx_BlockUnLock(uint16_t bl){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    cmd[0] = CMD_BLOCK_SECTOR_UNLOCK;
    cmd[1] = (uint8_t)( bl & 0x000FF );
    cmd[2] = (uint8_t)( ( bl & 0xFF00 )>>8 );
    cmd[3] = 0;

    W25Qx_WriteEnable();

    W25Q_CS_LOW;

    spi_tx( cmd, 4 );

    W25Q_CS_HIGH;

    free(cmd);
}


void W25Qx_ReadBlockLock(uint16_t bl, uint8_t* pdata){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    cmd[0] = CMD_BLOCK_SECTOR_LOCK;
    cmd[1] = (uint8_t)( bl & 0x000FF );
    cmd[2] = (uint8_t)( ( bl & 0xFF00 )>>8 );
    cmd[3] = 0;

    W25Qx_WriteEnable();

    W25Q_CS_LOW;

    spi_tx( cmd, 4 );
    spi_rx( pdata, 8 );//dabaigti!!!

    W25Q_CS_HIGH;

    free(cmd);
}


/* tikrinti */
void W25Qx_AllBlocksLock(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_GLOBAL_BL_SEC_LOCK;

    W25Qx_WriteEnable();

    W25Q_CS_LOW;

    spi_tx( cmd, 1 );

    W25Q_CS_HIGH;

    free(cmd);
}


/* tikrinti */
void W25Qx_AllBlocksUnLock(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_GLOBAL_BL_SEC_UNLOCK;

    W25Qx_WriteEnable();

    W25Q_CS_LOW;

    spi_tx( cmd, 1 );

    W25Q_CS_HIGH;

    free(cmd);
}
