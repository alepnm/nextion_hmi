#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

#include <stdint.h>


enum {PORTRATE = 0, LANDSCAPE};

typedef struct{
    struct{
        char OptionByte;

        uint16_t adc_x;
        uint16_t adc_y;
        uint16_t adc_p;
        uint16_t temperature;


    }XPT;
    struct{
        uint16_t    DisplaySizeX;
        uint16_t    DisplaySizeY;

        uint8_t     DisplaySizeX_Ratio;
        uint8_t     DisplaySizeY_Ratio;

        uint8_t Brightness;     //0-100%

        uint16_t PositionX;
        uint16_t PositionY;
        uint8_t Orient;
    }Display;
    struct{
        FunctionalState IsEnabled;
        FlagStatus      IsPressed;
        FlagStatus      TouchTimeoutOver;

        uint16_t    AdcX_Min;   // minimali ADC X koordinates reiksme (priklauso nuo XPT draiverio nustatymu)
        uint16_t    AdcX_Max;   // maksimali ADC X koordinates reiksme (priklauso nuo XPT draiverio nustatymu)
        uint16_t    AdcY_Min;   // minimali ADC Y koordinates reiksme (priklauso nuo XPT draiverio nustatymu)
        uint16_t    AdcY_Max;   // maksimali ADC Y koordinates reiksme (priklauso nuo XPT draiverio nustatymu)
    }Options;
}DispHandle_TypeDef;



void LCD_Init(void);
void LCD_ClearScreen(void);
void LCD_FillScreen_RGB(unsigned char r, unsigned char g, unsigned char b);
void LCD_FillScreen(unsigned int color);
void LCD_FillWindow(uint16_t colstart, uint16_t colend, uint16_t pagestart, uint16_t pageend, uint16_t color);

void LCD_DrawPixel(unsigned int x, unsigned int y);

#endif /* LCD_H_INCLUDED */
