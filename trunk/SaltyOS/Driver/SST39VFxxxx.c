#include "HAL\HCommon.h"
#include "HAL\FSMC.h"
#include "SST39VFxxxx.h"

#define ChipSpeed70ns//Speed may be 70ns or 90ns

const u8* volatile const SST39VFxxxx_Base = (u8*)(FSMC_Base2);
#define SST39VFxxxx_Data16(Address) ( ((u16* volatile)SST39VFxxxx_Base)+(Address))

bool SST39VFxxxx_Initialized = false;
NOR_HandleTypeDef SST39VFxxxx_FSMC_Handle;
u32 SST39VFxxxx_MaxProgramTime = 100;//In milliseconds
u32 SST39VFxxxx_MaxSectorEraseTime = 100;//In milliseconds
u32 SST39VFxxxx_MaxChipEraseTime = 1000;//In milliseconds
u32 SST39VFxxxx_ChipSize = 0;//In bytes
pstr SST39VFxxxx_ChipName = NULL;

u16 SST39VFxxxx_ReadProductID(void);
STATUS SST39VFxxxx_ReadCFI(void);
void SST39VFxxxx_SendCommandSequence(u16 CommandAddress, u16 Command);

STATUS SST39VFxxxx_FSMC_Init(void)
{
	FSMC_NORSRAM_TimingTypeDef Timing;

	SST39VFxxxx_FSMC_Handle.Instance = FSMC_NORSRAM_DEVICE;
	SST39VFxxxx_FSMC_Handle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
	/* SST39VFxxxx_FSMC_Handle.Init */
	SST39VFxxxx_FSMC_Handle.Init.NSBank = FSMC_NORSRAM_BANK2;
	SST39VFxxxx_FSMC_Handle.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
	SST39VFxxxx_FSMC_Handle.Init.MemoryType = FSMC_MEMORY_TYPE_NOR;
	SST39VFxxxx_FSMC_Handle.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
	SST39VFxxxx_FSMC_Handle.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
	SST39VFxxxx_FSMC_Handle.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
	SST39VFxxxx_FSMC_Handle.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
	SST39VFxxxx_FSMC_Handle.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
	SST39VFxxxx_FSMC_Handle.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
	SST39VFxxxx_FSMC_Handle.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
	SST39VFxxxx_FSMC_Handle.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
	SST39VFxxxx_FSMC_Handle.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
	SST39VFxxxx_FSMC_Handle.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
	SST39VFxxxx_FSMC_Handle.Init.PageSize = FSMC_PAGE_SIZE_NONE;
	/* Timing */
	Timing.AddressSetupTime = 0;
	Timing.AddressHoldTime = 1;
#ifdef ChipSpeed70ns
	Timing.DataSetupTime = 12;//70ns chip
#else
	Timing.DataSetupTime = 16;//90ns chip
#endif
	Timing.BusTurnAroundDuration = 0;
	Timing.CLKDivision = 2;
	Timing.DataLatency = 2;
	Timing.AccessMode = FSMC_ACCESS_MODE_B;
	/* ExtTiming */

	if (HAL_NOR_Init(&SST39VFxxxx_FSMC_Handle, &Timing, NULL) != HAL_OK)
	{
		return S_FAIL;
	}

	return S_OK;
}

STATUS SST39VFxxxx_Init(void)
{
	if (SST39VFxxxx_Initialized)
	{
		return S_OK;
	}

	if (FSMC_Init() != S_OK)
	{
		return S_FAIL;
	}

	if (SST39VFxxxx_FSMC_Init() != S_OK)
	{
		return S_FAIL;
	}

	switch (SST39VFxxxx_ReadProductID())
	{
	case 0x234B:
		SST39VFxxxx_ChipName = "SST39VF1601";
		break;
	case 0x234A:
		SST39VFxxxx_ChipName = "SST39VF1602";
		break;
	case 0x235B:
		SST39VFxxxx_ChipName = "SST39VF3201";
		break;
	case 0x235A:
		SST39VFxxxx_ChipName = "SST39VF3202";
		break;
	case 0x236B:
		SST39VFxxxx_ChipName = "SST39VF6401";
		break;
	case 0x236A:
		SST39VFxxxx_ChipName = "SST39VF6402";
		break;
	default:
		SST39VFxxxx_ChipName = "UNKNOWN";
		break;
	}

	if (SST39VFxxxx_ReadCFI() != S_OK)
	{
		return S_FAIL;
	}

	SST39VFxxxx_Initialized = true;

	return S_OK;
}

