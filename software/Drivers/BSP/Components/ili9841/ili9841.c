

#include "nextion.h"
#include "ili9841.h"



LCD_DrvTypeDef   ILI9841_DRV = {
    ili9841_Init,
    NULL,
    ili9841_DisplayOn,
    ili9841_DisplayOff,
    ili9841_SetCursor,
    ili9841_WritePixel,
    NULL,
    ili9841_SetDisplayWindow,
    ili9841_DrawHLine,
    ili9841_DrawVLine,
    ili9841_GetLcdPixelWidth,
    ili9841_GetLcdPixelHeight,
    ili9841_DrawBitmap,

};

LCD_TypeDef LCD;


static uint8_t BrightnessTemp = 0;


/*  */
void ili9841_Init(void) {

    uint8_t lcd_addr_mode = 1;


    LCD_IO_Init();


    LCD.orient = PORTRAIT;

    if(LCD.orient == PORTRAIT) {
        LCD.disp_x_size = ILI9841_LCD_PIXEL_WIDTH;
        LCD.disp_y_size = ILI9841_LCD_PIXEL_HEIGHT;
        lcd_addr_mode = 0x02;
    } else {
        LCD.disp_x_size = ILI9841_LCD_PIXEL_HEIGHT;
        LCD.disp_y_size = ILI9841_LCD_PIXEL_WIDTH;
        lcd_addr_mode = 0x01;
    }

    LCD.API = &ILI9841_DRV;

    LCD_IO_Init();

    LCD_CS_HIGH();
    LCD_RD_HIGH();
    LCD_WR_HIGH();
    LCD_RS_HIGH();
    LCD_RST_HIGH();

    LCD_IO_BusAsOutput();

    LCD_Delay(20);
    LCD_RST_LOW();
    LCD_Delay(20);
    LCD_RST_HIGH();

    LCD_Delay(10);

    LCD_CS_LOW();

    LCD_IO_Write_COM(LCD_COMM_EXIT_SLEEP_MODE);

    LCD_Delay(20);

    LCD_IO_Write_COM(LCD_COMM_POWER_SETTING);
    LCD_IO_Write_DATA_1(0x07);
    LCD_IO_Write_DATA_1(0x42);
    LCD_IO_Write_DATA_1(0x18);

    LCD_IO_Write_COM(LCD_COMM_VCOM_CONTROL);
    LCD_IO_Write_DATA_1(0x00);
    LCD_IO_Write_DATA_1(0x07);
    LCD_IO_Write_DATA_1(0x10);

    LCD_IO_Write_COM(LCD_COMM_POWER_SETTING_FOR_NORMAL_MODE);
    LCD_IO_Write_DATA_1(0x01);
    LCD_IO_Write_DATA_1(0x02);

    LCD_IO_Write_COM(LCD_COMM_FRAME_RATE_AND_INVERSION_CONTROL);
    LCD_IO_Write_DATA_1(0x03);

    LCD_IO_Write_COM(LCD_COMM_PANEL_DRIVING_SETTING);
    LCD_IO_Write_DATA_1(0x10);
    LCD_IO_Write_DATA_1(0x3B);
    LCD_IO_Write_DATA_1(0x00);
    LCD_IO_Write_DATA_1(0x02);
    LCD_IO_Write_DATA_1(0x11);

    LCD_IO_Write_COM(LCD_COMM_GAMMA_SETTING);
    LCD_IO_Write_DATA_1(0x00);
    LCD_IO_Write_DATA_1(0x32);
    LCD_IO_Write_DATA_1(0x36);
    LCD_IO_Write_DATA_1(0x45);
    LCD_IO_Write_DATA_1(0x06);
    LCD_IO_Write_DATA_1(0x16);
    LCD_IO_Write_DATA_1(0x37);
    LCD_IO_Write_DATA_1(0x75);
    LCD_IO_Write_DATA_1(0x77);
    LCD_IO_Write_DATA_1(0x54);
    LCD_IO_Write_DATA_1(0x0C);
    LCD_IO_Write_DATA_1(0x00);

    LCD_IO_Write_COM(LCD_COMM_SET_ADDRESS_MODE);
    LCD_IO_Write_DATA_1( 0x08 | (lcd_addr_mode<<5) );

    LCD_IO_Write_COM(LCD_COMM_SET_PIXEL_FORMAT);
    LCD_IO_Write_DATA_1(0x55);

    LCD_Delay(120);

    LCD_IO_Write_COM(LCD_COMM_SET_DISPLAY_ON);

    LCD_CS_HIGH();
}

/*  */
uint16_t ili9841_ReadID(void) {

    return 0;
}


/*  */
void ili9841_SetColor_RGB(uint8_t r, uint8_t g, uint8_t b) {
    //LCD.fnt_color_h = ((r & 248) | g >> 5);
    //LCD.fnt_color_l = ((g & 28) << 3 | b >> 3);
}

/*  */
void ili9841_SetColor_Word(uint16_t color) {
    LCD.fnt_color = color;
}

/*  */
void ili9841_SetBackColor_RGB(uint8_t r, uint8_t g, uint8_t b) {
    //LCD.bg_color_h = ((r & 248) | g >> 5);
    //LCD.bg_color_l = ((g & 28) << 3 | b >> 3);
    LCD.transparent = 0;
}

/*  */
void ili9841_SetBackColor_Word(uint32_t color) {
    if (color == VGA_TRANSPARENT) {
        LCD.transparent = 1;
    } else {
        LCD.bg_color = (uint16_t)(color & 0x0000FFFF);
        LCD.transparent = 0;
    }
}

/*   */
uint16_t ili9841_GetColor(void) {
    return LCD.fnt_color;
}

/*   */
uint16_t ili9841_GetBackColor(void) {
    return LCD.bg_color;
}






/*  */
void ili9841_DisplayOn(void) {

    LCD.Brightness = BrightnessTemp;

    LCD_SetBrightness();
}

/*  */
void ili9841_DisplayOff(void) {

    BrightnessTemp = LCD.Brightness;

    LCD.Brightness = 0;

    LCD_SetBrightness();
}

/*  */
void ili9841_SetCursor(uint16_t Xpos, uint16_t Ypos) {

}

/*  */
void ili9841_WritePixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode) {

}


/*  */
void ili9841_WriteReg(uint8_t LCDReg, uint8_t LCDRegValue) {
    //LCD_IO_Write_COM(LCDReg);
    //LCD_IO_Write_DATA_1(LCDRegValue);
}

/*  */
uint8_t ili9841_ReadReg(uint8_t LCDReg) {

    return 0;
}

/*  */
void ili9841_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height) {

}

/*  */
void ili9841_DrawHLine(uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos, uint16_t Length) {

}

/*  */
void ili9841_DrawVLine(uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos, uint16_t Length) {

}

/*  */
uint16_t ili9841_GetLcdPixelWidth(void) {

    return 0;
}


/*  */
uint16_t ili9841_GetLcdPixelHeight(void) {

    return 0;
}

/*  */
void ili9841_DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *pbmp) {

}


