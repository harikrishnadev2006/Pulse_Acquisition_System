#ifndef SSD1306_H
#define SSD1306_H

#include "main.h"

void OLED_Init(void);
void OLED_Clear(void);

void OLED_BufferClear(void);

void OLED_UpdateScreen(void);

void OLED_DrawPixel(uint8_t x, uint8_t y);

void OLED_DrawChar(uint8_t x, uint8_t y, char c);

void OLED_DrawString(uint8_t x, uint8_t y, char *str);

void OLED_WriteData(uint8_t dataByte);

#endif
