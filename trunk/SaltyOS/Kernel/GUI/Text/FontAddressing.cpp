#include "Kernel\Common\KCommon.h"
#include "Driver\SST39VFxxxx.h"
#include "FontAddressing.h"

u32 GetStartAddress(const FONTINDEX* Index)
{
	if (Index->StorageMode & AddressInFlash)
	{
		return Index->DataStart + (u32)SST39VFxxxx_Base;
	}
	else
	{
		return Index->DataStart;
	}
}

u32 GetEndAddress(const FONTINDEX* Index)
{
	if (Index->StorageMode | AddressInFlash)
	{
		return Index->DataEnd + (u32)SST39VFxxxx_Base;
	}
	else
	{
		return Index->DataEnd;
	}
}

static u32 GetStandardAddressingOffset(const FONTINDEX* Index, u16 Char)
{
	return Index->Size*(Char - Index->AscLBound);
}

static u32 GetGB2312AddressingOffset(const FONTINDEX* Index, u16 Char)
{
	u32 Sub = Char - Index->AscLBound;
	u32 Block = (Sub >> 8) & 0xFF;
	u32 Bit = Sub & 0xFF;
	return Index->Size*(94 * Block + Bit);
}

u32 GetAddressingOffset(const FONTINDEX* Index, u16 Char)
{
	switch (Index->StorageMode & AddressingBits)
	{
	default:
	case StandardAddressing:
		return GetStandardAddressingOffset(Index, Char);
		break;
	case GB2312Addressing:
		return GetGB2312AddressingOffset(Index, Char);
	}
}
