#include "Kernel\Common\KCommon.h"
#include "User\BodePlotterDataStore.h"
#include <stdlib.h>
#include <math.h>

BodePlotterDataStore::BodePlotterDataStore(BodePlotterScanEngine* ScanEngine)
{
	Start = ScanEngine->Start;
	End = ScanEngine->End;
	MaxPointIndex = ScanEngine->MaxPointIndex;

	Buffer = (BodePlotterDataType*)malloc(sizeof(BodePlotterDataType) * (MaxPointIndex + 1));

	LastPointIndex = 0;
}

BodePlotterDataStore::~BodePlotterDataStore()
{
	free(Buffer);
}

void BodePlotterDataStore::AddData(BodePlotterDataType Val)
{
	if (Buffer == NULL)
	{
		return;
	}
	if (LastPointIndex <= MaxPointIndex)
	{
		Buffer[LastPointIndex] = Val;
		LastPointIndex++;
	}
}

BodePlotterDataType BodePlotterDataStore::GetData(u32 Index)
{
	if (Buffer == NULL)
	{
		return 0.0;
	}
	if (Index <= LastPointIndex)
	{
		return Buffer[Index];
	}
	return 0.0;
}

double BodePlotterDataStore::GetFreq(u32 Index)
{
	return Start + (End - Start) * Index / MaxPointIndex;
}

double BodePlotterDataStore::GetStartFreq(void)
{
	return Start;
}

double BodePlotterDataStore::GetEndFreq(void)
{
	return GetFreq(LastPointIndex - 1);
}

bool BodePlotterDataStore::IsFinished(void)
{
	if (LastPointIndex == MaxPointIndex + 1)
	{
		return true;
	}
	return false;
}

u32 BodePlotterDataStore::GetFreqIndex(double Freq)
{
	float Ret = MaxPointIndex * (Freq - Start) / (End - Start) + 0.5;
	if (Ret < 0.0)
	{
		Ret = 0;
	}
	if (Ret > LastPointIndex)
	{
		Ret = LastPointIndex;
	}
	return Ret;
}
