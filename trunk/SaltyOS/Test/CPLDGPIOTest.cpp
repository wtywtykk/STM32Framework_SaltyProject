#include "HAL\HCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "HAL\PeripheralBus.h"

void CPLDGPIOTest(void)
{
	FONTGROUP* FGs = NewReferenceSafe(new_noexcpt FONTGROUP("ASC12"));
	char sbuf[128];
	u16 rdat[8];
	PeripheralBus_Write(4, 0x0000);
	PeripheralBus_Write(3, 0xFFFF);
	//while (1)
	{
		PeripheralBus_Write(2, 0xF);
		PeripheralBus_Write(4, 0x2);
		PeripheralBus_Write(1, 0xF);
		PeripheralBus_Write(4, 0x0);
	}
	for (u8 i = 0; i < 4; i++)
	{
		PeripheralBus_Write((i + 0) * 8 + 3, 0x000F);
		PeripheralBus_Write((i + 0) * 8 + 4, 0x0000);
		PeripheralBus_Write((i + 4) * 8 + 3, 0xFFF0);
		PeripheralBus_Write((i + 4) * 8 + 4, 0x0000);
	}
	static u16 ii = 0;
	ii++;
	ii &= 0x1FF;
	for (u8 i = 0; i < 8; i++)
	{
		PeripheralBus_Write(i * 8, ii);
	}
	for (u8 i = 0; i < 8; i++)
	{
		rdat[i] = PeripheralBus_Read(i * 8 + 0);
	}
	sprintf(sbuf, "%6d %6d %6d %6d %6d %6d %6d %6d %6d       ", ii, rdat[0] - ii, rdat[1] - ii, rdat[2] - ii, rdat[3] - ii, rdat[4] - ii, rdat[5] - ii, rdat[6] - ii, rdat[7] - ii);
	DrawStringHorizontal(g_LCDDC, FGs, sbuf, 0, 16, 0, 0, WHITE, BLACK);
	FreeAndEraseReference(FGs);
}
