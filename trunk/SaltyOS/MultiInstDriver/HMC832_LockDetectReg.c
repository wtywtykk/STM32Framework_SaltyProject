#include "HAL\HCommon.h"
#include "MultiInstDriver\HMC832.h"

//Register 0x07, Lock Detect Register (Default 0x00014D)

#define HMC832_LKD_WINCNT_MAX_Shift 0
#define HMC832_LKD_WINCNT_MAX_Mask (0x7 << HMC832_LKD_WINCNT_MAX_Shift)
#define HMC832_EnableInternalLockDetect_Shift 3
#define HMC832_EnableInternalLockDetect_Mask (0x1 << HMC832_EnableInternalLockDetect_Shift)
#define HMC832_LockDetectWindowType_Shift 6
#define HMC832_LockDetectWindowType_Mask (0x1 << HMC832_LockDetectWindowType_Shift)
#define HMC832_LDDigitalWindowDuration_Shift 7
#define HMC832_LDDigitalWindowDuration_Mask (0x7 << HMC832_LDDigitalWindowDuration_Shift)
#define HMC832_LDDigitalTimerFrequencyControl_Shift 10
#define HMC832_LDDigitalTimerFrequencyControl_Mask (0x3 << HMC832_LDDigitalTimerFrequencyControl_Shift)
#define HMC832_AutomaticRelockOneTry_Shift 13
#define HMC832_AutomaticRelockOneTry_Mask (0x1 << HMC832_AutomaticRelockOneTry_Shift)

void HMC832_LockDetect_Init(HMC832_Handle* Handle)
{
	Handle->Regs[7] = 0x00014D;
	Handle->Regs[7] = HMC832_SetRegBits(Handle->Regs[7], 0xFFFFFFFF, HMC832_EnableInternalLockDetect_Shift, HMC832_EnableInternalLockDetect_Mask);
}

void HMC832_LockDetect_MaxCounter(HMC832_Handle* Handle, u32 Val)
{
	Handle->Regs[7] = HMC832_SetRegBits(Handle->Regs[7], Val, HMC832_LKD_WINCNT_MAX_Shift, HMC832_LKD_WINCNT_MAX_Mask);
}

void HMC832_LockDetect_WindowType(HMC832_Handle* Handle, bool Digital)
{
	Handle->Regs[7] = HMC832_SetRegBits(Handle->Regs[7], Digital ? 0xFFFFFFFF : 0x0, HMC832_LockDetectWindowType_Shift, HMC832_LockDetectWindowType_Mask);
}

void HMC832_LockDetect_DigitalWindowDuration(HMC832_Handle* Handle, u32 Val)
{
	Handle->Regs[7] = HMC832_SetRegBits(Handle->Regs[7], Val, HMC832_LDDigitalWindowDuration_Shift, HMC832_LDDigitalWindowDuration_Mask);
}

void HMC832_LockDetect_DigitalTimerFrequencyControl(HMC832_Handle* Handle, u32 Val)
{
	Handle->Regs[7] = HMC832_SetRegBits(Handle->Regs[7], Val, HMC832_LDDigitalTimerFrequencyControl_Shift, HMC832_LDDigitalTimerFrequencyControl_Mask);
}

void HMC832_LockDetect_AutomaticRelockOneTry(HMC832_Handle* Handle, bool Val)
{
	Handle->Regs[7] = HMC832_SetRegBits(Handle->Regs[7], Val ? 0xFFFFFFFF : 0x0, HMC832_AutomaticRelockOneTry_Shift, HMC832_AutomaticRelockOneTry_Mask);
}
