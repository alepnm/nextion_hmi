#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

#include <stdint.h>


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


enum {LANDSCAPE = 0, PORTRAIT};


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
    uint16_t	    disp_x_size;
    uint16_t	    disp_y_size;
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

void        LCD_DrawBitmap(int x, int y, int sx, int sy, const uint16_t* data, int scale);
void        LCD_DrawBitmap_1(int x, int y, int sx, int sy, const uint16_t* data, int deg, int rox, int roy);

void        LCD_Char(unsigned char c, int x, int y);
void        LCD_RotateChar(unsigned char c, int x, int y, int pos, int deg);
void        LCD_Text(char *st, int x, int y, int deg);
void        LCD_PrintNumI(long num, int x, int y, int length, char filler);
void        LCD_PrintNumF(double num, unsigned char dec, int x, int y, char divider, int length, char filler);



void        LCD_SetFont(const uint8_t* font);
const uint8_t* LCD_GetFont(void);
uint8_t     LCD_GetFontXsize(void);
uint8_t     LCD_GetFontYsize(void);

#endif /* LCD_H_INCLUDED */
