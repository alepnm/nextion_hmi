
	LCD_Write_COM(0x2a); 
	LCD_Write_DATA_1(x1>>8);
	LCD_Write_DATA_1(x1);
	LCD_Write_DATA_1(x2>>8);
	LCD_Write_DATA_1(x2);
	LCD_Write_COM(0x2b); 
	LCD_Write_DATA_1(y1>>8);
	LCD_Write_DATA_1(y1);
	LCD_Write_DATA_1(y2>>8);
	LCD_Write_DATA_1(y2);
	LCD_Write_COM(0x2c); 
