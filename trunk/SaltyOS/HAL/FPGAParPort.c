#include "HAL\HCommon.h"
#include "HAL\UniGPIO.h"
#include "HAL\PeripheralBus.h"
#include "HAL\FPGAParPort.h"

DMA_HandleTypeDef FPGAParPort_DMA_Handle;

UniGPIO_Handle FPGA_Ready;
UniGPIO_Handle FPGA_Busy;
UniGPIO_Handle FPGA_Reset;
UniGPIO_Handle FPGA_IO4;
UniGPIO_Handle FPGA_IO5;

bool FPGAParPort_Initialized = false;

#define FPGAParPort_MaxBusyWaitTime 1

STATUS FPGAParPort_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	if (FPGAParPort_Initialized)
	{
		return S_OK;
	}

	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_32_InitPin(GPIOH, &GPIO_InitStruct, &FPGA_Ready);//IO1

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pin = GPIO_PIN_14;
	GPIO_32_InitPin(GPIOH, &GPIO_InitStruct, &FPGA_Busy);//IO2

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pin = GPIO_PIN_15;
	GPIO_32_InitPin(GPIOH, &GPIO_InitStruct, &FPGA_Reset);//IO3

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	GPIO_32_InitPin(GPIOI, &GPIO_InitStruct, &FPGA_IO4);//IO4

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_32_InitPin(GPIOI, &GPIO_InitStruct, &FPGA_IO5);//IO5

	FPGAParPort_DMA_Handle.Instance = DMA2_Stream2;
	FPGAParPort_DMA_Handle.Init.Channel = DMA_CHANNEL_7;
	FPGAParPort_DMA_Handle.Init.Direction = DMA_MEMORY_TO_MEMORY;
	FPGAParPort_DMA_Handle.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
	FPGAParPort_DMA_Handle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	FPGAParPort_DMA_Handle.Init.MemBurst = DMA_MBURST_INC8;
	FPGAParPort_DMA_Handle.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	FPGAParPort_DMA_Handle.Init.MemInc = DMA_MINC_ENABLE;
	FPGAParPort_DMA_Handle.Init.Mode = DMA_NORMAL;
	FPGAParPort_DMA_Handle.Init.PeriphBurst = DMA_PBURST_INC8;
	FPGAParPort_DMA_Handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	FPGAParPort_DMA_Handle.Init.PeriphInc = DMA_PINC_DISABLE;
	FPGAParPort_DMA_Handle.Init.Priority = DMA_PRIORITY_VERY_HIGH;

	if (HAL_DMA_Init(&FPGAParPort_DMA_Handle) != HAL_OK)
	{
		return S_FAIL;
	}

	FPGAParPort_Reset();
	UniGPIO_SetLow(&FPGA_IO5);

	FPGAParPort_Initialized = true;

	return S_OK;
}

STATUS ParPort_StartPipeline(void)
{
	volatile u16 __attribute__((unused)) DummyRead;
	if (FPGAParPort_WaitBusy(FPGAParPort_MaxBusyWaitTime) != S_OK)
	{
		return S_FAIL;
	}
	DummyRead = PeripheralBus_Read(PeripheralBus_FPGARead);
	//DummyRead = PeripheralBus_Read(PeripheralBus_FPGARead);
	return S_OK;
}

STATUS ParPort_Read(u16* Buffer, u32 BufferSizeInWord, u32* ReadSize, bool WaitForBusy)
{
	if (Buffer)
	{
		if (WaitForBusy)
		{
			*ReadSize = 0;
			for (u16 i = 0; i < BufferSizeInWord; i++)
			{
				if (FPGAParPort_WaitBusy(FPGAParPort_MaxBusyWaitTime) != S_OK)
				{
					return S_FAIL;
				}
				*Buffer = PeripheralBus_Read(PeripheralBus_FPGARead);
				Buffer++;
				(*ReadSize)++;
			}
		}
		else
		{
			*ReadSize = BufferSizeInWord;
			while (BufferSizeInWord)
			{
				u32 DataLength = BufferSizeInWord;
				//Max data length limited by DMA
				if (DataLength > 65535)
				{
					DataLength = 65535;
				}
				HAL_DMA_Start(&FPGAParPort_DMA_Handle, (u32)(PeripheralBusAddr + PeripheralBus_FPGARead), (u32)Buffer, DataLength);
				HAL_DMA_PollForTransfer(&FPGAParPort_DMA_Handle, HAL_DMA_FULL_TRANSFER, DataLength / 128 + 1);
				BufferSizeInWord -= DataLength;
				Buffer += DataLength;
			}
		}
	}
	else
	{
		*ReadSize = 0;
		return S_FAIL;
	}
	return S_OK;
}

STATUS FPGAParPort_WaitBusy(u32 TimeOut)
{
	u32 TimeOutTick = HAL_GetTick() + TimeOut;
	while (UniGPIO_Read(&FPGA_Busy))
	{
		if (TimeOutTick < HAL_GetTick())
		{
			return S_FAIL;
		}
	}
	return S_OK;
}

bool FPGAParPort_IsReady(void)
{
	if (UniGPIO_Read(&FPGA_Ready))
	{
		return true;
	}
	else
	{
		return false;
	}
}

STATUS FPGAParPort_WaitReady(u32 TimeOut)
{
	u32 TimeOutTick = HAL_GetTick() + TimeOut;
	while (!UniGPIO_Read(&FPGA_Ready))
	{
		if (TimeOutTick < HAL_GetTick())
		{
			return S_FAIL;
		}
	}
	return S_OK;
}

void FPGAParPort_Reset(void)
{
	volatile u16 __attribute__((unused)) DummyRead;
	UniGPIO_SetHigh(&FPGA_Reset);
	DummyRead = PeripheralBus_Read(PeripheralBus_FPGARead);//Sync reset
	UniGPIO_SetLow(&FPGA_Reset);
}

bool FPGAParPort_ReadIO4(void)
{
	if (UniGPIO_Read(&FPGA_IO4))
	{
		return true;
	}
	else
	{
		return false;
	}
}