u8 SST39VFxxxx_Read8(u32 Address)
{
	assert(Address < SST39VFxxxx_ChipSize);

	return *(SST39VFxxxx_Base + Address);
}

u16 SST39VFxxxx_Read16(u32 Address)
{
	assert(Address < SST39VFxxxx_ChipSize - 1);

	return *(u16*)(SST39VFxxxx_Base + Address);
}

u32 SST39VFxxxx_Read32(u32 Address)
{
	assert(Address < SST39VFxxxx_ChipSize - 3);

	return *(u32*)(SST39VFxxxx_Base + Address);
}

STATUS SST39VFxxxx_WaitToggleDQ6(u32 TimeOut)
{
	u32 EndTime = HAL_GetTick() + TimeOut;
	while (HAL_GetTick() <= EndTime)
	{
		if ((*SST39VFxxxx_Data16(0x0000) & 0x0040) == (*SST39VFxxxx_Data16(0x0000) & 0x0040))
		{
			return S_OK;
		}
	}
	return S_FAIL;
}

STATUS SST39VFxxxx_Program8(u32 Address, u8 Data)
{
	assert(Address < SST39VFxxxx_ChipSize);

	SST39VFxxxx_SendCommandSequence(0x5555, 0x00A0);
	if (Address & 0x01)
	{
		*SST39VFxxxx_Data16(Address / sizeof(u16)) = Data << 8 | 0x00FF;
	}
	else
	{
		*SST39VFxxxx_Data16(Address / sizeof(u16)) = Data | 0xFF00;
	}
	return SST39VFxxxx_WaitToggleDQ6(SST39VFxxxx_MaxProgramTime);
}

static STATUS SST39VFxxxx_Program16Unaligned(u32 Address, u16 Data)
{
	assert(Address & 0x1);

	if (SST39VFxxxx_Program8(Address, Data & 0xFF) != S_OK)
	{
		return S_FAIL;
	}
	if (SST39VFxxxx_Program8(Address + 1, Data >> 8) != S_OK)
	{
		return S_FAIL;
	}

	return S_OK;
}

static STATUS SST39VFxxxx_Program16Aligned(u32 Address, u16 Data)
{
	assert((Address & 0x1) == 0);

	SST39VFxxxx_SendCommandSequence(0x5555, 0x00A0);
	*SST39VFxxxx_Data16(Address / sizeof(u16)) = Data;

	return SST39VFxxxx_WaitToggleDQ6(SST39VFxxxx_MaxProgramTime);
}

STATUS SST39VFxxxx_Program16(u32 Address, u16 Data)
{
	assert(Address < SST39VFxxxx_ChipSize - 1);

	if (Address & 0x1)
	{
		return SST39VFxxxx_Program16Unaligned(Address, Data);
	}
	else
	{
		return SST39VFxxxx_Program16Aligned(Address, Data);
	}

	return S_OK;
}

static STATUS SST39VFxxxx_Program32Unaligned(u32 Address, u32 Data)
{
	assert(Address & 0x1);

	if (SST39VFxxxx_Program8(Address, Data & 0xFF) != S_OK)
	{
		return S_FAIL;
	}
	if (SST39VFxxxx_Program16(Address + 1, Data >> 8) != S_OK)
	{
		return S_FAIL;
	}
	if (SST39VFxxxx_Program8(Address + 3, Data >> 24) != S_OK)
	{
		return S_FAIL;
	}
	return S_OK;
}

static STATUS SST39VFxxxx_Program32Aligned(u32 Address, u32 Data)
{
	assert((Address & 0x1) == 0);

	if (SST39VFxxxx_Program16(Address, Data & 0xFFFF) != S_OK)
	{
		return S_FAIL;
	}
	if (SST39VFxxxx_Program16(Address + 2, Data >> 16) != S_OK)
	{
		return S_FAIL;
	}
	return S_OK;
}

STATUS SST39VFxxxx_Program32(u32 Address, u32 Data)
{
	assert(Address < SST39VFxxxx_ChipSize - 3);

	if (Address & 0x1)
	{
		return SST39VFxxxx_Program32Unaligned(Address, Data);
	}
	else
	{
		return SST39VFxxxx_Program32Aligned(Address, Data);
	}
	return S_OK;
}

