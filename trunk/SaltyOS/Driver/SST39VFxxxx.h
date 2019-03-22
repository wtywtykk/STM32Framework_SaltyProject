#pragma once

C_HEADER_BEGIN

/*Note:
	All addresses are in bytes.
	8 bit operations are slow.
	16/32 bir operations require the address being aligned to 16 bit.
*/

extern u32 SST39VFxxxx_ChipSize;
extern pstr SST39VFxxxx_ChipName;
extern const u8* volatile const SST39VFxxxx_Base;

STATUS SST39VFxxxx_Init(void);
u8 SST39VFxxxx_Read8(u32 Address);
u16 SST39VFxxxx_Read16(u32 Address);
u32 SST39VFxxxx_Read32(u32 Address);
STATUS SST39VFxxxx_Program8(u32 Address, u8 Data);
STATUS SST39VFxxxx_Program16(u32 Address, u16 Data);
STATUS SST39VFxxxx_Program32(u32 Address, u32 Data);
STATUS SST39VFxxxx_Program(u32 Address, void* Data, u32 Length);
STATUS SST39VFxxxx_ChipErase(void);
STATUS SST39VFxxxx_SectorErase(u32 Address);
STATUS SST39VFxxxx_BlockErase(u32 Address);
bool SST39VFxxxx_CanAccess(void);

C_HEADER_END
