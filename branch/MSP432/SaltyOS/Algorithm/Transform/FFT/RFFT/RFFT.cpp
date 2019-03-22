#include "Kernel\Common\KCommon.h"
#include "Algorithm\Transform\TwiddleTable.h"
#include "Algorithm\Transform\FFT\CFFT\CFFT_Radix2.h"
#include "Algorithm\MemCached\MemCached.h"
#include "Algorithm\Transform\FFT\CFFT\CFFT_Radix2_MemCached.h"

void RFFT_CombineComplex(float* Buf, float* DestBuf, u8 Log2Length)
{
	u32 FFTSize = 1L << Log2Length;
	DestBuf[0] = Buf[0] + Buf[1];
	DestBuf[1] = 0;
	for (u32 i = 1; i < FFTSize / 4; i++)
	{
		u32 n = TwiddleTableSize * i / FFTSize;
		float SrcLeftRe = Buf[2 * i];
		float SrcLeftIm = Buf[2 * i + 1];
		float SrcRightRe = Buf[2 * (FFTSize / 2 - i)];
		float SrcRightIm = Buf[2 * (FFTSize / 2 - i) + 1];
		float TwidderRe = GetTwiddleIm(n);
		float TwidderIm = -GetTwiddleRe(n);
		float LePRiRe = SrcLeftRe + SrcRightRe;
		float LePRiIm = SrcLeftIm + SrcRightIm;
		float LeMRiRe = SrcLeftRe - SrcRightRe;
		float LeMRiIm = SrcLeftIm - SrcRightIm;
		float ResLeftRe = LePRiRe + TwidderRe * LeMRiRe - TwidderIm * LePRiIm;
		float ResLeftIm = LeMRiIm + TwidderRe * LePRiIm + TwidderIm * LeMRiRe;
		float ResRightRe = LePRiRe + TwidderRe * (-LeMRiRe) - (-TwidderIm) * LePRiIm;
		float ResRightIm = -LeMRiIm + TwidderRe * LePRiIm + (-TwidderIm) * (-LeMRiRe);
		ResLeftRe /= 2.0;
		ResLeftIm /= 2.0;
		ResRightRe /= 2.0;
		ResRightIm /= 2.0;
		DestBuf[2 * i] = ResLeftRe;
		DestBuf[2 * i + 1] = ResLeftIm;
		DestBuf[2 * (FFTSize / 2 - i)] = ResRightRe;
		DestBuf[2 * (FFTSize / 2 - i) + 1] = ResRightIm;
	}
	DestBuf[FFTSize / 2] = Buf[FFTSize / 2];
	DestBuf[FFTSize / 2 + 1] = -Buf[FFTSize / 2 + 1];
}

void RIFFT_CombineComplex(float* Buf, float* DestBuf, u8 Log2Length)//BUG!!!!!
{
	u32 FFTSize = 1L << Log2Length;
	DestBuf[0] = Buf[0] + Buf[1];
	DestBuf[1] = 0;
	for (u32 i = 1; i < FFTSize / 4; i++)
	{
		u32 n = TwiddleTableSize * i / FFTSize;
		float SrcLeftRe = Buf[2 * i];
		float SrcLeftIm = Buf[2 * i + 1];
		float SrcRightRe = Buf[2 * (FFTSize / 2 - i)];
		float SrcRightIm = Buf[2 * (FFTSize / 2 - i) + 1];
		float TwidderRe = -GetTwiddleIm(n);
		float TwidderIm = -GetTwiddleRe(n);
		float LePRiRe = SrcLeftRe + SrcRightRe;
		float LePRiIm = SrcLeftIm + SrcRightIm;
		float LeMRiRe = SrcLeftRe - SrcRightRe;
		float LeMRiIm = SrcLeftIm - SrcRightIm;
		float ResLeftRe = LePRiRe + TwidderRe * LeMRiRe - TwidderIm * LePRiIm;
		float ResLeftIm = LeMRiIm + TwidderRe * LePRiIm + TwidderIm * LeMRiRe;
		float ResRightRe = LePRiRe + TwidderRe * (-LeMRiRe) - (-TwidderIm) * LePRiIm;
		float ResRightIm = -LeMRiIm + TwidderRe * LePRiIm + (-TwidderIm) * (-LeMRiRe);
		ResLeftRe /= 2.0;
		ResLeftIm /= 2.0;
		ResRightRe /= 2.0;
		ResRightIm /= 2.0;
		DestBuf[2 * i] = ResLeftRe;
		DestBuf[2 * i + 1] = ResLeftIm;
		DestBuf[2 * (FFTSize / 2 - i)] = ResRightRe;
		DestBuf[2 * (FFTSize / 2 - i) + 1] = ResRightIm;
	}
	DestBuf[FFTSize / 2] = Buf[FFTSize / 2];
	DestBuf[FFTSize / 2 + 1] = -Buf[FFTSize / 2 + 1];
}

void RFFT_CombineComplex_MemCached(FloatMemCache& Buf, FloatMemCache& DestBuf, u8 Log2Length)
{
	u32 FFTSize = 1L << Log2Length;
	DestBuf[0] = Buf[0] + Buf[1];
	DestBuf[1] = 0;
	for (u32 i = 1; i < FFTSize / 4; i++)
	{
		u32 n = TwiddleTableSize * i / FFTSize;
		float SrcLeftRe = Buf[2 * i];
		float SrcLeftIm = Buf[2 * i + 1];
		float SrcRightRe = Buf[2 * (FFTSize / 2 - i)];
		float SrcRightIm = Buf[2 * (FFTSize / 2 - i) + 1];
		float TwidderRe = GetTwiddleIm(n);
		float TwidderIm = -GetTwiddleRe(n);
		float LePRiRe = SrcLeftRe + SrcRightRe;
		float LePRiIm = SrcLeftIm + SrcRightIm;
		float LeMRiRe = SrcLeftRe - SrcRightRe;
		float LeMRiIm = SrcLeftIm - SrcRightIm;
		float ResLeftRe = LePRiRe + TwidderRe * LeMRiRe - TwidderIm * LePRiIm;
		float ResLeftIm = LeMRiIm + TwidderRe * LePRiIm + TwidderIm * LeMRiRe;
		float ResRightRe = LePRiRe + TwidderRe * (-LeMRiRe) - (-TwidderIm) * LePRiIm;
		float ResRightIm = -LeMRiIm + TwidderRe * LePRiIm + (-TwidderIm) * (-LeMRiRe);
		ResLeftRe /= 2.0;
		ResLeftIm /= 2.0;
		ResRightRe /= 2.0;
		ResRightIm /= 2.0;
		DestBuf[2 * i] = ResLeftRe;
		DestBuf[2 * i + 1] = ResLeftIm;
		DestBuf[2 * (FFTSize / 2 - i)] = ResRightRe;
		DestBuf[2 * (FFTSize / 2 - i) + 1] = ResRightIm;
	}
	DestBuf[FFTSize / 2] = Buf[FFTSize / 2];
	DestBuf[FFTSize / 2 + 1] = -Buf[FFTSize / 2 + 1];
}
