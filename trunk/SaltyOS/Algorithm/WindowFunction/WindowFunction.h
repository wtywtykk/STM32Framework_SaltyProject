#pragma once

#include "Kernel\Common\KCommon.h"
#include <assert.h>
#include "Algorithm\MemCached\MemCached.h"
#include "Algorithm\AlgorithmTypes.h"

#define WindowFunctionSize 131072
extern const float WindowFunction_Blackman[WindowFunctionSize / 2];

__inline void ApplyWindow(float* Buf, const float* Window, u32 Length)
{
	u8 LogLength = 0;
	u8 TableLogLength = 0;
	u8 LengthDiff = 0;
	u32 i;
	assert(Length);
	i = Length;
	while (i)
	{
		LogLength++;
		i >>= 1;
	}
	i = WindowFunctionSize;
	while (i)
	{
		TableLogLength++;
		i >>= 1;
	}
	assert(LogLength <= TableLogLength);
	LengthDiff = TableLogLength - LogLength;

	for (u32 i = 0; i < Length / 2; i++)
	{
		Buf[i] *= Window[i << LengthDiff];
	}
	for (u32 i = Length / 2; i < Length; i++)
	{
		Buf[i] *= Window[(Length - i - 1) << LengthDiff];
	}
}

__inline void ApplyWindow_MemCached(FloatMemCache& Buf, const float* Window, u32 Length)
{
	u8 LogLength = 0;
	u8 TableLogLength = 0;
	u8 LengthDiff = 0;
	u32 i;
	assert(Length);
	i = Length;
	while (i)
	{
		LogLength++;
		i >>= 1;
	}
	i = WindowFunctionSize;
	while (i)
	{
		TableLogLength++;
		i >>= 1;
	}
	assert(LogLength <= TableLogLength);
	LengthDiff = TableLogLength - LogLength;

	for (u32 i = 0; i < Length / 2; i++)
	{
		Buf[i] *= Window[i << LengthDiff];
	}
	for (u32 i = Length / 2; i < Length; i++)
	{
		Buf[i] *= Window[(Length - i - 1) << LengthDiff];
	}
}
