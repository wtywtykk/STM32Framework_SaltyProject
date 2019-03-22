#include "HAL\HCommon.h"
#include "HAL\FSMC.h"

volatile u16* const SRAMAddr = (u16*)(FSMC_Base1);
#define SRAMAccess(Addr) (*(SRAMAddr+(Addr)))

bool SRAM_Initialized = false;
SRAM_HandleTypeDef SRAM_FSMC_Handle;
u32 SRAMSize = 0;
u32 PseudorandomLastVal;

u32 SRAM_GetSize(void);
STATUS SRAM_SelfCheck(void);

STATUS SRAM_Init(void)
{
	FSMC_NORSRAM_TimingTypeDef Timing;

	if (SRAM_Initialized)
	{
		return S_OK;
	}

	SRAM_FSMC_Handle.Instance = FSMC_NORSRAM_DEVICE;
	SRAM_FSMC_Handle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;

	SRAM_FSMC_Handle.Init.NSBank = FSMC_NORSRAM_BANK1;
	SRAM_FSMC_Handle.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
	SRAM_FSMC_Handle.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
	SRAM_FSMC_Handle.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
	SRAM_FSMC_Handle.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
	SRAM_FSMC_Handle.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
	SRAM_FSMC_Handle.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
	SRAM_FSMC_Handle.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
	SRAM_FSMC_Handle.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
	SRAM_FSMC_Handle.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
	SRAM_FSMC_Handle.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
	SRAM_FSMC_Handle.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
	SRAM_FSMC_Handle.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
	SRAM_FSMC_Handle.Init.PageSize = FSMC_PAGE_SIZE_NONE;

	//IS62WV51216 is tooooooooooooooooooooooooooooooooooo ssslllooowww!
	Timing.AddressSetupTime = 5;
	Timing.AddressHoldTime = 1;
	Timing.DataSetupTime = 5;
	Timing.BusTurnAroundDuration = 0;
	Timing.CLKDivision = 2;
	Timing.DataLatency = 2;
	Timing.AccessMode = FSMC_ACCESS_MODE_A;

	//IS61LVxxx16
	Timing.AddressSetupTime = 2;
	Timing.AddressHoldTime = 1;
	Timing.DataSetupTime = 2;
	Timing.BusTurnAroundDuration = 0;
	Timing.CLKDivision = 2;
	Timing.DataLatency = 2;
	Timing.AccessMode = FSMC_ACCESS_MODE_A;

	if (HAL_SRAM_Init(&SRAM_FSMC_Handle, &Timing, NULL) != HAL_OK)
	{
		return S_FAIL;
	}

	SRAMSize = SRAM_GetSize();

	if (SRAM_SelfCheck() != S_OK)
	{
		return S_FAIL;
	}

	SRAM_Initialized = true;

	return S_OK;
}

u32 SRAM_GetSize(void)
{
	u32 RelAddr = 0xFFFFFF;
	RelAddr = RelAddr >> 1;
	SRAMAccess(RelAddr) = 0xAAAA;
	SRAMAccess(RelAddr - 1) = 0x5555;
	if (SRAMAccess(RelAddr) != 0xAAAA || SRAMAccess(RelAddr - 1) != 0x5555)
	{
		return 0;
	}
	do
	{
		if (SRAMAccess(RelAddr) != 0xAAAA || SRAMAccess(RelAddr - 1) != 0x5555)
		{
			return ((RelAddr << 1 | 1) + 1) * sizeof(u16);
		}
		RelAddr = RelAddr >> 1;
	} while (RelAddr);
	return 0;
}

//Linear congruential generator
void PseudorandomGeneratorSetSeed(u32 Val)
{
	PseudorandomLastVal = Val % 1013904223;
}

u16 PseudorandomGeneratorGetVal(void)
{
	PseudorandomLastVal = (22695477 * PseudorandomLastVal + 1103515245) % 1013904223;
	return PseudorandomLastVal;
}

STATUS SRAM_SelfCheck(void)
{
	u8 i;
#ifdef DEBUG
	u8 RepeatTimes = 1;
#else
	u8 RepeatTimes = 2;
#endif
	PseudorandomGeneratorSetSeed(SRAMSize);
	for (i = 0; i < RepeatTimes; i++)
	{
		u32 SizeInu16 = SRAMSize / sizeof(u16);
		u32 Seed = PseudorandomGeneratorGetVal() | PseudorandomGeneratorGetVal() << 16;
		PseudorandomGeneratorSetSeed(Seed);
		for (u32 i = 0; i < SizeInu16; i++)
		{
			SRAMAccess(i) = PseudorandomGeneratorGetVal();
		}
		PseudorandomGeneratorSetSeed(Seed);
		for (u32 i = 0; i < SizeInu16; i++)
		{
			if (SRAMAccess(i) != PseudorandomGeneratorGetVal())
			{
				return S_FAIL;
			}
		}

		PseudorandomGeneratorSetSeed(Seed);
		for (u32 i = 0; i < SizeInu16; i++)
		{
			SRAMAccess(i) = ~PseudorandomGeneratorGetVal();
		}
		PseudorandomGeneratorSetSeed(Seed);
		for (u32 i = 0; i < SizeInu16; i++)
		{
			if (SRAMAccess(i) != (u16)~(PseudorandomGeneratorGetVal()))
			{
				return S_FAIL;
			}
		}
	}
	return S_OK;
}

bool SRAM_CanAccess(void)
{
	return SRAM_Initialized && SRAMSize;
}
