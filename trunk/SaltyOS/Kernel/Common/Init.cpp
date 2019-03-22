#include "KCommon.h"
#include "HAL\HCommon.h"
#include "BugCheck.h"

#include "HAL\PowerManagement.h"

#include "HAL\Interrupt.h"
#include "HAL\UniGPIO.h"
#include "HAL\BoardReset.h"
#include "HAL\Beep.h"
#include "HAL\Clock.h"
#include "HAL\FSMC.h"
#include "Driver\ILI9806G.h"

#include "Driver\LowLevelGraphic.h"

#include "HAL\DMA.h"
#include "Kernel\MemMan\MemMan.h"
#include "Driver\SRAM.h"
#include "HAL\PeripheralBus.h"
#include "Driver\SST39VFxxxx.h"
#include "Driver\W25Qxx.h"
#include "Driver\KeyBoard.h"
#include "Driver\ADS8363.h"
#include "HAL\USB.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "HAL\FPGAParPort.h"
#include "HAL\FPGASPIPort.h"
#include "Algorithm\SincInterpolation.h"

#include "Driver\FT5336.h"
#include "Driver\AD7671.h"
#include "Driver\AD9959.h"
#include "Driver\LMH6518.h"

#include "Kernel\Input\KeyBoardMap.h"
#include "Kernel\GUI\Window\WindowManager.h"
#include "Kernel\GUI\Window\ScreenWindow.h"
#include "Kernel\GUI\Menu\GlobalMenu.h"

typedef STATUS(*InitFunction)(void);
typedef struct
{
	InitFunction InitFunc;
	pcstr Description;
}Phase2Struct;

InitFunction CriticalInit[] = { Interrupt_Init , GPIO_32_Init, Beep_Init ,BoardReset_Init };
InitFunction Phase1Init[] = { Clock_Init, FSMC_Init, LCD_Init };
Phase2Struct Phase2Init[] =
{
	{
		DMA_Init,
		"Internal memory pool initialization"
	},
	{
		MemMan_Init,
		"Internal memory pool initialization"
	},
	{
		SRAM_Init,
		"SRAM initialization and check"
	},
	{
		MemMan_InitExtendedPool,
		"Extended memory pool initialization"
	},
	{
		PeripheralBus_Init,
		"Peripheral initialization and check"
	},
	{
		GPIO_CPLD_Init,
		"CPLD GPIO initialization"
	},
	{
		SST39VFxxxx_Init,
		"NOR flash initialization"
	},
	{
		W25Qxx_Init,
		"NAND flash initialization"
	},
	{
		KeyBoard_Init,
		"Key board initialization"
	},
	/*{
		ADS8363_Init,
		"ADS8363 initialization"
	},*/
	{
		USB_Init,
		"USB device initialization"
	},
	{
		LCDDC::InitLCDDC,
		"LCD device context initialization"
	},
	{
		FPGAParPort_Init,
		"FPGA parallel port initialization"
	},
	{
		FPGASPIPort_Init,
		"FPGA serial port initialization"
	},
	{
		AD9959_Init,
		"AD9959 initialization"
	},
	/*{
		SincInterpolation_Init,
		"Sinc interpolation initialization"
	},*/
	{
		KeyBoardMap_Init,
		"Key map initialization"
	},
	{
		WindowManager_Init,
		"Starting GUI--Initializing window manager"
	},
	{
		SCREENWINDOW::ScreenWindow_Init,
		"Starting GUI--Creating screen window"
	},
	{
		GlobalMenu_Init,
		"Starting GUI--Creating menu"
	},
	{
		WindowManager_RefreshUI,
		"Starting GUI--Refresh UI"
	},
};

void KernelCriticalInitError(u32 ErrorCode)
{
	DisableInterrupt();
	HardwareRestart();
	while (1);
}

void KernelPhase1InitError(u32 ErrorCode)
{
	BeepAndReset(ErrorCode);
	while (1);
}

STATUS InitKernel(void)
{
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
	LLGraphic_Fill(0, LCD_Height - 50, LCD_Width, LCD_Height, DGRAY);
	for (u32 i = 0; i < sizeof(Phase2Init) / sizeof(Phase2Struct); i++)
	{
		LLGraphic_DrawString(Phase2Init[i].Description, 0, LCD_Height - 70, WHITE, BLACK);
		if (Phase2Init[i].InitFunc() != S_OK)
		{
			BugCheck(KernelInitFailed, i, (u32)Phase2Init[i].Description, 0, 0);
		}
		LLGraphic_Fill(0, LCD_Height - 50, LCD_Width * (i + 1) / (sizeof(Phase2Init) / sizeof(Phase2Struct)), LCD_Height, WHITE);
		LLGraphic_DrawString("                                                        ", 0, LCD_Height - 70, WHITE, BLACK);
	}
	LLGraphic_Fill(0, LCD_Height - 50, LCD_Width, LCD_Height, BLACK);
	return S_OK;
}
