#pragma once

typedef enum
{
	SST = 0,
	SPI = 1,
	NullFlash = 2,
}FlashIndex;

typedef struct
{
	char ChipName[32];
	u32 ChipSize;
}InformationStruct;

STATUS FlashAbstract_SectorErase(FlashIndex Index, u32 Address);
STATUS FlashAbstract_BlockErase(FlashIndex Index, u32 Address);
STATUS FlashAbstract_ChipErase(FlashIndex Index);
STATUS FlashAbstract_Program(FlashIndex Index, u32 Address, void* Buf, u32 Length);
u8 FlashAbstract_Readu8(FlashIndex Index, u32 Address);
STATUS FlashAbstract_ReadInformationBlock(FlashIndex Index, InformationStruct* InfoStru);
