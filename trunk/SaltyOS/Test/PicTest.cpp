#include "HAL\HCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Picture\DirectDataPic.h"
#include "Kernel\GUI\Picture\FlashFSPic.h"
//#include <EmbeddedResources.h>

void PicTest(void)
{
	/*u16* PicDat = (u16*)EmbeddedResources::Test_PicTestPic_SP.data();
	GUIPOS Width;
	GUIPOS Height;
	Width = *PicDat;
	PicDat++;
	Height = *PicDat;
	PicDat++;
	DIRECTDATAPIC DPic(Width, Height, PicDat);
	g_LCDDC->Fill(0, 0, DPic.GetWidth(), DPic.GetHeight(), BLACK);
	DPic.Draw(g_LCDDC, 0, 0);*/
	FLASHFSPIC FPic("MnuPopDispS.SP");
	g_LCDDC->Fill(500, 0, 500 + FPic.GetWidth(), FPic.GetHeight(), BLACK);
	FPic.Draw(g_LCDDC, 500, 0);
}