STATUS SST39VFxxxx_Program(u32 Address, void* Data, u32 Length)
{
	u8* CurData = (u8*)Data;
	//make sure that the address is aligned to word
	if (Address & 0x1)
	{
		if (SST39VFxxxx_Program8(Address, *CurData) != S_OK)
		{
			return S_FAIL;
		}
		Address++;
		CurData++;
		Length--;
	}

	//combine two operations to one. that will make it faster.
	//combine into u32 makes no sence. because stm32's fsmc only has 16 data lines....
	while (Length >= 2)
	{
		if (SST39VFxxxx_Program16(Address, *(u16*)CurData) != S_OK)
		{
			return S_FAIL;
		}
		Address += 2;
		CurData += 2;
		Length -= 2;
	}

	//process the remaining bytes
	if (Length)
	{
		if (SST39VFxxxx_Program8(Address, *CurData) != S_OK)
		{
			return S_FAIL;
		}
	}
	return S_OK;
}

STATUS SST39VFxxxx_ChipErase(void)
{
	SST39VFxxxx_SendCommandSequence(0x5555, 0x0080);
	SST39VFxxxx_SendCommandSequence(0x5555, 0x0010);

	return SST39VFxxxx_WaitToggleDQ6(SST39VFxxxx_MaxChipEraseTime);
}

STATUS SST39VFxxxx_SectorErase(u32 Address)//Address in bytes
{
	SST39VFxxxx_SendCommandSequence(0x5555, 0x0080);
	SST39VFxxxx_SendCommandSequence(Address / 2, 0x0030);

	return SST39VFxxxx_WaitToggleDQ6(SST39VFxxxx_MaxChipEraseTime);
}

STATUS SST39VFxxxx_BlockErase(u32 Address)//Address in bytes
{
	SST39VFxxxx_SendCommandSequence(0x5555, 0x0080);
	SST39VFxxxx_SendCommandSequence(Address / 2, 0x0050);

	return SST39VFxxxx_WaitToggleDQ6(SST39VFxxxx_MaxChipEraseTime);
}

bool SST39VFxxxx_CanAccess(void)
{
	return SST39VFxxxx_Initialized && SST39VFxxxx_ChipSize;
}

u16 SST39VFxxxx_ReadProductID(void)
{
	u16 DeviceID;

	//Software Product ID Entry
	SST39VFxxxx_SendCommandSequence(0x5555, 0x0090);
	HAL_Delay(1);

	if (*SST39VFxxxx_Data16(0x0000) != 0x00BF)//SST Manufacturer ID
	{
		return 0x0000;
	}

	DeviceID = *SST39VFxxxx_Data16(0x0001);

	//Software Product ID/CFI/Sec ID Exit
	SST39VFxxxx_SendCommandSequence(0x5555, 0x00F0);
	HAL_Delay(1);

	return DeviceID;
}

STATUS SST39VFxxxx_ReadCFI(void)
{
	//CFI Query Entry
	SST39VFxxxx_SendCommandSequence(0x5555, 0x0090);
	HAL_Delay(1);

	if (*SST39VFxxxx_Data16(0x0010) != 'Q' || *SST39VFxxxx_Data16(0x0011) != 'R' || *SST39VFxxxx_Data16(0x0012) != 'Y')
	{
		return S_FAIL;
	}

	SST39VFxxxx_MaxProgramTime = 1 << (*SST39VFxxxx_Data16(0x001F) + *SST39VFxxxx_Data16(0x0023));
	if (SST39VFxxxx_MaxProgramTime == 0)
	{
		return S_FAIL;
	}
	SST39VFxxxx_MaxProgramTime = SST39VFxxxx_MaxProgramTime / 1000 + 1;

	SST39VFxxxx_MaxSectorEraseTime = 1 << (*SST39VFxxxx_Data16(0x0021) + *SST39VFxxxx_Data16(0x0025));
	if (SST39VFxxxx_MaxSectorEraseTime == 0)
	{
		return S_FAIL;
	}

	SST39VFxxxx_MaxChipEraseTime = 1 << (*SST39VFxxxx_Data16(0x0022) + *SST39VFxxxx_Data16(0x0026));
	if (SST39VFxxxx_MaxChipEraseTime == 0)
	{
		return S_FAIL;
	}

	SST39VFxxxx_ChipSize = 1 << (*SST39VFxxxx_Data16(0x0027));
	if (SST39VFxxxx_ChipSize == 0)
	{
		return S_FAIL;
	}

	//Software Product ID/CFI/Sec ID Exit
	SST39VFxxxx_SendCommandSequence(0x5555, 0x00F0);
	HAL_Delay(1);

	return S_OK;
}

void SST39VFxxxx_SendCommandSequence(u16 CommandAddress, u16 Command)
{
	*SST39VFxxxx_Data16(0x5555) = 0x00AA;
	*SST39VFxxxx_Data16(0x2AAA) = 0x0055;
	*SST39VFxxxx_Data16(CommandAddress) = Command;
}