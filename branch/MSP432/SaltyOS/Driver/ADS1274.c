#include "HAL\HCommon.h"
#include "HAL\UniGPIO.h"

static bool ADS1274_Initialized = false;

STATUS ADS1274_Init(void)
{
	if (ADS1274_Initialized)
	{
		return S_OK;
	}

	ADS1274_Initialized = true;

	return S_OK;
}
