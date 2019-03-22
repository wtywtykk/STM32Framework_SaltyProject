#pragma once

C_HEADER_BEGIN

#define ExpandReadWriteFunctions

extern u16 LCD_Width;
extern u16 LCD_Height;

STATUS LCD_Init(void);
void LCD_SetDirection(uint Direction);
void LCD_SetBrightness(u8 Brightness);
void LCD_SetCurrentPoint(u16 X, u16 Y);
void LCD_ClipArea(u16 XStart, u16 YStart, u16 XEnd, u16 YEnd);
void LCD_EnterReadMode(void);
void LCD_EnterWriteMode(void);
u16 LCD_Read(void);
void LCD_Write(u16 Dat);

C_HEADER_END
