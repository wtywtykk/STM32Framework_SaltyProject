#pragma once

#include "Kernel\Common\KCommon.h"

class BodePlotterScanEngine
{
	friend class BodePlotterDataStore;
protected:
	double Start = 0.0;
	double End = 0.0;
	u32 MaxPointIndex = 0;

private:
	u32 CurPointIndex = 0;
	u32 LastTick = 0;

	const u32 PointInterval = 10;
public:
	void LoadPattern(double StartFreq, double EndFreq, u32 ScanPointCount);
	bool IsNextReady(void);
	bool IsFinished(void);
	double GetTxFreq(void);
	double GetSampleFreq(void);
	double GetNCOFreq(void);
	u32 GetCurrentIndex(void);
};
