#include "HAL\HCommon.h"
#include "Driver\FT5336.h"
#include "Kernel\GUI\GUICommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Shape\Circle.h"

#define FT5336_MAX_POINTS 5
extern TouchRawData RawData[FT5336_MAX_POINTS];

PIXEL Colors[FT5336_MAX_POINTS] = { RED,GREEN,BLUE,YELLOW,PURPLE };

void FT5336Test(void)
{
	if (Touch_Read() != S_OK)
	{
		g_LCDDC->Fill(0, 0, 1000, 1000, RED);
		g_LCDDC->Fill(0, 0, 1000, 1000, GREEN);
		return;
	}
	g_LCDDC->Fill(0, 0, 1000, 1000, BLACK);
	for (u8 i = 0; i < FT5336_MAX_POINTS; i++)
	{
		if (RawData[i].Weight)
		{
			DrawCircle(g_LCDDC, RawData[i].X, RawData[i].Y, RawData[i].Weight, Colors[RawData[i].TouchID]);
			DrawCircle(g_LCDDC, RawData[i].X, RawData[i].Y, RawData[i].Area * 10, Colors[RawData[i].TouchID]);
		}
	}
}