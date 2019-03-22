#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\DC\ClippedDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "Driver\W25Qxx.h"
#include <string.h>

void W25QxxTest(void)
{
	u16 buf[2048];
	//W25Qxx_Erase_Chip();
	//W25Qxx_SectorErase(0);
	//W25Qxx_SectorErase(4096);
	for (u32 i = 0; i < 2048; i++)
	{
		buf[i] = i;
	}
	//W25Qxx_Program(2, buf, sizeof(buf));
	for (u32 i = 0; i < 2048; i++)
	{
		buf[i] = 0;
	}
	//W25Qxx_Read(0, buf, sizeof(buf));
	buf[0] = 0xABCD;
	//W25Qxx_Program_Safe(0, buf, sizeof(u16));
	for (u32 i = 0; i < 2048; i++)
	{
		buf[i] = 0;
	}
	W25Qxx_Read(0, buf, sizeof(buf));
	DC* cache = NewReferenceSafe(new_noexcpt CLIPPEDDC(g_LCDDC, 0, 0, g_LCDDC->GetWidth(), g_LCDDC->GetHeight(), true, false));
	FONTGROUP* FGs = NewReferenceSafe(new_noexcpt FONTGROUP("ASC12;HZK12"));
	cache->Fill(0, 0, cache->GetWidth(), cache->GetHeight(), BLACK);
	DrawStringHorizontal(cache, FGs, (pstr)buf, 0, 0, 0, 0, WHITE, BLACK);
	FreeAndEraseReference(FGs);
	FreeAndEraseReference(cache);
}
