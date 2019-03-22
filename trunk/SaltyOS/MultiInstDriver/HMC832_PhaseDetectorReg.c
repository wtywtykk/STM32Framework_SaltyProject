#include "HAL\HCommon.h"
#include "MultiInstDriver\HMC832.h"

//Register 0x0B, PD Register (Default 0x0F8061)
#define HMC832_PD_DEL_SEL_Shift 0
#define HMC832_PD_DEL_SEL_Mask (0x7 << HMC832_PD_DEL_SEL_Shift)
#define HMC832_PD_UP_EN_Shift 5
#define HMC832_PD_UP_EN_Mask (0x1 << HMC832_PD_UP_EN_Shift)
#define HMC832_PD_DN_EN_Shift 6
#define HMC832_PD_DN_EN_Mask (0x1 << HMC832_PD_DN_EN_Shift)
#define HMC832_CSPMode_Shift 7
#define HMC832_CSPMode_Mask (0x3 << HMC832_CSPMode_Shift)
#define HMC832_ForceCPUp_Shift 9
#define HMC832_ForceCPUp_Mask (0x1 << HMC832_ForceCPUp_Shift)
#define HMC832_ForceCPDown_Shift 10
#define HMC832_ForceCPDown_Mask (0x1 << HMC832_ForceCPDown_Shift)
#define HMC832_SPIVoltageLevel_Shift 22
#define HMC832_SPIVoltageLevel_Mask (0x1 << HMC832_SPIVoltageLevel_Shift)

void HMC832_PhaseDetector_Init(HMC832_Handle* Handle)
{
	Handle->Regs[0x0B] = 0x0F8061;
	Handle->Regs[0x0B] = HMC832_SetRegBits(Handle->Regs[0x0B], 0xFFFFFFFF, HMC832_SPIVoltageLevel_Shift, HMC832_SPIVoltageLevel_Mask);
}

void HMC832_PhaseDetector_SetDelay(HMC832_Handle* Handle, u32 Val)
{
	Handle->Regs[0x0B] = HMC832_SetRegBits(Handle->Regs[0x0B], Val, HMC832_PD_DEL_SEL_Shift, HMC832_PD_DEL_SEL_Mask);
}

void HMC832_PhaseDetector_SetEnables(HMC832_Handle* Handle, bool Up, bool Down)
{
	Handle->Regs[0x0B] = HMC832_SetRegBits(Handle->Regs[0x0B], Up ? 0xFFFFFFFF : 0x0, HMC832_PD_UP_EN_Shift, HMC832_PD_UP_EN_Mask);
	Handle->Regs[0x0B] = HMC832_SetRegBits(Handle->Regs[0x0B], Up ? 0xFFFFFFFF : 0x0, HMC832_PD_DN_EN_Shift, HMC832_PD_DN_EN_Mask);
}

void HMC832_PhaseDetector_SetCSPMode(HMC832_Handle* Handle, u32 Val)
{
	Handle->Regs[0x0B] = HMC832_SetRegBits(Handle->Regs[0x0B], Val, HMC832_CSPMode_Shift, HMC832_CSPMode_Mask);
}

void HMC832_PhaseDetector_SetForce(HMC832_Handle* Handle, bool Up, bool Down)
{
	Handle->Regs[0x0B] = HMC832_SetRegBits(Handle->Regs[0x0B], Up ? 0xFFFFFFFF : 0x0, HMC832_ForceCPUp_Shift, HMC832_ForceCPUp_Mask);
	Handle->Regs[0x0B] = HMC832_SetRegBits(Handle->Regs[0x0B], Down ? 0xFFFFFFFF : 0x0, HMC832_ForceCPDown_Shift, HMC832_ForceCPDown_Mask);
}
