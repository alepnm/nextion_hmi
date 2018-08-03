
#include <stdlib.h>
#include "stm32f0xx_hal.h"
#include "winbond_spi_flash.h"


#define  W25Q_CS_LOW    HAL_GPIO_WritePin(W25QCS_GPIO_Port, W25QCS_Pin, GPIO_PIN_RESET)
#define  W25Q_CS_HIGH   HAL_GPIO_WritePin(W25QCS_GPIO_Port, W25QCS_Pin, GPIO_PIN_SET)


extern SPI_HandleTypeDef hspi1;


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

void W25Qx_ReadUID(uint8_t* pdata){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*5);
    cmd[0] = CMD_READ_UID;

    W25Q_CS_LOW;

    (void)HAL_SPI_Transmit(&hspi1, cmd, 5, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    (void)HAL_SPI_Receive(&hspi1, pdata, 8, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    W25Q_CS_HIGH;

    free(cmd);
}
void W25Qx_ReadManDevID(uint8_t* pdata){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);
    cmd[0] = CMD_READ_DEVID;

    W25Q_CS_LOW;

    (void)HAL_SPI_Transmit(&hspi1, cmd, 4, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    (void)HAL_SPI_Receive(&hspi1, pdata, 2, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    W25Q_CS_HIGH;

    free(cmd);
}
void W25Qx_ReadData(uint8_t* pdata, uint32_t addr, uint32_t len){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*4);

    cmd[0] = CMD_READ_DATA;
    cmd[1] = (uint8_t)( addr & 0x000000FF );
    cmd[2] = (uint8_t)( ( addr & 0x0000FF00 )>>8 );
    cmd[3] = (uint8_t)( ( addr & 0x00FF0000 )>>16 );


    W25Q_CS_LOW;

    (void)HAL_SPI_Transmit(&hspi1, cmd, 4, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    (void)HAL_SPI_Receive(&hspi1, pdata, len, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    W25Q_CS_HIGH;

    free(cmd);
}


static void W25Qx_ReadStatusRegisters(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_READ_STATUS_REG1;

    W25Q_CS_LOW;

    (void)HAL_SPI_Transmit(&hspi1, cmd, 1, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    (void)HAL_SPI_Receive(&hspi1, &StatusRegister.SR1, 1, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    W25Q_CS_HIGH;

    *cmd = CMD_READ_STATUS_REG2;

    W25Q_CS_LOW;

    (void)HAL_SPI_Transmit(&hspi1, cmd, 1, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    (void)HAL_SPI_Receive(&hspi1, &StatusRegister.SR2, 1, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    W25Q_CS_HIGH;

    *cmd = CMD_READ_STATUS_REG3;

    W25Q_CS_LOW;

    (void)HAL_SPI_Transmit(&hspi1, cmd, 1, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    (void)HAL_SPI_Receive(&hspi1, &StatusRegister.SR3, 1, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    W25Q_CS_HIGH;

    free(cmd);
}

static void W25Qx_WriteStatusReg1(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_WRITE_STATUS_REG1;

    W25Qx_WriteEnable();

    W25Q_CS_LOW;

    (void)HAL_SPI_Transmit(&hspi1, cmd, 1, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    (void)HAL_SPI_Transmit(&hspi1, &StatusRegister.SR1, 1, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    W25Q_CS_HIGH;

    free(cmd);

    while( W25Qx_GetStatusBUSY_Flag() != RESET );
}
static void W25Qx_WriteStatusReg2(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_WRITE_STATUS_REG2;

    W25Qx_WriteEnable();

    W25Q_CS_LOW;

    (void)HAL_SPI_Transmit(&hspi1, cmd, 1, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    (void)HAL_SPI_Transmit(&hspi1, &StatusRegister.SR2, 1, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    W25Q_CS_HIGH;

    free(cmd);

    while( W25Qx_GetStatusBUSY_Flag() != RESET );
}
static void W25Qx_WriteStatusReg3(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_WRITE_STATUS_REG3;

    W25Qx_WriteEnable();

    W25Q_CS_LOW;

    (void)HAL_SPI_Transmit(&hspi1, cmd, 1, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    (void)HAL_SPI_Transmit(&hspi1, &StatusRegister.SR3, 1, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    W25Q_CS_HIGH;

    free(cmd);

    while( W25Qx_GetStatusBUSY_Flag() != RESET );
}



FlagStatus W25Qx_GetStatusWEL_Flag(void){

    W25Qx_ReadStatusRegisters();

    return (FlagStatus)( StatusRegister.SR_32BIT & W25Q_STATUS_WEL );
}
FlagStatus W25Qx_GetStatusBUSY_Flag(void){

    W25Qx_ReadStatusRegisters();

    return (FlagStatus)( StatusRegister.SR_32BIT & W25Q_STATUS_BUSY );
}




void W25Qx_ResetDevice(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_RESET_DEV;

    W25Q_CS_LOW;

    (void)HAL_SPI_Transmit(&hspi1, cmd, 1, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    W25Q_CS_HIGH;

    free(cmd);

    HAL_Delay(1);   //reikia pauzes 30us
}


void W25Qx_WriteDisable(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_WRITE_DISABLE;

    W25Q_CS_LOW;

    (void)HAL_SPI_Transmit(&hspi1, cmd, 1, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    W25Q_CS_HIGH;

    free(cmd);
}


void W25Qx_WriteEnable(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_WRITE_ENABLE;

    W25Q_CS_LOW;

    (void)HAL_SPI_Transmit(&hspi1, cmd, 1, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    W25Q_CS_HIGH;

    free(cmd);
}



void W25Qx_ChipErase(void){

    uint8_t* cmd = (uint8_t*)malloc(sizeof(uint8_t)*1);

    *cmd = CMD_CHIP_ERASE;

    W25Qx_WriteEnable();

    W25Q_CS_LOW;

    (void)HAL_SPI_Transmit(&hspi1, cmd, 1, 10);
    while( hspi1.State == HAL_SPI_STATE_BUSY );

    W25Q_CS_HIGH;

    free(cmd);

    while( W25Qx_GetStatusBUSY_Flag() != RESET );
}
