

#include "stm32f0xx_hal.h"
#include "microsd.h"



#define GO_IDLE_STATE       0   //Программная перезагрузка
#define SEND_IF_COND        8   //Для SDC V2 - проверка диапазона напряжений
#define READ_SINGLE_BLOCK   17  //Чтение указанного блока данных
#define WRITE_SINGLE_BLOCK  24  //Запись указанного блока данных
#define SD_SEND_OP_COND     41  //Начало процесса инициализации
#define APP_CMD             55  //Главная команда из ACMD  команд
#define READ_OCR            58  //Чтение регистра OCR


#define CS_LOW              HAL_GPIO_WritePin(SDCS_GPIO_Port, SDCS_Pin, GPIO_PIN_RESET);
#define CS_HIGH    	        HAL_GPIO_WritePin(SDCS_GPIO_Port, SDCS_Pin, GPIO_PIN_SET);


extern SPI_HandleTypeDef hspi1;

uint8_t  SDHC;





static uint8_t SD_sendCommand(uint8_t cmd, uint32_t arg);
static uint8_t spi_send (uint8_t data);
static uint8_t spi_read (void);


/*  */
uint8_t SD_init(void) {

    uint8_t   i;
    uint8_t   response;
    uint8_t   SD_version = 2;
    uint16_t  retry = 0 ;

    //spi_init();

    for(i=0; i<10; i++) spi_send(0xff);

    CS_LOW;

    while(SD_sendCommand(GO_IDLE_STATE, 0) != 0x01)
        if(retry++ >0x20)  return 1;

    CS_HIGH;

    spi_send (0xff);
    spi_send (0xff);

    retry = 0;

    while(SD_sendCommand(SEND_IF_COND, 0x000001AA) != 0x01) {
        if(retry++ >0xfe) {
            SD_version = 1;
            break;
        }
    }

    retry = 0;

    do {
        response = SD_sendCommand(APP_CMD, 0);
        response = SD_sendCommand(SD_SEND_OP_COND, 0x40000000);
        retry++;
        if(retry > 0xffe) return 1;
    } while(response != 0x00);


    retry = 0;
    SDHC = 0;
    if (SD_version == 2) {
        while(SD_sendCommand(READ_OCR,0) != 0x00)
            if(retry++>0xfe)  break;
    }

    return 0;
}



/*  */
static uint8_t SD_sendCommand(uint8_t cmd, uint32_t arg) {

    uint8_t response, wait=0, tmp;

    if(SDHC == 0)
        if(cmd == READ_SINGLE_BLOCK || cmd == WRITE_SINGLE_BLOCK )  {
            arg = arg << 9;
        }

    CS_LOW;

    spi_send(cmd | 0x40);
    spi_send(arg>>24);
    spi_send(arg>>16);
    spi_send(arg>>8);
    spi_send(arg);

    if(cmd == SEND_IF_COND) spi_send(0x87);
    else                    spi_send(0x95);

    while((response = spi_read()) == 0xff)
        if(wait++ > 0xfe) break;

    if(response == 0x00 && cmd == 58) {
        tmp = spi_read();
        if(tmp & 0x40) SDHC = 1;
        else           SDHC = 0;

        spi_read();
        spi_read();
        spi_read();
    }

    spi_read();

    CS_HIGH;

    return response;
}


/*  */
uint8_t SD_ReadSector(uint32_t block, uint8_t *buff) {

    uint16_t i=0;

    if( SD_sendCommand(READ_SINGLE_BLOCK, block) ) return 1;

    CS_LOW;

    while(spi_read() != 0xfe)
        if(i++ > 0xfffe) {
            CS_HIGH;
            return 1;
        }

    for(i=0; i<512; i++) *buff++ = spi_read();

    spi_read();
    spi_read();
    spi_read();

    CS_HIGH;

    return 0;
}

/*  */
uint8_t SD_WriteSector(uint32_t block,uint8_t *buff) {

    uint8_t     response;
    uint16_t    i, wait=0;

    if( SD_sendCommand(WRITE_SINGLE_BLOCK, block) ) return 1;

    CS_LOW;

    spi_send(0xfe);

    for(i=0; i<512; i++) spi_send(*buff++);

    spi_send(0xff);
    spi_send(0xff);

    response = spi_read();

    if( (response & 0x1f) != 0x05) {
        CS_HIGH;
        return 1;
    }

    while(!spi_read())
        if(wait++ > 0xfffe) {
            CS_HIGH;
            return 1;
        }

    CS_HIGH;

    spi_send(0xff);

    CS_LOW;

    while(!spi_read())
        if(wait++ > 0xfffe) {
            CS_HIGH;
            return 1;
        }

    CS_HIGH;

    return 0;
}


//*********************************************************************************************
//function  обмен данными по SPI1                                                            //
//argument  передаваемый байт                                                                //
//return    принятый байт                                                                    //
//*********************************************************************************************
static uint8_t spi_send (uint8_t data) {

        HAL_SPI_Transmit(&hspi1, &data, 1, 10);

        return 0;
}

//*********************************************************************************************
//function  прием байт по SPI1                                                               //
//argument  none                                                                             //
//return    принятый байт                                                                    //
//*********************************************************************************************
static uint8_t spi_read (void) {

        uint8_t data;

        HAL_SPI_Receive(&hspi1, &data, 1, 10);

        return data;
}
