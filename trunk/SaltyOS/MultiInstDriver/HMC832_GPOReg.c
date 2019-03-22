#include "HAL\HCommon.h"
#include "MultiInstDriver\HMC832.h"

//Register 0x0F, GPO_SPI_RDIV Register (Default 0x000001)
#define HMC832_GPO_SELECT_Shift 0
#define HMC832_GPO_SELECT_Mask (0x1F << HMC832_GPO_SELECT_Shift)
#define HMC832_GPOTestData_Shift 5
#define HMC832_GPOTestData_Mask (0x1 << HMC832_GPOTestData_Shift)
#define HMC832_PreventSutomuxSDO_Shift 6
#define HMC832_PreventSutomuxSDO_Mask (0x1 << HMC832_PreventSutomuxSDO_Shift)
#define HMC832_LDODriverAlwaysOn_Shift 7
#define HMC832_LDODriverAlwaysOn_Mask (0x1 << HMC832_LDODriverAlwaysOn_Shift)
#define HMC832_DisablePFET_Shift 8
#define HMC832_DisablePFET_Mask (0x1 << HMC832_DisablePFET_Shift)
#define HMC832_DisableNFET_Shift 9
#define HMC832_DisableNFET_Mask (0x1 << HMC832_DisableNFET_Shift)

void HMC832_GPO_Init(HMC832_Handle* Handle)
{
	Handle->Regs[0x0F] = 0x000001;
	Handle->Regs[0x0F] = HMC832_SetRegBits(Handle->Regs[0x0F], 0, HMC832_PreventSutomuxSDO_Shift, HMC832_PreventSutomuxSDO_Mask);
	Handle->Regs[0x0F] = HMC832_SetRegBits(Handle->Regs[0x0F], 0, HMC832_LDODriverAlwaysOn_Shift, HMC832_LDODriverAlwaysOn_Mask);
	Handle->Regs[0x0F] = HMC832_SetRegBits(Handle->Regs[0x0F], 0, HMC832_DisablePFET_Shift, HMC832_DisablePFET_Mask);
	Handle->Regs[0x0F] = HMC832_SetRegBits(Handle->Regs[0x0F], 0, HMC832_DisableNFET_Shift, HMC832_DisableNFET_Mask);
}

void HMC832_GPO_SetGPO_SELECT(HMC832_Handle* Handle, u32 Val)
{
	Handle->Regs[0x0F] = HMC832_SetRegBits(Handle->Regs[0x0F], Val, HMC832_GPO_SELECT_Shift, HMC832_GPO_SELECT_Mask);
}
