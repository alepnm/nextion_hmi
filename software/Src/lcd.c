#include "stm32f0xx_hal.h"
#include "lcd.h"
#include "lcd_commands.h"


#define PULSE_WR_LOW()      HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_RESET);\
                            HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET);



extern TIM_HandleTypeDef htim1;

DispHandle_TypeDef LCD;



static void LCD_Write_COM_DATA(unsigned char commmand, int data);
static void LCD_Write_COM(unsigned char vl);
static void LCD_Write_DATA(unsigned char vh, unsigned char vl);
static void LCD_Write_DATA_1(unsigned char vl);
static void LCD_Write_Bus(unsigned char vh, unsigned char vl);

static void LCD_SetPixel(unsigned int color);

static void _fast_fill_16(unsigned int ch, unsigned int cl, unsigned long pix);



/*  */
void LCD_Init(void)
{
    HAL_GPIO_WritePin(SD_RST_GPIO_Port, SD_RST_Pin, GPIO_PIN_SET);

    LCD.Display.DisplaySizeX = 320;
    LCD.Display.DisplaySizeY = 480;
    LCD.Display.Brightness = 100;
    LCD.Display.Orient = LANDSCAPE;

    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(20);
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);

    HAL_Delay(10);

    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

    LCD_Write_COM(LCD_COMM_EXIT_SLEEP_MODE);

    HAL_Delay(20);

//    LCD_Write_COM(LCD_COMM_POWER_SETTING);
//    LCD_Write_DATA_1(0x07);
//    LCD_Write_DATA_1(0x42);
//    LCD_Write_DATA_1(0x18);

//    LCD_Write_COM(LCD_COMM_VCOM_CONTROL);
//    LCD_Write_DATA_1(0x00);
//    LCD_Write_DATA_1(0x07);
//    LCD_Write_DATA_1(0x10);

//    LCD_Write_COM(LCD_COMM_POWER_SETTING_FOR_NORMAL_MODE);
//    LCD_Write_DATA_1(0x01);
//    LCD_Write_DATA_1(0x02);

//    LCD_Write_COM(LCD_COMM_FRAME_RATE_AND_INVERSION_CONTROL);
//    LCD_Write_DATA_1(0x03);

//    LCD_Write_COM(LCD_COMM_PANEL_DRIVING_SETTING);
//    LCD_Write_DATA_1(0x10);
//    LCD_Write_DATA_1(0x3B);
//    LCD_Write_DATA_1(0x00);
//    LCD_Write_DATA_1(0x02);
//    LCD_Write_DATA_1(0x11);

//    LCD_Write_COM(LCD_COMM_GAMMA_SETTING);
//    LCD_Write_DATA_1(0x00);
//    LCD_Write_DATA_1(0x32);
//    LCD_Write_DATA_1(0x36);
//    LCD_Write_DATA_1(0x45);
//    LCD_Write_DATA_1(0x06);
//    LCD_Write_DATA_1(0x16);
//    LCD_Write_DATA_1(0x37);
//    LCD_Write_DATA_1(0x75);
//    LCD_Write_DATA_1(0x77);
//    LCD_Write_DATA_1(0x54);
//    LCD_Write_DATA_1(0x0C);
//    LCD_Write_DATA_1(0x00);

    LCD_Write_COM(LCD_COMM_SET_ADDRESS_MODE);
    LCD_Write_DATA_1(0x08);

    LCD_Write_COM(LCD_COMM_SET_PIXEL_FORMAT);
    LCD_Write_DATA_1(0x55);

//    LCD_Write_COM(LCD_COMM_SET_COLUMN_ADDRESS);
//    LCD_Write_DATA_1(0x00);
//    LCD_Write_DATA_1(0x00);
//    LCD_Write_DATA_1(0x01);
//    LCD_Write_DATA_1(0x3F);

