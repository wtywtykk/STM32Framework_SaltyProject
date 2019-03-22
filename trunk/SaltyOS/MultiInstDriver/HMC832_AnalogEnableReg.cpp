#include "HAL\HCommon.h"
#include "MultiInstDriver\HMC832.h"

//Register 0x08, Analog EN Register (Default 0xC1BEFF)
#define HMC832_BIAS_EN_Shift 0
#define HMC832_BIAS_EN_Mask (0x1 << HMC832_BIAS_EN_Shift)
#define HMC832_CP_EN_Shift 1
#define HMC832_CP_EN_Mask (0x1 << HMC832_CP_EN_Shift)
#define HMC832_PD_EN_Shift 2
#define HMC832_PD_EN_Mask (0x1 << HMC832_PD_EN_Shift)
#define HMC832_REFBUF_EN_Shift 3
#define HMC832_REFBUF_EN_Mask (0x1 << HMC832_REFBUF_EN_Shift)
#define HMC832_VCOBUF_EN_Shift 4
#define HMC832_VCOBUF_EN_Mask (0x1 << HMC832_VCOBUF_EN_Shift)
#define HMC832_GPO_PAD_EN_Shift 5
#define HMC832_GPO_PAD_EN_Mask (0x1 << HMC832_GPO_PAD_EN_Shift)
#define HMC832_VCOBufferAndPrescalerBiasEnable_Shift 10
#define HMC832_VCOBufferAndPrescalerBiasEnable_Mask (0x1 << HMC832_VCOBufferAndPrescalerBiasEnable_Shift)
#define HMC832_HighFrequencyReference_Shift 21
#define HMC832_HighFrequencyReference_Mask (0x1 << HMC832_HighFrequencyReference_Shift)

void HMC832_AnalogEnable_Init(HMC832_Handle* Handle)
{
	Handle->Regs[8] = 0xC1BEFF;
	Handle->Regs[8] = HMC832_SetRegBits(Handle->Regs[8], 0xFFFFFFFF, HMC832_BIAS_EN_Shift, HMC832_BIAS_EN_Mask);
	Handle->Regs[8] = HMC832_SetRegBits(Handle->Regs[8], 0xFFFFFFFF, HMC832_CP_EN_Shift, HMC832_CP_EN_Mask);
	Handle->Regs[8] = HMC832_SetRegBits(Handle->Regs[8], 0xFFFFFFFF, HMC832_PD_EN_Shift, HMC832_PD_EN_Mask);
	Handle->Regs[8] = HMC832_SetRegBits(Handle->Regs[8], 0xFFFFFFFF, HMC832_REFBUF_EN_Shift, HMC832_REFBUF_EN_Mask);
	Handle->Regs[8] = HMC832_SetRegBits(Handle->Regs[8], 0xFFFFFFFF, HMC832_VCOBUF_EN_Shift, HMC832_VCOBUF_EN_Mask);
	Handle->Regs[8] = HMC832_SetRegBits(Handle->Regs[8], 0xFFFFFFFF, HMC832_GPO_PAD_EN_Shift, HMC832_GPO_PAD_EN_Mask);
	Handle->Regs[8] = HMC832_SetRegBits(Handle->Regs[8], 0xFFFFFFFF, HMC832_VCOBufferAndPrescalerBiasEnable_Shift, HMC832_VCOBufferAndPrescalerBiasEnable_Mask);
	Handle->Regs[8] = HMC832_SetRegBits(Handle->Regs[8], 0x0, HMC832_HighFrequencyReference_Shift, HMC832_HighFrequencyReference_Mask);
}

void HMC832_AnalogEnable_SetEnables(HMC832_Handle* Handle, bool Bias, bool CP, bool PD, bool RefBuf, bool VCOBuf, bool GPOPad, bool VCOBufferAndPrescalerBias)
{
	Handle->Regs[8] = HMC832_SetRegBits(Handle->Regs[8], Bias ? 0xFFFFFFFF : 0, HMC832_BIAS_EN_Shift, HMC832_BIAS_EN_Mask);
	Handle->Regs[8] = HMC832_SetRegBits(Handle->Regs[8], CP ? 0xFFFFFFFF : 0, HMC832_CP_EN_Shift, HMC832_CP_EN_Mask);
	Handle->Regs[8] = HMC832_SetRegBits(Handle->Regs[8], PD ? 0xFFFFFFFF : 0, HMC832_PD_EN_Shift, HMC832_PD_EN_Mask);
	Handle->Regs[8] = HMC832_SetRegBits(Handle->Regs[8], RefBuf ? 0xFFFFFFFF : 0, HMC832_REFBUF_EN_Shift, HMC832_REFBUF_EN_Mask);
	Handle->Regs[8] = HMC832_SetRegBits(Handle->Regs[8], VCOBuf ? 0xFFFFFFFF : 0, HMC832_VCOBUF_EN_Shift, HMC832_VCOBUF_EN_Mask);
	Handle->Regs[8] = HMC832_SetRegBits(Handle->Regs[8], GPOPad ? 0xFFFFFFFF : 0, HMC832_GPO_PAD_EN_Shift, HMC832_GPO_PAD_EN_Mask);
	Handle->Regs[8] = HMC832_SetRegBits(Handle->Regs[8], VCOBufferAndPrescalerBias ? 0xFFFFFFFF : 0, HMC832_VCOBufferAndPrescalerBiasEnable_Shift, HMC832_VCOBufferAndPrescalerBiasEnable_Mask);
}

void HMC832_AnalogEnable_SetHighFrequencyReference(HMC832_Handle* Handle, bool HighFreq)
{
	Handle->Regs[8] = HMC832_SetRegBits(Handle->Regs[8], HighFreq ? 0xFFFFFFFF : 0, HMC832_HighFrequencyReference_Shift, HMC832_HighFrequencyReference_Mask);
}
