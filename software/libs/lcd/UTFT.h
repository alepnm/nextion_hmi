#ifndef UTFT_h
#define UTFT_h
//========================================================================================================
#define UTFT_VERSION	 1.0
//========================================================================================================
// Port UTFT LCD defines
//========================================================================================================
#define LCD_LO_DDR   	 PORTA
#define LCD_LO_PORT  	 PORTA
#define LCD_LO_PIN   	 PORTA

#define LCD_HI_DDR   	 PORTC
#define LCD_HI_PORT  	 PORTC
#define LCD_HI_PIN   	 PORTC


#define LCD_WR_DDR   	 PORTD
#define LCD_WR_PORT  	 PORTD
#define LCD_WR_PIN   	 PORTD
#define LCD_WR_BIT   	 0
 
#define LCD_RS_DDR   	 PORTD
#define LCD_RS_PORT  	 PORTD
#define LCD_RS_PIN   	 PORTD
#define LCD_RS_BIT   	 1 

#define LCD_RST_DDR  	 PORTD
#define LCD_RST_PORT 	 PORTD
#define LCD_RST_PIN  	 PORTD
#define LCD_RST_BIT  	 2

#define LCD_CS_DDR   	 PORTD
#define LCD_CS_PORT  	 PORTD
#define LCD_CS_PIN   	 PORTD
#define LCD_CS_BIT   	 3
 
#define LCD_RD_DDR   	 PORTD
#define LCD_RD_PORT  	 PORTD
#define LCD_RD_PIN   	 PORTD
#define LCD_RD_BIT   	 4 
 
//===========================================================================================
// Routines UTFT pins display
//========================================================================================================
#define LCD_Bus_Input()	      { LCD_LO_DDR = 0x00; LCD_HI_DDR = 0x00; } // LCD Bus as input
#define LCD_Bus_Output()      { LCD_LO_DDR = 0xFF; LCD_HI_DDR = 0xFF; LCD_LO_PORT = 0xFF; LCD_HI_PORT = 0xFF; } // LCD Bus as output
 
#define LCD_SET_DBH	      LCD_HI_PORT 
#define LCD_SET_DBL	      LCD_LO_PORT 
 
#define LCD_GET_DBH()     LCD_HI_PIN 
#define LCD_GET_DBL()     LCD_LO_PIN 
 
#define LCD_SET_CS()      LCD_CS_PORT |=   1<<LCD_CS_BIT 
#define LCD_CLR_CS()      LCD_CS_PORT &= ~(1<<LCD_CS_BIT) 
#define LCD_DIR_CS_OUT()  LCD_CS_DDR |=   1<<LCD_CS_BIT 
#define LCD_DIR_CS_IN()   LCD_CS_DDR &= ~(1<<LCD_CS_BIT) 
 
#define LCD_SET_RS()      LCD_RS_PORT |=   1<<LCD_RS_BIT 
#define LCD_CLR_RS()      LCD_RS_PORT &= ~(1<<LCD_RS_BIT) 
#define LCD_DIR_RS_OUT()  LCD_RS_DDR |=   1<<LCD_RS_BIT 
#define LCD_DIR_RS_IN()   LCD_RS_DDR &= ~(1<<LCD_RS_BIT) 
 
#define LCD_SET_WR()      LCD_WR_PORT |=   1<<LCD_WR_BIT 
#define LCD_CLR_WR()      LCD_WR_PORT &= ~(1<<LCD_WR_BIT) 
#define LCD_DIR_WR_OUT()  LCD_WR_DDR |=   1<<LCD_WR_BIT 
#define LCD_DIR_WR_IN()   LCD_WR_DDR &= ~(1<<LCD_WR_BIT) 
 
#define LCD_SET_RD()      LCD_RD_PORT |=   1<<LCD_RD_BIT 
#define LCD_CLR_RD()      LCD_RD_PORT &= ~(1<<LCD_RD_BIT) 
#define LCD_DIR_RD_OUT()  LCD_RD_DDR |=   1<<LCD_RD_BIT 
#define LCD_DIR_RD_IN()   LCD_RD_DDR &= ~(1<<LCD_RD_BIT) 
 
