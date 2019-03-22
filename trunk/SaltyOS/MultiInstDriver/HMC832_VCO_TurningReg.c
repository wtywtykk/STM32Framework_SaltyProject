#include "HAL\HCommon.h"
#include "MultiInstDriver\HMC832.h"

//VCO_REG 0x00, Tuning Register
#define HMC832_CAL_Shift 0
#define HMC832_CAL_Mask (0x1 << HMC832_CAL_Shift)
#define HMC832_CAPS_Shift 1
#define HMC832_CAPS_Mask (0xFF << HMC832_CAPS_Shift)

void HMC832_VCO_Turning_Init(HMC832_Handle* Handle)
{
	Handle->VCORegs[0] = 0x0020;
}

void HMC832_VCO_Turning_SetSubband(HMC832_Handle* Handle, u8 Val)
{
	Handle->VCORegs[0] = HMC832_SetRegBits(Handle->VCORegs[0], Val, HMC832_CAPS_Shift, HMC832_CAPS_Mask);
}
