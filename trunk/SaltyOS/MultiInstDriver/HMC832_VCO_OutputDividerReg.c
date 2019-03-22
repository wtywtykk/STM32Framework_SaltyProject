#include "HAL\HCommon.h"
#include "MultiInstDriver\HMC832.h"

//VCO_REG 0x02, Output Divider Register
#define HMC832_RFDivideRatio_Shift 0
#define HMC832_RFDivideRatio_Mask (0x3F << HMC832_RFDivideRatio_Shift)

void HMC832_VCO_OutputDivider_Init(HMC832_Handle* Handle)
{
	Handle->VCORegs[2] = 0x0001;
}

void HMC832_VCO_OutputDivider_Set(HMC832_Handle* Handle, u8 Val)
{
	Handle->VCORegs[2] = HMC832_SetRegBits(Handle->VCORegs[2], Val, HMC832_RFDivideRatio_Shift, HMC832_RFDivideRatio_Mask);
}
