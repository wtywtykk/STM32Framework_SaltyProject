#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "Driver\KeyBoard.h"
#include "HAL\Beep.h"

void ZLG7290Test(void)
{
	FONTGROUP* FGs = NewReferenceSafe(new_noexcpt FONTGROUP("ASC12"));
	char sbuf[64];
	//u8 KeyVal = KeyBoard_GetKey_Single();
	u8 KeyVal = KeyBoard_GetKey_Repeat();
	static u8 LastKey = 0;
	sprintf(sbuf, "LastValid:%2d  Current:%2d    ", LastKey, KeyVal);
	if (KeyVal)
	{
		Beep(10);
		LastKey = KeyVal;
	}
	DrawStringHorizontal(g_LCDDC, FGs, sbuf, 0, 0, 0, 0, WHITE, BLACK);
	FreeAndEraseReference(FGs);
}
