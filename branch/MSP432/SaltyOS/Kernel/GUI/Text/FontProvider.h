#pragma once

#include "Kernel\Common\KCommon.h"

typedef enum
{
	StandardAddressing = 0,
	GB2312Addressing = 1,

	AddressingBits = 0x0F
}ADDRESSINGMODE;

#define AddressInFlash 0x40
#define Transposed 0x80

typedef struct
{
	char Name[8];
	u16 Width;
	u16 Height;
	u16 Size;
	u16 AscLBound;
	u16 AscUBound;
	u16 StorageMode;
	u32 DataStart;
	u32 DataEnd;
}FONTINDEX;

const FONTINDEX* GetIndexAddress(pcstr FontName);
