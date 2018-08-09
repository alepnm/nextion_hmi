#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

#include <stdint.h>


enum {PORTRAIT = 0, LANDSCAPE};


typedef struct _font {
    const uint8_t* font;
    uint8_t x_size;
    uint8_t y_size;
    uint8_t offset;
    uint8_t numchars;
} Font_TypeDef;

extern Font_TypeDef Font;


typedef struct _lcd_param {
    uint8_t         orient;
    uint16_t	    disp_a_size;
    uint16_t	    disp_b_size;
    uint8_t         transparent;
    uint16_t        fnt_color;
    uint16_t        bg_color;

    uint8_t         Brightnes;     //0-100%
} LCD_TypeDef;

extern LCD_TypeDef LCD;


void        LCD_Init(void);
void        LCD_ClearScreen(void);

void        LCD_SetColor_RGB(unsigned char r, unsigned char g, unsigned char b);
void        LCD_SetColor_Word(unsigned int color);
void        LCD_SetBackColor_RGB(unsigned char r, unsigned char g, unsigned char b);
void        LCD_SetBackColor_Word(uint32_t color);
uint16_t    LCD_GetColor(void);
uint16_t    LCD_GetBackColor(void);

void        LCD_FillScreen_RGB(unsigned char r, unsigned char g, unsigned char b);
void        LCD_FillScreen_Color(unsigned int color);
void        LCD_Fill(uint16_t colstart, uint16_t colend, uint16_t pagestart, uint16_t pageend, uint16_t color);

void        LCD_DrawPixel(unsigned int x, unsigned int y);
void        LCD_DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void        LCD_DrawHLine(unsigned int x, unsigned int y, int l);
void        LCD_DrawVLine(unsigned int x, unsigned int y, int l);

void        LCD_DrawBitmap(int x, int y, int sx, int sy, unsigned int* data, int scale);
void        LCD_DrawBitmap_1(int x, int y, int sx, int sy, unsigned int* data, int deg, int rox, int roy);

void        LCD_Char(unsigned char c, int x, int y);
void        LCD_RotateChar(unsigned char c, int x, int y, int pos, int deg);
void        LCD_Text(char *st, int x, int y, int deg);
void        LCD_PrintNumI(long num, int x, int y, int length, char filler);
void        LCD_PrintNumF(double num, unsigned char dec, int x, int y, char divider, int length, char filler);



void        LCD_SetFont(const uint8_t* font);
const uint8_t* LCD_GetFont(void);
uint8_t     LCD_GetFontXsize(void);
uint8_t     LCD_GetFontYsize(void);

uint16_t    LCD_GetDisplayXSize(void);
uint16_t    LCD_GetDisplayYSize(void);

#endif /* LCD_H_INCLUDED */
