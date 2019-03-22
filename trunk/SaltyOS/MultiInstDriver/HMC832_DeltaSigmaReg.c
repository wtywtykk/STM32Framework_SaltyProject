#include "HAL\HCommon.h"
#include "MultiInstDriver\HMC832.h"

//Register 0x06, ж▓ - жд Configuration Register(Default 0x200B4A)
#define HMC832_Seed_Shift 0
#define HMC832_Seed_Mask (0x3 << HMC832_Seed_Shift)
#define HMC832_FRAC_BYPASS_Shift 7
#define HMC832_FRAC_BYPASS_Mask (0x1 << HMC832_FRAC_BYPASS_Shift)
#define HMC832_Initialization_Shift 8
#define HMC832_Initialization_Mask (0x7 << HMC832_Initialization_Shift)
#define HMC832_SDenable_Shift 11
#define HMC832_SDenable_Mask (0x1 << HMC832_SDenable_Shift)
#define HMC832_AutomaticClockConfiguration_Shift 21
#define HMC832_AutomaticClockConfiguration_Mask (0x1 << HMC832_AutomaticClockConfiguration_Shift)

void HMC832_DeltaSigma_Init(HMC832_Handle* Handle)
{
	Handle->Regs[6] = 0x200B4A;
	Handle->Regs[6] = HMC832_SetRegBits(Handle->Regs[6], 2, HMC832_Seed_Shift, HMC832_Seed_Mask);
	Handle->Regs[6] = HMC832_SetRegBits(Handle->Regs[6], 0, HMC832_FRAC_BYPASS_Shift, HMC832_FRAC_BYPASS_Mask);
	Handle->Regs[6] = HMC832_SetRegBits(Handle->Regs[6], 7, HMC832_Initialization_Shift, HMC832_Initialization_Mask);
	Handle->Regs[6] = HMC832_SetRegBits(Handle->Regs[6], 1, HMC832_SDenable_Shift, HMC832_SDenable_Mask);
	Handle->Regs[6] = HMC832_SetRegBits(Handle->Regs[6], 0, HMC832_AutomaticClockConfiguration_Shift, HMC832_AutomaticClockConfiguration_Mask);
}

void HMC832_DeltaSigma_SetFracEnable(HMC832_Handle* Handle, bool Enable)
{
	Handle->Regs[6] = HMC832_SetRegBits(Handle->Regs[6], Enable ? 0 : 0xFFFFFFFF, HMC832_FRAC_BYPASS_Shift, HMC832_FRAC_BYPASS_Mask);
	Handle->Regs[6] = HMC832_SetRegBits(Handle->Regs[6], Enable ? 0xFFFFFFFF : 0, HMC832_SDenable_Shift, HMC832_SDenable_Mask);
}
