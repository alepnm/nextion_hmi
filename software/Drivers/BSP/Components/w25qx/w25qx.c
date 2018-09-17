#include <stdlib.h>
#include "nextion.h"
#include "w25qx.h"



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


#define W25Q_STATUS_BPx_OFFSET      2
#define W25Q_STATUS_BPx_MASK        0x07

#define W25Q_STATUS_LBx_OFFSET      11
#define W25Q_STATUS_LBx_MASK        0x07

#define W25Q_STATUS_SRPx_OFFSET     7
#define W25Q_STATUS_SRPx_MASK       0x03

#define W25Q_STATUS_DRVx_OFFSET     21
#define W25Q_STATUS_DRVx_MASK       0x03

#define W25Q_STATUS_TB_OFFSET       5
#define W25Q_STATUS_SEC_OFFSET      6
#define W25Q_STATUS_QE_OFFSET       9
#define W25Q_STATUS_CMP_OFFSET      14
#define W25Q_STATUS_WPS_OFFSET      18
#define W25Q_STATUS_RST_OFFSET      23


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
    CMD_PROGRAM_SECURITY_REGISTERS = 0x42,
    CMD_ERASE_SECURITY_REGISTERS = 0x44,
    CMD_READ_SECURITY_REGISTERS = 0x48,
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


W25Qx_TypeDef W25Qx_Flash;


/* Private functions */
static void W25Qx_ReadUID(void);
static void W25Qx_ReadManDevID(void);

static void W25Qx_ReadStatusRegisters(void);
static void W25Qx_ReadStatusReg1(void);
static void W25Qx_ReadStatusReg2(void);
static void W25Qx_ReadStatusReg3(void);

static void W25Qx_WriteStatusReg1(void);
static void W25Qx_WriteStatusReg2(void);
static void W25Qx_WriteStatusReg3(void);


void W25Qx_Init(void){

    W25Q_CS_HIGH();

    W25Qx_ReadStatusRegisters();

    CLEAR_BIT( W25Qx_Flash.StatusRegister_32, W25Q_STATUS_BP0);
    CLEAR_BIT( W25Qx_Flash.StatusRegister_32, W25Q_STATUS_BP1);
    CLEAR_BIT( W25Qx_Flash.StatusRegister_32, W25Q_STATUS_BP2);

    CLEAR_BIT( W25Qx_Flash.StatusRegister_32, W25Q_STATUS_TB);
    CLEAR_BIT( W25Qx_Flash.StatusRegister_32, W25Q_STATUS_SEC);

    CLEAR_BIT( W25Qx_Flash.StatusRegister_32, W25Q_STATUS_SRP0);
    CLEAR_BIT( W25Qx_Flash.StatusRegister_32, W25Q_STATUS_SRP1);

    SET_BIT( W25Qx_Flash.StatusRegister_32, W25Q_STATUS_QE);

    CLEAR_BIT( W25Qx_Flash.StatusRegister_32, W25Q_STATUS_LB1);   //security lock bit for SecurityRegister1. OTP, 0-unlocked/1-locked permanently
    CLEAR_BIT( W25Qx_Flash.StatusRegister_32, W25Q_STATUS_LB2);   //security lock bit for SecurityRegister2
    CLEAR_BIT( W25Qx_Flash.StatusRegister_32, W25Q_STATUS_LB3);   //security lock bit for SecurityRegister3

    CLEAR_BIT( W25Qx_Flash.StatusRegister_32, W25Q_STATUS_CMP);
    CLEAR_BIT( W25Qx_Flash.StatusRegister_32, W25Q_STATUS_WPS);

    SET_BIT( W25Qx_Flash.StatusRegister_32, W25Q_STATUS_DRV0);
    SET_BIT( W25Qx_Flash.StatusRegister_32, W25Q_STATUS_DRV1);

    CLEAR_BIT( W25Qx_Flash.StatusRegister_32, W25Q_STATUS_RST);

    W25Qx_WriteStatusReg1();
    W25Qx_WriteStatusReg2();
    W25Qx_WriteStatusReg3();

    W25Qx_ReadStatusRegisters();

    W25Qx_ReadSecurityRegisters();

    W25Qx_ReadUID();
    W25Qx_ReadManDevID();

}

