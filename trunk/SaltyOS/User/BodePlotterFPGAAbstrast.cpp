#include "Kernel\Common\KCommon.h"
#include "HAL\FPGASPIPort.h"
#include "User\BodePlotterFPGAAbstrast.h"

BodePlotterFPGAAbstrast::BodePlotterFPGAAbstrast(void)
{
}

BodePlotterFPGAAbstrast::~BodePlotterFPGAAbstrast(void)
{
}

void BodePlotterFPGAAbstrast::ReteriveValue(s64* Val, bool* OverRange)
{
	FPGASPIPort_Receive(&FPGAResult, sizeof(FPGAResult));
	*Val = FPGAResult.Val;
	*OverRange = FPGAResult.OverRange ? true : false;
}

void BodePlotterFPGAAbstrast::SetNCO(double NCOFreq, double RefFreq)
{
	FPGAConfig.NCO = (u32)((u64)(NCOFreq * ((u64)1 << 32) / RefFreq));
	FPGASPIPort_Transmit(&FPGAConfig, sizeof(FPGAConfig));
}
