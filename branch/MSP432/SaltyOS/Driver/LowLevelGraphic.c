#include "HAL\HCommon.h"
#include "ILI9806G.h"
#include "ASC16.h"

void LLGraphic_DrawCharData(u8* CharData, s16 X, s16 Y, u16 Width, u16 Height, u16 ForeColor, u16 BackColor)
{
	u16 i, j;
	u8 BitCounter = 0, CurByte = *CharData;
	LCD_ClipArea(X, Y, X + Width, Y + Height);
	LCD_EnterWriteMode();
	for (i = 0; i < Height; i++)
	{
		for (j = 0; j < Width; j++)
		{
			if (CurByte & 0x80)
			{
				LCD_Write(ForeColor);
			}
			else
			{
				LCD_Write(BackColor);
			}
			CurByte <<= 1;
			BitCounter++;
			if (BitCounter == 8)
			{
				BitCounter = 0;
				CharData++;
				CurByte = *CharData;
			}
		}
		if (BitCounter)
		{
			BitCounter = 0;
			CharData++;
			CurByte = *CharData;
		}
	}
	LCD_ClipArea(0, 0, LCD_Width, LCD_Height);
}

void LLGraphic_DrawString(pcstr String, s16 X, s16 Y, u16 ForeColor, u16 BackColor)
{
	pcstr StrPtr = String;
	u16 CurChar;
	u16 CurX = X;

	while (1)
	{
		CurChar = *StrPtr++;
		if (CurChar == 0)
		{
			break;
		}

		if (CurChar <= 127)
		{
			const u8* CharDataAddress = ASC16Font + CurChar * 16;
			LLGraphic_DrawCharData((u8*)CharDataAddress, CurX, Y, 8, 16, ForeColor, BackColor);

			CurX += 8;
		}
	}
}

void LLGraphic_Fill(s16 X1, s16 Y1, s16 X2, s16 Y2, u16 Color)
{
	u16 Width = X2 - X1;
	u16 Height = Y2 - Y1;
	u32 i;
	LCD_ClipArea(X1, Y1, X2, Y2);
	LCD_EnterWriteMode();
	for (i = 0; i < Width * Height; i++)
	{
		LCD_Write(Color);
	}
	LCD_ClipArea(0, LCD_Width, 0, LCD_Height);
}
