#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Driver\AD7671.h"
#include <stdlib.h>
#include <math.h>
#include "HAL\HCommon.h"

void AD7671Test(void)
{
	u16 Width = g_LCDDC->GetWidth();
	u16 Height = g_LCDDC->GetHeight();
	s16 buf[840];
	AD7671_SetWarpMode();
	AD7671_SetParallel();
	AD7671_SetFormatTwosComp();
	AD7671_SetClkDiv(100);
	AD7671_SetClockedMode();

	Width = 840;
	for (u16 i = 0; i < Width; i++)
	{
		buf[i] = AD7671_GetTwosCompResult();
	}
	g_LCDDC->Fill(0, 0, Width, Height, BLACK);
	for (u16 i = 0; i < Width; i++)
	{
		g_LCDDC->SetPixel(i, buf[i] * Height / 2 / 0x7FFF + Height / 2, WHITE);
	}
	HAL_Delay(5);
}
