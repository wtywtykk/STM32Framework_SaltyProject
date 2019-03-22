#include "HAL\HCommon.h"
#include "HAL\FPGAParPort.h"
#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "Kernel\GUI\Shape\Line.h"
#include "Kernel\GUI\Shape\Circle.h"
#include "Kernel\GUI\DC\ClippedDC.h"

#define DataCount 250

void ParPortTest(void)
{
	FONTGROUP* FGs = NewReferenceSafe(new_noexcpt FONTGROUP("ASC12"));
	u16 Buf[DataCount];
	char sbuf[128];
	if (FPGAParPort_IsReady())
	{
		u32 RdSize;
		ParPort_StartPipeline();
		ParPort_Read(Buf, DataCount, &RdSize, true);
		FPGAParPort_Reset();

		DC* cache = NewReferenceSafe(new_noexcpt CLIPPEDDC(g_LCDDC, 0, 0, g_LCDDC->GetWidth(), g_LCDDC->GetHeight(), true, false));
		cache->Fill(0, 0, cache->GetWidth(), cache->GetHeight(), BLACK);
		for (u16 i = 0; i < DataCount; i++)
		{
			Buf[i] = Buf[i] & 0xFFF;
			Buf[i] = ((s16)(Buf[i] << 4)) + 32768;
			sprintf(sbuf, "%6x ", Buf[i]);
			//DrawStringHorizontal(cache, FGs, sbuf, 50 * (i % 17), 16 * (i / 17), 0, 0, WHITE, BLACK);
		}
		DrawLine(cache, 0, 32768 >> 7, cache->GetWidth(), 32768 >> 7, DGRAY);
		DrawLine(cache, 127 * 3, 0, 127 * 3, cache->GetHeight(), DGRAY);
		for (u16 i = 0; i < DataCount; i++)
		{
			//DrawCircle(cache, i * 3, Buf[i] >> 7, 2, WHITE);
		}
		for (u16 i = 1; i < DataCount; i++)
		{
			DrawLine(cache, i * 3 - 3, Buf[i - 1] >> 7, i * 3, Buf[i] >> 7, YELLOW);
		}
		FreeAndEraseReference(cache);
	}

	FreeAndEraseReference(FGs);
}
