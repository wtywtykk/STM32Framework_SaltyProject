#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Driver\AD9959.h"
#include <stdio.h>

void AD9959Test(void)
{
	static double Freq = 0;
	char Buf[64];
	FONTGROUP* FGs = NewReferenceSafe(new_noexcpt FONTGROUP("ASC16"));

	sprintf(Buf, "  %f MHz     ", Freq / 1e6);
	DrawStringHorizontal(g_LCDDC, FGs, Buf, 0, 0, 0, 0, RED, BLACK);

	sprintf(Buf, "r %f MHz     ", AD9959_SetChannelFrequency(1, Freq) / 1e6);
	DrawStringHorizontal(g_LCDDC, FGs, Buf, 0, 16, 0, 0, RED, BLACK);

	Freq += 0.5e6;
	if (Freq > 250e6)
	{
		Freq = 0;
	}

	HAL_Delay(100);

	FreeAndEraseReference(FGs);
}
