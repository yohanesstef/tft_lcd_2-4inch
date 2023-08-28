/*
 * lcd.c
 *
 *  Created on: Aug 23, 2023
 *      Author: yohanes
 */

#include "lcd_module.h"

uint16_t ID = 0;

void lcd_init(){
	ID = readID();
	HAL_Delay(100);
	tft_init(ID);



	LCD_Touch_Init(&hadc1, ADC_CHANNEL_7, &hadc1, ADC_CHANNEL_8);
	LCD_SetMode(LCD_MODE_TOUCH);
	//sampai sini dulu
}

