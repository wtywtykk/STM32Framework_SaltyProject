#include "HCommon.h"
#include "HAL\UniGPIO.h"

volatile static u32 TickCount = 0;

void TickHandler(void)
{
	TickCount++;
}

STATUS Tick_Init(void)
{
	TickCount = 0;
	SysTick_enableModule();
	SysTick_setPeriod(CS_getMCLK() / 1000);
	SysTick_registerInterrupt(TickHandler);
	SysTick_enableInterrupt();
	return S_OK;
}

void HAL_Delay(u32 Interval)
{
	u32 EndTick = TickCount + Interval;
	while (EndTick > TickCount);
}

u32 HAL_GetTick(void)
{
	return TickCount;
}
