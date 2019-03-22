#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "HAL\FPGASPIPort.h"

void FPGASPITest(void)
{
	FONTGROUP* FGs = NewReferenceSafe(new_noexcpt FONTGROUP("ASC16"));
	char sbuf[256];
	static u8 Val[16] = { 0x80, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
	//static u8 Val[16] = { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 };
	u8 RVal[16] = { 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 };
	FPGASPIPort_Transmit(Val, sizeof(Val));
	FPGASPIPort_Receive(RVal, sizeof(RVal));
	for (u8 i = 0; i < 16; i++)
	{
		sprintf(sbuf, "%6X %6X %6X     ", Val[i], RVal[i], Val[i] - RVal[i]);
		DrawStringHorizontal(g_LCDDC, FGs, sbuf, 0, i * 16, 0, 0, WHITE, BLACK);
		//Val[i]++;
	}
	FreeAndEraseReference(FGs);
}
