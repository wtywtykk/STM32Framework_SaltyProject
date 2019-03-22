#include "Kernel\Common\KCommon.h"
#include "HAL\UniGPIO.h"
#include "HAL\GPIO_CPLD.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "Kernel\GUI\Shape\Line.h"
#include "Kernel\GUI\Shape\Circle.h"

#include "Driver\KeyBoard.h"

#include <string.h>
#include <stdlib.h>

UniGPIO_Handle Amp1;
UniGPIO_Handle Att5;
UniGPIO_Handle Att10;
UniGPIO_Handle Amp2;
UniGPIO_Handle Bw5;
UniGPIO_Handle Bw10;

void SetIO(u8 TargetGain, u8 Bw);
void Disp(u8 Gain, u8 Bw);
void DispBackIO(void);

void aaaTaskLauncher(void)
{
	u8 TargetGain = 60;
	u8 Bw = 0;

	GPIO_CPLD_InitPin(0, 0, true, &Amp1);
	GPIO_CPLD_InitPin(0, 1, true, &Att5);
	GPIO_CPLD_InitPin(0, 2, true, &Att10);
	GPIO_CPLD_InitPin(0, 3, true, &Amp2);
	GPIO_CPLD_InitPin(0, 4, true, &Bw5);
	GPIO_CPLD_InitPin(0, 5, true, &Bw10);

	while (1)
	{
		u8 Key = KeyBoard_GetKey_Repeat();
		switch (Key)
		{
		case 1:
			//Gain+
			if (TargetGain < 60)
			{
				TargetGain += 5;
			}
			break;
		case 2:
			//Gain-
			if (TargetGain > 5)
			{
				TargetGain -= 5;
			}
			break;
		case 3:
			//Bw+
			if (Bw < 2)
			{
				Bw++;
			}
			break;
		case 4:
			//Bw-
			if (Bw)
			{
				Bw--;
			}
			break;
		default:
			break;
		}
		SetIO(TargetGain, Bw);
		Disp(TargetGain, Bw);
		DispBackIO();
	}
}

void Disp(u8 Gain, u8 Bw)
{
	FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC48;HZK48S;HZK48T"));
	char buf[128];
	pcstr BWStr;
	switch (Bw)
	{
	default:
	case 0:
		BWStr = "5MHz";
		break;
	case 1:
		BWStr = "10MHz";
		break;
	case 2:
		BWStr = "无限制";
		break;
	}
	sprintf(buf, "最大增益：%ddB    \n\r带宽：%s      ", Gain, BWStr);
	DrawStringHorizontal(g_LCDDC, FG, buf, 200, 100, 0, 0, WHITE, BLACK);
	FreeAndEraseReference(FG);
}

void SetIO(u8 TargetGain, u8 Bw)
{
	u8 GainDiff = 60 - TargetGain;
	if (GainDiff >= 20)
	{
		GainDiff -= 20;
		UniGPIO_SetLow(&Amp2);
	}
	else
	{
		UniGPIO_SetHigh(&Amp2);
	}
	if (GainDiff >= 20)
	{
		GainDiff -= 20;
		UniGPIO_SetLow(&Amp1);
	}
	else
	{
		UniGPIO_SetHigh(&Amp1);
	}
	if (GainDiff >= 10)
	{
		GainDiff -= 10;
		UniGPIO_SetHigh(&Att10);
	}
	else
	{
		UniGPIO_SetLow(&Att10);
	}
	if (GainDiff >= 5)
	{
		GainDiff -= 5;
		UniGPIO_SetHigh(&Att5);
	}
	else
	{
		UniGPIO_SetLow(&Att5);
	}

	switch (Bw)
	{
	default:
	case 0:
		UniGPIO_SetLow(&Bw5);
		UniGPIO_SetHigh(&Bw10);
		break;
	case 1:
		UniGPIO_SetHigh(&Bw5);
		UniGPIO_SetLow(&Bw10);
		break;
	case 2:
		UniGPIO_SetHigh(&Bw5);
		UniGPIO_SetHigh(&Bw10);
		break;
	}
}

void DispBackIO(void)
{
	bool Amp1Val = UniGPIO_Read(&Amp1);
	bool Att5Val = UniGPIO_Read(&Att5);
	bool Att10Val = UniGPIO_Read(&Att10);
	bool Amp2Val = UniGPIO_Read(&Amp2);
	bool Bw5Val = UniGPIO_Read(&Bw5);
	bool Bw10Val = UniGPIO_Read(&Bw10);

	FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC16"));
	DrawStringHorizontal(g_LCDDC, FG, "Amp1", 0, 0, 0, 0, Amp1Val ? RED : GREEN, BLACK);
	DrawStringHorizontal(g_LCDDC, FG, "Att5", 0, 16, 0, 0, Att5Val ? RED : GREEN, BLACK);
	DrawStringHorizontal(g_LCDDC, FG, "Att10", 0, 32, 0, 0, Att10Val ? RED : GREEN, BLACK);
	DrawStringHorizontal(g_LCDDC, FG, "Amp2", 0, 48, 0, 0, Amp2Val ? RED : GREEN, BLACK);
	DrawStringHorizontal(g_LCDDC, FG, "Bw5", 0, 64, 0, 0, Bw5Val ? RED : GREEN, BLACK);
	DrawStringHorizontal(g_LCDDC, FG, "Bw10", 0, 80, 0, 0, Bw10Val ? RED : GREEN, BLACK);
	FreeAndEraseReference(FG);
}