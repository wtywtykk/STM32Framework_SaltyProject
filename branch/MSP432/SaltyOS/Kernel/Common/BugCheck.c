#include "HAL/HCommon.h"
#include "HAL\PowerManagement.h"
#include "Driver\ILI9806G.h"
#include "Driver\LowLevelGraphic.h"
#include "BugCheck.h"
#include <stdlib.h>

char BugCheckStrBuf[17];

void BugCheckIntegerToDecStr(u32 Val)
{
	u8 i = 0;
	while (i < 16)
	{
		BugCheckStrBuf[15 - i] = (Val % 10) + '0';
		Val /= 10;
		i++;
	}
	BugCheckStrBuf[16] = 0;
}

void BugCheckIntegerToHexStr(u32 Val)
{
	u8 i = 0;
	while (i < 16)
	{
		BugCheckStrBuf[15 - i] = Val % 16;
		if (BugCheckStrBuf[15 - i] < 10)
		{
			BugCheckStrBuf[15 - i] = BugCheckStrBuf[15 - i] + '0';
		}
		else
		{
			BugCheckStrBuf[15 - i] = BugCheckStrBuf[15 - i] - 10 + 'A';
		}
		Val /= 16;
		i++;
	}
	BugCheckStrBuf[16] = 0;
}

void BugCheck(BugCheckCode ErrorCode, u32 Param1, u32 Param2, u32 Param3, u32 Param4)
{
	u16 DBLUE = 0x000F;
	u16 WHITE = 0xFFFF;

	__set_FAULTMASK(1);
	LLGraphic_Fill(0, 0, LCD_Width, LCD_Height, DBLUE);

	switch (ErrorCode)
	{
	case KernelInitFailed:
		LLGraphic_DrawString("Kernel initialization failed.", 0, 0, WHITE, DBLUE);
		LLGraphic_DrawString("FailureIndex:", 0, 16, WHITE, DBLUE);
		BugCheckIntegerToDecStr(Param1);
		LLGraphic_DrawString(BugCheckStrBuf, 0, 32, WHITE, DBLUE);
		LLGraphic_DrawString((const char *)Param2, 0, 48, WHITE, DBLUE);
		break;
	case MemoryCorruption:
		LLGraphic_DrawString("Memory pool corrupted!. At block:", 0, 0, WHITE, DBLUE);
		BugCheckIntegerToHexStr(Param1);
		LLGraphic_DrawString(BugCheckStrBuf, 0, 16, WHITE, DBLUE);
		break;
	case InvalidCall:
		LLGraphic_DrawString("Kernel invalid function call occurred.", 0, 0, WHITE, DBLUE);
		break;
	default:
		LLGraphic_DrawString("Something wrong with bugcheck", 0, 0, WHITE, DBLUE);
		break;
	}
#ifdef KeResetOnBug
	HardwareRestart();
#endif
	while (1);
}
