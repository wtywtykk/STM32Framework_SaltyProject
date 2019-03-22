#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "Driver\LOBoard.h"

void LOBoardTest(void)
{
	static bool Inited = false;
	if (!Inited)
	{
		LOBoard_Init();
	}
	LOBoard_SetFreq(12345);
	LOBoard_SetExtRef(true);
	//HAL_Delay(50);
	LOBoard_SetExtRef(false);
	//HAL_Delay(50);
}
