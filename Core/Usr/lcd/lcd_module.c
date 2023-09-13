/*
 * lcd.c
 *
 *  Created on: Aug 23, 2023
 *      Author: yohanes
 */

#include "lcd_module.h"

uint16_t ID = 0;
uint8_t lcd_flag;
uint8_t touch_flag;

LCD_TouchPoint p;

void lcd_init(void){
	ID = readID();
	lcd_flag = 1;
	HAL_Delay(100);
	tft_init(ID);
	lcd_flag = 2;
	  setRotation(0);

	  fillScreen(BLACK);

	  fillScreen(BLACK);

	  setRotation(0);
//	  testFillScreen();
//	  testLines(CYAN);
//	  testFastLines(RED, BLUE);
//	  testFilledCircles(10, MAGENTA);
//	  testCircles(10, WHITE);
//	  scrollup(100);
//	  invertDisplay(1);
	  fillScreen(WHITE);
	  printnewtstr(100, RED, &mono9x7bold, 3, "HELLO");
	//  fillRect(10, 10, 100, 200, WHITE);
	  lcd_flag = 3;
	LCD_Touch_Init(&hadc1, ADC_CHANNEL_5, &hadc1, ADC_CHANNEL_4);
	LCD_SetMode(LCD_MODE_TOUCH);
	lcd_flag = 4;
	//sampai sini dulu
}

lcd_touchscreen_routine(){
	LCD_SetMode(LCD_MODE_TOUCH);
	  if (LCD_Touch_Read(&p) == LCD_TOUCH_READ_SUCCESS) {
//		  LCD_Touch_Draw_ConnectLastPoint(&p);
//		  LCD_Touch_Draw_PrintInfo();
		  touch_flag++;
	  }
//	  if ((p.x < 200) & (p.x > 150) & (p.y < 200) & (p.y > 150)){
//		  p.x = 0;
//		  p.y = 0;
//		  LCD_SetMode(LCD_MODE_DRAW);
//		  testLines(CYAN);
//	  }
}