//    LCD_Write_COM(LCD_COMM_SET_PAGE_ADDRESS);
//    LCD_Write_DATA_1(0x00);
//    LCD_Write_DATA_1(0x00);
//    LCD_Write_DATA_1(0x01);
//    LCD_Write_DATA_1(0xE0);

    HAL_Delay(120);

    //LCD_FillScreen(0x0000);

    LCD_Write_COM(LCD_COMM_SET_DISPLAY_ON);

    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);

    __HAL_TIM_SET_COMPARE( &htim1, TIM_CHANNEL_1, LCD.Display.Brightness);
}


/*  */
void LCD_ClearScreen(void)
{
    LCD_FillWindow( 0, LCD.Display.DisplaySizeX, 0, LCD.Display.DisplaySizeY, 0x0000 );
}


/*  */
void LCD_FillScreen_RGB(unsigned char r, unsigned char g, unsigned char b)
{
    unsigned int color;

    color = ((r & 248) << 8 | (g & 252) << 3 | (b & 248) >> 3);

    LCD_FillScreen(color);
}


/*  */
void LCD_FillScreen(unsigned int color)
{
    LCD_FillWindow( 0, LCD.Display.DisplaySizeX, 0, LCD.Display.DisplaySizeY, color );
}


/*   */
void LCD_FillWindow(uint16_t colstart, uint16_t colend, uint16_t pagestart, uint16_t pageend, uint16_t color)
{

    unsigned char ch = (unsigned char)(color >> 8);
    unsigned char cl = (unsigned char)(color & 0x00FF);

    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);

    LCD_Write_COM(LCD_COMM_SET_COLUMN_ADDRESS);
    LCD_Write_DATA_1( (uint8_t)(colstart>>8) );
    LCD_Write_DATA_1( (uint8_t)(colstart & 0x00FF) );
    LCD_Write_DATA_1( (uint8_t)(colend>>8) );
    LCD_Write_DATA_1( (uint8_t)(colend & 0x00FF) );

    LCD_Write_COM(LCD_COMM_SET_PAGE_ADDRESS);
    LCD_Write_DATA_1( (uint8_t)(pagestart>>8) );
    LCD_Write_DATA_1( (uint8_t)(pagestart & 0x00FF) );
    LCD_Write_DATA_1( (uint8_t)(pageend>>8) );
    LCD_Write_DATA_1( (uint8_t)(pageend & 0x00FF) );

    LCD_Write_COM(LCD_COMM_WRITE_MEMORY_START);

    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);

    _fast_fill_16( ch, cl, (unsigned long)( (colend-colstart)+1 ) * (unsigned long)( (pageend-pagestart)+1 ) );

    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);


}


/*  */
void LCD_DrawPixel(unsigned int x, unsigned int y)
{
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
    //LCD_SetXY(x, y, x, y);
    //LCD_SetPixel((lcd_param.fnt_color_h << 8) | lcd_param.fnt_color_l);
    //LCD_ClrXY();
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}



/* */
static void LCD_SetPixel(unsigned int color)
{
    LCD_Write_DATA((color >> 8),(color & 0xFF));
}


static void LCD_Write_COM(unsigned char vl)
{
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
    LCD_Write_Bus(0x00, vl);
}



static void LCD_Write_COM_DATA(unsigned char commmand, int data)
{
    LCD_Write_COM(commmand);
    LCD_Write_DATA((unsigned char)data >> 8, (unsigned char)data);
}


static void LCD_Write_DATA(unsigned char vh, unsigned char vl)
{
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
    LCD_Write_Bus(vh, vl);
}


static void LCD_Write_DATA_1(unsigned char vl)
{
    HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
    LCD_Write_Bus(0x00, vl);
}


static void LCD_Write_Bus(unsigned char vh, unsigned char vl)
{
    GPIOB->ODR = (uint16_t)( vh<<8 | vl );
    PULSE_WR_LOW()
}


static void _fast_fill_16(unsigned int ch, unsigned int cl, unsigned long pix)
{
    unsigned long i = 0;

    GPIOB->ODR = (uint16_t)( ch<<8 | cl );

    do
    {
        PULSE_WR_LOW();
    }
    while(++i < pix);
}
