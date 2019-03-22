#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Driver\ADS8363.h"
#include <stdlib.h>
#include <math.h>
#include "HAL\HCommon.h"
#include "Kernel\GUI\Shape\Line.h"

void ADS8363Test(void)
{
	u16 Width = g_LCDDC->GetWidth();
	u16 Height = g_LCDDC->GetHeight();
	s16 bufA[840];
	s16 bufB[840];

	static bool Inited = false;
	if (!Inited)
	{
		Inited = true;
		ADS8363_Init();
		ADS8363_SetChannel(0);
		ADS8363_SetPseudoDifferential(false);
		ADS8363_SetREFDAC1(false, 2.5);
		ADS8363_SetREFDAC2(false, 1);
		ADS8363_SetREFCM(0xFF00);
	}

	Width = 840;
	for (u16 i = 0; i < Width; i++)
	{
		while (ADS8363_IsReady());
		ADS8363_GetResult(&bufA[i], &bufB[i]);
	}
	g_LCDDC->Fill(0, 0, Width, Height, BLACK);
	for (u16 i = 1; i < Width; i++)
	{
		DrawLine(g_LCDDC, i - 1, bufA[i - 1] * Height / 2 / 0x7FFF + Height / 2, i, bufA[i] * Height / 2 / 0x7FFF + Height / 2, GREEN);
		DrawLine(g_LCDDC, i - 1, bufB[i - 1] * Height / 2 / 0x7FFF + Height / 2, i, bufB[i] * Height / 2 / 0x7FFF + Height / 2, RED);
	}
	HAL_Delay(100);
}
