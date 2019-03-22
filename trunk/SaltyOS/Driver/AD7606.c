#include "HAL\HCommon.h"
#include "HAL\PeripheralBus.h"

bool AD7606_Initialized = false;

//GPIOD
#define AD7606_RD GPIO_PIN_2
#define AD7606_BUSY GPIO_PIN_3
//GPIOG
#define AD7606_STBY GPIO_PIN_8
#define AD7606_RESET GPIO_PIN_11
#define AD7606_CONVA GPIO_PIN_13
#define AD7606_CONVB GPIO_PIN_14
#define AD7606_FRSTDATA GPIO_PIN_15

uint ResultsReady = 0;
s16 ConvertResults[8] = { 0 };

STATUS AD7606_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	if (AD7606_Initialized)
	{
		return S_OK;
	}

	if (PeripheralBus_Init() != S_OK)
	{
		return S_FAIL;
	}

	GPIO_InitStruct.Pin = AD7606_RD;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = 0;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = AD7606_BUSY;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = 0;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = AD7606_STBY | AD7606_RESET | AD7606_CONVA | AD7606_CONVB;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = 0;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = AD7606_FRSTDATA;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = 0;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	HAL_GPIO_WritePin(GPIOD, AD7606_RD, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOG, AD7606_STBY | AD7606_RESET | AD7606_CONVA | AD7606_CONVB, GPIO_PIN_SET);
	HAL_Delay(1);
	//Reset several times just to make sure
	HAL_GPIO_WritePin(GPIOG, AD7606_RESET, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOG, AD7606_RESET, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOG, AD7606_RESET, GPIO_PIN_RESET);
	HAL_Delay(1);

	AD7606_Initialized = true;

	return S_OK;
}

void AD7606_Standby(void)
{
	HAL_GPIO_WritePin(GPIOG, AD7606_STBY, GPIO_PIN_RESET);
}

void AD7606_Wakeup(void)
{
	HAL_GPIO_WritePin(GPIOG, AD7606_STBY, GPIO_PIN_SET);
	HAL_Delay(1);
	//Reset several times just to make sure
	HAL_GPIO_WritePin(GPIOG, AD7606_RESET, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOG, AD7606_RESET, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOG, AD7606_RESET, GPIO_PIN_RESET);
	HAL_Delay(1);
}

void AD7606_ConvertA(void)
{
	ResultsReady = 0;
	HAL_GPIO_WritePin(GPIOG, AD7606_CONVA, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG, AD7606_CONVA, GPIO_PIN_SET);
}

void AD7606_ConvertB(void)
{
	ResultsReady = 0;
	HAL_GPIO_WritePin(GPIOG, AD7606_CONVB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG, AD7606_CONVB, GPIO_PIN_SET);
}

void AD7606_ConvertBoth(void)
{
	ResultsReady = 0;
	HAL_GPIO_WritePin(GPIOG, AD7606_CONVA | AD7606_CONVB, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG, AD7606_CONVA | AD7606_CONVB, GPIO_PIN_SET);
}

bool AD7606_IsBusy(void)
{
	return (HAL_GPIO_ReadPin(GPIOD, AD7606_BUSY) == GPIO_PIN_SET) ? true : false;
}

void AD7606_Wait(void)
{
	while (HAL_GPIO_ReadPin(GPIOD, AD7606_BUSY) == GPIO_PIN_SET);
}

STATUS AD7606_GetRestltsFromChip(void)
{
	if (!ResultsReady)
	{
		uint i = 10;
		//New convert started.We need to read the data from AD again.
		//PeripheralBus_PrepareInput();
		for (; i > 0; i--)
		{
			HAL_GPIO_WritePin(GPIOD, AD7606_RD, GPIO_PIN_RESET);
			if (HAL_GPIO_ReadPin(GPIOG, AD7606_FRSTDATA) == GPIO_PIN_SET)
			{
				break;
			}
			HAL_GPIO_WritePin(GPIOD, AD7606_RD, GPIO_PIN_SET);
		}
		if (i == 0)
		{
			//Error,can't find first data
			return S_FAIL;
		}
		//Read first 7 channels.The last channel is read separately to ensure that RD is tied high after read.
		for (i = 0; i < 7; i++)
		{
			//*((u16*)ConvertResults + i) = PeripheralBus_Read();
			HAL_GPIO_WritePin(GPIOD, AD7606_RD, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, AD7606_RD, GPIO_PIN_RESET);
		}
		//*((u16*)ConvertResults + 7) = PeripheralBus_Read();
		HAL_GPIO_WritePin(GPIOD, AD7606_RD, GPIO_PIN_SET);

		ResultsReady = 1;
	}

	return S_OK;
}

s16 AD7606_GetResult(u16 Index)
{
	assert(Index < 8);

	if (AD7606_GetRestltsFromChip() != S_OK)
	{
		return 0;
	}

	return ConvertResults[Index];
}
