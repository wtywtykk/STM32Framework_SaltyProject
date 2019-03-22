#include "Kernel\Common\KCommon.h"
#include "User\LoadRecogniseSampler.h"
#include "User\LoadRecogniseCharacteristicProvider.h"
#include "User\LoadRecogniseContext.h"
#include "User\LoadRecogniseEngine.h"
#include "Kernel\FlashFS\FlashFS.h"
#include <math.h>
#include <assert.h>

RandomizedLoadCharacteristic Loads[LoadCount];
bool LoadState[LoadCount];

#define LoadRecogniseEngineDataFileName "Load.Dat"

void LoadRecogniseEngine_ExtractRandomalizedCharacteristic(RandomizedLoadCharacteristic* RandChar, LoadCharacteristic* Char, u8 Count)
{
	float PowerAverage = 0.0;
	float PowerVariance = 0.0;
	float HarmonicReAverage[HarmonicCount];
	float HarmonicReVariance[HarmonicCount];
	float HarmonicImAverage[HarmonicCount];
	float HarmonicImVariance[HarmonicCount];
	float PeaksCenterAverage[SpectrumPeakCount];
	float PeaksWidthAverage[SpectrumPeakCount];
	float PeaksAreaAverage[SpectrumPeakCount];
	float PeaksAreaVariance[SpectrumPeakCount];
	for (u8 i = 0; i < HarmonicCount; i++)
	{
		HarmonicReAverage[i] = 0.0;
		HarmonicReVariance[i] = 0.0;
		HarmonicImAverage[i] = 0.0;
		HarmonicImVariance[i] = 0.0;
	}
	for (u8 i = 0; i < SpectrumPeakCount; i++)
	{
		PeaksCenterAverage[i] = 0.0;
		PeaksWidthAverage[i] = 0.0;
		PeaksAreaAverage[i] = 0.0;
		PeaksAreaVariance[i] = 0.0;
	}
	for (u8 i = 0; i < Count; i++)
	{
		PowerAverage += Char[i].Power;
		for (u8 j = 0; j < HarmonicCount; j++)
		{
			HarmonicReAverage[j] += Char[i].Harmonic[j].Re;
			HarmonicImAverage[j] += Char[i].Harmonic[j].Im;
		}
	}
	for (u8 i = 0; i < 1; i++)
	{
		for (u8 j = 0; j < SpectrumPeakCount; j++)
		{
			PeaksCenterAverage[j] += Char[i].SpectrumPeak[j].Center;
			PeaksWidthAverage[j] += Char[i].SpectrumPeak[j].Width;
			PeaksAreaAverage[j] += Char[i].SpectrumPeak[j].Area;
		}
	}
	PowerAverage /= Count;
	for (u8 i = 0; i < HarmonicCount; i++)
	{
		HarmonicReAverage[i] /= Count;
		HarmonicImAverage[i] /= Count;
	}
	for (u8 i = 0; i < SpectrumPeakCount; i++)
	{
		PeaksCenterAverage[i] /= Count;
		PeaksWidthAverage[i] /= Count;
	}
	for (u8 i = 0; i < Count; i++)
	{
		PowerVariance += (Char[i].Power - PowerAverage) * (Char[i].Power - PowerAverage);
		for (u8 j = 0; j < HarmonicCount; j++)
		{
			HarmonicReVariance[j] += (Char[i].Harmonic[j].Re - HarmonicReAverage[j]) * (Char[i].Harmonic[j].Re - HarmonicReAverage[j]);
			HarmonicImVariance[j] += (Char[i].Harmonic[j].Im - HarmonicImAverage[j]) * (Char[i].Harmonic[j].Im - HarmonicImAverage[j]);
		}
	}
	for (u8 i = 0; i < 1; i++)
	{
		for (u8 j = 0; j < SpectrumPeakCount; j++)
		{
			PeaksAreaVariance[j] += (Char[i].SpectrumPeak[j].Center - PeaksCenterAverage[j]) * (Char[i].SpectrumPeak[j].Center - PeaksCenterAverage[j]);
			PeaksAreaVariance[j] += (Char[i].SpectrumPeak[j].Width - PeaksWidthAverage[j]) * (Char[i].SpectrumPeak[j].Width - PeaksWidthAverage[j]);
			PeaksAreaVariance[j] += (Char[i].SpectrumPeak[j].Area - PeaksAreaAverage[j]) * (Char[i].SpectrumPeak[j].Area - PeaksAreaAverage[j]);
		}
	}
	PowerVariance /= Count;
	for (u8 i = 0; i < HarmonicCount; i++)
	{
		HarmonicReVariance[i] /= Count;
		HarmonicImVariance[i] /= Count;
	}
	for (u8 i = 0; i < SpectrumPeakCount; i++)
	{
		PeaksAreaVariance[i] /= Count;
	}
	RandChar->Power.Average = PowerAverage;
	RandChar->Power.Variance = PowerVariance;
	for (u8 i = 0; i < HarmonicCount; i++)
	{
		RandChar->Harmonic[i].Re.Average = HarmonicReAverage[i];
		RandChar->Harmonic[i].Re.Variance = HarmonicReVariance[i];
		RandChar->Harmonic[i].Im.Average = HarmonicImAverage[i];
		RandChar->Harmonic[i].Im.Variance = HarmonicImVariance[i];
	}
	for (u8 i = 0; i < SpectrumPeakCount; i++)
	{
		RandChar->SpectrumPeak[i].Center = PeaksCenterAverage[i];
		RandChar->SpectrumPeak[i].Width = PeaksWidthAverage[i];
		RandChar->SpectrumPeak[i].Area.Average = PeaksAreaAverage[i];
		//RandChar->SpectrumPeak[i].Area.Variance = PeaksAreaVariance[i];
		RandChar->SpectrumPeak[i].Area.Variance = PeaksWidthAverage[i] / 100;
	}
}

