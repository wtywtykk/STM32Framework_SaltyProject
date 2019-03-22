#pragma once

C_HEADER_BEGIN

extern u16* const SRAMAddr;
extern u32 const SRAMSize;

STATUS SRAM_Init(void);
bool SRAM_CanAccess(void);

C_HEADER_END
