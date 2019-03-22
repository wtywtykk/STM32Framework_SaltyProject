#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\DC\ClippedDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"

void ClippedDCTest(void)
{
	FONTGROUP* FG;
	FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC48;HZK24S;HZK24T"));

	DC* cdc;

	g_LCDDC->Fill(200, 200, 600, 450, DGRAY);
	cdc = NewReferenceSafe(new_noexcpt CLIPPEDDC(g_LCDDC, 300, 300, 500, 400, true, true));
	DrawStringHorizontal(cdc, FG, "CLIPPED!", 0, 0, 0, 0, GREEN, DCYAN);
	DrawStringHorizontal(cdc, FG, "ºº×Ö", 0, 50, 0, 0, GREEN, DCYAN);
	cdc->Fill(100, 40, cdc->GetWidth(), cdc->GetHeight(), BLUE);
	FreeAndEraseReference(cdc);

	FreeAndEraseReference(FG);
}
