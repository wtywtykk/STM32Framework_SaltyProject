#include "HAL\HCommon.h"
#include "Kernel\Common\Init.h"
#include "Kernel\Power\Power.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "Test\Tests.h"

#include <stdlib.h>

#include "Setup\FlashWriter.h"

__weak void TaskLauncher(void)
{
	//EnterFlashWriterMode();
	RunTests();

	FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC16"));
	DrawStringHorizontal(g_LCDDC, FG, "Unable to start.", 0, 0, 300, 50, GREEN, RED);
	FreeAndEraseReference(FG);

	while (1);
}

int main(void)
{
	HAL_Init();

	InitKernel();

	TaskLauncher();

	KernelPowerDown();
}
