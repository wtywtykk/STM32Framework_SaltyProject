#include "HCommon.h"
#include "Interrupt.h"

void HardwareRestart(void)
{
	SysCtl_rebootDevice();
}

void BeepAndReset(uint Time)
{
	volatile u32 i = Time;
	__set_FAULTMASK(1);
#ifndef DEBUG
	//SysCtl_rebootDevice();
#endif
	while (1);
}
