#pragma once

#include "Algorithm\MemCached\MemCached.h"
#include "Algorithm\AlgorithmTypes.h"
#include "Algorithm\Transform\FFT\CFFT\CFFT_Radix2_MemCached.h"

void CFFT_BitReverse(float* Buf, u32 Length);
void CFFT_BitNormal(float* Buf, u32 Length);
void CFFT_MemCached_BitReverse(FloatMemCache& Buf, u32 Length);
void CFFT_MemCached_BitNormal(FloatMemCache& Buf, u32 Length);
void RFFT_BitNormal(float* Buf, float* DestBuf, u32 Length);
void RFFT_MemCached_BitNormal(FloatMemCache& Buf, FloatMemCache& DestBuf, u32 Length);