#define LCD_SET_RST()     LCD_RST_PORT |=  1<<LCD_RST_BIT 
#define LCD_CLR_RST()     LCD_RST_PORT &= ~(1<<LCD_RST_BIT) 
#define LCD_DIR_RST_OUT() LCD_RST_DDR |=  1<<LCD_RST_BIT 
#define LCD_DIR_RST_IN()  LCD_RST_DDR &= ~(1<<LCD_RST_BIT) 
//===========================================================================================
#define PULSE_WR_LOW()  LCD_CLR_WR(); asm("nop");  LCD_SET_WR();
#define PULSE_WR_HIGH() LCD_SET_WR(); asm("nop");  LCD_CLR_WR();
//===========================================================================================
#define LEFT			  0
#define RIGHT 			  9999
#define CENTER 			  9998
//===========================================================================================
#define PORTRAIT 		  0
#define LANDSCAPE 		  1
//===========================================================================================
// Модели дисплеев
//===========================================================================================
#define YX32B			  2 // Мой дисплей
#define ITDB32S			  2	// SSD1289  (16bit)
#define TFT01_32		  2	// SSD1289  (16bit)
#define CTE32			  2	// SSD1289  (16bit)
#define GEEE28			  1	// ILI9320	(16bit)
//===========================================================================================
// Контроллеры на которых построен модуль дисплея
//===========================================================================================
#define ILI1920		 	  1
#define SSD1289		 	  2
#define ILI9481		 	  3
//===========================================================================================
// UTFT VGA color palette
//========================================================================================================
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
//===========================================================================================
#define swap(type, i, j) { type t = i; i = j; j = t; }
//===========================================================================================
#define TRANSFER_MODE_16	0
#define TRANSFER_MODE_8		1
#define TRANSFER_MODE_OTHER	2
//===========================================================================================
// Структура описания фонта
//===========================================================================================
typedef struct _current_font
{
  const uint8_t* font;     // Указатель на фонт
  uint8_t x_size;    // Размер по горизонтали
  uint8_t y_size;    // Размер по вертикали
  uint8_t offset;    // Межбуквенное расстояние
  uint8_t numchars;  // Количество символов
} _current_font;

extern _current_font cfont;

//===========================================================================================
// Структура описания параметров
//===========================================================================================
typedef struct _lcd_param
{
  uint8_t model;     		 // Модель дисплея
  uint8_t orient;    		 // Ориентация дисплея (Портрет или Альбом)
  unsigned long	disp_x_size; // Размер экрана по горизонтали
  unsigned long	disp_y_size; // Размер экрана по вертикали
  uint8_t _transparent;      // Вкл/Выкл прозрачность
  uint8_t fnt_color_h;       // Цвет фонта старший байт
  uint8_t fnt_color_l;       // Цвет фонта младший байт
  uint8_t bg_color_h;        // Цвет фона старший байт
  uint8_t bg_color_l;        // Цвет фона младший байт
  uint8_t transfer_mode;     // Метод заполнения области экрана
} _lcd_param;

extern _lcd_param lcd_param;

#define fontbyte(x) pgm_read_byte(&cfont.font[x])  
#define bitmapdatatype unsigned int*

//===========================================================================================
// Functions prototype defines
//===========================================================================================
void LCD_Init(unsigned char display_model,unsigned char orientacia);
void LCD_Write_COM_DATA(unsigned char commmand, int data);
void LCD_Write_COM(unsigned char VL);
void LCD_Write_DATA(unsigned char VH, unsigned char VL);
void LCD_Write_DATA_1(unsigned char VL);
void LCD_Write_Bus(unsigned char VH, unsigned char VL);
void LCD_SetColor_RGB(unsigned char r, unsigned char g, unsigned char b);
void LCD_SetColor_Word(unsigned int color);
void LCD_SetBackColor_RGB(unsigned char r, unsigned char g, unsigned char b);
void LCD_SetBackColor_Word(uint32_t color);
unsigned int LCD_GetColor(void);
unsigned int LCD_GetBackColor(void);
void LCD_SetXY(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_ClrXY(void);
void LCD_ClrScreen(void);
void LCD_FillScreen_RGB(unsigned char r, unsigned char g, unsigned char b);
void LCD_FillScreen(unsigned int color);
void LCD_SetPixel(unsigned int color);
void LCD_DrawPixel(unsigned int x, unsigned int y);
void LCD_DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_DrawHLine(unsigned int x, unsigned int y, unsigned int l);
void LCD_DrawVLine(unsigned int x, unsigned int y, unsigned int l);
void LCD_DrawRect(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_DrawRoundRect(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_DrawCircle(int x, int y, int radius);
void LCD_FillCircle(int x, int y, int radius);
void LCD_FillRect(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_FillRoundRect(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_Lcd_Off(void);
void LCD_Lcd_On(void);
void LCD_SetContrast(unsigned char c);
unsigned int LCD_GetDisplayXSize(void);
unsigned int LCD_GetDisplayYSize(void);
//===========================================================================================
void LCD_SetFont(const uint8_t* font);
uint8_t* LCD_GetFont(void);
uint8_t LCD_GetFontXsize(void);
uint8_t LCD_GetFontYsize(void);
void LCD_Char(unsigned char c, int x, int y);
void LCD_RotateChar(unsigned char c, int x, int y, int pos, int deg);
void LCD_Text(char *st, int x, int y, int deg);
//===========================================================================================
void LCD_DrawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int scale);
void LCD_DrawBitmap_1(int x, int y, int sx, int sy, bitmapdatatype data, int deg, int rox, int roy);
//===========================================================================================
// Вывод чисел
//===========================================================================================
void LCD_PrintNumI(long num, int x, int y, int length, char filler);
void LCD_PrintNumF(double num, unsigned char dec, int x, int y, char divider, int length, char filler);
//===========================================================================================
// Вспомогательные функции
//===========================================================================================
void _convert_float(char *buf, double num, int width, unsigned char prec);
void _fast_fill_16(unsigned int ch, unsigned int cl, unsigned long pix);
void _fast_fill_8(unsigned int ch, unsigned long pix);
//===========================================================================================
//===========================================================================================
//===========================================================================================
//===========================================================================================
#endif

