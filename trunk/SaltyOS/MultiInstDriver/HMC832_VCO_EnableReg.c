#include "HAL\HCommon.h"
#include "MultiInstDriver\HMC832.h"

//VCO_REG 0x01, Enable Register
#define HMC832_MasterEnableVCOSubsystem_Shift 0
#define HMC832_MasterEnableVCOSubsystem_Mask (0x1 << HMC832_MasterEnableVCOSubsystem_Shift)
#define HMC832_VCOEnable_Shift 1
#define HMC832_VCOEnable_Mask (0x1 << HMC832_VCOEnable_Shift)
#define HMC832_PLLBufferEnable_Shift 2
#define HMC832_PLLBufferEnable_Mask (0x1 << HMC832_PLLBufferEnable_Shift)
#define HMC832_InputOutputMasterEnable_Shift 3
#define HMC832_InputOutputMasterEnable_Mask (0x1 << HMC832_InputOutputMasterEnable_Shift)
#define HMC832_OutputStageEnable_Shift 5
#define HMC832_OutputStageEnable_Mask (0x1 << HMC832_OutputStageEnable_Shift)

void HMC832_VCO_Enable_Init(HMC832_Handle* Handle)
{
	Handle->VCORegs[1] = 0x01FF;
}

void HMC832_VCO_Enable_SetEnables(HMC832_Handle* Handle, bool MasterEnableVCOSubsystem, bool VCOEnable, bool PLLBufferEnable, bool InputOutputMasterEnable, bool OutputStageEnable)
{
	Handle->VCORegs[1] = HMC832_SetRegBits(Handle->VCORegs[1], MasterEnableVCOSubsystem ? 0xFFFF : 0, HMC832_MasterEnableVCOSubsystem_Shift, HMC832_MasterEnableVCOSubsystem_Mask);
	Handle->VCORegs[1] = HMC832_SetRegBits(Handle->VCORegs[1], VCOEnable ? 0xFFFF : 0, HMC832_VCOEnable_Shift, HMC832_VCOEnable_Mask);
	Handle->VCORegs[1] = HMC832_SetRegBits(Handle->VCORegs[1], PLLBufferEnable ? 0xFFFF : 0, HMC832_PLLBufferEnable_Shift, HMC832_PLLBufferEnable_Mask);
	Handle->VCORegs[1] = HMC832_SetRegBits(Handle->VCORegs[1], InputOutputMasterEnable ? 0xFFFF : 0, HMC832_InputOutputMasterEnable_Shift, HMC832_InputOutputMasterEnable_Mask);
	Handle->VCORegs[1] = HMC832_SetRegBits(Handle->VCORegs[1], OutputStageEnable ? 0xFFFF : 0, HMC832_OutputStageEnable_Shift, HMC832_OutputStageEnable_Mask);
}
