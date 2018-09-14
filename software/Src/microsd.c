

#include "stm32f0xx_hal.h"
#include "microsd.h"



#define SD_CMD_GO_IDLE_STATE        0   //Программная перезагрузка
#define SEND_IF_COND                8   //Для SDC V2 - проверка диапазона напряжений
#define READ_SINGLE_BLOCK           17  //Чтение указанного блока данных
#define WRITE_SINGLE_BLOCK          24  //Запись указанного блока данных
#define SD_SEND_OP_COND             41  //Начало процесса инициализации
#define APP_CMD                     55  //Главная команда из ACMD  команд
#define READ_OCR                    58  //Чтение регистра OCR


#define SD_CS_LOW           HAL_GPIO_WritePin(SDCS_GPIO_Port, SDCS_Pin, GPIO_PIN_RESET);
#define SD_CS_HIGH    	    HAL_GPIO_WritePin(SDCS_GPIO_Port, SDCS_Pin, GPIO_PIN_SET);


uint8_t  SDHC;


extern uint8_t spi_tx( uint8_t spi, uint8_t* data, uint16_t len);
extern uint8_t spi_rx( uint8_t spi, uint8_t* data, uint16_t len);


static uint8_t SD_sendCommand(uint8_t cmd, uint32_t arg);
static uint8_t spi_send_byte (uint8_t data);
static uint8_t spi_read_byte (void);
static uint8_t spi_send_data (uint8_t* data, uint16_t len);
static uint8_t spi_read_data (uint8_t* data, uint16_t len);

/*  */
uint8_t SD_init(void) {

    uint8_t   i;
    uint8_t   response;
    uint8_t   SD_version = 2;
    uint16_t  retry = 0 ;

    SD_CS_HIGH;

    for(i=0; i<10; i++) spi_send_byte(0xFF);



    //SD_CS_LOW;

    while(SD_sendCommand(SD_CMD_GO_IDLE_STATE, 0) != 0x01)
        if(retry++ >0x20)  return 1;

    SD_CS_HIGH;

    spi_send_byte (0xff);
    spi_send_byte (0xff);

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
        while(SD_sendCommand(READ_OCR, 0) != 0x00)
            if(retry++>0xfe)  break;
    }

    return 0;
}



/*  */
static uint8_t SD_sendCommand(uint8_t cmd, uint32_t arg) {

    uint8_t response, wait = 0, tmp;

    if(SDHC == 0)
        if(cmd == READ_SINGLE_BLOCK || cmd == WRITE_SINGLE_BLOCK )  {
            arg = arg << 9;
        }

    SD_CS_LOW;

    spi_send_byte(cmd | 0x40);
    spi_send_byte(arg>>24);
    spi_send_byte(arg>>16);
    spi_send_byte(arg>>8);
    spi_send_byte(arg);

    if(cmd == SEND_IF_COND) spi_send_byte(0x87);
    else                    spi_send_byte(0x95);

    while((response = spi_read_byte()) == 0xff)
        if(wait++ > 0xfe) break;

    if(response == 0x00 && cmd == 58) {
        tmp = spi_read_byte();
        if(tmp & 0x40) SDHC = 1;
        else           SDHC = 0;

        spi_read_byte();
        spi_read_byte();
        spi_read_byte();
    }

    spi_read_byte();

    SD_CS_HIGH;

    return response;
}


/*  */
uint8_t SD_ReadSector(uint32_t block, uint8_t *buff) {

    uint16_t i = 0;

    if( SD_sendCommand(READ_SINGLE_BLOCK, block) ) return 1;

    SD_CS_LOW;

    while(spi_read_byte() != 0xfe)
        if(i++ > 0xfffe) {
            SD_CS_HIGH;
            return 1;
        }

    for(i=0; i<512; i++) *buff++ = spi_read_byte();

    spi_read_byte();
    spi_read_byte();
    spi_read_byte();

    SD_CS_HIGH;

    return 0;
}


/*  */
uint8_t SD_WriteSector(uint32_t block,uint8_t *buff) {

    uint8_t     response;
    uint16_t    i, wait = 0;

    if( SD_sendCommand(WRITE_SINGLE_BLOCK, block) ) return 1;

    SD_CS_LOW;

    spi_send_byte(0xfe);

    for(i=0; i<512; i++) spi_send_byte(*buff++);

    spi_send_byte(0xff);
    spi_send_byte(0xff);

    response = spi_read_byte();

    if( (response & 0x1f) != 0x05) {
        SD_CS_HIGH;
        return 1;
    }

    while(!spi_read_byte())
        if(wait++ > 0xfffe) {
            SD_CS_HIGH;
            return 1;
        }

    SD_CS_HIGH;

    spi_send_byte(0xff);

    SD_CS_LOW;

    while(!spi_read_byte())
        if(wait++ > 0xfffe) {
            SD_CS_HIGH;
            return 1;
        }

    SD_CS_HIGH;

    return 0;
}


/*  */
static uint8_t spi_send_byte (uint8_t data) {

    (void)spi_tx( 1, &data, 1);

    return 0;
}


/*  */
static uint8_t spi_read_byte (void) {

    uint8_t data;

    (void)spi_rx( 1, &data, 1);

    return data;
}


/*  */
static uint8_t spi_send_data (uint8_t* data, uint16_t len) {

    (void)spi_tx( 1, data, len);

    return 0;
}


/*  */
static uint8_t spi_read_data (uint8_t* data, uint16_t len) {

    (void)spi_rx( 1, data, len);

    return 0;
}

