#include "Kernel\Common\KCommon.h"
#include "Algorithm\Transform\FFT\CFFT\CFFT_Radix2.h"
#include "Algorithm\MemCached\MemCached.h"
#include "Algorithm\AlgorithmTypes.h"
#include "Algorithm\Transform\FFT\CFFT\CFFT_Radix2_MemCached.h"
#include "Algorithm\Transform\FFT\RFFT\RFFT.h"
#include <assert.h>

u8 CFFT_LengthToLog2Length(u32 Length)
{
	u8 Ret = 0;
	assert(Length);
	while (Length)
	{
		Ret++;
		Length >>= 1;
	}
	return Ret - 1;
}

void CFFT_BitReverse(float* Buf, u32 Length)
{
	CFFT_Radix2_BitReverse(Buf, CFFT_LengthToLog2Length(Length));
}

void CFFT_BitNormal(float* Buf, u32 Length)
{
	u8 Log2Length = CFFT_LengthToLog2Length(Length);
	CFFT_Radix2_BitReverse(Buf, Log2Length);
	CFFT_Radix2_ReOrder(Buf, Log2Length);
}

void CFFT_MemCached_BitReverse(FloatMemCache& Buf, u32 Length)
{
	CFFT_Radix2_MemCached_BitReverse_Recursive(Buf, 0, CFFT_LengthToLog2Length(Length));
}

void CFFT_MemCached_BitNormal(FloatMemCache& Buf, u32 Length)
{
	u8 Log2Length = CFFT_LengthToLog2Length(Length);
	CFFT_Radix2_MemCached_BitReverse_Recursive(Buf, 0, Log2Length);
	CFFT_Radix2_MemCached_ReOrder(Buf, Log2Length);
}

void RFFT_BitNormal(float* Buf, float* DestBuf, u32 Length)
{
	u8 Log2Length = CFFT_LengthToLog2Length(Length);
	CFFT_Radix2_BitReverse(Buf, Log2Length - 1);
	CFFT_Radix2_ReOrder(Buf, Log2Length - 1);
	RFFT_CombineComplex(Buf, DestBuf, Log2Length);
}

void RFFT_MemCached_BitNormal(FloatMemCache& Buf, FloatMemCache& DestBuf, u32 Length)
{
	u8 Log2Length = CFFT_LengthToLog2Length(Length);
	CFFT_Radix2_MemCached_BitReverse_Recursive(Buf, 0, Log2Length - 1);
	CFFT_Radix2_MemCached_ReOrder(Buf, Log2Length - 1);
	RFFT_CombineComplex_MemCached(Buf, DestBuf, Log2Length);
}
