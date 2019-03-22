#include "HAL\HCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\DC\ClippedDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "HAL\UniGPIO.h"
#include "Kernel\GUI\Shape\Line.h"
#include "Kernel\GUI\Shape\Circle.h"
#include <math.h>

TIM_HandleTypeDef htim3;

#define sqr(x) ((x)*(x))

void TIM3_Init(void)
{
	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;
	TIM_IC_InitTypeDef sConfigIC;

	//__HAL_RCC_TIM3_CLK_ENABLE();
	SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);
	HAL_Delay(1);

	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 26;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 65535;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
	{
		while (1);
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
	{
		while (1);
	}

	if (HAL_TIM_IC_Init(&htim3) != HAL_OK)
	{
		while (1);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
	{
		while (1);
	}

	sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
	sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
	sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
	sConfigIC.ICFilter = 0;
	if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
	{
		while (1);
	}

	if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
	{
		while (1);
	}

	if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_3) != HAL_OK)
	{
		while (1);
	}

	if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_4) != HAL_OK)
	{
		while (1);
	}
}

void CalcPos(float deltaX, float deltaY, float* X, float* Y)
{
	float TargetX = 0.5;
	float TargetY = 0.5;

	for (u32 i = 1; i <= 100; i++)
	{
		float dX;
		float dY;
		float AverageFactor;
		AverageFactor = i * 2;
		dX = sqrtf(sqr(TargetX) + sqr(TargetY)) - sqrtf(sqr(TargetX - 1.0) + sqr(TargetY));
		if (dX > deltaX)
		{
			TargetX = TargetX * AverageFactor / (AverageFactor + 1);
		}
		else if (dX < deltaX)
		{
			TargetX = (TargetX * AverageFactor + 1.0) / (AverageFactor + 1);
		}
		dY = sqrtf(sqr(TargetX) + sqr(TargetY)) - sqrtf(sqr(TargetX) + sqr(TargetY - 1.0));
		if (dY > deltaY)
		{
			TargetY = TargetY * AverageFactor / (AverageFactor + 1);
		}
		else if (dY < deltaY)
		{
			TargetY = (TargetY * AverageFactor + 1.0) / (AverageFactor + 1);
		}
	}
	*X = TargetX;
	*Y = TargetY;
}

void UsPosTest(void)
{
	FONTGROUP* FGs = NewReferenceSafe(new_noexcpt FONTGROUP("ASC48"));
	GPIO_InitTypeDef GPIO_InitStruct;
	UniGPIO_Handle KeyHandle;

	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_32_InitPin(GPIOC, &GPIO_InitStruct, NULL);

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_32_InitPin(GPIOC, &GPIO_InitStruct, &KeyHandle);

	TIM3_Init();
	HAL_TIM_IC_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_IC_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_IC_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_IC_Start(&htim3, TIM_CHANNEL_4);

	float UnitdX = 1;
	float UnitdY = 1;
	while (1)
	{
		while (!(__HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_CC1) && __HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_CC2) && __HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_CC3)));
		if (!(__HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_CC1OF) || __HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_CC2OF) || __HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_CC3OF)))
		{
			float dX = (float)(u16)__HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1) - (u16)__HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_2);
			float dY = (float)(u16)__HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_1) - (u16)__HAL_TIM_GET_COMPARE(&htim3, TIM_CHANNEL_3);
			if (UniGPIO_Read(&KeyHandle))
			{
				UnitdX = (UnitdX * 10 + dX) / 11;
				UnitdY = (UnitdY * 10 + dY) / 11;
			}
			DC* cache = NewReferenceSafe(new_noexcpt CLIPPEDDC(g_LCDDC, 0, 0, g_LCDDC->GetWidth(), g_LCDDC->GetHeight(), true, false));

			cache->Fill(0, 0, 400, 400, BLACK);
			DrawLine(cache, 400, 0, 400, 400, GREEN);
			DrawLine(cache, 0, 400, 400, 400, GREEN);
			for (u32 i = 0; i < 400; i += 40)
			{
				DrawLine(cache, i, 0, i, 400, DGRAY);
				DrawLine(cache, 0, i, 400, i, DGRAY);
			}

			float PosX, PosY;
			CalcPos(dX / UnitdX, dY / UnitdY, &PosX, &PosY);
			DrawCircle(cache, 400 * PosX, 400 * PosY, 3, RED);

			char Buf[256];
			sprintf(Buf, "X:%ld; Y:%ld dx:%ld dy:%ld       ", (s32)(PosX * 100), (s32)(PosY * 100), (s32)(1000 * dX / UnitdX), (s32)(1000 * dY / UnitdY));
			DrawStringHorizontal(cache, FGs, Buf, 0, 410, 0, 0, WHITE, BLACK);
			FreeAndEraseReference(cache);
		}
		__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_CC1);
		__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_CC2);
		__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_CC3);
		__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_CC4);
		__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_CC1OF);
		__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_CC2OF);
		__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_CC3OF);
		__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_CC4OF);
	}
	FreeAndEraseReference(FGs);
}
