#pragma once

#include "Algorithm\MemCached\MemCached.h"
#include "Algorithm\AlgorithmTypes.h"

void CFFT_Radix2_MemCached_BitReverse_Recursive(FloatMemCache& Buf, u32 AddressOffset, u8 Log2Length);
void CFFT_Radix2_MemCached_BitReverse(FloatMemCache& Buf, u8 Log2Length);
void CFFT_Radix2_MemCached_ReOrder(FloatMemCache& Buf, u8 Log2Length);