float LoadRecogniseEngine_JudgeErrorFunction(float x, float Var)
{
	float Ret;
	if (x < 1.0)
	{
		Ret = x;
	}
	else
	{
		Ret = 1 / x;
	}
	if (Var < 0.5)
	{
		Var = 0.5;
	}
	else if (Var > 2)
	{
		Var = 2;
	}
	return powf(Ret, 1 / Var);
}

float LoadRecogniseEngine_GetPowerWeight(void)
{
	float Weight = 1;
	float CurPower = 0;
	for (u8 i = 0; i < LoadCount; i++)
	{
		if (LoadState[i])
		{
			float Var = Loads[i].Power.Variance * 10;
			if (Var > 1)
			{
				Weight /= Var;
			}
			CurPower += Loads[i].Power.Average;
		}
	}
	if (CurPower > 5)
	{
		Weight /= CurPower / 5;
	}
	return Weight;
}

void LoadRecogniseEngine_JudgeStateChange(RandomizedLoadCharacteristic* RandChar, s8* Status, float PowerWeight)
{
	if (RandChar->Power.Average <= 0.0)
	{
		*Status = -1;
	}
	else
	{
		float CurPower;
		LoadRecogniseCharacteristicProvider_GetBasicCharacteristic(NULL, NULL, &CurPower);
		if (RandChar->Power.Average > 2.0 * CurPower)
		{
			*Status = -1;
			return;
		}

		float PowerJudgeValue = 0;
		float PowerVariance = 0;
		float HarmonicJudgeValue = 0;
		float HarmonicVariance = 0;
		float SpectrumJudgeValue = 0;
		float SpectrumVariance = 0;
		float TotalJudgeValue = 0;
		float TotalVariance = 0;
		LoadCharacteristic CurrentCharacteristic;
		LoadRecogniseCharacteristicProvider_GetCharacteristicRecord(&CurrentCharacteristic);

		PowerJudgeValue = LoadRecogniseEngine_JudgeErrorFunction(CurrentCharacteristic.Power / RandChar->Power.Average, RandChar->Power.Variance) / RandChar->Power.Variance;
		PowerVariance = 1.0 / RandChar->Power.Variance;

		for (u8 i = 0; i < HarmonicCount; i++)
		{
			HarmonicJudgeValue += LoadRecogniseEngine_JudgeErrorFunction(CurrentCharacteristic.Harmonic->Re / RandChar->Harmonic->Re.Average, RandChar->Harmonic->Re.Variance) / RandChar->Harmonic->Re.Variance;
			HarmonicVariance += 1.0 / sqrtf(RandChar->Harmonic->Re.Variance);
			HarmonicJudgeValue += LoadRecogniseEngine_JudgeErrorFunction(CurrentCharacteristic.Harmonic->Im / RandChar->Harmonic->Im.Average, RandChar->Harmonic->Im.Variance) / RandChar->Harmonic->Im.Variance;
			HarmonicVariance += 1.0 / sqrtf(RandChar->Harmonic->Im.Variance);
		}

		for (u8 i = 0; i < SpectrumPeakCount; i++)
		{
			SpectrumJudgeValue += LoadRecogniseEngine_JudgeErrorFunction(LoadRecogniseCharacteristicProvider_GetSpectrumArea(RandChar->SpectrumPeak[i].Center, RandChar->SpectrumPeak[i].Width) / RandChar->SpectrumPeak[i].Area.Average, RandChar->SpectrumPeak[i].Area.Variance) / RandChar->SpectrumPeak[i].Area.Variance;
			SpectrumVariance += 1.0 / RandChar->SpectrumPeak[i].Area.Variance;
		}
		if (isnanf(SpectrumJudgeValue) || isnanf(SpectrumVariance))
		{
			SpectrumJudgeValue = 0.0;
			SpectrumVariance = 0.0;
		}


		TotalJudgeValue = PowerWeight * 0.1 * PowerJudgeValue + (1 - PowerWeight) * (HarmonicJudgeValue + 5 * SpectrumJudgeValue);
		TotalVariance = PowerWeight * 0.1 * PowerVariance + (1 - PowerWeight) * (HarmonicVariance + 5 * SpectrumVariance);

		TotalJudgeValue /= TotalVariance;

		if (TotalJudgeValue > 0.7)
		{
			if (CurrentCharacteristic.Power > RandChar->Power.Average * 0.5)
			{
				*Status = 1;
			}
		}
		else if (TotalJudgeValue < -0.3)
		{
			*Status = -1;
		}
		else
		{
			*Status = 0;
		}
	}
}

