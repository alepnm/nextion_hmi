
//#include "main.h"
#include "lcd_commands.h"


void SoftReset(void){

    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_RESET);


    /* COMMAND */
    HAL_GPIO_WritePin(DB0_GPIO_Port, DB0_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DB1_GPIO_Port, DB1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DB2_GPIO_Port, DB2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DB3_GPIO_Port, DB3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DB4_GPIO_Port, DB4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DB5_GPIO_Port, DB5_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DB6_GPIO_Port, DB6_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DB7_GPIO_Port, DB7_Pin, GPIO_PIN_RESET);

    /* SHOT */
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET);
}
