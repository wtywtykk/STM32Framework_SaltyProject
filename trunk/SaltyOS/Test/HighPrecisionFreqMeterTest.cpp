#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "HAL\FPGASPIPort.h"

static bool Inited = false;

void HighPrecisionFreqMeterTest(void)
{
	if (!Inited)
	{
		FPGASPIPort_Reset();
		u32 TVal[4] = { 0,0,0,0 };
		FPGASPIPort_Transmit(TVal, sizeof(TVal));
		Inited = true;
	}
	while (!FPGASPIPort_ReadIO2());
	FONTGROUP* FGs = NewReferenceSafe(new_noexcpt FONTGROUP("ASC16"));
	char sbuf[256];
	u32 RVal[4] = { 0,0,0,0 };
	u32 TVal[4] = { 0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF };
	FPGASPIPort_Receive(RVal, sizeof(RVal));
	u32 Meas1 = RVal[0];
	u32 Ref1 = RVal[1];
	u32 Meas2 = RVal[2];
	u32 Ref2 = RVal[3];
	sprintf(sbuf, "%6lX %6lX %6lX %6lX     ", Meas1, Ref1, Meas2, Ref2);
	DrawStringHorizontal(g_LCDDC, FGs, sbuf, 0, 0, 0, 0, WHITE, BLACK);
	for (u8 i = 0; i < 32; i++)
	{
		if (RVal[0] & 1L << (31 - i))
		{
			sbuf[i] = '1';
		}
		else
		{
			sbuf[i] = '0';
		}
	}
	sbuf[32] = 0;
	DrawStringHorizontal(g_LCDDC, FGs, sbuf, 0, 16, 0, 0, WHITE, BLACK);
	//Ref1 += 8;
	sprintf(sbuf, "%8.10f     ", (double)Meas1 / Ref1 * 1000 * 2);
	DrawStringHorizontal(g_LCDDC, FGs, sbuf, 0, 32, 0, 0, WHITE, BLACK);
	FreeAndEraseReference(FGs);
	FPGASPIPort_Transmit(TVal, sizeof(TVal));
	TVal[0] = 0;
	TVal[1] = 0;
	TVal[2] = 0;
	TVal[3] = 0;
	FPGASPIPort_Transmit(TVal, sizeof(TVal));
}
