#pragma once

#include "HAL\UniGPIO.h"
#include "HAL\UniSPI.h"

C_HEADER_BEGIN

#define HMC832_RegCount 0x14
#define HMC832_VCORegCount 0x08

typedef struct
{
	UniGPIO_Handle SCK;
	UniGPIO_Handle SDI;
	UniGPIO_Handle SEN;
	UniGPIO_Handle SDO_LD;
	u32 Regs[HMC832_RegCount];
	u16 VCORegs[HMC832_VCORegCount];
}HMC832_Handle;

#define HMC832_SetRegBits(x,Val,Shift,Mask) (((x) & ~Mask) | (((u32)(Val) << Shift) & Mask))
#define HMC832_GetRegBits(x,Shift,Mask) (((x) & Mask) >> Shift)

void HMC832_GenericReg_Init(HMC832_Handle* Handle);
void HMC832_GenericReg_SetReadAddress(HMC832_Handle* Handle, u32 Val);
void HMC832_GenericReg_SetChipEnable(HMC832_Handle* Handle, bool Enable);
void HMC832_GenericReg_SetRDIV(HMC832_Handle* Handle, u32 Val);
void HMC832_GenericReg_SetINTG(HMC832_Handle* Handle, u32 Val);
void HMC832_GenericReg_SetFRAC(HMC832_Handle* Handle, u32 Val);
void HMC832_GenericReg_SetNbrOfChannelsPrefPD(HMC832_Handle* Handle, u32 Val);
void HMC832_VCOSPI_Init(HMC832_Handle* Handle);
void HMC832_VCOSPI_PrepareWrite(HMC832_Handle* Handle, u8 Addr, u16 Data);
void HMC832_VCOSPI_EndWrite(HMC832_Handle* Handle, u32 Reg10Val);
void HMC832_DeltaSigma_Init(HMC832_Handle* Handle);
void HMC832_DeltaSigma_SetFracEnable(HMC832_Handle* Handle, bool Enable);
void HMC832_LockDetect_Init(HMC832_Handle* Handle);
void HMC832_LockDetect_MaxCounter(HMC832_Handle* Handle, u32 Val);
void HMC832_LockDetect_WindowType(HMC832_Handle* Handle, bool Digital);
void HMC832_LockDetect_DigitalWindowDuration(HMC832_Handle* Handle, u32 Val);
void HMC832_LockDetect_DigitalTimerFrequencyControl(HMC832_Handle* Handle, u32 Val);
void HMC832_LockDetect_AutomaticRelockOneTry(HMC832_Handle* Handle, bool Val);
void HMC832_AnalogEnable_Init(HMC832_Handle* Handle);
void HMC832_AnalogEnable_SetEnables(HMC832_Handle* Handle, bool Bias, bool CP, bool PD, bool RefBuf, bool VCOBuf, bool GPOPad, bool VCOBufferAndPrescalerBias);
void HMC832_AnalogEnable_SetHighFrequencyReference(HMC832_Handle* Handle, bool HighFreq);
void HMC832_ChargePump_Init(HMC832_Handle* Handle);
void HMC832_ChargePump_SetGain(HMC832_Handle* Handle, u32 DownGain, u32 UpGain);
void HMC832_ChargePump_SetOffset(HMC832_Handle* Handle, u32 Mag, bool Up, bool Down);
void HMC832_AutoCalibration_Init(HMC832_Handle* Handle);
void HMC832_AutoCalibration_SetVTUNEResolution(HMC832_Handle* Handle, u32 Val);
void HMC832_AutoCalibration_SetAutocalibrationDisable(HMC832_Handle* Handle, bool Val);
void HMC832_AutoCalibration_SetFSM_VSPIClockSelect(HMC832_Handle* Handle, u32 Val);
void HMC832_PhaseDetector_Init(HMC832_Handle* Handle);
void HMC832_PhaseDetector_SetDelay(HMC832_Handle* Handle, u32 Val);
void HMC832_PhaseDetector_SetEnables(HMC832_Handle* Handle, bool Up, bool Down);
void HMC832_PhaseDetector_SetCSPMode(HMC832_Handle* Handle, u32 Val);
void HMC832_PhaseDetector_SetForce(HMC832_Handle* Handle, bool Up, bool Down);
void HMC832_GPO_Init(HMC832_Handle* Handle);
void HMC832_GPO_SetGPO_SELECT(HMC832_Handle* Handle, u32 Val);

void HMC832_VCO_Turning_Init(HMC832_Handle* Handle);
void HMC832_VCO_Turning_SetSubband(HMC832_Handle* Handle, u8 Val);
void HMC832_VCO_Enable_Init(HMC832_Handle* Handle);
void HMC832_VCO_Enable_SetEnables(HMC832_Handle* Handle, bool MasterEnableVCOSubsystem, bool VCOEnable, bool PLLBufferEnable, bool InputOutputMasterEnable, bool OutputStageEnable);
void HMC832_VCO_OutputDivider_Init(HMC832_Handle* Handle);
void HMC832_VCO_OutputDivider_Set(HMC832_Handle* Handle, u8 Val);
void HMC832_VCO_Configuration_Init(HMC832_Handle* Handle);
void HMC832_VCO_Configuration_SetProgrammablePerformanceMode(HMC832_Handle* Handle, bool HighPerformance);
void HMC832_VCO_Configuration_SetRFOutputEnables(HMC832_Handle* Handle, bool RF_N, bool RF_P);
void HMC832_VCO_Configuration_SetReturnLoss(HMC832_Handle* Handle, bool ReturnLoss10dB);
void HMC832_VCO_Configuration_SetMuteMode(HMC832_Handle* Handle, u8 MuteMode);
void HMC832_VCO_Reserved_Init(HMC832_Handle* Handle);
void HMC832_VCO_OutputPowerControl_Init(HMC832_Handle* Handle);
void HMC832_VCO_OutputPowerControl_SetOutputStageGainControl(HMC832_Handle* Handle, u8 Val);

STATUS HMC832_Comm_Init(HMC832_Handle* Handle);
void HMC832_WriteReg(HMC832_Handle* Handle, u32 RegIndex);
u32 HMC832_ReadReg(HMC832_Handle* Handle, u32 RegIndex);
void HMC832_WriteVCOReg(HMC832_Handle* Handle, u32 RegIndex);

STATUS HMC832_Init(HMC832_Handle* Handle, u8 PortNum);
void HMC832_UpdateAllRegs(HMC832_Handle* Handle);
bool HMC832_IsLocked(HMC832_Handle* Handle);

C_HEADER_END
