#include "Kernel\Common\KCommon.h"
#include "Algorithm\AlgorithmTypes.h"
#include "Algorithm\Transform\TwiddleTable.h"
#include "Algorithm\MemCached\MemCached.h"

void CDFT_CalculatePoint(float* Buf, u32 Length, u32 Omega, float* Re, float* Im)
{
	float ReVal = 0.0;
	float ImVal = 0.0;
	for (u32 i = 0; i < Length; i++)
	{
		u32 n = TwiddleTableSize * i * Omega / Length;
		float SrcRe = Buf[2 * i];
		float SrcIm = Buf[2 * i + 1];
		float TwidderRe;
		float TwidderIm;
		while (n > TwiddleTableSize)
		{
			n -= TwiddleTableSize;
		}
		TwidderRe = GetTwiddleRe(n);
		TwidderIm = GetTwiddleIm(n);
		ReVal += SrcRe * TwidderRe - SrcIm * TwidderIm;
		ImVal += SrcRe * TwidderIm + SrcIm * TwidderRe;
	}
	if (Re)
	{
		*Re = ReVal;
	}
	if (Im)
	{
		*Im = ImVal;
	}
}

void CDFT_CalculatePoint_MemCached(FloatMemCache& Buf, u32 Length, u32 Omega, float* Re, float* Im)
{
	float ReVal = 0.0;
	float ImVal = 0.0;
	for (u32 i = 0; i < Length; i++)
	{
		u32 n = TwiddleTableSize * i * Omega / Length;
		float SrcRe = Buf[2 * i];
		float SrcIm = Buf[2 * i + 1];
		float TwidderRe;
		float TwidderIm;
		while (n > TwiddleTableSize)
		{
			n -= TwiddleTableSize;
		}
		TwidderRe = GetTwiddleRe(n);
		TwidderIm = GetTwiddleIm(n);
		ReVal += SrcRe * TwidderRe - SrcIm * TwidderIm;
		ImVal += SrcRe * TwidderIm + SrcIm * TwidderRe;
	}
	if (Re)
	{
		*Re = ReVal;
	}
	if (Im)
	{
		*Im = ImVal;
	}
}

void RDFT_CalculatePoint(float* Buf, u32 Length, u32 Omega, float* Re, float* Im)
{
	float ReVal = 0.0;
	float ImVal = 0.0;
	for (u32 i = 0; i < Length; i++)
	{
		u32 n = TwiddleTableSize * i * Omega / Length;
		float Src = Buf[i];
		float TwidderRe;
		float TwidderIm;
		while (n > TwiddleTableSize)
		{
			n -= TwiddleTableSize;
		}
		TwidderRe = GetTwiddleRe(n);
		TwidderIm = GetTwiddleIm(n);
		ReVal += Src * TwidderRe;
		ImVal += Src * TwidderIm;
	}
	if (Re)
	{
		*Re = ReVal;
	}
	if (Im)
	{
		*Im = ImVal;
	}
}

void RDFT_CalculatePoint_MemCached(FloatMemCache& Buf, u32 Length, u32 Omega, float* Re, float* Im)
{
	float ReVal = 0.0;
	float ImVal = 0.0;
	for (u32 i = 0; i < Length; i++)
	{
		u32 n = TwiddleTableSize * i * Omega / Length;
		float Src = Buf[i];
		float TwidderRe;
		float TwidderIm;
		while (n > TwiddleTableSize)
		{
			n -= TwiddleTableSize;
		}
		TwidderRe = GetTwiddleRe(n);
		TwidderIm = GetTwiddleIm(n);
		ReVal += Src * TwidderRe;
		ImVal += Src * TwidderIm;
	}
	if (Re)
	{
		*Re = ReVal;
	}
	if (Im)
	{
		*Im = ImVal;
	}
}
