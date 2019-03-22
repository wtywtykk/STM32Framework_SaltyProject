#include "HCommon.h"
#include "Interrupt.h"
#include "Beep.h"

void HardwareRestart(void)
{
	NVIC_SystemReset();
}

void BeepAndReset(uint Time)
{
	volatile u32 i;
	DisableInterrupt();
	while (Time--)
	{
		//Interrupts are disabled so SysTick won't work.The Beep function won't work.
		BeepStart();
		i = 2000000;
		while (i--);
		BeepStop();
		i = 2000000;
		while (i--);
	}
#ifndef DEBUG
	//HardwareRestart();
#endif
	while (1);
}
