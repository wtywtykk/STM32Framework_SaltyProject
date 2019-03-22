#include "HAL\HCommon.h"
#include "MultiInstDriver\HMC832.h"

//VCO_REG 0x04, Calibration/Bias Register
//VCO_REG 0x05, CF_CAL Register
//VCO_REG 0x06, MSB Calibration Register

void HMC832_VCO_Reserved_Init(HMC832_Handle* Handle)
{
	Handle->VCORegs[4] = 201;
	Handle->VCORegs[5] = 170;
	Handle->VCORegs[6] = 255;
}