/* skaitom UID */
static void W25Qx_ReadUID(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*5);
    cmd[0] = CMD_READ_UID;

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 5 );
    spi_rx( USED_SPI, W25Qx_Flash.UID, 8 );

    W25Q_CS_HIGH();

    free(cmd);
}

/* skaitom gamintojo ir gaminio ID */
static void W25Qx_ReadManDevID(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);
    cmd[0] = CMD_READ_DEVID;

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 4 );
    spi_rx( USED_SPI, W25Qx_Flash.ManDeviceID, 2 );

    W25Q_CS_HIGH();

    free(cmd);
}

/* tikrinti */
void W25Qx_ReadSFDPRegister(uint8_t* pdata, uint16_t addr, uint16_t len){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*5);
    cmd[0] = CMD_READ_SFDP_REGISTER;
    cmd[1] = (uint8_t)( ( addr>>16) & 0x000000FF );
    cmd[2] = (uint8_t)( ( addr>>8)  & 0x000000FF );
    cmd[3] = (uint8_t)( addr & 0x000000FF );
    cmd[4] = 0x00;  //dummy byte

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 5 );
    spi_rx( USED_SPI, pdata, len );

    W25Q_CS_HIGH();

    free(cmd);
}

/* skaitom viena Security registra is banko/adreso */
uint8_t W25Qx_ReadSecurityRegister(uint8_t bank, uint8_t reg){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*5);

    cmd[0] = CMD_READ_SECURITY_REGISTERS;
    cmd[1] = 0x00;
    cmd[2] = (bank<<4) & 0x30;
    cmd[3] = reg;
    cmd[4] = 0x00;  //dummy byte

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 5 );
    spi_rx( USED_SPI, &reg, 1 );

    W25Q_CS_HIGH();

    free(cmd);

    return reg;
}


/* skaitom visa registru rinkini (256 registrai). #1-#3 rinkinys */
void W25Qx_ReadSecurityRegisterBank(uint8_t bank) {

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*5);
    uint8_t* pdata = W25Qx_Flash.SecurityRegister1;

    switch(bank) {
    case 1:
        pdata = W25Qx_Flash.SecurityRegister1;
        break;
    case 2:
        pdata = W25Qx_Flash.SecurityRegister2;
        break;
    case 3:
        pdata = W25Qx_Flash.SecurityRegister3;
        break;
    }

    cmd[0] = CMD_READ_SECURITY_REGISTERS;
    cmd[1] = 0x00;
    cmd[2] = (bank<<4) & 0x30;
    cmd[3] = 0x00;
    cmd[4] = 0x00;  //dummy byte

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 5 );
    spi_rx( USED_SPI, pdata, 256 );

    W25Q_CS_HIGH();

    free(cmd);
}

/* skaitom visus rinkinius #1-#3 */
void W25Qx_ReadSecurityRegisters(void){

    W25Qx_ReadSecurityRegisterBank(1);
    W25Qx_ReadSecurityRegisterBank(2);
    W25Qx_ReadSecurityRegisterBank(3);
}


/* patikrinta */
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


/* tikrinti */
void W25Qx_ReadPage(uint8_t* pdata, uint16_t page){
    W25Qx_ReadData(pdata, page, 256);
}


/* tikrinti */
void W25Qx_ReadData(uint8_t* pdata, uint32_t addr, uint32_t len){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    cmd[0] = CMD_READ_DATA;
    cmd[1] = (uint8_t)( (addr>>16) & 0x000000FF );
    cmd[2] = (uint8_t)( (addr>>8)  & 0x000000FF );
    cmd[3] = (uint8_t)( addr & 0x000000FF );

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 4 );
    spi_rx( USED_SPI, pdata, len );

    W25Q_CS_HIGH();

    free(cmd);
}


/* patikrinta */
void W25Qx_WriteByte(uint8_t data, uint32_t addr){
    W25Qx_WriteData(&data, addr, 1);
}

