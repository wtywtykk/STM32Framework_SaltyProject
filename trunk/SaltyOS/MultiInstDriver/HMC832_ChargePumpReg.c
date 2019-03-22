#include "HAL\HCommon.h"
#include "MultiInstDriver\HMC832.h"

//Register 0x09, Charge Pump Register (Default 0x403264)
#define HMC832_CPDownGain_Shift 0
#define HMC832_CPDownGain_Mask (0x7F << HMC832_CPDownGain_Shift)
#define HMC832_CPUpGain_Shift 7
#define HMC832_CPUpGain_Mask (0x7F << HMC832_CPUpGain_Shift)
#define HMC832_OffsetMagnitude_Shift 14
#define HMC832_OffsetMagnitude_Mask (0x7F << HMC832_OffsetMagnitude_Shift)
#define HMC832_OffsetUpEnable_Shift 21
#define HMC832_OffsetUpEnable_Mask (0x1 << HMC832_OffsetUpEnable_Shift)
#define HMC832_OffsetDownEnable_Shift 22
#define HMC832_OffsetDownEnable_Mask (0x1 << HMC832_OffsetDownEnable_Shift)

void HMC832_ChargePump_Init(HMC832_Handle* Handle)
{
	Handle->Regs[9] = 0x403264;
	Handle->Regs[9] = HMC832_SetRegBits(Handle->Regs[9], 0xFFFFFFFF, HMC832_OffsetUpEnable_Shift, HMC832_OffsetUpEnable_Mask);
	Handle->Regs[9] = HMC832_SetRegBits(Handle->Regs[9], 0x0, HMC832_OffsetDownEnable_Shift, HMC832_OffsetDownEnable_Mask);
}

void HMC832_ChargePump_SetGain(HMC832_Handle* Handle, u32 DownGain, u32 UpGain)
{
	Handle->Regs[9] = HMC832_SetRegBits(Handle->Regs[9], DownGain, HMC832_CPDownGain_Shift, HMC832_CPDownGain_Mask);
	Handle->Regs[9] = HMC832_SetRegBits(Handle->Regs[9], UpGain, HMC832_CPUpGain_Shift, HMC832_CPUpGain_Mask);
}

void HMC832_ChargePump_SetOffset(HMC832_Handle* Handle, u32 Mag, bool Up, bool Down)
{
	Handle->Regs[9] = HMC832_SetRegBits(Handle->Regs[9], Mag, HMC832_OffsetMagnitude_Shift, HMC832_OffsetMagnitude_Mask);
	Handle->Regs[9] = HMC832_SetRegBits(Handle->Regs[9], Up ? 0xFFFFFFFF : 0x0, HMC832_OffsetUpEnable_Shift, HMC832_OffsetUpEnable_Mask);
	Handle->Regs[9] = HMC832_SetRegBits(Handle->Regs[9], Down ? 0xFFFFFFFF : 0x0, HMC832_OffsetDownEnable_Shift, HMC832_OffsetDownEnable_Mask);
}
