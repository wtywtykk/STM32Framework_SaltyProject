#include "HAL\HCommon.h"
#include "MultiInstDriver\HMC832.h"

//Register 0x00, ID Register(Read Only)
#define HMC832_ID_Shift 0
#define HMC832_ID_Mask (0xFFFFFF << HMC832_ID_Shift)
//Register 0x00, Read Address / RST Strobe Register(Write Only)
#define HMC832_ReadAddress_Shift 0
#define HMC832_ReadAddress_Mask (0x1F << HMC832_ReadAddress_Shift)
#define HMC832_SoftReset_Shift 5
#define HMC832_SoftReset_Mask (0x1 << HMC832_SoftReset_Shift)
//Register 0x01, RST Register(Default 0x000002)
#define HMC832_RST_CHIPEN_PIN_SELECT_Shift 0
#define HMC832_RST_CHIPEN_PIN_SELECT_Mask (0x1 << HMC832_RST_CHIPEN_PIN_SELECT_Shift)
#define HMC832_RST_CHIPEN_FROM_SPI_Shift 1
#define HMC832_RST_CHIPEN_FROM_SPI_Mask (0x1 << HMC832_RST_CHIPEN_FROM_SPI_Shift)
//Register 0x02, REFDIV Register(Default 0x000001)
#define HMC832_RDIV_Shift 0
#define HMC832_RDIV_Mask (0x3FFF << HMC832_RDIV_Shift)
//Register 0x03, Frequency Register, Integer Part(Default 0x000019)
#define HMC832_INTG_REG_Shift 0
#define HMC832_INTG_REG_Mask (0x7FFFF << HMC832_INTG_REG_Shift)
//Register 0x04, Frequency Register, Fractional Part(Default 0x000000)
#define HMC832_FRAC_Shift 0
#define HMC832_FRAC_Mask (0xFFFFFF << HMC832_FRAC_Shift)
//Register 0x0C, Exact Frequency Mode Register (Default 0x000000)
#define HMC832_NbrOfChannelsPrefPD_Shift 0
#define HMC832_NbrOfChannelsPrefPD_Mask (0x3FFF << HMC832_NbrOfChannelsPrefPD_Shift)

void HMC832_GenericReg_Init(HMC832_Handle* Handle)
{
	Handle->Regs[0] = 0x000000;
	Handle->Regs[1] = 0x000002;
	Handle->Regs[2] = 0x000001;
	Handle->Regs[3] = 0x000019;
	Handle->Regs[4] = 0x000000;
	Handle->Regs[0x0C] = 0x000000;
	Handle->Regs[0] = HMC832_SetRegBits(Handle->Regs[0], 0, HMC832_SoftReset_Shift, HMC832_SoftReset_Mask);
}

void HMC832_GenericReg_SetReadAddress(HMC832_Handle* Handle, u32 Val)
{
	Handle->Regs[0] = HMC832_SetRegBits(Handle->Regs[0], Val, HMC832_ReadAddress_Shift, HMC832_ReadAddress_Mask);
}

void HMC832_GenericReg_SetChipEnable(HMC832_Handle* Handle, bool Enable)
{
	Handle->Regs[1] = HMC832_SetRegBits(Handle->Regs[1], Enable ? 0xFFFFFFFF : 0, HMC832_RST_CHIPEN_FROM_SPI_Shift, HMC832_RST_CHIPEN_FROM_SPI_Mask);
}

void HMC832_GenericReg_SetRDIV(HMC832_Handle* Handle, u32 Val)
{
	Handle->Regs[2] = HMC832_SetRegBits(Handle->Regs[2], Val, HMC832_RDIV_Shift, HMC832_RDIV_Mask);
}

void HMC832_GenericReg_SetINTG(HMC832_Handle* Handle, u32 Val)
{
	Handle->Regs[3] = HMC832_SetRegBits(Handle->Regs[3], Val, HMC832_INTG_REG_Shift, HMC832_INTG_REG_Mask);
}

void HMC832_GenericReg_SetFRAC(HMC832_Handle* Handle, u32 Val)
{
	Handle->Regs[4] = HMC832_SetRegBits(Handle->Regs[4], Val, HMC832_FRAC_Shift, HMC832_FRAC_Mask);
}

void HMC832_GenericReg_SetNbrOfChannelsPrefPD(HMC832_Handle* Handle, u32 Val)
{
	Handle->Regs[0x0C] = HMC832_SetRegBits(Handle->Regs[0x0C], Val, HMC832_NbrOfChannelsPrefPD_Shift, HMC832_NbrOfChannelsPrefPD_Mask);
}
