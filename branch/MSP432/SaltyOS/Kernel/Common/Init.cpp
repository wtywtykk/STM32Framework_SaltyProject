#include "KCommon.h"
#include "HAL\HCommon.h"
#include "BugCheck.h"

#include "HAL\PowerManagement.h"
#include "HAL/Tick.h"

#include "HAL\UniGPIO.h"
#include "HAL\Clock.h"
#include "Driver\ILI9806G.h"

#include "Driver\LowLevelGraphic.h"

#include "Kernel\MemMan\MemMan.h"
#include "Kernel\GUI\DC\LCDDC.h"

#include "Driver\FT5336.h"

typedef STATUS(*InitFunction)(void);
typedef struct
{
	InitFunction InitFunc;
	pcstr Description;
}Phase2Struct;

InitFunction CriticalInit[] = { GPIO_32_Init ,Tick_Init };
InitFunction Phase1Init[] = { Clock_Init, LCD_Init };
Phase2Struct Phase2Init[] =
{
	{
		MemMan_Init,
		"Internal memory pool initialization"
	},
	{
		LCDDC::InitLCDDC,
		"LCD device context initialization"
	},
};

void KernelCriticalInitError(u32 ErrorCode)
{
	//HardwareRestart();
	while (1);
}

void KernelPhase1InitError(u32 ErrorCode)
{
	//BeepAndReset(ErrorCode);
	while (1);
}

void InitIOForLowPower(void)
{
	/* Terminating all remaining pins to minimize power consumption. This is
	done by register accesses for simplicity and to minimize branching API
	calls */
	GPIO_setAsOutputPin(GPIO_PORT_P1, PIN_ALL8);
	GPIO_setOutputLowOnPin(GPIO_PORT_P1, PIN_ALL8);
	//GPIO_setAsOutputPin(GPIO_PORT_P2, PIN_ALL8);
	//GPIO_setOutputLowOnPin(GPIO_PORT_P2, PIN_ALL8);
	GPIO_setAsOutputPin(GPIO_PORT_P3, PIN_ALL8);
	GPIO_setOutputLowOnPin(GPIO_PORT_P3, PIN_ALL8);
	GPIO_setAsOutputPin(GPIO_PORT_P4, PIN_ALL8);
	GPIO_setOutputLowOnPin(GPIO_PORT_P4, PIN_ALL8);
	GPIO_setAsOutputPin(GPIO_PORT_P5, PIN_ALL8);
	GPIO_setOutputLowOnPin(GPIO_PORT_P5, PIN_ALL8);
	GPIO_setAsOutputPin(GPIO_PORT_P6, PIN_ALL8);
	GPIO_setOutputLowOnPin(GPIO_PORT_P6, PIN_ALL8);
	GPIO_setAsOutputPin(GPIO_PORT_P7, PIN_ALL8);
	GPIO_setOutputLowOnPin(GPIO_PORT_P7, PIN_ALL8);
	//GPIO_setAsOutputPin(GPIO_PORT_P8, PIN_ALL8);
	//GPIO_setOutputLowOnPin(GPIO_PORT_P8, PIN_ALL8);
	GPIO_setAsOutputPin(GPIO_PORT_P9, PIN_ALL8);
	GPIO_setOutputLowOnPin(GPIO_PORT_P9, PIN_ALL8);
	GPIO_setAsOutputPin(GPIO_PORT_P10, PIN_ALL8);
	GPIO_setOutputLowOnPin(GPIO_PORT_P10, PIN_ALL8);
}

STATUS InitKernel(void)
{
	__set_FAULTMASK(0);
	FPU_enableModule();
	FPU_enableStacking();
	FPU_enableLazyStacking();

	InitIOForLowPower();

	//Critical initialization. If those failed we have no choice but to reset and try again.
	for (u32 i = 0; i < sizeof(CriticalInit) / sizeof(InitFunction); i++)
	{
		if (CriticalInit[i]() != S_OK)
		{
			KernelCriticalInitError(i);
		}
	}

	//Initializations that enables lcd. If those failed,we can't show anything,but we can beep to indicate which routine has failed.
	for (u32 i = 0; i < sizeof(Phase1Init) / sizeof(InitFunction); i++)
	{
		if (Phase1Init[i]() != S_OK)
		{
			KernelPhase1InitError(i);
		}
	}

	//Final initializations. We can display a progress bar on the screen and show error messages.
	LLGraphic_Fill(0, LCD_Height - 30, LCD_Width, LCD_Height, DGRAY);
	for (u32 i = 0; i < sizeof(Phase2Init) / sizeof(Phase2Struct); i++)
	{
		LLGraphic_DrawString(Phase2Init[i].Description, 0, LCD_Height - 50, WHITE, BLACK);
		if (Phase2Init[i].InitFunc() != S_OK)
		{
			BugCheck(KernelInitFailed, i, (u32)Phase2Init[i].Description, 0, 0);
		}
		LLGraphic_Fill(0, LCD_Height - 30, LCD_Width * (i + 1) / (sizeof(Phase2Init) / sizeof(Phase2Struct)), LCD_Height, WHITE);
		LLGraphic_DrawString("                                                        ", 0, LCD_Height - 50, WHITE, BLACK);
	}
	LLGraphic_Fill(0, LCD_Height - 30, LCD_Width, LCD_Height, BLACK);
	return S_OK;
}
