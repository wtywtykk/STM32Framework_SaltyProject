#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "User\BodePlotterScanEngine.h"
#include <math.h>

void BodePlotterScanEngine::LoadPattern(double StartFreq, double EndFreq, u32 ScanPointCount)
{
	Start = StartFreq;
	End = EndFreq;
	MaxPointIndex = ScanPointCount - 1;

	CurPointIndex = 0;
	LastTick = HAL_GetTick();
}

bool BodePlotterScanEngine::IsNextReady(void)
{
	if (HAL_GetTick() < LastTick + PointInterval)
	{
		return false;
	}
	else
	{
		if (CurPointIndex < MaxPointIndex)
		{
			CurPointIndex++;
			LastTick = HAL_GetTick();
		}
		return true;
	}
}

bool BodePlotterScanEngine::IsFinished(void)
{
	if (CurPointIndex == MaxPointIndex)
	{
		if (HAL_GetTick() < LastTick + PointInterval)
		{
			return false;
		}
		return true;
	}
	return false;
}

double BodePlotterScanEngine::GetTxFreq(void)
{
	return Start + (End - Start) * CurPointIndex / MaxPointIndex;
}

double BodePlotterScanEngine::GetSampleFreq(void)
{
	double Freq = GetTxFreq() * 97.0 / 37.0;
	if (Freq < 50.0e6)
	{
		Freq = 97.0e6;
	}
	while (Freq > 120.0e6)
	{
		Freq = Freq * 31.0 / 37.0;
	}
	return Freq;
	//return 120e6;
}

double BodePlotterScanEngine::GetNCOFreq(void)
{
	double TxFreq = GetTxFreq();
	double SampleFreq = GetSampleFreq();
	while (TxFreq > SampleFreq)
	{
		TxFreq -= SampleFreq;
	}
	if (TxFreq >= SampleFreq / 2)
	{
		TxFreq = SampleFreq - TxFreq;
	}
	return TxFreq;
}

u32 BodePlotterScanEngine::GetCurrentIndex(void)
{
	return CurPointIndex;
}
