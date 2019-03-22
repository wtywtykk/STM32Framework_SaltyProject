#include "HAL\HCommon.h"
#include "MultiInstDriver\HMC832.h"

//VCO_REG 0x03, Configuration Register
#define HMC832_ProgrammablePerformanceMode_Shift 0
#define HMC832_ProgrammablePerformanceMode_Mask (0x3 << HMC832_ProgrammablePerformanceMode_Shift)
#define HMC832_RF_NOutputEnable_Shift 2
#define HMC832_RF_NOutputEnable_Mask (0x1 << HMC832_RF_NOutputEnable_Shift)
#define HMC832_RF_POutputEnable_Shift 3
#define HMC832_RF_POutputEnable_Mask (0x1 << HMC832_RF_POutputEnable_Shift)
#define HMC832_ReturnLoss_Shift 5
#define HMC832_ReturnLoss_Mask (0x1 << HMC832_ReturnLoss_Shift)
#define HMC832_MuteMode_Shift 7
#define HMC832_MuteMode_Mask (0x3 << HMC832_MuteMode_Shift)

void HMC832_VCO_Configuration_Init(HMC832_Handle* Handle)
{
	Handle->VCORegs[3] = 0x0092;
	Handle->VCORegs[3] = HMC832_SetRegBits(Handle->VCORegs[3], 3, HMC832_ProgrammablePerformanceMode_Shift, HMC832_ProgrammablePerformanceMode_Mask);
	Handle->VCORegs[3] = HMC832_SetRegBits(Handle->VCORegs[3], 0xFFFF, HMC832_RF_NOutputEnable_Shift, HMC832_RF_NOutputEnable_Mask);
	Handle->VCORegs[3] = HMC832_SetRegBits(Handle->VCORegs[3], 0xFFFF, HMC832_RF_POutputEnable_Shift, HMC832_RF_POutputEnable_Mask);
}

void HMC832_VCO_Configuration_SetProgrammablePerformanceMode(HMC832_Handle* Handle, bool HighPerformance)
{
	Handle->VCORegs[3] = HMC832_SetRegBits(Handle->VCORegs[3], HighPerformance ? 3 : 1, HMC832_ProgrammablePerformanceMode_Shift, HMC832_ProgrammablePerformanceMode_Mask);
}

void HMC832_VCO_Configuration_SetRFOutputEnables(HMC832_Handle* Handle, bool RF_N, bool RF_P)
{
	Handle->VCORegs[3] = HMC832_SetRegBits(Handle->VCORegs[3], RF_N ? 0xFFFF : 0x0, HMC832_RF_NOutputEnable_Shift, HMC832_RF_NOutputEnable_Mask);
	Handle->VCORegs[3] = HMC832_SetRegBits(Handle->VCORegs[3], RF_P ? 0xFFFF : 0x0, HMC832_RF_POutputEnable_Shift, HMC832_RF_POutputEnable_Mask);
}

void HMC832_VCO_Configuration_SetReturnLoss(HMC832_Handle* Handle, bool ReturnLoss10dB)
{
	Handle->VCORegs[3] = HMC832_SetRegBits(Handle->VCORegs[3], ReturnLoss10dB ? 0xFFFF : 0x0, HMC832_ReturnLoss_Shift, HMC832_ReturnLoss_Mask);
}

void HMC832_VCO_Configuration_SetMuteMode(HMC832_Handle* Handle, u8 MuteMode)
{
	Handle->VCORegs[3] = HMC832_SetRegBits(Handle->VCORegs[3], MuteMode, HMC832_MuteMode_Shift, HMC832_MuteMode_Mask);
}
