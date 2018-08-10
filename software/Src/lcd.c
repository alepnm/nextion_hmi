#include <math.h>
#include <string.h>
#include "stm32f0xx_hal.h"
#include "lcd.h"
#include "lcd_commands.h"


#define LCD_CS_LOW()        HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
#define LCD_CS_HIGH()       HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);

#define LCD_RST_LOW()       HAL_GPIO_WritePin(SD_RST_GPIO_Port, SD_RST_Pin, GPIO_PIN_RESET);
#define LCD_RST_HIGH()      HAL_GPIO_WritePin(SD_RST_GPIO_Port, SD_RST_Pin, GPIO_PIN_SET);

#define LCD_RD_LOW()        HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_RESET);
#define LCD_RD_HIGH()       HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_SET);

#define LCD_WR_LOW()        HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_RESET);
#define LCD_WR_HIGH()       HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET);

#define LCD_RS_LOW()        HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
#define LCD_RS_HIGH()       HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);

#define PULSE_WR_LOW()      LCD_WR_LOW(); asm("nop"); LCD_WR_HIGH();

//===========================================================================================
// UTFT VGA color palette
//========================================================================================================

#define LEFT			  0
#define RIGHT 			  9999
#define CENTER 			  9998


extern TIM_HandleTypeDef htim1;

LCD_TypeDef LCD;
Font_TypeDef Font;


extern void LCD_BusAsInput(void);
extern void LCD_BusAsOutput(void);

static void LCD_Write_COM(unsigned char vl);
static void LCD_Write_DATA(unsigned char vh, unsigned char vl);
static void LCD_Write_DATA_1(unsigned char vl);
static void LCD_Write_Bus(unsigned char vh, unsigned char vl);

