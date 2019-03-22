#include "Kernel\Common\KCommon.h"
#include "Setup\FlashAbstract.h"
#include "Driver\SST39VFxxxx.h"
#include "Driver\W25Qxx.h"
#include <string.h>

STATUS FlashAbstract_SectorErase(FlashIndex Index, u32 Address)
{
	switch (Index)
	{
	case SST:
		return SST39VFxxxx_SectorErase(Address);
		break;
	case SPI:
		return W25Qxx_SectorErase(Address);
		break;
	default:
		return S_FAIL;
		break;
	}
}

STATUS FlashAbstract_BlockErase(FlashIndex Index, u32 Address)
{
	switch (Index)
	{
	case SST:
		return SST39VFxxxx_BlockErase(Address);
		break;
	case SPI:
		return W25Qxx_Block32Erase(Address);
		break;
	default:
		return S_FAIL;
		break;
	}
}

STATUS FlashAbstract_ChipErase(FlashIndex Index)
{
	switch (Index)
	{
	case SST:
		return SST39VFxxxx_ChipErase();
		break;
	case SPI:
		return W25Qxx_ChipErase();
		break;
	default:
		return S_FAIL;
		break;
	}
}

STATUS FlashAbstract_Program(FlashIndex Index, u32 Address, void* Buf, u32 Length)
{
	switch (Index)
	{
	case SST:
		return SST39VFxxxx_Program(Address, Buf, Length);
		break;
	case SPI:
		return W25Qxx_Program(Address, Buf, Length);
		break;
	default:
		return S_FAIL;
		break;
	}
}

u8 FlashAbstract_Readu8(FlashIndex Index, u32 Address)
{
	switch (Index)
	{
	case SST:
		return SST39VFxxxx_Read8(Address);
		break;
	case SPI:
	{
		u8 Buf = 0;
		if (W25Qxx_Read(Address, &Buf, sizeof(Buf)) == S_OK)
		{
			return Buf;
		}
		else
		{
			return 0;
		}
	}
	break;
	default:
		return 0;
		break;
	}
}

STATUS FlashAbstract_ReadInformationBlock(FlashIndex Index, InformationStruct* InfoStru)
{
	switch (Index)
	{
	case SST:
		strcpy(InfoStru->ChipName, SST39VFxxxx_ChipName);
		InfoStru->ChipSize = SST39VFxxxx_ChipSize;
		return S_OK;
		break;
	case SPI:
	{
		strcpy(InfoStru->ChipName, W25Qxx_ChipName);
		InfoStru->ChipSize = W25Qxx_ChipSize;
		return S_OK;
	}
	break;
	default:
		strcpy(InfoStru->ChipName, "");
		InfoStru->ChipSize = 0;
		return S_FAIL;
		break;
	}
}
