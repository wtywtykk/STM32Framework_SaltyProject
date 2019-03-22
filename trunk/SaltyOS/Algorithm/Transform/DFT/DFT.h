#pragma once

#include "Algorithm\MemCached\MemCached.h"
#include "Algorithm\AlgorithmTypes.h"

void CDFT_CalculatePoint(float* Buf, u32 Length, u32 Omega, float* Re, float* Im);
void CDFT_CalculatePoint_MemCached(FloatMemCache& Buf, u32 Length, u32 Omega, float* Re, float* Im);
void RDFT_CalculatePoint(float* Buf, u32 Length, u32 Omega, float* Re, float* Im);
void RDFT_CalculatePoint_MemCached(FloatMemCache& Buf, u32 Length, u32 Omega, float* Re, float* Im);
