#ifndef ILI9841_H_INCLUDED
#define ILI9841_H_INCLUDED


#include "../Drivers/BSP/Components/Common/lcd.h"


#define VGA_BLACK		  0x0000
#define VGA_WHITE		  0xFFFF
#define VGA_RED			  0xF800
#define VGA_GREEN		  0x0400
#define VGA_BLUE		  0x001F
#define VGA_SILVER		  0xC618
#define VGA_GRAY		  0x8410
#define VGA_MAROON		  0x8000
#define VGA_YELLOW		  0xFFE0
#define VGA_OLIVE		  0x8400
#define VGA_LIME		  0x07E0
#define VGA_AQUA		  0x07FF
#define VGA_TEAL		  0x0410
#define VGA_NAVY		  0x0010
#define VGA_FUCHSIA		  0xF81F
#define VGA_PURPLE		  0x8010
#define VGA_TRANSPARENT	  0xFFFFFFFF


enum {
    LCD_COMM_NOP =                                          0x00,
    LCD_COMM_SOFT_RESET =                                   0x01,
    LCD_COMM_GET_POWER_MODE =                               0x0A,
    LCD_COMM_GET_ADDRESS_MODE =                             0x0B,
    LCD_COMM_GET_PIXEL_FORMAT =                             0x0C,
    LCD_COMM_GET_DISPLAY_MODE =                             0x0D,
    LCD_COMM_GET_SIGNAL_MODE =                              0x0E,
    LCD_COMM_GET_DIAGNOSTIC_RESULT =                        0x0F,
    LCD_COMM_ENTER_SLEEP_MODE =                             0x10,
    LCD_COMM_EXIT_SLEEP_MODE =                              0X11,
    LCD_COMM_ENTER_PARTIAL_MODE =                           0x12,
    LCD_COMM_ENTER_NORMAL_MODE =                            0x13,
    LCD_COMM_EXIT_INVERT_MODE =                             0x20,
    LCD_COMM_ENTER_INVERT_MODE =                            0x21,
    LCD_COMM_SET_DISPLAY_OFF =                              0x28,
    LCD_COMM_SET_DISPLAY_ON =                               0x29,
    LCD_COMM_SET_COLUMN_ADDRESS =                           0x2A,
    LCD_COMM_SET_PAGE_ADDRESS =                             0x2B,
    LCD_COMM_WRITE_MEMORY_START =                           0x2C,
    LCD_COMM_READ_MEMORY_START =                            0x2E,
    LCD_COMM_SET_PARTIAL_AREA =                             0x30,
    LCD_COMM_SET_SCROLL_AREA =                              0x33,
    LCD_COMM_SET_TEAR_OFF =                                 0x34,
    LCD_COMM_SET_TEAR_ON =                                  0x35,
    LCD_COMM_SET_ADDRESS_MODE =                             0x36,
    LCD_COMM_SET_SCROLL_START =                             0x37,
    LCD_COMM_EXIT_IDLE_MODE =                               0x38,
    LCD_COMM_ENTER_IDLE_MODE =                              0x39,
    LCD_COMM_SET_PIXEL_FORMAT =                             0x3A,
    LCD_COMM_WRITE_MEMORY_CONTINUE =                        0x3C,
    LCD_COMM_READ_MEMORY_CONTINUE =                         0x3E,
    LCD_COMM_SET_TEAR_SCANLINE =                            0x44,
    LCD_COMM_GET_SCANLINE =                                 0x45,
    LCD_COMM_READ_DDB_START =                               0xA1,
    LCD_COMM_COMMAND_ACCESS_PROTECT =                       0xB0,
    LCD_COMM_LOW_POWER_MODE_CONTROL =                       0xB1,
    LCD_COMM_FRAME_MEMORY_ACCESS_AND_INTERFACE_SETTING =    0xB3,
    LCD_COMM_DISPLAY_MODE_AND_FRAME_MEMORY_WRITE_MODE_SETTING = 0xB4,
    LCD_COMM_DEVICE_CODE_READ =                             0xBF,
    LCD_COMM_PANEL_DRIVING_SETTING =                        0xC0,
    LCD_COMM_DISPLAY_TIMING_SETTING_FOR_NORMAL_MODE =       0xC1,
    LCD_COMM_DISPLAY_TIMING_SETTING_FOR_PARTIAL_MODE =      0xC2,
    LCD_COMM_DISPLAY_TIMING_SETTING_FOR_IDLE_MODE =         0xC3,
    LCD_COMM_FRAME_RATE_AND_INVERSION_CONTROL =             0xC5,
    LCD_COMM_INTERFACE_CONTROL =                            0xC6,
    LCD_COMM_GAMMA_SETTING =                                0xC8,
    LCD_COMM_POWER_SETTING =                                0xD0,
    LCD_COMM_VCOM_CONTROL =                                 0xD1,
    LCD_COMM_POWER_SETTING_FOR_NORMAL_MODE =                0xD2,
    LCD_COMM_POWER_SETTING_FOR_PARTIAL_MODE =               0xD3,
    LCD_COMM_POWER_SETTING_FOR_IDLE_MODE =                  0xD4,
    LCD_COMM_NV_MEMORY_WRITE =                              0xE0,
    LCD_COMM_NV_MEMORY_CONTROL =                            0xE1,
    LCD_COMM_NV_MEMORY_STATUS_READ =                        0xE2,
    LCD_COMM_NV_MEMORY_PROTECTION =                         0xE3
}eLCD_COMMAND;

enum {LANDSCAPE = 0, PORTRAIT}eLCD_ORIENTATION;

#define  ILI9841_LCD_PIXEL_WIDTH    ((uint16_t)320)
#define  ILI9841_LCD_PIXEL_HEIGHT   ((uint16_t)480)


typedef struct _lcd_param {
    uint8_t             orient;
    uint16_t	        disp_x_size;
    uint16_t	        disp_y_size;
    uint8_t             transparent;
    uint16_t            fnt_color;
    uint16_t            bg_color;

    uint8_t             Brightnes;      //0-100%
    LCD_DrvTypeDef*     API;            //  API funkcijos
} LCD_TypeDef;

extern LCD_TypeDef LCD;


void     ili9841_Init(void);
uint16_t ili9841_ReadID(void);

void     ili9841_DisplayOn(void);
void     ili9841_DisplayOff(void);
void     ili9841_SetCursor(uint16_t Xpos, uint16_t Ypos);
void     ili9841_WritePixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode);
void     ili9841_WriteReg(uint8_t LCDReg, uint8_t LCDRegValue);
uint8_t  ili9841_ReadReg(uint8_t LCDReg);

void     ili9841_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     ili9841_DrawHLine(uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos, uint16_t Length);
void     ili9841_DrawVLine(uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos, uint16_t Length);

uint16_t ili9841_GetLcdPixelWidth(void);
uint16_t ili9841_GetLcdPixelHeight(void);
void     ili9841_DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *pbmp);



#endif /* ILI9841_H_INCLUDED */
