#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\DC\ClippedDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "Kernel\FlashFS\FlashFS.h"
#include <string.h>

void DrawPic(pcstr FileName)
{
	s16 Width;
	s16 Height;
	FlashFS_Read(FileName, &Width, 0, sizeof(s16), NULL);
	FlashFS_Read(FileName, &Height, 2, sizeof(s16), NULL);
	u32 DataAddr = 4;
#define Pic_BufferLength 1024
	s16 PixelVal[Pic_BufferLength];
	FlashFS_Read(FileName, PixelVal, DataAddr, sizeof(s16) * Pic_BufferLength, NULL);
	u32 BufferCount = 0;
	g_LCDDC->StartNativeClip(0, 0, Width, Height);
	for (s16 y = 0; y < Height; y++)
	{
		for (s16 x = 0; x < Width; x++)
		{
			g_LCDDC->SequenceWrite(PixelVal[BufferCount]);
			BufferCount++;
			if (BufferCount == Pic_BufferLength)
			{
				DataAddr += sizeof(s16) * Pic_BufferLength;
				BufferCount = 0;
				FlashFS_Read(FileName, PixelVal, DataAddr, sizeof(s16) * Pic_BufferLength, NULL);
			}
		}
	}
	g_LCDDC->EndNativeClip();
}

void FlashFSTest(void)
{
	DC* cache = NewReferenceSafe(new_noexcpt CLIPPEDDC(g_LCDDC, 0, 0, g_LCDDC->GetWidth(), g_LCDDC->GetHeight(), true, false));
	//FONTGROUP* FGs = NewReferenceSafe(new_noexcpt FONTGROUP("ASC12;HZK12"));
	//char* Buf[4096];
	//FlashFS_Read("a.SaltyPic", Buf, 0, 4096, NULL);
	//cache->Fill(0, 0, cache->GetWidth(), cache->GetHeight(), BLACK);
	DrawPic("MnuBlank.SP");
	DrawPic("MnuPopNdS.SP");
	//DrawStringHorizontal(cache, FGs, (pstr)Buf, 0, 0, 0, 0, WHITE, BLACK);
	//FreeAndEraseReference(FGs);
	FreeAndEraseReference(cache);
}
