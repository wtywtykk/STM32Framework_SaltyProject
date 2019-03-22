#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"

void TextTest(void)
{
	FONTGROUP* FG;
	FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC48;HZK48S;HZK48T"));
	DrawStringHorizontal(g_LCDDC, FG, "64pt文字测试。", 0, 0, 0, 0, GREEN, BLACK);
	FreeAndEraseReference(FG);
	FG = NewReferenceSafe(new_noexcpt FONTGROUP("HZK40S;HZK40T"));
	DrawStringHorizontal(g_LCDDC, FG, "四十。", 0, 100, 0, 0, WHITE, BLACK);
	FreeAndEraseReference(FG);
	FG = NewReferenceSafe(new_noexcpt FONTGROUP("HZK32"));
	DrawStringHorizontal(g_LCDDC, FG, "三十二点。", 0, 150, 0, 0, WHITE, BLACK);
	FreeAndEraseReference(FG);
	FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC24;HZK24S;HZK24T"));
	DrawStringHorizontal(g_LCDDC, FG, "abc24点。", 0, 200, 0, 0, WHITE, BLACK);
	FreeAndEraseReference(FG);
	FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC16;HZK16"));
	DrawStringHorizontal(g_LCDDC, FG, "abc16点。", 0, 230, 0, 0, WHITE, BLACK);
	FreeAndEraseReference(FG);
}
