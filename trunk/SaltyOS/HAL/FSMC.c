#include "HCommon.h"

static bool FSMC_Initialized = false;

STATUS FSMC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	if (FSMC_Initialized)
	{
		return S_OK;
	}

	//Peripheral clock enable
	__HAL_RCC_FSMC_CLK_ENABLE();

	/** FSMC GPIO Configuration
	PE3   ------> FSMC_A19
	PE4   ------> FSMC_A20
	PE5   ------> FSMC_A21
	PF0   ------> FSMC_A0
	PF1   ------> FSMC_A1
	PF2   ------> FSMC_A2
	PF3   ------> FSMC_A3
	PF4   ------> FSMC_A4
	PF5   ------> FSMC_A5
	PF12   ------> FSMC_A6
	PF13   ------> FSMC_A7
	PF14   ------> FSMC_A8
	PF15   ------> FSMC_A9
	PG0   ------> FSMC_A10
	PG1   ------> FSMC_A11
	PE7   ------> FSMC_D4
	PE8   ------> FSMC_D5
	PE9   ------> FSMC_D6
	PE10   ------> FSMC_D7
	PE11   ------> FSMC_D8
	PE12   ------> FSMC_D9
	PE13   ------> FSMC_D10
	PE14   ------> FSMC_D11
	PE15   ------> FSMC_D12
	PD8   ------> FSMC_D13
	PD9   ------> FSMC_D14
	PD10   ------> FSMC_D15
	PD11   ------> FSMC_A16
	PD12   ------> FSMC_A17
	PD13   ------> FSMC_A18
	PD14   ------> FSMC_D0
	PD15   ------> FSMC_D1
	PG2   ------> FSMC_A12
	PG3   ------> FSMC_A13
	PG4   ------> FSMC_A14
	PG5   ------> FSMC_A15
	PD0   ------> FSMC_D2
	PD1   ------> FSMC_D3
	PD4   ------> FSMC_NOE
	PD5   ------> FSMC_NWE
	PD7   ------> FSMC_NE1
	PG9   ------> FSMC_NE2
	PG10   ------> FSMC_NE3
	PG12   ------> FSMC_NE4
	PE0   ------> FSMC_NBL0
	PE1   ------> FSMC_NBL1
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5
		| GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9
		| GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12
		| GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15
		| GPIO_PIN_0 | GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FSMC;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2
		| GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5
		| GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14
		| GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FSMC;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2
		| GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5
		| GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FSMC;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10
		| GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13
		| GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_0
		| GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5
		| GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF12_FSMC;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	FSMC_Initialized = true;

	return S_OK;
}
