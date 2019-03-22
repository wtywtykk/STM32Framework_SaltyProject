#pragma once

C_HEADER_BEGIN

//ARM architecture requires data aligned to boundaries......
#define POOL_ALIGNMENT 4
#define POOL_INVALIDBITS (POOL_ALIGNMENT - 1)

STATUS Pool_Init(void* Pool, u32 Size);
void* Pool_Alloc(void* Pool, u32 Size);
void Pool_Free(void* Ptr);

C_HEADER_END