/* tikrinti */
void W25Qx_WriteWord(uint16_t data, uint32_t addr){

    uint8_t data8[2] ={ (data>>8) & 0x00FF, data & 0x00FF };

    W25Qx_WriteData(data8, addr, 2);
}

/* tikrinti */
void W25Qx_WriteDWord(uint32_t data, uint32_t addr){

    uint8_t data8[4] ={ (data>>24) & 0x000000FF, (data>>16) & 0x000000FF, (data>>8) & 0x000000FF, data & 0x000000FF };

    W25Qx_WriteData(data8, addr, 4);
}


/* tikrinti */
void W25Qx_WritePage(uint8_t* pdata, uint32_t addr){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    cmd[0] = CMD_PAGE_PROGRAM;
    cmd[1] = (uint8_t)( (addr>>16)  & 0x000000FF );
    cmd[2] = (uint8_t)( (addr>>8)   & 0x000000FF );
    cmd[3] = 0x00;

    W25Qx_WriteEnable();

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 4 );
    spi_tx( USED_SPI, pdata, 256 );

    W25Q_CS_HIGH();

    while( W25Qx_GetStatusBUSY_Flag() != RESET );

    free(cmd);
}


/* tikrinti. rasyti galima TIK i isanksto istrinta atminti (0xFF)!!!
kazko neraso nuo paskutinio baito peidze...
*/
void W25Qx_WriteData(uint8_t* pdata, uint32_t addr, uint32_t len){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    while(len>0){

        /* irasom qqq baitu (iki paidzo pabaigos) */
        cmd[0] = CMD_PAGE_PROGRAM;
        cmd[1] = (uint8_t)( (addr>>16)  & 0x000000FF );
        cmd[2] = (uint8_t)( (addr>>8)   & 0x000000FF );
        cmd[3] = (uint8_t)(  addr       & 0x000000FF );

        uint16_t left = 256 - cmd[3];    // kiek baitu galim dar rasyti iki peidzo galo

        if(left > len) left = len;        // jai liko baitu maziau, kiek telpa i peidza, tiek ir irasom. kitaip - via peidza

        W25Qx_WriteEnable();

        W25Q_CS_LOW();

        spi_tx( USED_SPI, cmd, 4 );
        spi_tx( USED_SPI, pdata, left );

        W25Q_CS_HIGH();

        while( W25Qx_GetStatusBUSY_Flag() != RESET );

        len -= left;

        if(len == 0) break;

        addr += left;
        pdata += left;
    }

    free(cmd);
}




/* tikrinti */
void W25Qx_ReadStatusRegisters(void){

    W25Qx_ReadStatusReg1();
    W25Qx_ReadStatusReg2();
    W25Qx_ReadStatusReg3();

    W25Qx_Flash.Bit.BPx = (char)( (W25Qx_Flash.StatusRegister_32>>W25Q_STATUS_BPx_OFFSET) & W25Q_STATUS_BPx_MASK);
    W25Qx_Flash.Bit.TB = (char)( (W25Qx_Flash.StatusRegister_32>>W25Q_STATUS_TB_OFFSET) & 0x00000001);
    W25Qx_Flash.Bit.SEC = (char)( (W25Qx_Flash.StatusRegister_32>>W25Q_STATUS_SEC_OFFSET) & 0x00000001);
    W25Qx_Flash.Bit.SRPx = (char)( (W25Qx_Flash.StatusRegister_32>>W25Q_STATUS_SRPx_OFFSET) & W25Q_STATUS_SRPx_MASK);

    W25Qx_Flash.Bit.QE = (char)( (W25Qx_Flash.StatusRegister_32>>W25Q_STATUS_QE_OFFSET) & 0x00000001);
    W25Qx_Flash.Bit.LBx = (char)( (W25Qx_Flash.StatusRegister_32>>W25Q_STATUS_LBx_OFFSET) & W25Q_STATUS_LBx_MASK);
    W25Qx_Flash.Bit.CMP = (char)( (W25Qx_Flash.StatusRegister_32>>W25Q_STATUS_CMP_OFFSET) & 0x00000001);

    W25Qx_Flash.Bit.WPS = (char)( (W25Qx_Flash.StatusRegister_32>>W25Q_STATUS_WPS_OFFSET) & 0x00000001);
    W25Qx_Flash.Bit.DRV = (char)( (W25Qx_Flash.StatusRegister_32>>W25Q_STATUS_DRVx_OFFSET) & W25Q_STATUS_DRVx_MASK);
    W25Qx_Flash.Bit.RST = (char)( (W25Qx_Flash.StatusRegister_32>>W25Q_STATUS_RST_OFFSET) & 0x00000001);
}


