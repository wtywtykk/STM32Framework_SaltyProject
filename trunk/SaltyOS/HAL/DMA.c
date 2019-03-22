#include "HCommon.h"

bool DMA_Initialized = false;

STATUS DMA_Init(void)
{
	if (DMA_Initialized)
	{
		return S_OK;
	}

	__HAL_RCC_DMA1_CLK_ENABLE();
	__HAL_RCC_DMA2_CLK_ENABLE();

	DMA_Initialized = true;

	return S_OK;
}
