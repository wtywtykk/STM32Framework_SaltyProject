#pragma once

C_HEADER_BEGIN

STATUS MemMan_Init(void);
STATUS MemMan_InitExtendedPool(void);
void* MemMan_malloc(u32 Size);
void MemMan_free(void* Ptr);

C_HEADER_END
