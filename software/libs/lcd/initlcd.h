//========================================================================================================
// Команды инициализации дисплея ILI9481
//========================================================================================================
	LCD_Write_COM(0x11);
	_delay_ms(20);
	LCD_Write_COM(0xD0);
	LCD_Write_DATA_1(0x07);
	LCD_Write_DATA_1(0x42);
	LCD_Write_DATA_1(0x18);

	LCD_Write_COM(0xD1);
	LCD_Write_DATA_1(0x00);
	LCD_Write_DATA_1(0x07);
	LCD_Write_DATA_1(0x10);

	LCD_Write_COM(0xD2);
	LCD_Write_DATA_1(0x01);
	LCD_Write_DATA_1(0x02);

	LCD_Write_COM(0xC0);
	LCD_Write_DATA_1(0x10);
	LCD_Write_DATA_1(0x3B);
	LCD_Write_DATA_1(0x00);
	LCD_Write_DATA_1(0x02);
	LCD_Write_DATA_1(0x11);

	LCD_Write_COM(0xC5);
	LCD_Write_DATA_1(0x03);

	LCD_Write_COM(0xC8);
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

	LCD_Write_COM(0x36);
	LCD_Write_DATA_1(0x0A);


	LCD_Write_COM(0x3A);
	LCD_Write_DATA_1(0x55);

	LCD_Write_COM(0x2A);
	LCD_Write_DATA_1(0x00);
	LCD_Write_DATA_1(0x00);
	LCD_Write_DATA_1(0x01);
	LCD_Write_DATA_1(0x3F);

	LCD_Write_COM(0x2B);
	LCD_Write_DATA_1(0x00);
	LCD_Write_DATA_1(0x00);
	LCD_Write_DATA_1(0x01);
	LCD_Write_DATA_1(0xE0);
	_delay_ms(120);
	LCD_Write_COM(0x29);
//========================================================================================================