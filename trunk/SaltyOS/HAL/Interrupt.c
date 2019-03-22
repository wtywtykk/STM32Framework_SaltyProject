#include "HCommon.h"

static bool Interrupt_Initialized = false;

STATUS Interrupt_Init(void)
{
	if (Interrupt_Initialized)
	{
		return S_OK;
	}

	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	/* System interrupt init*/
	/* MemoryManagement_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	/* BusFault_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	/* UsageFault_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
	/* SVCall_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
	/* DebugMonitor_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
	/* PendSV_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

	Interrupt_Initialized = true;

	return S_OK;
}

void DisableInterrupt(void)
{
	__set_FAULTMASK(1);
}

void EnableInterrupt(void)
{
	__set_FAULTMASK(0);
}