/* tikrinti */
static void W25Qx_ReadStatusReg1(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_READ_STATUS_REG1;

    W25Qx_WriteEnable();

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 1 );
    spi_rx( USED_SPI, &W25Qx_Flash.StatusRegister[0], 1 );

    W25Q_CS_HIGH();

    free(cmd);
}

/* tikrinti */
static void W25Qx_ReadStatusReg2(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_READ_STATUS_REG2;

    W25Qx_WriteEnable();

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 1 );
    spi_rx( USED_SPI, &W25Qx_Flash.StatusRegister[1], 1 );

    W25Q_CS_HIGH();

    free(cmd);
}

/* tikrinti */
static void W25Qx_ReadStatusReg3(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_READ_STATUS_REG3;

    W25Qx_WriteEnable();

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 1 );
    spi_rx( USED_SPI, &W25Qx_Flash.StatusRegister[2], 1 );

    W25Q_CS_HIGH();

    free(cmd);
}





/* tikrinti */
static void W25Qx_WriteStatusReg1(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_WRITE_STATUS_REG1;

    W25Qx_WriteEnable();

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 1 );
    spi_tx( USED_SPI, &W25Qx_Flash.StatusRegister[0], 1 );

    W25Q_CS_HIGH();

    free(cmd);

    while( W25Qx_GetStatusBUSY_Flag() != RESET );
}

/* tikrinti */
static void W25Qx_WriteStatusReg2(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_WRITE_STATUS_REG2;

    W25Qx_WriteEnable();

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 1 );
    spi_tx( USED_SPI, &W25Qx_Flash.StatusRegister[1], 1 );

    W25Q_CS_HIGH();

    free(cmd);

    while( W25Qx_GetStatusBUSY_Flag() != RESET );
}

/* tikrinti */
static void W25Qx_WriteStatusReg3(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_WRITE_STATUS_REG3;

    W25Qx_WriteEnable();

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 1 );
    spi_tx( USED_SPI, &W25Qx_Flash.StatusRegister[2], 1 );

    W25Q_CS_HIGH();

    free(cmd);

    while( W25Qx_GetStatusBUSY_Flag() != RESET );
}

/* tikrinti */
FlagStatus W25Qx_GetStatusWEL_Flag(void){

    W25Qx_ReadStatusRegisters();

    return (FlagStatus)( W25Qx_Flash.StatusRegister_32 & W25Q_STATUS_WEL );
}

/* tikrinti */
FlagStatus W25Qx_GetStatusBUSY_Flag(void){

    W25Qx_ReadStatusRegisters();

    return (FlagStatus)( W25Qx_Flash.StatusRegister_32 & W25Q_STATUS_BUSY );
}

/* tikrinti */
void W25Qx_ResetDevice(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_RESET_DEV;

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 1 );

    W25Q_CS_HIGH();

    free(cmd);

    HAL_Delay(1);   //reikia pauzes 30us
}


/* tikrinti */
void W25Qx_DisableReset(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_ENABLE_RESET;

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 1 );

    W25Q_CS_HIGH();

    *cmd = 0x00;            // disable RESET

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 1 );

    W25Q_CS_HIGH();

    free(cmd);
}


/* tikrinti */
void W25Qx_EnableReset(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_ENABLE_RESET;

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 1 );

    W25Q_CS_HIGH();

    *cmd = CMD_RESET_DEV;   // enable RESET

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 1 );

    W25Q_CS_HIGH();

    free(cmd);
}



/* tikrinti */
void W25Qx_WriteDisable(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_WRITE_DISABLE;

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 1 );

    W25Q_CS_HIGH();

    free(cmd);
}

