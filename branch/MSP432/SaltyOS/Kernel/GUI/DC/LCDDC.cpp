#include "Kernel\GUI\GUICommon.h"
#include "Kernel\Common\KObject.h"
#include "Kernel\GUI\DC\DC.h"
#include "LCDDC.h"
#include "Driver\ILI9806G.h"

DC* g_LCDDC;

STATUS LCDDC::InitLCDDC(void)
{
	g_LCDDC = NewReferenceSafe(new_noexcpt LCDDC());
	if (g_LCDDC)
	{
		g_LCDDC->MarkObjectStatic();
		return S_OK;
	}
	else
	{
		return S_FAIL;
	}
}

LCDDC::LCDDC(void)
{
	LCD_ClipArea(0, LCD_Width, 0, LCD_Height);
	LCDState = Unknown;
}

LCDDC::~LCDDC(void)
{
}

void LCDDC::Fill(GUIPOS X1, GUIPOS Y1, GUIPOS X2, GUIPOS Y2, PIXEL Color)
{
	if (X1 < 0)
	{
		X1 = 0;
	}
	if (Y1 < 0)
	{
		Y1 = 0;
	}
	if (X2 > LCD_Width)
	{
		X2 = LCD_Width;
	}
	if (Y2 > LCD_Height)
	{
		Y2 = LCD_Height;
	}
	if (X1 < X2 && Y1 < Y2)
	{
		GUIPOS Width = X2 - X1;
		GUIPOS Height = Y2 - Y1;
		LCD_ClipArea(X1, Y1, X2, Y2);
		LCD_EnterWriteMode();
		for (s32 i = 0; i < Width * Height; i++)
		{
			LCD_Write(Color);
		}
		LCD_ClipArea(0, 0, LCD_Width, LCD_Height);
		LCDState = Unknown;
	}
}

void LCDDC::SetPos(GUIPOS X, GUIPOS Y)
{
	if (X < LCD_Width && Y < LCD_Height)
	{
		LCD_SetCurrentPoint(X, Y);
		LCDState = Unknown;
	}
}

void LCDDC::SequenceWrite(PIXEL Color)
{
	if (LCDState != Writing)
	{
		LCD_EnterWriteMode();
		LCDState = Writing;
	}
	LCD_Write(Color);
}

void LCDDC::SetPixel(GUIPOS X, GUIPOS Y, PIXEL Color)
{
	if (X >= 0 && Y >= 0 && X < LCD_Width && Y < LCD_Height)
	{
		LCD_SetCurrentPoint(X, Y);
		LCD_EnterWriteMode();
		LCD_Write(Color);
		LCDState = Writing;
	}
}

PIXEL LCDDC::GetPixel(GUIPOS X, GUIPOS Y)
{
	if (X >= 0 && Y >= 0 && X < LCD_Width && Y < LCD_Height)
	{
		LCD_SetCurrentPoint(X, Y);
		LCD_EnterReadMode();
		LCDState = Reading;
		return LCD_Read();
	}
	else
	{
		return 0;
	}
}

PIXEL LCDDC::SequenceRead(void)
{
	if (LCDState != Reading)
	{
		LCD_EnterReadMode();
		LCDState = Reading;
	}
	return LCD_Read();
}

GUIPOS LCDDC::GetWidth(void)
{
	return LCD_Width;
}

GUIPOS LCDDC::GetHeight(void)
{
	return LCD_Height;
}

bool LCDDC::SupportNativeClip(void)
{
	return true;
}

void LCDDC::StartNativeClip(GUIPOS X1, GUIPOS Y1, GUIPOS X2, GUIPOS Y2)
{
	LCD_ClipArea(X1, Y1, X2, Y2);
	LCDState = Unknown;
}

void LCDDC::EndNativeClip(void)
{
	LCD_ClipArea(0, LCD_Width, 0, LCD_Height);
	LCDState = Unknown;
}

void LCDDC::BlockWrite(const PIXEL* Data, u32 Length)
{
	if (LCDState != Writing)
	{
		LCD_EnterWriteMode();
		LCDState = Writing;
	}

	while (Length)
	{
		LCD_Write(*(Data++));
		Length--;
	}
}