void LoadRecogniseEngine_CheckStateChange(void)
{
	float PowerWeight = LoadRecogniseEngine_GetPowerWeight();

	for (u8 i = 0; i < LoadCount; i++)
	{
		s8 StateChange = 0;
		LoadRecogniseEngine_JudgeStateChange(&Loads[i], &StateChange, PowerWeight);
		if (StateChange == -1)
		{
			LoadState[i] = false;
		}
		else if (StateChange == 1)
		{
			LoadState[i] = true;
		}
	}
}

bool LoadRecogniseEngine_GetState(u8 Index)
{
	assert(Index < LoadCount);
	return LoadState[Index];
}

void LoadRecogniseEngine_Learn(u8 Index, LoadCharacteristic* Char, u8 Count)
{
	assert(Index < LoadCount);
	LoadRecogniseEngine_ExtractRandomalizedCharacteristic(&Loads[Index], Char, Count);
}

void LoadRecogniseEngine_Remove(u8 Index)
{
	assert(Index < LoadCount);
	Loads[Index].Power.Average = -1;
}

void LoadRecogniseEngine_LoadData(void)
{
	u32 BytesRead = 0;
	if (FlashFS_Read(LoadRecogniseEngineDataFileName, Loads, 0, sizeof(Loads), &BytesRead) != S_OK || BytesRead != sizeof(Loads))
	{
		for (u8 i = 0; i < LoadCount; i++)
		{
			Loads[i].Power.Average = -1;
		}
		return;
	}
}

STATUS LoadRecogniseEngine_SaveData(void)
{
	return FlashFS_Write(LoadRecogniseEngineDataFileName, Loads, 0, sizeof(Loads), NULL);
}
