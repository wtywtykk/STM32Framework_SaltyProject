#include "HCommon.h"
#include "PeripheralBus.h"

volatile u16* const PeripheralBusAddr = (u16*)(FSMC_Base4);

bool PeripheralBus_Initialized = false;
SRAM_HandleTypeDef PeripheralBus_FSMC_Handle;

STATUS PeripheralBus_SelfCheck(void);

STATUS PeripheralBus_Init(void)
{
	FSMC_NORSRAM_TimingTypeDef Timing;

	if (PeripheralBus_Initialized)
	{
		return S_OK;
	}

	PeripheralBus_FSMC_Handle.Instance = FSMC_NORSRAM_DEVICE;
	PeripheralBus_FSMC_Handle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;

	PeripheralBus_FSMC_Handle.Init.NSBank = FSMC_NORSRAM_BANK4;
	PeripheralBus_FSMC_Handle.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
	PeripheralBus_FSMC_Handle.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
	PeripheralBus_FSMC_Handle.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
	PeripheralBus_FSMC_Handle.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
	PeripheralBus_FSMC_Handle.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
	PeripheralBus_FSMC_Handle.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
	PeripheralBus_FSMC_Handle.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
	PeripheralBus_FSMC_Handle.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
	PeripheralBus_FSMC_Handle.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
	PeripheralBus_FSMC_Handle.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
	PeripheralBus_FSMC_Handle.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
	PeripheralBus_FSMC_Handle.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
	PeripheralBus_FSMC_Handle.Init.PageSize = FSMC_PAGE_SIZE_NONE;

	Timing.AddressSetupTime = 3;
	Timing.AddressHoldTime = 1;
	Timing.DataSetupTime = 3;
	Timing.BusTurnAroundDuration = 0;
	Timing.CLKDivision = 2;
	Timing.DataLatency = 2;
	Timing.AccessMode = FSMC_ACCESS_MODE_A;

	/*
	Timing.AddressSetupTime = 15;
	Timing.AddressHoldTime = 15;
	Timing.DataSetupTime = 255;
	Timing.BusTurnAroundDuration = 15;
	Timing.CLKDivision = 16;
	Timing.DataLatency = 2;
	Timing.AccessMode = FSMC_ACCESS_MODE_A;
	*/

	if (HAL_SRAM_Init(&PeripheralBus_FSMC_Handle, &Timing, NULL) != HAL_OK)
	{
		return S_FAIL;
	}

	PeripheralBus_Write(PeripheralBus_Config, PeripheralBus_ConfigBit_Reset);
	HAL_Delay(1);
	PeripheralBus_Write(PeripheralBus_Config, 0);
	HAL_Delay(1);

	if (PeripheralBus_SelfCheck() != S_OK)
	{
		return S_FAIL;
	}

	PeripheralBus_Initialized = true;

	return S_OK;
}

#ifndef ExpandReadWriteFunctions

u16 PeripheralBus_Read(u8 Addr)
{
	return *(__IO u16* const)(PeripheralBusAddr + Addr);
}

void PeripheralBus_Write(u8 Addr, u16 Data)
{
	*(__IO u16* const)(PeripheralBusAddr + Addr) = Data;
}

#endif

STATUS PeripheralBus_SelfCheck(void)
{
	u16 Arr[16];
	for (u8 i = 0; i < 16; i++)
	{
		PeripheralBus_Write(PeripheralBus_CommTest, 1 << i);
		Arr[i] = ~PeripheralBus_Read(PeripheralBus_CommTest);
	}
	for (u8 i = 0; i < 16; i++)
	{
		assert(Arr[i] == 1 << i);
		if (Arr[i] != 1 << i)
		{
			return S_FAIL;
		}
	}
	return S_OK;
}
