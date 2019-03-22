#include "HAL\HCommon.h"
#include "MultiInstDriver\HMC832.h"

//Register 0x0A, VCO Autocalibration Configuration Register (Default 0x002205)
#define HMC832_VTUNEResolution_Shift 0
#define HMC832_VTUNEResolution_Mask (0x7 << HMC832_VTUNEResolution_Shift)
#define HMC832_ReservedTo8d_Shift 3
#define HMC832_ReservedTo8d_Mask (0x7F << HMC832_ReservedTo8d_Shift)
#define HMC832_ForceCurve_Shift 10
#define HMC832_ForceCurve_Mask (0x1 << HMC832_ForceCurve_Shift)
#define HMC832_AutocalibrationDisable_Shift 11
#define HMC832_AutocalibrationDisable_Mask (0x1 << HMC832_AutocalibrationDisable_Shift)
#define HMC832_NoVSPITrigger_Shift 12
#define HMC832_NoVSPITrigger_Mask (0x1 << HMC832_NoVSPITrigger_Shift)
#define HMC832_FSM_VSPIClockSelect_Shift 13
#define HMC832_FSM_VSPIClockSelect_Mask (0x3 << HMC832_FSM_VSPIClockSelect_Shift)

void HMC832_AutoCalibration_Init(HMC832_Handle* Handle)
{
	Handle->Regs[0x0A] = 0x002205;
	Handle->Regs[0x0A] = HMC832_SetRegBits(Handle->Regs[0x0A], 8, HMC832_ReservedTo8d_Shift, HMC832_ReservedTo8d_Mask);
	Handle->Regs[0x0A] = HMC832_SetRegBits(Handle->Regs[0x0A], 0, HMC832_ForceCurve_Shift, HMC832_ForceCurve_Mask);
	Handle->Regs[0x0A] = HMC832_SetRegBits(Handle->Regs[0x0A], 0, HMC832_AutocalibrationDisable_Shift, HMC832_AutocalibrationDisable_Mask);
}

void HMC832_AutoCalibration_SetVTUNEResolution(HMC832_Handle* Handle, u32 Val)
{
	Handle->Regs[0x0A] = HMC832_SetRegBits(Handle->Regs[0x0A], Val, HMC832_VTUNEResolution_Shift, HMC832_VTUNEResolution_Mask);
}

void HMC832_AutoCalibration_SetAutocalibrationDisable(HMC832_Handle* Handle, bool Val)
{
	Handle->Regs[0x0A] = HMC832_SetRegBits(Handle->Regs[0x0A], Val ? 0xFFFFFFFF : 0x0, HMC832_AutocalibrationDisable_Shift, HMC832_AutocalibrationDisable_Mask);
}

void HMC832_AutoCalibration_SetFSM_VSPIClockSelect(HMC832_Handle* Handle, u32 Val)
{
	Handle->Regs[0x0A] = HMC832_SetRegBits(Handle->Regs[0x0A], Val, HMC832_FSM_VSPIClockSelect_Shift, HMC832_FSM_VSPIClockSelect_Mask);
}
