#include "Kernel\Common\KCommon.h"
#include "Algorithm\Transform\TwiddleTable.h"

__inline void CFFT_Radix2_Butterfly(float& a_Re, float& a_Im, float& b_Re, float& b_Im, float Wn_Re, float Wn_Im)
{
	float Res_a_Re = a_Re + b_Re;
	float Res_a_Im = a_Im + b_Im;
	float a_minus_b_Re = a_Re - b_Re;
	float a_minus_b_Im = a_Im - b_Im;
	float Res_b_Re = a_minus_b_Re * Wn_Re - a_minus_b_Im * Wn_Im;
	float Res_b_Im = a_minus_b_Re * Wn_Im + a_minus_b_Im * Wn_Re;
	a_Re = Res_a_Re;
	a_Im = Res_a_Im;
	b_Re = Res_b_Re;
	b_Im = Res_b_Im;
}

void CFFT_Radix2_BitReverse_Recursive(float* Buf, u8 Log2Length)
{
	u32 FFTSize = 1L << Log2Length;
	u32 HalfLength = 1L << (Log2Length - 1);
	for (u32 i = 0; i < HalfLength; i++)
	{
		u32 n = TwiddleTableSize * i / FFTSize;
		float TwidderRe = GetTwiddleRe(n);
		float TwidderIm = GetTwiddleIm(n);
		CFFT_Radix2_Butterfly(Buf[2 * i], Buf[2 * i + 1], Buf[2 * (i + HalfLength)], Buf[2 * (i + HalfLength) + 1], TwidderRe, TwidderIm);
	}
	if (Log2Length > 1)
	{
		CFFT_Radix2_BitReverse_Recursive(Buf, Log2Length - 1);
		CFFT_Radix2_BitReverse_Recursive(Buf + 2 * HalfLength, Log2Length - 1);
	}
}

void CFFT_Radix2_BitReverse(float* Buf, u8 Log2Length)
{
	u32 FFTSize = 1L << Log2Length;
	for (u8 Stage = Log2Length; Stage > 0; Stage--)
	{
		u32 TwidderStep = 1 << (Log2Length - Stage);
		u32 MaxTwidder = 1L << (Stage - 1);
		u32 ButterflySpacing = 1L << Stage;
		u32 ButterflyHeight = ButterflySpacing / 2;
		for (u32 TwidderIndex = 0; TwidderIndex < MaxTwidder; TwidderIndex += 1)
		{
			u32 n = TwiddleTableSize * TwidderStep * TwidderIndex / FFTSize;
			float TwidderRe = GetTwiddleRe(n);
			float TwidderIm = GetTwiddleIm(n);
			for (u32 i = 0; i < FFTSize; i += ButterflySpacing)
			{
				CFFT_Radix2_Butterfly(Buf[2 * (i + TwidderIndex)], Buf[2 * (i + TwidderIndex) + 1], Buf[2 * (i + TwidderIndex + ButterflyHeight)], Buf[2 * (i + TwidderIndex + ButterflyHeight) + 1], TwidderRe, TwidderIm);
			}
		}
	}
}

void CIFFT_Radix2_BitReverse(float* Buf, u8 Log2Length)
{
	u32 FFTSize = 1L << Log2Length;
	for (u8 Stage = Log2Length; Stage > 0; Stage--)
	{
		u32 TwidderStep = 1 << (Log2Length - Stage);
		u32 MaxTwidder = 1L << (Stage - 1);
		u32 ButterflySpacing = 1L << Stage;
		u32 ButterflyHeight = ButterflySpacing / 2;
		for (u32 TwidderIndex = 0; TwidderIndex < MaxTwidder; TwidderIndex += 1)
		{
			u32 n = TwiddleTableSize * TwidderStep * TwidderIndex / FFTSize;
			float TwidderRe = GetTwiddleRe(n);
			float TwidderIm = -GetTwiddleIm(n);
			for (u32 i = 0; i < FFTSize; i += ButterflySpacing)
			{
				CFFT_Radix2_Butterfly(Buf[2 * (i + TwidderIndex)], Buf[2 * (i + TwidderIndex) + 1], Buf[2 * (i + TwidderIndex + ButterflyHeight)], Buf[2 * (i + TwidderIndex + ButterflyHeight) + 1], TwidderRe, TwidderIm);
			}
		}
	}
}

void CFFT_Radix2_ReOrder(float* Buf, u8 Log2Length)
{
	u32 FFTSize = 1L << Log2Length;
	for (u32 i = 1; i < FFTSize; i++)
	{
		u32 NormalPos = i;
		u32 ReversedPos = 0;
		for (u8 j = 0; j < Log2Length; j++)
		{
			ReversedPos <<= 1;
			ReversedPos |= NormalPos & 0x1;
			NormalPos >>= 1;
		}
		if (i < ReversedPos)
		{
			float Temp = Buf[i * 2];
			Buf[i * 2] = Buf[ReversedPos * 2];
			Buf[ReversedPos * 2] = Temp;
			Temp = Buf[i * 2 + 1];
			Buf[i * 2 + 1] = Buf[ReversedPos * 2 + 1];
			Buf[ReversedPos * 2 + 1] = Temp;
		}
	}
}
