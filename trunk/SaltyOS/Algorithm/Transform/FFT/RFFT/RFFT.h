#pragma once

#include "Kernel\Common\KCommon.h"
#include "Algorithm\MemCached\MemCached.h"
#include "Algorithm\AlgorithmTypes.h"
#include "Algorithm\Transform\FFT\CFFT\CFFT_Radix2_MemCached.h"

void RFFT_CombineComplex(float* Buf, float* DestBuf, u8 Log2Length);
void RFFT_CombineComplex_MemCached(FloatMemCache& Buf, FloatMemCache& DestBuf, u8 Log2Length);
