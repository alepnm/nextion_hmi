/*
 * TFT_ILI9481_UTFT.c
 *
 * Created: 06.04.2017 9:46:37
 *  Author: ldv
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <math.h>
//========================================================================================================
#include "UTFT.h"
#include "define_fonts.h"

int main(void)
{	
	
	DDRB = 0b00000001;		//PB0 выход (светодиод)
	PORTB |= _BV(PB0);		//зажечь
	_delay_ms(4000);
	PORTB &= ~_BV(PB0);	//погасить
	
	
	LCD_Init(ILI9481, LANDSCAPE);
	PORTB |= _BV(PB0);		//зажечь
	_delay_ms(1000);
	
	LCD_ClrScreen();
	LCD_SetFont(BigFont);
	LCD_SetColor_Word(VGA_WHITE);
	LCD_Text("Fill Screen",0,0,0);
	_delay_ms(1000);
	PORTB &= ~_BV(PB0);	//погасить
/*	
	LCD_ClrScreen(); // работает
	LCD_FillScreen(VGA_RED); // работает
	_delay_ms(500);
	LCD_FillScreen(VGA_GREEN); // работает
	_delay_ms(500);
	LCD_FillScreen(VGA_BLUE); // работает
	_delay_ms(500);
	LCD_FillScreen(VGA_YELLOW); // работает
	_delay_ms(500);
	
	LCD_ClrScreen(); // работает
	LCD_SetFont(BigFont); // работает
	LCD_SetColor_Word(VGA_WHITE); // работает
	LCD_Text("Fill Rect",0,0,0); // работает
	_delay_ms(1000);
	
	LCD_ClrScreen(); // работает
	LCD_SetColor_Word(VGA_RED); // работает
	LCD_SetBackColor_Word(VGA_BLACK); // работает
	LCD_FillRect(0,0,100,100); // работает
	LCD_SetColor_Word(VGA_WHITE); // работает
	LCD_FillRect(100,100,200,200); // работает
	LCD_SetColor_Word(VGA_GREEN); // работает
	LCD_FillRect(100,100,300,200); // работает
	LCD_SetColor_Word(VGA_YELLOW); // работает
	LCD_FillRect(170,180,240,200); // работает
	_delay_ms(1000);
	
	LCD_ClrScreen(); // работает
	LCD_SetFont(BigFont); // работает
	LCD_SetColor_Word(VGA_WHITE); // работает
	LCD_Text("Fill Round Rect",0,0,0); // работает
	_delay_ms(1000);

	LCD_ClrScreen(); // работает
	LCD_SetColor_Word(VGA_RED); // работает
	LCD_SetBackColor_Word(VGA_BLACK); // работает
	LCD_FillRoundRect(0,0,100,100); // работает
	LCD_SetColor_Word(VGA_WHITE); // работает
	LCD_FillRoundRect(100,100,200,200); // работает
	LCD_SetColor_Word(VGA_GREEN); // работает
	LCD_FillRoundRect(100,100,300,200); // работает
	LCD_SetColor_Word(VGA_YELLOW); // работает
	LCD_FillRoundRect(170,180,240,200); // работает
	_delay_ms(1000);
	
	LCD_ClrScreen(); // работает
	LCD_SetFont(BigFont); // работает
	LCD_SetColor_Word(VGA_WHITE); // работает
	LCD_Text("Draw Rect",0,0,0); // работает
	_delay_ms(1000);
	
	LCD_ClrScreen(); // работает
	LCD_SetColor_Word(VGA_RED); // работает
	LCD_SetBackColor_Word(VGA_BLACK); // работает
	LCD_DrawRect(0,0,100,100); // работает
	LCD_SetColor_Word(VGA_WHITE); // работает
	LCD_DrawRect(100,100,200,200); // работает
	LCD_SetColor_Word(VGA_GREEN); // работает
	LCD_DrawRect(100,100,300,200); // работает
	LCD_SetColor_Word(VGA_YELLOW); // работает
	LCD_DrawRect(170,180,240,200); // работает
	_delay_ms(1000);
	
	LCD_ClrScreen(); // работает
	LCD_SetFont(BigFont); // работает
	LCD_SetColor_Word(VGA_WHITE); // работает
	LCD_Text("Draw Round Rect",0,0,0); // работает
	_delay_ms(1000);

	LCD_ClrScreen(); // работает
	LCD_SetColor_Word(VGA_RED); // работает
	LCD_SetBackColor_Word(VGA_BLACK); // работает
	LCD_DrawRoundRect(0,0,100,100); // работает
	LCD_SetColor_Word(VGA_WHITE); // работает
	LCD_DrawRoundRect(100,100,200,200); // работает
	LCD_SetColor_Word(VGA_GREEN); // работает
	LCD_DrawRoundRect(100,100,300,200); // работает
	LCD_SetColor_Word(VGA_YELLOW); // работает
	LCD_DrawRoundRect(170,180,240,200); // работает
	_delay_ms(1000);
	
	LCD_ClrScreen(); // работает
	LCD_SetFont(BigFont); // работает
	LCD_SetColor_Word(VGA_WHITE); // работает
	LCD_Text("Draw Pixel",0,0,0); // работает
	_delay_ms(1000);

	LCD_ClrScreen(); // работает
	LCD_SetPixel(VGA_WHITE); // работает
	LCD_DrawPixel(0, 0); // работает
	LCD_SetPixel(VGA_RED); // работает
	LCD_DrawPixel(0, 239); // работает
	LCD_SetPixel(VGA_GREEN); // работает
	LCD_DrawPixel(319, 239); // работает
	LCD_SetPixel(VGA_YELLOW); // работает
	LCD_DrawPixel(319, 0); // работает
	LCD_SetPixel(VGA_AQUA); // работает
	LCD_DrawPixel(160, 120); // работает
	_delay_ms(1000);
	
	LCD_ClrScreen(); // работает
	LCD_SetFont(BigFont); // работает
	LCD_SetColor_Word(VGA_WHITE); // работает
	LCD_Text("Draw Circle",0,0,0); // работает
	_delay_ms(1000);

	LCD_ClrScreen(); // работает
	LCD_SetColor_Word(VGA_RED); // работает
	LCD_DrawCircle(20, 20, 10); // работает
	LCD_SetColor_Word(VGA_WHITE); // работает
	LCD_DrawCircle(30, 30, 30); // работает
	LCD_SetColor_Word(VGA_YELLOW); // работает
	LCD_DrawCircle(120, 150, 60); // работает
	LCD_SetColor_Word(VGA_BLUE); // работает
	LCD_DrawCircle(100, 80, 80); // работает
	_delay_ms(1000);

	LCD_ClrScreen(); // работает
	LCD_SetFont(BigFont); // работает
	LCD_SetColor_Word(VGA_WHITE); // работает
	LCD_Text("Draw Fill Circle",0,0,0); // работает
	_delay_ms(1000);

	LCD_ClrScreen(); // работает
	LCD_SetColor_Word(VGA_RED); // работает
	LCD_FillCircle(20, 20, 10); // работает
	LCD_SetColor_Word(VGA_WHITE); // работает
	LCD_FillCircle(30, 30, 30); // работает
	LCD_FillCircle(120, 150, 60); // работает
	LCD_SetColor_Word(VGA_YELLOW); // работает
	LCD_FillCircle(100, 80, 80); // работает
	_delay_ms(1000);
	
	LCD_ClrScreen(); // работает
	LCD_SetFont(BigFont); // работает
	LCD_SetColor_Word(VGA_WHITE); // работает
	LCD_Text("Draw Line",0,0,0); // работает
	_delay_ms(1000);

	LCD_ClrScreen(); // работает
	LCD_SetColor_Word(VGA_RED); // работает
	LCD_DrawHLine(0, 0, 319);
	LCD_SetColor_Word(VGA_GREEN); // работает
	LCD_DrawVLine(0, 0, 239);
	LCD_SetColor_Word(VGA_YELLOW);
	LCD_DrawHLine(0, 239, 319);
	LCD_SetColor_Word(VGA_BLUE);
	LCD_DrawVLine(319, 0, 239);
	LCD_SetColor_Word(VGA_WHITE); // работает
	LCD_DrawLine(0, 0, 319, 239);
	LCD_DrawLine(319, 0, 0, 239);
	_delay_ms(1000);
*/
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}