//========================================================================================================
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <math.h> 
#include <string.h> 
#include <stdlib.h>
#include "UTFT.h"
//========================================================================================================
_lcd_param lcd_param; // Параметры
_current_font cfont;  // Текущий фонт
//========================================================================================================
void LCD_Init(unsigned char display_model,unsigned char orientacia)
{
// Настройка щины данных и управления дисплея
LCD_Bus_Output(); // Порты шины на выход
LCD_DIR_CS_OUT(); LCD_DIR_RS_OUT(); LCD_DIR_RST_OUT(); LCD_DIR_WR_OUT(); LCD_DIR_RD_OUT(); // Пины управления на выход
LCD_SET_CS(); LCD_SET_RS(); LCD_SET_RST(); LCD_SET_WR(); LCD_SET_RD(); // Пины управления установить в 1
// Железный сброс дисплея
_delay_ms(10);
LCD_CLR_RST();
_delay_ms(10);
LCD_SET_RST();
_delay_ms(10);
// Выбрали дисплей
LCD_CLR_CS();
// Инициализируем дисплей
switch(display_model)
{
  case SSD1289:
#ifdef SSD1289
  lcd_param.disp_x_size = 239;
  lcd_param.disp_y_size = 319;
  lcd_param.model = display_model;
  lcd_param.orient = orientacia;
  lcd_param._transparent = 0;
  lcd_param.transfer_mode = TRANSFER_MODE_16;
  #include "drivers/SSD1289/initlcd.h"
#endif
  break;
  case ILI1920:
#ifdef ILI1920
  lcd_param.disp_x_size = 239;
  lcd_param.disp_y_size = 319;
  lcd_param.model = display_model;
  lcd_param.orient = orientacia;
  lcd_param._transparent = 0;
  lcd_param.transfer_mode = TRANSFER_MODE_16;
  #include "drivers/ILI1920/initlcd.h"
#endif
  break;
  case ILI9481:
#ifdef ILI9481
  lcd_param.disp_x_size = 320;
  lcd_param.disp_y_size = 480;
  lcd_param.model = display_model;
  lcd_param.orient = orientacia;
  lcd_param._transparent = 0;
  lcd_param.transfer_mode = TRANSFER_MODE_16;
  #include "drivers/ILI9481/initlcd.h"
#endif
  break;

}
//========================================================================================================
LCD_SET_CS();
LCD_SetColor_RGB(255, 255, 255);
LCD_SetBackColor_RGB(0, 0, 0);
cfont.font = 0;
}
//========================================================================================================
// Отправка на дисплей комманды и данные
//========================================================================================================
void LCD_Write_COM_DATA(unsigned char commmand, int data)
{
LCD_Write_COM(commmand);
LCD_Write_DATA(data >> 8, data);
}
//========================================================================================================
// Отправка на дисплей комманды
//========================================================================================================
void LCD_Write_COM(unsigned char VL)
{
LCD_CLR_RS();
LCD_Write_Bus(0x00, VL);
}
//========================================================================================================
// Отправка на дисплей данные (старший и младший байт)
//========================================================================================================
void LCD_Write_DATA(unsigned char VH, unsigned char VL)
{
LCD_SET_RS();
LCD_Write_Bus(VH, VL);
}
//========================================================================================================
// Отправка на дисплей данные (младший байт)
//========================================================================================================
void LCD_Write_DATA_1(unsigned char VL)
{
LCD_SET_RS();
LCD_Write_Bus(0x00, VL);
}
//========================================================================================================
// Запись в шину данных дисплея
//========================================================================================================
void LCD_Write_Bus(unsigned char VH, unsigned char VL)
{
LCD_HI_PORT = VH;
LCD_LO_PORT = VL;
asm("nop");
PULSE_WR_LOW();
asm("nop");
}
//========================================================================================================
void LCD_SetColor_RGB(unsigned char r, unsigned char g, unsigned char b)
{
lcd_param.fnt_color_h = ((r & 248) | g >> 5);
lcd_param.fnt_color_l = ((g & 28) << 3 | b >> 3);

}
//========================================================================================================
void LCD_SetColor_Word(unsigned int color)
{
lcd_param.fnt_color_h = (color >> 8);
lcd_param.fnt_color_l = (color & 0xFF);
}
//========================================================================================================
void LCD_SetBackColor_RGB(unsigned char r, unsigned char g, unsigned char b)
{
lcd_param.bg_color_h = ((r & 248) | g >> 5);
lcd_param.bg_color_l = ((g & 28) << 3 | b >> 3);
lcd_param._transparent = 0;
}
//========================================================================================================
void LCD_SetBackColor_Word(uint32_t color)
{
if (color == VGA_TRANSPARENT)
{
  lcd_param._transparent = 1;
} else {
  lcd_param.bg_color_h = (color >> 8);
  lcd_param.bg_color_l = (color & 0xFF);
  lcd_param._transparent = 0;
}
}
//========================================================================================================
unsigned int LCD_GetColor(void)
{
return (lcd_param.fnt_color_h << 8) | lcd_param.fnt_color_l;
}
//========================================================================================================
unsigned int LCD_GetBackColor(void)
{
return (lcd_param.bg_color_h << 8) | lcd_param.bg_color_l;
}
//========================================================================================================
void LCD_SetXY(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
if (lcd_param.orient == LANDSCAPE)
{
  swap(unsigned int, x1, y1);
  swap(unsigned int, x2, y2)
  y1 = lcd_param.disp_y_size - y1;
  y2 = lcd_param.disp_y_size - y2;
  swap(unsigned int, y1, y2)
}
switch(lcd_param.model)
{
  case SSD1289:
#ifdef SSD1289
  #include "drivers/SSD1289/setxy.h"
#endif
  break;
  case ILI1920:
#ifdef ILI1920
  #include "drivers/ILI1920/setxy.h"
#endif
  break;
#ifdef ILI9481
  #include "drivers/ILI9481/setxy.h"
#endif
break;

}
}
//========================================================================================================
void LCD_ClrXY(void)
{
if (lcd_param.orient == PORTRAIT)
{
  LCD_SetXY(0, 0, lcd_param.disp_x_size, lcd_param.disp_y_size);
} else {
  LCD_SetXY(0, 0, lcd_param.disp_y_size, lcd_param.disp_x_size);
}
}
//========================================================================================================
void LCD_ClrScreen(void)
{
unsigned int i;
LCD_CLR_CS();
LCD_ClrXY();
LCD_SET_RS();
if (lcd_param.transfer_mode == TRANSFER_MODE_16)
{
  _fast_fill_16(0,0, ((lcd_param.disp_x_size + 1) * (lcd_param.disp_y_size + 1)));
} else if (lcd_param.transfer_mode == 8) {
  _fast_fill_8(0,((lcd_param.disp_x_size + 1) * (lcd_param.disp_y_size + 1)));
} else {
  for (i = 0; i < ((lcd_param.disp_x_size + 1) * (lcd_param.disp_y_size + 1)); i++)
  {
	LCD_Write_Bus(0,0);
  }
}
LCD_SET_CS();
}
//========================================================================================================
void LCD_FillScreen_RGB(unsigned char r, unsigned char g, unsigned char b)
{
unsigned int color;
color = ((r & 248) << 8 | (g & 252) << 3 | (b & 248) >> 3);
LCD_FillScreen(color);
}
//========================================================================================================
void LCD_FillScreen(unsigned int color)
{
unsigned int i;
unsigned char ch, cl;
ch = (unsigned char)(color >> 8);
cl = (unsigned char)(color & 0xFF);
LCD_CLR_CS();
LCD_ClrXY();
LCD_SET_RS();
if (lcd_param.transfer_mode == TRANSFER_MODE_16)
{
  _fast_fill_16(ch,cl, ((lcd_param.disp_x_size + 1) * (lcd_param.disp_y_size + 1)));
} else if ((lcd_param.transfer_mode == 8) && (ch == cl)) {
  _fast_fill_8(ch,((lcd_param.disp_x_size + 1) * (lcd_param.disp_y_size + 1)));
} else {
  for (i = 0; i < ((lcd_param.disp_x_size + 1) * (lcd_param.disp_y_size + 1)); i++)
  {
	LCD_Write_Bus(ch,cl);
  }
}
LCD_SET_CS();
}
//========================================================================================================
void LCD_SetPixel(unsigned int color)
{
LCD_Write_DATA((color >> 8),(color & 0xFF));
}
//========================================================================================================
void LCD_DrawPixel(unsigned int x, unsigned int y)
{
LCD_CLR_CS();
LCD_SetXY(x, y, x, y);
LCD_SetPixel((lcd_param.fnt_color_h << 8) | lcd_param.fnt_color_l);
LCD_ClrXY();
LCD_SET_CS();
}
//========================================================================================================
void LCD_DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
int dx, dy, xstep, ystep, col, row, t;
if (y1 == y2) {
  LCD_DrawHLine(x1, y1, x2 - x1);
} else if (x1 == x2) {
  LCD_DrawVLine(x1, y1, y2 - y1);
} else {
  dx = (x2 > x1 ? x2 - x1 : x1 - x2);
  xstep =  x2 > x1 ? 1 : -1;
  dy = (y2 > y1 ? y2 - y1 : y1 - y2);
  ystep =  y2 > y1 ? 1 : -1;
  col = x1; 
  row = y1;
  LCD_CLR_CS();
  if (dx < dy)
  {
    t = - (dy >> 1);
	while (1)
	{
      LCD_SetXY(col,row,col,row);
 	  LCD_Write_DATA (lcd_param.fnt_color_h, lcd_param.fnt_color_l);
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
  }	else {
    t = - (dx >> 1);
	while (1)
	{
      LCD_SetXY(col,row,col,row);
 	  LCD_Write_DATA (lcd_param.fnt_color_h, lcd_param.fnt_color_l);
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
  LCD_SET_CS();
}
LCD_ClrXY();
}
//========================================================================================================
void LCD_DrawHLine(unsigned int x, unsigned int y, unsigned int l)
{
unsigned int i;
if (l < 0)
{
  l = -l;
  x -= l;
}
LCD_CLR_CS();
LCD_SetXY(x, y, x + l, y);
if (lcd_param.transfer_mode == TRANSFER_MODE_16)
{
  LCD_SET_RS();
  _fast_fill_16(lcd_param.fnt_color_h, lcd_param.fnt_color_l, l);
} else if ((lcd_param.transfer_mode == TRANSFER_MODE_8) && (lcd_param.fnt_color_h == lcd_param.fnt_color_l)) {
  LCD_SET_RS();
  _fast_fill_8(lcd_param.fnt_color_h, l);
} else {
  for (i = 0; i < l + 1; i++)
  {
	LCD_Write_DATA(lcd_param.fnt_color_h, lcd_param.fnt_color_l);
  }
}
LCD_SET_CS();
LCD_ClrXY();
}
//========================================================================================================
void LCD_DrawVLine(unsigned int x, unsigned int y, unsigned int l)
{
unsigned int i;
if (l < 0)
{
  l = -l;
  y -= l;
}
LCD_CLR_CS();
LCD_SetXY(x, y, x, y + l);
if (lcd_param.transfer_mode == TRANSFER_MODE_16)
{
  LCD_SET_RS();
  _fast_fill_16(lcd_param.fnt_color_h, lcd_param.fnt_color_l, l);
} else if ((lcd_param.transfer_mode == TRANSFER_MODE_8) && (lcd_param.fnt_color_h == lcd_param.fnt_color_l)) {
  LCD_SET_RS();
  _fast_fill_8(lcd_param.fnt_color_h, l);
} else {
  for (i = 0; i < l + 1; i++)
  {
	LCD_Write_DATA(lcd_param.fnt_color_h, lcd_param.fnt_color_l);
  }
}
LCD_SET_CS();
LCD_ClrXY();
}
//========================================================================================================
void LCD_Lcd_Off(void)
{
LCD_CLR_CS();
LCD_SET_CS();
}
//========================================================================================================
void LCD_Lcd_On(void)
{
LCD_CLR_CS();
LCD_SET_CS();
}
//========================================================================================================
void LCD_SetContrast(unsigned char c)
{
LCD_CLR_CS();
LCD_SET_CS();
}
//========================================================================================================
unsigned int LCD_GetDisplayXSize(void)
{
if (lcd_param.orient == PORTRAIT)
{
  return lcd_param.disp_x_size + 1;
} else {
  return lcd_param.disp_y_size + 1;
}
}
//========================================================================================================
unsigned int LCD_GetDisplayYSize(void)
{
if (lcd_param.orient == PORTRAIT)
{
  return lcd_param.disp_y_size + 1;
} else {
  return lcd_param.disp_x_size + 1;
}
}
//========================================================================================================
void LCD_DrawRect(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
if (x1 > x2)
{
  swap(unsigned int, x1, x2);
}
if ( y1 > y2)
{
  swap(unsigned int, y1, y2);
}
LCD_DrawHLine(x1, y1, x2 - x1);
LCD_DrawHLine(x1, y2, x2 - x1);
LCD_DrawVLine(x1, y1, y2 - y1);
LCD_DrawVLine(x2, y1, y2 - y1);
}
//========================================================================================================
void LCD_DrawRoundRect(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
if (x1 > x2)
{
  swap(unsigned int, x1, x2);
}
if ( y1 > y2)
{
  swap(unsigned int, y1, y2);
}
if ((x2 - x1) > 4 && (y2 - y1) > 4)
{
  LCD_DrawPixel(x1 + 1,y1 + 1);
  LCD_DrawPixel(x2 - 1,y1 + 1);
  LCD_DrawPixel(x1 + 1,y2 - 1);
  LCD_DrawPixel(x2 - 1,y2 - 1);
  LCD_DrawHLine(x1 + 2, y1, x2 - x1 - 4);
  LCD_DrawHLine(x1 + 2, y2, x2 - x1 - 4);
  LCD_DrawVLine(x1, y1 + 2, y2 - y1 - 4);
  LCD_DrawVLine(x2, y1 + 2, y2 - y1 - 4);
}
}
//========================================================================================================
void LCD_FillRect(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
unsigned int i;
if (x1 > x2)
{
  swap(unsigned int, x1, x2);
}
if ( y1 > y2)
{
  swap(unsigned int, y1, y2);
}
if (lcd_param.transfer_mode == TRANSFER_MODE_16) {
  LCD_CLR_CS();
  LCD_SetXY(x1, y1, x2, y2);
  LCD_SET_RS();
  _fast_fill_16(lcd_param.fnt_color_h, lcd_param.fnt_color_l, ((unsigned long)(x2 - x1) + 1) * ((unsigned long)(y2 - y1) + 1));
  LCD_SET_CS();
} else if ((lcd_param.transfer_mode == TRANSFER_MODE_8) && (lcd_param.fnt_color_h == lcd_param.fnt_color_l)) {
  LCD_CLR_CS();
  LCD_SetXY(x1, y1, x2, y2);
  LCD_SET_RS();
  _fast_fill_8(lcd_param.fnt_color_h,((unsigned long)(x2 - x1) + 1) * ((unsigned long)(y2 - y1) + 1));
  LCD_SET_CS();
} else {
  if (lcd_param.orient == PORTRAIT)
  {
	for (i = 0; i < ((y2 - y1) / 2) + 1; i++)
	{
	  LCD_DrawHLine(x1, y1 + i, x2 - x1);
	  LCD_DrawHLine(x1, y2 - i, x2 - x1);
	}
  }	else {
	for (i = 0; i < ((x2 - x1) / 2) + 1; i++)
	{
	  LCD_DrawVLine(x1 + i, y1, y2 - y1);
	  LCD_DrawVLine(x2 - i, y1, y2 - y1);
	}
  }
}
}
//========================================================================================================
void LCD_FillRoundRect(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
{
unsigned int i;
if (x1 > x2)
{
  swap(unsigned int, x1, x2);
}
if ( y1 > y2)
{
  swap(unsigned int, y1, y2);
}
if ((x2 - x1) > 4 && (y2 - y1) > 4)
{
  for (i = 0; i < ((y2 - y1) / 2) + 1; i++)
  {
	switch(i)
	{
   	  case 0:
		LCD_DrawHLine(x1 + 2, y1 + i, x2 - x1 - 4);
		LCD_DrawHLine(x1 + 2, y2 - i, x2 - x1 - 4);
	  break;
	  case 1:
		LCD_DrawHLine(x1 + 1, y1 + i, x2 - x1 - 2);
		LCD_DrawHLine(x1 + 1, y2 - i, x2 - x1 - 2);
	  break;
	  default:
		LCD_DrawHLine(x1, y1 + i, x2 - x1);
		LCD_DrawHLine(x1, y2 - i, x2 - x1);
	}
  }
}
}
//========================================================================================================
void LCD_DrawCircle(int x, int y, int radius)
{
int f = 1 - radius;
int ddF_x = 1;
int ddF_y = -2 * radius;
int x1 = 0;
int y1 = radius;
LCD_CLR_CS();
LCD_SetXY(x, y + radius, x, y + radius);
LCD_Write_DATA(lcd_param.fnt_color_h, lcd_param.fnt_color_l);
LCD_SetXY(x, y - radius, x, y - radius);
LCD_Write_DATA(lcd_param.fnt_color_h, lcd_param.fnt_color_l);
LCD_SetXY(x + radius, y, x + radius, y);
LCD_Write_DATA(lcd_param.fnt_color_h, lcd_param.fnt_color_l);
LCD_SetXY(x - radius, y, x - radius, y);
LCD_Write_DATA(lcd_param.fnt_color_h, lcd_param.fnt_color_l);
while(x1 < y1)
{
  if (f >= 0) {
	y1--;
	ddF_y += 2;
	f += ddF_y;
  }
  x1++;
  ddF_x += 2;
  f += ddF_x;    
  LCD_SetXY(x + x1, y + y1, x + x1, y + y1);
  LCD_Write_DATA(lcd_param.fnt_color_h, lcd_param.fnt_color_l);
  LCD_SetXY(x - x1, y + y1, x - x1, y + y1);
  LCD_Write_DATA(lcd_param.fnt_color_h, lcd_param.fnt_color_l);
  LCD_SetXY(x + x1, y - y1, x + x1, y - y1);
  LCD_Write_DATA(lcd_param.fnt_color_h, lcd_param.fnt_color_l);
  LCD_SetXY(x - x1, y - y1, x - x1, y - y1);
  LCD_Write_DATA(lcd_param.fnt_color_h, lcd_param.fnt_color_l);
  LCD_SetXY(x + y1, y + x1, x + y1, y + x1);
  LCD_Write_DATA(lcd_param.fnt_color_h, lcd_param.fnt_color_l);
  LCD_SetXY(x - y1, y + x1, x - y1, y + x1);
  LCD_Write_DATA(lcd_param.fnt_color_h, lcd_param.fnt_color_l);
  LCD_SetXY(x + y1, y - x1, x + y1, y - x1);
  LCD_Write_DATA(lcd_param.fnt_color_h, lcd_param.fnt_color_l);
  LCD_SetXY(x - y1, y - x1, x - y1, y - x1);
  LCD_Write_DATA(lcd_param.fnt_color_h, lcd_param.fnt_color_l);
}
LCD_SET_CS();
LCD_ClrXY();
}
//========================================================================================================
void LCD_FillCircle(int x, int y, int radius)
{
int x1, y1;
for (y1 =- radius; y1 <= 0; y1++) 
{
  for (x1 =- radius; x1 <= 0; x1++)
  {
	if(x1 * x1 + y1 * y1 <= radius * radius) {
	  LCD_DrawHLine(x + x1, y + y1, 2 * (-x1));
	  LCD_DrawHLine(x + x1, y - y1, 2 * (-x1));
  	  break;
	}
  }
}
}
//========================================================================================================
void LCD_SetFont(const uint8_t* font)
{
cfont.font = font;
cfont.x_size = fontbyte(0);
cfont.y_size = fontbyte(1);
cfont.offset = fontbyte(2);
cfont.numchars = fontbyte(3);
}
//========================================================================================================
uint8_t* LCD_GetFont(void)
{
return cfont.font;
}
//========================================================================================================
uint8_t LCD_GetFontXsize(void)
{
return cfont.x_size;
}
//========================================================================================================
uint8_t LCD_GetFontYsize(void)
{
return cfont.y_size;
}
//========================================================================================================
void LCD_DrawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int scale)
{
int col;
int tx, ty, tc, tsx, tsy;
if (scale == 1){
  if (lcd_param.orient == PORTRAIT)	{
    LCD_CLR_CS();
    LCD_SetXY(x, y, x + sx - 1, y + sy - 1);
	for (tc = 0; tc < (sx * sy); tc++)
	{
	  col = pgm_read_word(&data[tc]);
	  LCD_Write_DATA(col >> 8, col & 0xff);
	}
    LCD_SET_CS();
  }	else {
    LCD_CLR_CS();
	for (ty=0; ty<sy; ty++)
	{
	  LCD_SetXY(x, y + ty, x + sx - 1, y + ty);
	  for (tx = sx - 1; tx >= 0; tx--)
 	  {
		col = pgm_read_word(&data[(ty * sx) + tx]);
		LCD_Write_DATA(col >> 8,col & 0xff);
 	  }
	}
    LCD_SET_CS();
  }
} else {
  if (lcd_param.orient == PORTRAIT)	{
    LCD_CLR_CS();
	for (ty = 0; ty < sy; ty++)
	{
	  LCD_SetXY(x, y + (ty * scale), x + ((sx * scale) - 1), y + (ty * scale) + scale);
	  for (tsy = 0; tsy < scale; tsy++)
		for (tx=0; tx<sx; tx++)
		{
		  col = pgm_read_word(&data[(ty*sx)+tx]);
		  for (tsx = 0; tsx < scale; tsx++)
			LCD_Write_DATA(col>>8,col & 0xff);
		}
	}
    LCD_SET_CS();
} else {
  LCD_CLR_CS();
  for (ty = 0; ty < sy; ty++)
  {
	for (tsy = 0; tsy < scale; tsy++)
	{
	  LCD_SetXY(x, y + (ty * scale) + tsy, x + ((sx * scale) - 1), y + (ty * scale) + tsy);
	  for (tx = sx - 1; tx >= 0; tx--)
	  {
		col = pgm_read_word(&data[(ty * sx) + tx]);
		for (tsx = 0; tsx < scale; tsx++)
		LCD_Write_DATA(col >> 8,col & 0xff);
	  }
	}
  }
  LCD_SET_CS();
}
}
LCD_ClrXY();
}
//========================================================================================================
void LCD_DrawBitmap_1(int x, int y, int sx, int sy, bitmapdatatype data, int deg, int rox, int roy)
{
int col;
int tx, ty, newx, newy;
double radian;
radian = deg * 0.0175;  
if (deg == 0) {
  LCD_DrawBitmap(x, y, sx, sy, data, 0);
} else {
  LCD_CLR_CS();
  for (ty = 0; ty < sy; ty++)
	for (tx = 0; tx < sx; tx++)
	{
	  col = pgm_read_word(&data[(ty*sx)+tx]);
	  newx = x + rox + (((tx - rox) * cos(radian)) - ((ty - roy) * sin(radian)));
	  newy = y + roy + (((ty - roy) * cos(radian)) + ((tx - rox) * sin(radian)));
	  LCD_SetXY(newx, newy, newx, newy);
	  LCD_Write_DATA(col >> 8,col & 0xff);
	}
    LCD_SET_CS();
}
LCD_ClrXY();
}
//========================================================================================================
void LCD_Char(unsigned char c, int x, int y)
{
unsigned char i,ch;
int zz, j, temp; 
LCD_CLR_CS();
if (!lcd_param._transparent) {
  if (lcd_param.orient == PORTRAIT)	{
	LCD_SetXY(x,y,x + cfont.x_size - 1,y + cfont.y_size - 1);
	temp = ((c - cfont.offset) * ((cfont.x_size / 8) * cfont.y_size)) + 4;
	for (j = 0;j < ((cfont.x_size / 8) * cfont.y_size); j++)
	{
	  ch = pgm_read_byte(&cfont.font[temp]);
	  for(i = 0; i < 8; i++)
	  {   
		if ((ch & (1<<(7 - i))) != 0) {
		  LCD_SetPixel((lcd_param.fnt_color_h << 8) | lcd_param.fnt_color_l);
		} else {
		  LCD_SetPixel((lcd_param.bg_color_h << 8) | lcd_param.bg_color_l);
		}   
	  }
	  temp++;
	}
  }	else {
	temp = ((c - cfont.offset) * ((cfont.x_size / 8) * cfont.y_size)) + 4;
	for (j = 0; j < ((cfont.x_size / 8) * cfont.y_size); j += (cfont.x_size / 8))
	{
	  LCD_SetXY(x,y + (j / (cfont.x_size / 8)), x + cfont.x_size - 1,y + (j / (cfont.x_size / 8)));
	  for (zz = (cfont.x_size / 8) - 1; zz >= 0; zz--)
	  {
		ch = pgm_read_byte(&cfont.font[temp+zz]);
		for ( i = 0;i < 8; i++)
		{   
		  if ((ch & (1<<i)) != 0) {
		    LCD_SetPixel((lcd_param.fnt_color_h << 8) | lcd_param.fnt_color_l);
		  }	else {
		    LCD_SetPixel((lcd_param.bg_color_h << 8) | lcd_param.bg_color_l);
		}   
	  }
	}
	temp += (cfont.x_size / 8);
  }
}
} else {
  temp = ((c - cfont.offset) * ((cfont.x_size / 8) * cfont.y_size)) + 4;
  for (j = 0;j < cfont.y_size;j++)
  {
	for (zz = 0; zz < (cfont.x_size / 8); zz++)
	{
	  ch = pgm_read_byte(&cfont.font[temp + zz]); 
	  for (i = 0; i < 8; i++)
	  {   
		LCD_SetXY(x + i + (zz * 8),y + j,x + i + (zz * 8) + 1,y + j + 1);
		if ((ch&(1 << (7 - i))) != 0)   
		{
		  LCD_SetPixel((lcd_param.fnt_color_h << 8) | lcd_param.fnt_color_l);
		} 
	  }
	}
	temp += (cfont.x_size / 8);
  }
}
LCD_SET_CS();
LCD_ClrXY();
}
//========================================================================================================
void LCD_RotateChar(unsigned char c, int x, int y, int pos, int deg)
{
unsigned char i, j, ch;
int temp, zz; 
int newx, newy;
double radian;
radian = deg * 0.0175;  
LCD_CLR_CS();
temp = ((c - cfont.offset) * ((cfont.x_size / 8) * cfont.y_size)) + 4;
for (j = 0; j < cfont.y_size; j++) 
{
  for (zz = 0; zz < (cfont.x_size / 8); zz++)
  {
	ch = pgm_read_byte(&cfont.font[temp + zz]); 
	for (i = 0; i < 8; i++)
	{   
	  newx = x + (((i + (zz * 8) + (pos * cfont.x_size))* cos(radian))- ((j) * sin(radian)));
	  newy = y + (((j) * cos(radian)) + ((i + (zz * 8) + (pos * cfont.x_size)) * sin(radian)));
	  LCD_SetXY(newx, newy, newx + 1,newy + 1);
	  if ((ch & (1 << (7 - i))) != 0)   
	  {
		LCD_SetPixel((lcd_param.fnt_color_h << 8) | lcd_param.fnt_color_l);
	  }	else {
		if (!lcd_param._transparent)
		  LCD_SetPixel((lcd_param.bg_color_h << 8) | lcd_param.bg_color_l);
	  }   
	}
  }
  temp += (cfont.x_size / 8);
}
LCD_SET_CS();
LCD_ClrXY();
}
//========================================================================================================
void LCD_Text(char *st, int x, int y, int deg)
{
int stl, i;
stl = strlen(st);
if (lcd_param.orient == PORTRAIT) {
  if (x == RIGHT) {	x = (lcd_param.disp_x_size + 1) - (stl * cfont.x_size); }
  if (x == CENTER) { x = ((lcd_param.disp_x_size + 1) - (stl * cfont.x_size)) / 2; }
} else {
  if (x == RIGHT) {	x = (lcd_param.disp_y_size + 1) - (stl * cfont.x_size); }
  if (x == CENTER) { x = ((lcd_param.disp_y_size + 1) - (stl * cfont.x_size)) / 2; }
}
for (i = 0; i < stl; i++)
{
  if (deg == 0)
	LCD_Char(*st++, x + (i * (cfont.x_size)), y);
  else
	LCD_RotateChar(*st++, x, y, i, deg);
}
}
//========================================================================================================
void LCD_PrintNumI(long num, int x, int y, int length, char filler)
{
char buf[25];
char st[27];
unsigned char neg = 0;
int c = 0, f = 0, i;

if (num == 0)
{
  if (length != 0)
  {
	for (c = 0; c < (length - 1); c++)
	{
 	  st[c] = filler;
	  st[c] = 48;
	  st[c + 1] = 0;
    }
  }	else {
	st[0] = 48;
	st[1] = 0;
  }
} else {
  if (num < 0)
  {
	neg = 1;
	num = -num;
  }
  while (num > 0)
  {
	buf[c] = 48 + (num % 10);
	c++;
	num = (num - (num % 10)) / 10;
  }
  buf[c] = 0;
  if (neg == 1)
  {
	st[0] = 45;
  }
  if (length > (c + neg))
  {
	for (i = 0; i < (length - c - neg); i++)
	{
	  st[i + neg] = filler;
 	  f++;
	}
  }
  for (i = 0; i < c; i++)
  {
	st[i + neg + f] = buf[c - i - 1];
  }
  st[c + neg + f] = 0;
}
LCD_Text(st, x, y, 0);
}
//========================================================================================================
void LCD_PrintNumF(double num, unsigned char dec, int x, int y, char divider, int length, char filler)
{
char st[27];
unsigned char neg = 0;
int i;
if (dec < 1)
  dec = 1;
else if (dec > 5)
  dec = 5;
if (num < 0)
  neg = 1;
_convert_float(st, num, length, dec);
if (divider != '.')
{
  for (i = 0; i < sizeof(st); i++)
	if (st[i] == '.')
	  st[i] = divider;
}
if (filler != ' ')
{
  if (neg == 1)
  {
	st[0] = '-';
	for (i = 1; i < sizeof(st); i++)
	  if ((st[i] == ' ') || (st[i] == '-'))
		st[i] = filler;
  }	else {
	for (i = 0; i < sizeof(st); i++)
	  if (st[i] == ' ')
		st[i] = filler;
  }
}
LCD_Text(st, x, y, 0);
}
//========================================================================================================
//========================================================================================================
//========================================================================================================
//========================================================================================================
//========================================================================================================
void _convert_float(char *buf, double num, int width, unsigned char prec)
{
dtostrf(num, width, prec, buf);
}
//========================================================================================================
void _fast_fill_16(unsigned int ch, unsigned int cl, unsigned long pix)
{
unsigned long blocks;
unsigned int i;
LCD_HI_PORT = ch;
LCD_LO_PORT = cl;
blocks = pix / 16;
for (i = 0; i < blocks; i++)
{
  PULSE_WR_LOW();
  PULSE_WR_LOW();
  PULSE_WR_LOW();
  PULSE_WR_LOW();
  PULSE_WR_LOW();
  PULSE_WR_LOW();
  PULSE_WR_LOW();
  PULSE_WR_LOW();
  PULSE_WR_LOW();
  PULSE_WR_LOW();
  PULSE_WR_LOW();
  PULSE_WR_LOW();
  PULSE_WR_LOW();
  PULSE_WR_LOW();
  PULSE_WR_LOW();
  PULSE_WR_LOW();
}
if ((pix % 16) != 0)
{
  for (i = 0; i < (pix % 16) + 1; i++)
  {
    PULSE_WR_LOW();
  }
}
}
//========================================================================================================
void _fast_fill_8(unsigned int ch, unsigned long pix)
{
unsigned long blocks;
unsigned int i;
LCD_HI_PORT = ch;
blocks = pix / 16;
for (i = 0; i < blocks; i++)
{
  PULSE_WR_LOW(); PULSE_WR_LOW();
  PULSE_WR_LOW(); PULSE_WR_LOW();
  PULSE_WR_LOW(); PULSE_WR_LOW();
  PULSE_WR_LOW(); PULSE_WR_LOW();
  PULSE_WR_LOW(); PULSE_WR_LOW();
  PULSE_WR_LOW(); PULSE_WR_LOW();
  PULSE_WR_LOW(); PULSE_WR_LOW();
  PULSE_WR_LOW(); PULSE_WR_LOW();
  PULSE_WR_LOW(); PULSE_WR_LOW();
  PULSE_WR_LOW(); PULSE_WR_LOW();
  PULSE_WR_LOW(); PULSE_WR_LOW();
  PULSE_WR_LOW(); PULSE_WR_LOW();
  PULSE_WR_LOW(); PULSE_WR_LOW();
  PULSE_WR_LOW(); PULSE_WR_LOW();
  PULSE_WR_LOW(); PULSE_WR_LOW();
  PULSE_WR_LOW(); PULSE_WR_LOW();
}
if ((pix % 16) != 0)
{
  for (i = 0; i < (pix % 16) + 1; i++)
  {
    PULSE_WR_LOW(); PULSE_WR_LOW();
  }
}
}
//========================================================================================================
