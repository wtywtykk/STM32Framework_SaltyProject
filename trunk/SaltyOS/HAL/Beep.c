#include "HCommon.h"
#include "HAL\UniGPIO.h"

bool Beep_Initialized = false;
UniGPIO_Handle BeepPin;

STATUS Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	if (Beep_Initialized)
	{
		return S_OK;
	}

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_32_InitPin(GPIOE, &GPIO_InitStruct, &BeepPin);
	UniGPIO_SetLow(&BeepPin);

	Beep_Initialized = true;

	return S_OK;
}

void Beep(uint Delay)
{
	UniGPIO_SetHigh(&BeepPin);
	HAL_Delay(Delay);
	UniGPIO_SetLow(&BeepPin);
}

void BeepStart(void)
{
	UniGPIO_SetHigh(&BeepPin);
}

void BeepStop(void)
{
	UniGPIO_SetLow(&BeepPin);
}
