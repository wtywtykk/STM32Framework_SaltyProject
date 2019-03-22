#include "HCommon.h"
#include "HAL\UniGPIO.h"
#include "HAL\BoardReset.h"

bool BoardReset_Initialized = false;
UniGPIO_Handle BoardResetPin;

STATUS BoardReset_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	if (BoardReset_Initialized)
	{
		return S_OK;
	}

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_32_InitPin(GPIOH, &GPIO_InitStruct, &BoardResetPin);
	UniGPIO_SetHigh(&BoardResetPin);

	BoardReset_Issue();

	BoardReset_Initialized = true;

	return S_OK;
}

void BoardReset_Issue(void)
{
	volatile u32 i = 0;
	UniGPIO_SetLow(&BoardResetPin);
	while (i++ < 1000);
	UniGPIO_SetHigh(&BoardResetPin);
	i = 0;
	while (i++ < 1000);
}
