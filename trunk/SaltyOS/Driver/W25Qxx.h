#pragma once

C_HEADER_BEGIN

extern u32 W25Qxx_ChipSize;
extern pstr W25Qxx_ChipName;

STATUS W25Qxx_Init(void);
STATUS W25Qxx_ChipErase(void);
STATUS W25Qxx_SectorErase(u32 Addr);
STATUS W25Qxx_Block32Erase(u32 Addr);
STATUS W25Qxx_Block64Erase(u32 Addr);
STATUS W25Qxx_PowerDown(void);
STATUS W25Qxx_WakeUp(void);
STATUS W25Qxx_Read(u32 Addr, void* Buffer, u32 BufferSize);
STATUS W25Qxx_Program(u32 Addr, void* Buffer, u32 BufferSize);
STATUS W25Qxx_Program_Safe(u32 Addr, void* Buffer, u32 BufferSize);

C_HEADER_END