/* tikrinti */
void W25Qx_WriteEnable(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_WRITE_ENABLE;

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 1 );

    W25Q_CS_HIGH();

    free(cmd);
}


/* patikrinta */
void W25Qx_ChipErase(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_CHIP_ERASE;

    W25Qx_WriteEnable();

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 1 );

    W25Q_CS_HIGH();

    free(cmd);

    while( W25Qx_GetStatusBUSY_Flag() != RESET );
}

/* tikrinti *//* 4096 sectors */
void W25Qx_SectorErase(uint16_t addr){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    cmd[0] = CMD_SECTOR_ERASE;
    cmd[1] = 0x00;
    cmd[2] = (uint8_t)( (addr>>8) & 0x00FF );
    cmd[3] = (uint8_t)( addr & 0x00FF );

    W25Qx_WriteEnable();

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 4 );

    W25Q_CS_HIGH();

    free(cmd);

    while( W25Qx_GetStatusBUSY_Flag() != RESET );
}


/* tikrinti *//* 512 32k blocks  */
void W25Qx_Block32kErase(uint16_t bl){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    cmd[0] = CMD_BLOCK32K_ERASE;
    cmd[1] = 0x00;
    cmd[2] = (uint8_t)( (bl>>8) & 0x00FF );
    cmd[3] = (uint8_t)( bl & 0x00FF );

    W25Qx_WriteEnable();

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 4 );

    W25Q_CS_HIGH();

    free(cmd);

    while( W25Qx_GetStatusBUSY_Flag() != RESET );
}

/* tikrinti *//* 256 64k blocks */
void W25Qx_Block64kErase(uint8_t bl){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    cmd[0] = CMD_BLOCK64K_ERASE;
    cmd[1] = 0x00;
    cmd[2] = 0x00;
    cmd[3] = bl;

    W25Qx_WriteEnable();

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 4 );

    W25Q_CS_HIGH();

    free(cmd);

    while( W25Qx_GetStatusBUSY_Flag() != RESET );
}

/* tikrinti */
void W25Qx_BlockLock(uint16_t bl){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    cmd[0] = CMD_BLOCK_SECTOR_LOCK;
    cmd[1] = 0x00;
    cmd[2] = (uint8_t)( (bl>>8) & 0x00FF );
    cmd[3] = (uint8_t)( bl & 0x00FF );

    W25Qx_WriteEnable();

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 4 );

    W25Q_CS_HIGH();

    free(cmd);
}

/* tikrinti */
void W25Qx_BlockUnLock(uint16_t bl){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    cmd[0] = CMD_BLOCK_SECTOR_UNLOCK;
    cmd[1] = 0x00;
    cmd[2] = (uint8_t)( (bl>>8) & 0x00FF );
    cmd[3] = (uint8_t)( bl & 0x00FF );

    W25Qx_WriteEnable();

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 4 );

    W25Q_CS_HIGH();

    free(cmd);
}


void W25Qx_ReadBlockLock(uint8_t* pdata, uint16_t bl){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    cmd[0] = CMD_BLOCK_SECTOR_LOCK;
    cmd[1] = 0x00;
    cmd[2] = (uint8_t)( (bl>>8) & 0x00FF );
    cmd[3] = (uint8_t)( bl & 0x00FF );

    W25Qx_WriteEnable();

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 4 );
    spi_rx( USED_SPI, pdata, 8 );//dabaigti!!!

    W25Q_CS_HIGH();

    free(cmd);
}


/* tikrinti */
void W25Qx_AllBlocksLock(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_GLOBAL_BL_SEC_LOCK;

    W25Qx_WriteEnable();

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 1 );

    W25Q_CS_HIGH();

    free(cmd);
}


/* tikrinti */
void W25Qx_AllBlocksUnLock(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_GLOBAL_BL_SEC_UNLOCK;

    W25Qx_WriteEnable();

    W25Q_CS_LOW();

    spi_tx( USED_SPI, cmd, 1 );

    W25Q_CS_HIGH();

    free(cmd);
}

