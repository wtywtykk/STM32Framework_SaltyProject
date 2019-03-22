#include "HAL\HCommon.h"
#include "HAL\UniGPIO.h"
#include "MultiInstDriver\HMC832.h"
#include <string.h>
#include <math.h>

STATUS HMC832_Init(HMC832_Handle* Handle, u8 PortNum)
{
	GPIO_CPLD_InitPin(PortNum, 8, false, &Handle->SCK);
	GPIO_CPLD_InitPin(PortNum, 6, false, &Handle->SDI);
	GPIO_CPLD_InitPin(PortNum, 7, false, &Handle->SDO_LD);
	GPIO_CPLD_InitPin(PortNum, 4, false, &Handle->SEN);

	memset(Handle->Regs, 0, sizeof(Handle->Regs));
	memset(Handle->VCORegs, 0, sizeof(Handle->VCORegs));

	HMC832_GenericReg_Init(Handle);
	HMC832_VCOSPI_Init(Handle);
	HMC832_DeltaSigma_Init(Handle);
	HMC832_LockDetect_Init(Handle);
	HMC832_AnalogEnable_Init(Handle);
	HMC832_ChargePump_Init(Handle);
	HMC832_AutoCalibration_Init(Handle);
	HMC832_PhaseDetector_Init(Handle);
	HMC832_GPO_Init(Handle);

	HMC832_VCO_Turning_Init(Handle);
	HMC832_VCO_Enable_Init(Handle);
	HMC832_VCO_OutputDivider_Init(Handle);
	HMC832_VCO_Configuration_Init(Handle);
	HMC832_VCO_Reserved_Init(Handle);
	HMC832_VCO_OutputPowerControl_Init(Handle);

	HMC832_Comm_Init(Handle);

	HMC832_UpdateAllRegs(Handle);

	return S_OK;
}

void HMC832_UpdateAllRegs(HMC832_Handle* Handle)
{
	u8 i;
	for (i = 0; i < HMC832_RegCount; i++)
	{
		HMC832_WriteReg(Handle, i);
	}

	for (i = 0; i < HMC832_VCORegCount; i++)
	{
		HMC832_WriteVCOReg(Handle, i);
	}
}

bool HMC832_IsLocked(HMC832_Handle* Handle)
{
	u32 RegGPO2 = HMC832_ReadReg(Handle, 0x12);
	return (RegGPO2 & 0x2) ? true : false;
}
