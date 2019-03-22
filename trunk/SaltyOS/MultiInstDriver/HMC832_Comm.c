#include "HAL\HCommon.h"
#include "HAL\UniGPIO.h"
#include "MultiInstDriver\HMC832.h"

#define HMC832_TransmitInterval 0
#define HMC832_AppendRegControlBits(Index,x) (((x) & 0xFFFFFFF8) | ((Index) & 0x7))

STATUS HMC832_Comm_Init(HMC832_Handle* Handle)
{
	UniGPIO_SetLow(&Handle->SCK);
	UniGPIO_SetLow(&Handle->SDI);
	UniGPIO_SetLow(&Handle->SEN);

	UniGPIO_SetOutput(&Handle->SCK);
	UniGPIO_SetOutput(&Handle->SDI);
	UniGPIO_SetInput(&Handle->SDO_LD);
	UniGPIO_SetOutput(&Handle->SEN);

	return S_OK;
}

u32 HMC832_Comm_ExchangeData(HMC832_Handle* Handle, u32 Val, u32 Addr)
{
	const u32 ChipAddress = 0;
	u32 SendVal = ((Val & 0xFFFFFF) << 8) | ((Addr & 0x1F) << 3) | ((ChipAddress & 0x7) << 0);
	u32 RecvVal = 0x0;
	u32 i = 0;
	UniGPIO_SetLow(&Handle->SEN);
	for (; i < 32; i++)
	{
		UniGPIO_SetVal(&Handle->SDI, SendVal & 0x80000000 ? true : false);
		SendVal <<= 1;
		if (HMC832_TransmitInterval)
		{
			HAL_Delay(HMC832_TransmitInterval);
		}
		UniGPIO_SetHigh(&Handle->SCK);
		if (HMC832_TransmitInterval)
		{
			HAL_Delay(HMC832_TransmitInterval);
		}
		RecvVal <<= 1;
		RecvVal |= UniGPIO_Read(&Handle->SDO_LD);
		UniGPIO_SetLow(&Handle->SCK);
	}
	UniGPIO_SetHigh(&Handle->SEN);
	HAL_Delay(HMC832_TransmitInterval);
	return RecvVal;
}

void HMC832_WriteReg(HMC832_Handle* Handle, u32 RegIndex)
{
	HMC832_Comm_ExchangeData(Handle, Handle->Regs[RegIndex], RegIndex);
}

u32 HMC832_ReadReg(HMC832_Handle* Handle, u32 RegIndex)
{
	HMC832_GenericReg_SetReadAddress(Handle, RegIndex);
	HMC832_WriteReg(Handle, 0);
	return HMC832_Comm_ExchangeData(Handle, Handle->Regs[0], 0) >> 8;
}

void HMC832_WriteVCOReg(HMC832_Handle* Handle, u32 RegIndex)
{
	HMC832_VCOSPI_PrepareWrite(Handle, RegIndex, Handle->VCORegs[RegIndex]);
	HMC832_WriteReg(Handle, 0x5);
	HMC832_VCOSPI_EndWrite(Handle, HMC832_ReadReg(Handle, 0x10));
	HMC832_WriteReg(Handle, 0x5);
}
