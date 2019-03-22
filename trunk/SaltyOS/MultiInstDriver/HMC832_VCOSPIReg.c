#include "HAL\HCommon.h"
#include "MultiInstDriver\HMC832.h"

//Register 0x05, VCO SPI Register (Default 0x000000)
#define HMC832_VCO_ID_Shift 0
#define HMC832_VCO_ID_Mask (0x7 << HMC832_VCO_ID_Shift)
#define HMC832_VCO_REGADDR_Shift 3
#define HMC832_VCO_REGADDR_Mask (0xF << HMC832_VCO_REGADDR_Shift)
#define HMC832_VCO_DATA_Shift 7
#define HMC832_VCO_DATA_Mask (0x1FF << HMC832_VCO_DATA_Shift)

void HMC832_VCOSPI_Init(HMC832_Handle* Handle)
{
	Handle->Regs[5] = 0x000000;
}

void HMC832_VCOSPI_PrepareWrite(HMC832_Handle* Handle, u8 Addr, u16 Data)
{
	Handle->Regs[5] = HMC832_SetRegBits(Handle->Regs[5], Addr, HMC832_VCO_REGADDR_Shift, HMC832_VCO_REGADDR_Mask);
	Handle->Regs[5] = HMC832_SetRegBits(Handle->Regs[5], Data, HMC832_VCO_DATA_Shift, HMC832_VCO_DATA_Mask);
}

void HMC832_VCOSPI_EndWrite(HMC832_Handle* Handle, u32 Reg10Val)
{
	u16 ReconstructedData = 0;
	ReconstructedData |= ((Reg10Val >> 6) & 0x3) << 14;
	ReconstructedData |= 1 << 13;
	ReconstructedData |= ((Reg10Val >> 0) & 0x1F) << 8;
	Handle->Regs[5] = HMC832_SetRegBits(Handle->Regs[5], 0, HMC832_VCO_REGADDR_Shift, HMC832_VCO_REGADDR_Mask);
	Handle->Regs[5] = HMC832_SetRegBits(Handle->Regs[5], ReconstructedData >> HMC832_VCO_DATA_Shift, HMC832_VCO_DATA_Shift, HMC832_VCO_DATA_Mask);
}
