#pragma once

#include "Kernel\Common\KCommon.h"

class BodePlotterFPGAAbstrast
{
	typedef struct
	{
		u32 Padding[3];
		u32 NCO;
	}FPGAConfigStruct;

	typedef struct
	{
		u16 Padding[3];
		u8 Padding1;
		u8 OverRange;
		s64 Val;
	}FPGAResultStruct;

	FPGAConfigStruct FPGAConfig;
	FPGAResultStruct FPGAResult;
public:
	BodePlotterFPGAAbstrast(void);
	~BodePlotterFPGAAbstrast(void);
	void ReteriveValue(s64 * Val, bool * OverRange);
	void SetNCO(double NCOFreq, double RefFreq);
};
