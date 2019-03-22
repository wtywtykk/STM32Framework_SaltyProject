#include "HAL\HCommon.h"
#include "MultiInstDriver\HMC832.h"

//VCO_REG 0x07, Output Power Control Register
#define HMC832_OutputStageGainControl_Shift 0
#define HMC832_OutputStageGainControl_Mask (0xF << HMC832_OutputStageGainControl_Shift)
#define HMC832_Initialization_Shift 4
#define HMC832_Initialization_Mask (0x1 << HMC832_Initialization_Shift)
#define HMC832_Reserved4d_Shift 5
#define HMC832_Reserved4d_Mask (0xF << HMC832_Reserved4d_Shift)

void HMC832_VCO_OutputPowerControl_Init(HMC832_Handle* Handle)
{
	Handle->VCORegs[7] = 0x008F;
	Handle->VCORegs[7] = HMC832_SetRegBits(Handle->VCORegs[7], 1, HMC832_Initialization_Shift, HMC832_Initialization_Mask);
	Handle->VCORegs[7] = HMC832_SetRegBits(Handle->VCORegs[7], 4, HMC832_Reserved4d_Shift, HMC832_Reserved4d_Mask);
}

void HMC832_VCO_OutputPowerControl_SetOutputStageGainControl(HMC832_Handle* Handle, u8 Val)
{
	Handle->VCORegs[7] = HMC832_SetRegBits(Handle->VCORegs[7], Val, HMC832_OutputStageGainControl_Shift, HMC832_OutputStageGainControl_Mask);
}