static void LCD_SetPixel(unsigned int color);
static void LCD_SetXY(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
static void LCD_ClrXY(void);

static void _fast_fill_16(uint8_t ch, uint8_t cl, unsigned long pix);
static void _convert_float(char *buf, double num, int width, unsigned char prec);



/* patikrinta */
void LCD_Init(void) {

    uint8_t lcd_addr_mode;

    LCD.orient = PORTRAIT;

    if(LCD.orient == PORTRAIT) {
        LCD.disp_x_size = 320;
        LCD.disp_y_size = 480;
        lcd_addr_mode = 0x02;
    } else {
        LCD.disp_x_size = 480;
        LCD.disp_y_size = 320;
        lcd_addr_mode = 0x01;
    }


    LCD.Brightnes = 100;
    LCD.fnt_color = VGA_GREEN;
    LCD.bg_color = VGA_BLACK;

    LCD_RST_LOW();
    HAL_Delay(20);
    LCD_RST_HIGH();

    LCD_CS_HIGH();
    LCD_RD_HIGH();
    LCD_WR_HIGH();
    LCD_RS_HIGH();

    LCD_BusAsOutput();

    HAL_Delay(10);

    LCD_CS_LOW();

    LCD_Write_COM(LCD_COMM_EXIT_SLEEP_MODE);

    HAL_Delay(20);

    LCD_Write_COM(LCD_COMM_POWER_SETTING);
    LCD_Write_DATA_1(0x07);
    LCD_Write_DATA_1(0x42);
    LCD_Write_DATA_1(0x18);

    LCD_Write_COM(LCD_COMM_VCOM_CONTROL);
    LCD_Write_DATA_1(0x00);
    LCD_Write_DATA_1(0x07);
    LCD_Write_DATA_1(0x10);

    LCD_Write_COM(LCD_COMM_POWER_SETTING_FOR_NORMAL_MODE);
    LCD_Write_DATA_1(0x01);
    LCD_Write_DATA_1(0x02);

    LCD_Write_COM(LCD_COMM_FRAME_RATE_AND_INVERSION_CONTROL);
    LCD_Write_DATA_1(0x03);

    LCD_Write_COM(LCD_COMM_PANEL_DRIVING_SETTING);
    LCD_Write_DATA_1(0x10);
    LCD_Write_DATA_1(0x3B);
    LCD_Write_DATA_1(0x00);
    LCD_Write_DATA_1(0x02);
    LCD_Write_DATA_1(0x11);

    LCD_Write_COM(LCD_COMM_GAMMA_SETTING);
    LCD_Write_DATA_1(0x00);
    LCD_Write_DATA_1(0x32);
    LCD_Write_DATA_1(0x36);
    LCD_Write_DATA_1(0x45);
    LCD_Write_DATA_1(0x06);
    LCD_Write_DATA_1(0x16);
    LCD_Write_DATA_1(0x37);
    LCD_Write_DATA_1(0x75);
    LCD_Write_DATA_1(0x77);
    LCD_Write_DATA_1(0x54);
    LCD_Write_DATA_1(0x0C);
    LCD_Write_DATA_1(0x00);

    LCD_Write_COM(LCD_COMM_SET_ADDRESS_MODE);
    LCD_Write_DATA_1( 0x08 | (lcd_addr_mode<<5) );

    LCD_Write_COM(LCD_COMM_SET_PIXEL_FORMAT);
    LCD_Write_DATA_1(0x55);

    HAL_Delay(120);

    LCD_Write_COM(LCD_COMM_SET_DISPLAY_ON);

    LCD_CS_HIGH();

    __HAL_TIM_SET_COMPARE( &htim1, TIM_CHANNEL_1, LCD.Brightnes);
}

/* tikrinti */
void LCD_SetColor_RGB(unsigned char r, unsigned char g, unsigned char b) {

    uint8_t fnt_color_h = ((r & 248) | g >> 5);
    uint8_t fnt_color_l = ((g & 28) << 3 | b >> 3);

    LCD.fnt_color = (uint16_t)( (fnt_color_h<<8) | fnt_color_l );
}


/* tikrinti */
void LCD_SetColor_Word(unsigned int color) {
    LCD.fnt_color = color;
}


/* tikrinti */
void LCD_SetBackColor_RGB(unsigned char r, unsigned char g, unsigned char b) {

    uint8_t bg_color_h = ((r & 248) | g >> 5);
    uint8_t bg_color_l = ((g & 28) << 3 | b >> 3);

    LCD.bg_color = (uint16_t)( (bg_color_h<<8) | bg_color_l );
    LCD.transparent = 0;
}


/* tikrinti */
void LCD_SetBackColor_Word(uint32_t color) {
    if (color == VGA_TRANSPARENT) {
        LCD.transparent = 1;
    } else {
        LCD.bg_color = color;
        LCD.transparent = 0;
    }
}

/* tikrinti */
uint16_t LCD_GetColor(void) {
    return LCD.fnt_color;
}


/* tikrinti */
uint16_t LCD_GetBackColor(void) {
    return LCD.bg_color;
}


/* patikrinta */
void LCD_ClearScreen(void) {
    LCD_Fill( 0, LCD.disp_x_size, 0, LCD.disp_y_size, 0x0000 );
}


/* patikrinta */
void LCD_FillScreen_RGB(unsigned char r, unsigned char g, unsigned char b) {

    unsigned int color;

    color = ((r & 248) << 8 | (g & 252) << 3 | (b & 248) >> 3);

    LCD_Fill( 0, LCD.disp_x_size, 0, LCD.disp_y_size, color );
}


/* patikrinta */
void LCD_FillScreen_Color(unsigned int color) {
    LCD_Fill( 0, LCD.disp_x_size, 0, LCD.disp_y_size, color );
}


/* patikrinta */
void LCD_Fill(uint16_t colstart, uint16_t colend, uint16_t pagestart, uint16_t pageend, uint16_t color) {

    unsigned char ch = (unsigned char)(color >> 8);
    unsigned char cl = (unsigned char)(color & 0x00FF);

    LCD_CS_LOW();

    LCD_SetXY(colstart, pagestart, colend, pageend);

    LCD_RS_HIGH();

    _fast_fill_16( ch, cl, (unsigned long)( (colend-colstart)+1 ) * (unsigned long)( (pageend-pagestart)+1 ) );

    LCD_CS_HIGH();
}


/* patikrinta */
void LCD_DrawPixel(unsigned int x, unsigned int y) {

    LCD_CS_LOW();

    LCD_SetXY(x, y, x, y);

    LCD_SetPixel(LCD.fnt_color);

    LCD_CS_HIGH();
}


/* patikrinta */
void LCD_SetOff(void) {

    LCD_CS_LOW();

    LCD_Write_COM(LCD_COMM_SET_DISPLAY_OFF);

    LCD_CS_HIGH();

    __HAL_TIM_SET_COMPARE( &htim1, TIM_CHANNEL_1, 0);
}


/* patikrinta */
void LCD_SetOn(void) {

    LCD_CS_LOW();

    LCD_Write_COM(LCD_COMM_SET_DISPLAY_ON);

    LCD_CS_HIGH();

    __HAL_TIM_SET_COMPARE( &htim1, TIM_CHANNEL_1, LCD.Brightnes);
}


/* dabaigti */
void LCD_SetContrast(unsigned char c) {
    LCD_CS_LOW();
    LCD_CS_HIGH();
}


/* patikrinta */
void LCD_DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {

    int dx, dy, xstep, ystep, col, row, t;

    if(y1 == y2) {
        LCD_DrawHLine(x1, y1, x2 - x1);
    } else if(x1 == x2) {
        LCD_DrawVLine(x1, y1, y2 - y1);
    } else {
        dx = (x2 > x1 ? x2 - x1 : x1 - x2);
        xstep =  x2 > x1 ? 1 : -1;
        dy = (y2 > y1 ? y2 - y1 : y1 - y2);
        ystep =  y2 > y1 ? 1 : -1;
        col = x1;
        row = y1;

        LCD_CS_LOW();

        if(dx < dy) {

            t = - (dy >> 1);

            while(1) {
                LCD_SetXY(col, row, col, row);
                LCD_Write_DATA ( (uint8_t)(LCD.fnt_color>>8), (uint8_t)(LCD.fnt_color & 0x00FF) );
                if (row == y2) {
                    return;
                }

                row += ystep;
                t += dx;
                if (t >= 0) {
                    col += xstep;
                    t -= dy;
                }
            }
        } else {

            t = - (dx >> 1);

            while(1) {
                LCD_SetXY(col, row, col, row);
                LCD_Write_DATA ( (uint8_t)(LCD.fnt_color>>8), (uint8_t)(LCD.fnt_color & 0x00FF) );
                if (col == x2) {
                    return;
                }

                col += xstep;
                t += dy;
                if (t >= 0) {
                    row += ystep;
                    t -= dx;
                }
            }
        }

        LCD_CS_HIGH();
    }
}


/* patikrinta */
void LCD_DrawHLine(unsigned int x, unsigned int y, int l) {

    if (l < 0) {
        l = -l;
        x -= l;
    }

    LCD_CS_LOW();

    LCD_SetXY(x, y, x + l, y);

    LCD_RS_HIGH();

    _fast_fill_16( (uint8_t)(LCD.fnt_color>>8), (uint8_t)(LCD.fnt_color & 0x00FF), l);

    LCD_CS_HIGH();
}


/* patikrinta */
void LCD_DrawVLine(unsigned int x, unsigned int y, int l) {

    if (l < 0) {
        l = -l;
        y -= l;
    }

    LCD_CS_LOW();

    LCD_SetXY(x, y, x, y + l);

    LCD_RS_HIGH();

    _fast_fill_16( (uint8_t)(LCD.fnt_color>>8), (uint8_t)(LCD.fnt_color & 0x00FF), l);

    LCD_CS_HIGH();
}


/* patikrinta */
void LCD_SetFont(const uint8_t* font) {
    Font.font = font;
    Font.x_size = *(font);
    Font.y_size = *(font+1);
    Font.offset = *(font+2);
    Font.numchars = *(font+3);
}

/* patikrinta */
const uint8_t* LCD_GetFont(void) {
    return Font.font;
}

/* patikrinta */
uint8_t LCD_GetFontXsize(void) {
    return Font.x_size;
}

/* patikrinta */
uint8_t LCD_GetFontYsize(void) {
    return Font.y_size;
}


/* patikrinta */
void LCD_DrawBitmap(int x, int y, int sx, int sy, const uint16_t* data, int scale) {

    int col;
    int tx, ty, tc, tsx, tsy;

    LCD_CS_LOW();

    if(scale == 1) {

        if(LCD.orient == LANDSCAPE) {

            LCD_SetXY(x, y, x + sx - 1, y + sy - 1);

            for(tc = 0; tc < (sx * sy); tc++) {

                col = data[tc];

                LCD_Write_DATA( (uint8_t)col >> 8, (uint8_t)(col & 0x00FF) );
            }

        } else {

            for(ty=0; ty<sy; ty++) {

                LCD_SetXY(x, y + ty, x + sx - 1, y + ty);

                for(tx = sx - 1; tx >= 0; tx--) {

                    col = data[(ty * sx) + tx];

                    LCD_Write_DATA( (uint8_t)(col >> 8), (uint8_t)(col & 0x00FF) );
                }
            }
        }

    } else {

        if(LCD.orient == LANDSCAPE)	{

            for(ty = 0; ty < sy; ty++) {

                for(tsy = 0; tsy < scale; tsy++) {

                    LCD_SetXY(x, y + (ty * scale) + tsy, x + ((sx * scale) - 1), y + (ty * scale) + tsy);

                    for(tx = sx - 1; tx >= 0; tx--) {

                        col = data[(ty * sx) + tx];

                        for(tsx = 0; tsx < scale; tsx++) {
                            LCD_Write_DATA( (uint8_t)(col >> 8), (uint8_t)(col & 0x00FF) );
                        }
                    }
                }
            }
        } else {
            for(ty = 0; ty < sy; ty++) {

                LCD_SetXY(x, y + (ty * scale), x + ((sx * scale) - 1), y + (ty * scale) + scale);

                for(tsy = 0; tsy < scale; tsy++) {

                    for(tx=0; tx<sx; tx++) {

                        col = data[(ty*sx)+tx];

                        for(tsx = 0; tsx < scale; tsx++) {
                            LCD_Write_DATA( (uint8_t)(col>>8), (uint8_t)(col & 0x00FF) );
                        }
                    }
                }
            }
        }
    }

    LCD_CS_HIGH();
}


/* tikrinti */
void LCD_DrawBitmap_1(int x, int y, int sx, int sy, const uint16_t* data, int deg, int rox, int roy) {

    int col;
    int tx, ty, newx, newy;

    double radian = deg * 0.0175;

    if(deg == 0) {
        LCD_DrawBitmap(x, y, sx, sy, data, 0);
    } else {

        LCD_CS_LOW();

        for(ty = 0; ty < sy; ty++) {

            for(tx = 0; tx < sx; tx++) {

                col = data[(ty*sx)+tx];

                newx = x + rox + (((tx - rox) * cos(radian)) - ((ty - roy) * sin(radian)));
                newy = y + roy + (((ty - roy) * cos(radian)) + ((tx - rox) * sin(radian)));

                LCD_SetXY(newx, newy, newx, newy);

                LCD_Write_DATA( (uint8_t)(col >> 8), (uint8_t)(col & 0x00FF) ) ;
            }
        }

        LCD_CS_HIGH();
    }
}


/* patikrinta */
void LCD_Char(unsigned char c, int x, int y) {

    unsigned char i,ch;
    int zz, j, temp;

    LCD_CS_LOW();

    if(!LCD.transparent) {

        LCD_SetXY(x, y, x + Font.x_size - 1, y + Font.y_size - 1);

        temp = ((c - Font.offset) * ((Font.x_size / 8) * Font.y_size)) + 4;

        for(j = 0; j < ((Font.x_size / 8) * Font.y_size); j++) {

            ch = Font.font[temp];

            for(i = 0; i < 8; i++) {
                if((ch & (1<<(7 - i))) != 0) {
                    LCD_SetPixel(LCD.fnt_color);
                } else {
                    LCD_SetPixel(LCD.bg_color);
                }
            }

            temp++;
        }
    } else {

        temp = ((c - Font.offset) * ((Font.x_size / 8) * Font.y_size)) + 4;

        for(j = 0; j < Font.y_size; j++) {

            for(zz = 0; zz < (Font.x_size / 8); zz++) {

                ch = Font.font[temp + zz];

                for(i = 0; i < 8; i++) {

                    LCD_SetXY(x + i + (zz * 8), y + j, x + i + (zz * 8) + 1, y + j + 1);

                    if((ch&(1 << (7 - i))) != 0) {

                        LCD_SetPixel(LCD.fnt_color);
                    }
                }
            }

            temp += (Font.x_size / 8);
        }
    }

    LCD_CS_HIGH();
}


/* tikrinti */
void LCD_RotateChar(unsigned char c, int x, int y, int pos, int deg) {

    unsigned char i, j, ch;
    int temp, zz;
    int newx, newy;

    double radian = deg * 0.0175;

    LCD_CS_LOW();

    temp = ((c - Font.offset) * ((Font.x_size / 8) * Font.y_size)) + 4;

    for(j = 0; j < Font.y_size; j++) {
        for(zz = 0; zz < (Font.x_size / 8); zz++) {

            ch = Font.font[temp + zz];

            for(i = 0; i < 8; i++) {

                newx = x + (((i + (zz * 8) + (pos * Font.x_size))* cos(radian))- ((j) * sin(radian)));

                newy = y + (((j) * cos(radian)) + ((i + (zz * 8) + (pos * Font.x_size)) * sin(radian)));

                LCD_SetXY(newx, newy, newx + 1, newy + 1);

                if((ch & (1 << (7 - i))) != 0) {
                    LCD_SetPixel(LCD.fnt_color);
                } else {
                    if(!LCD.transparent)
                        LCD_SetPixel(LCD.bg_color);
                }
            }
        }

        temp += (Font.x_size / 8);
    }

    LCD_CS_HIGH();
}


/* patikrinta */
void LCD_Text(char *st, int x, int y, int deg) {

    int i, stl = strlen(st);

    if(x == RIGHT) {
        x = (LCD.disp_x_size + 1) - (stl * Font.x_size);
    }

    if(x == CENTER) {
        x = ((LCD.disp_x_size + 1) - (stl * Font.x_size)) / 2;
    }

    for(i = 0; i < stl; i++) {
        if(deg == 0)
            LCD_Char(*st++, x + (i * (Font.x_size)), y);
        else
            LCD_RotateChar(*st++, x, y, i, deg);
    }
}


/* tikrinti */
void LCD_PrintNumI(long num, int x, int y, int length, char filler) {

    char buf[25];
    char st[27];
    unsigned char neg = 0;
    int c = 0, f = 0, i;

    if(num == 0) {
        if(length != 0) {
            for (c = 0; c < (length - 1); c++) {
                st[c] = filler;
                st[c] = 48;     //?????
                st[c + 1] = 0;
            }
        } else {
            st[0] = 48;
            st[1] = 0;
        }
    } else {
        if(num < 0) {
            neg = 1;
            num = -num;
        }

        while(num > 0) {
            buf[c] = 48 + (num % 10);
            c++;
            num = (num - (num % 10)) / 10;
        }

        buf[c] = 0;

        if(neg == 1) {
            st[0] = 45;
        }

        if(length > (c + neg)) {
            for (i = 0; i < (length - c - neg); i++) {
                st[i + neg] = filler;
                f++;
            }
        }

        for(i = 0; i < c; i++) {
            st[i + neg + f] = buf[c - i - 1];
        }

        st[c + neg + f] = 0;
    }

    LCD_Text(st, x, y, 0);
}


/* tikrinti */
void LCD_PrintNumF(double num, unsigned char dec, int x, int y, char divider, int length, char filler) {

    char st[27];
    unsigned char neg = 0;
    int i;

    if(dec < 1)
        dec = 1;
    else if(dec > 5)
        dec = 5;
    if(num < 0)
        neg = 1;

    _convert_float(st, num, length, dec);

    if(divider != '.') {
        for(i = 0; i < sizeof(st); i++)
            if(st[i] == '.')
                st[i] = divider;
    }

    if(filler != ' ') {
        if(neg == 1) {
            st[0] = '-';
            for(i = 1; i < sizeof(st); i++)
                if ((st[i] == ' ') || (st[i] == '-'))
                    st[i] = filler;
        } else {
            for(i = 0; i < sizeof(st); i++)
                if(st[i] == ' ')
                    st[i] = filler;
        }
    }

    LCD_Text(st, x, y, 0);
}



/* patikrinta */
static void LCD_SetXY(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {

    LCD_Write_COM(LCD_COMM_SET_COLUMN_ADDRESS);
    LCD_Write_DATA_1(x1>>8);
    LCD_Write_DATA_1(x1);
    LCD_Write_DATA_1(x2>>8);
    LCD_Write_DATA_1(x2);

    LCD_Write_COM(LCD_COMM_SET_PAGE_ADDRESS);
    LCD_Write_DATA_1(y1>>8);
    LCD_Write_DATA_1(y1);
    LCD_Write_DATA_1(y2>>8);
    LCD_Write_DATA_1(y2);

    LCD_Write_COM(LCD_COMM_WRITE_MEMORY_START);
}


/* patikrinta */
static void LCD_ClrXY(void) {
    LCD_SetXY(0, 0, LCD.disp_x_size, LCD.disp_y_size);
}


/* patikrinta */
static void LCD_SetPixel(unsigned int color) {
    LCD_Write_DATA((color >> 8),(color & 0xFF));
}

/* patikrinta */
static void LCD_Write_COM(unsigned char vl) {
    LCD_RS_LOW();
    LCD_Write_Bus(0x00, vl);
}


/* patikrinta */
static void LCD_Write_DATA(unsigned char vh, unsigned char vl) {
    LCD_RS_HIGH();
    LCD_Write_Bus(vh, vl);
}

/* patikrinta */
static void LCD_Write_DATA_1(unsigned char vl) {
    LCD_RS_HIGH();
    LCD_Write_Bus(0x00, vl);
}

/* patikrinta */
static void LCD_Write_Bus(unsigned char vh, unsigned char vl) {
    GPIOB->ODR = (uint16_t)( vh<<8 | vl );
    PULSE_WR_LOW()
}


/* patikrinta */
static void _fast_fill_16(uint8_t ch, uint8_t cl, unsigned long pix) {

    unsigned long i = 0;

    GPIOB->ODR = (uint16_t)( ch<<8 | cl );

    do {
        PULSE_WR_LOW();
    } while(++i < pix);
}


/* dabaigti */
static void _convert_float(char *buf, double num, int width, unsigned char prec) {
    //dtostrf(num, width, prec, buf);
}
