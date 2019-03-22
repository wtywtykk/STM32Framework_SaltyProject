#pragma once

#include "Kernel\Common\KCommon.h"
#include "User\BodePlotterScanEngine.h"

typedef double BodePlotterDataType;

class BodePlotterDataStore
{
private:
	double Start;
	double End;
	u32 MaxPointIndex;
	BodePlotterDataType* Buffer;
	u32 LastPointIndex;
public:
	BodePlotterDataStore(BodePlotterScanEngine* ScanEngine);
	~BodePlotterDataStore();
	void AddData(BodePlotterDataType Val);
	BodePlotterDataType GetData(u32 Index);
	double GetFreq(u32 Index);
	double GetStartFreq(void);
	double GetEndFreq(void);
	bool IsFinished(void);
	u32 GetFreqIndex(double Freq);
};
