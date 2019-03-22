#pragma once

C_HEADER_BEGIN

typedef enum
{
	KernelInitFailed,
	MemoryCorruption,
	InvalidCall,
}BugCheckCode;

void BugCheck(BugCheckCode ErrorCode, u32 Param1, u32 Param2, u32 Param3, u32 Param4);

C_HEADER_END
