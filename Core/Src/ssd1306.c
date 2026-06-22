#include "ssd1306.h"
#include "font5x7.h"

extern I2C_HandleTypeDef hi2c1;
static uint8_t OLED_Buffer[1024];


void OLED_WriteCommand(uint8_t cmd)
{
    uint8_t data[2];

    data[0] = 0x00;
    data[1] = cmd;

    HAL_I2C_Master_Transmit(
        &hi2c1,
        0x3C << 1,
        data,
        2,
        HAL_MAX_DELAY
    );
}
void OLED_BufferClear(void)
{
    for(uint16_t i = 0; i < 1024; i++)
    {
        OLED_Buffer[i] = 0;
    }
}
void OLED_DrawPixel(uint8_t x, uint8_t y)
{
    uint16_t index;

    index = x + (y / 8) * 128;

    OLED_Buffer[index] |= (1 << (y % 8));
}
void OLED_UpdateScreen(void)
{
    for(uint8_t page = 0; page < 8; page++)
    {
        OLED_WriteCommand(0xB0 + page);

        OLED_WriteCommand(0x00);

        OLED_WriteCommand(0x10);

        for(uint8_t col = 0; col < 128; col++)
        {
            OLED_WriteData(
                OLED_Buffer[page * 128 + col]
            );
        }
    }
}

void OLED_WriteData(uint8_t dataByte)
{
    uint8_t data[2];

    data[0] = 0x40;
    data[1] = dataByte;

    HAL_I2C_Master_Transmit(
        &hi2c1,
        0x3C << 1,
        data,
        2,
        HAL_MAX_DELAY
    );
}


void OLED_Init(void)
{
    OLED_WriteCommand(0xAE);

    OLED_WriteCommand(0x20);
    OLED_WriteCommand(0x00);

    OLED_WriteCommand(0xA8);
    OLED_WriteCommand(0x3F);

    OLED_WriteCommand(0xD3);
    OLED_WriteCommand(0x00);

    OLED_WriteCommand(0x40);

    OLED_WriteCommand(0xA1);

    OLED_WriteCommand(0xC8);

    OLED_WriteCommand(0x8D);
    OLED_WriteCommand(0x14);

    OLED_WriteCommand(0x81);
    OLED_WriteCommand(0xCF);

    OLED_WriteCommand(0xAF);
}


void OLED_Clear(void)
{
    for(uint8_t page = 0; page < 8; page++)
    {
        OLED_WriteCommand(0xB0 + page);

        OLED_WriteCommand(0x00);
        OLED_WriteCommand(0x10);

        for(uint8_t col = 0; col < 128; col++)
        {
            OLED_WriteData(0x00);
        }
    }
}

void OLED_DrawChar(uint8_t x, uint8_t y, char c)
{
    const uint8_t *bitmap = 0;

    if(c >= '0' && c <= '9')
    {
        bitmap = Font5x7[c - '0'];
    }
    else if(c == 'C')
    {
        bitmap = Font5x7[10];
    }
    else if(c == 'P')
    {
        bitmap = Font5x7[11];
    }
    else if(c == 'S')
    {
        bitmap = Font5x7[12];
    }
    else if(c == 'A')
    {
        bitmap = Font5x7[13];
    }
    else if(c == 'V')
    {
        bitmap = Font5x7[14];
    }
    else if(c == 'G')
    {
        bitmap = Font5x7[15];
    }
    else if(c == 'M')
    {
        bitmap = Font5x7[16];
    }
    else if(c == 'X')
    {
        bitmap = Font5x7[17];
    }
    else if(c == 'I')
    {
        bitmap = Font5x7[18];
    }
    else if(c == 'N')
    {
        bitmap = Font5x7[19];
    }
    else if(c == 'T')
    {
        bitmap = Font5x7[20];
    }
    else if(c == ':')
    {
        bitmap = Font5x7[21];
    }
    else if(c == ' ')
    {
        bitmap = Font5x7[22];
    }
    else
    {
        return;
    }

    for(uint8_t col = 0; col < 5; col++)
    {
        for(uint8_t row = 0; row < 7; row++)
        {
            if(bitmap[col] & (1 << row))
            {
                OLED_DrawPixel(x + col, y + row);
            }
        }
    }
}

void OLED_DrawString(uint8_t x, uint8_t y, char *str)
{
    while(*str)
    {
        OLED_DrawChar(x, y, *str);

        x += 6;

        str++;
    }
}
