#include "Kernel\Common\KCommon.h"
#include "HAL\FPGAParPort.h"
#include "HAL\FPGASPIPort.h"

//2048 point FFT
//Only Prev half is used
const float FFTClock = 16e3;
const u32 FFTPoints = 2048;
const u16 FFTAverageRatio = 4;
u16 FFTVal[FFTPoints / 2];
u32 FFTValAverage[FFTPoints / 2] = { 0 };
float PeakFreq[1];

void ReteriveFFT(void)
{
	FPGAParPort_Reset();
	if (ParPort_StartPipeline())
	{
		u32 ReadSize = 0;
		ParPort_Read(FFTVal, 1024, &ReadSize, false);
	}
	for (u32 i = 0; i < sizeof(FFTValAverage) / sizeof(FFTValAverage[0]); i++)
	{
		FFTValAverage[i] = (FFTValAverage[i] * (FFTAverageRatio - 1) + FFTVal[i]) / FFTAverageRatio;
	}
}

void SearchSignals(void)
{
	u16 MaxVal = 0;
	u32 MaxIndex = 0;
	for (u32 i = 0; i < sizeof(FFTValAverage) / sizeof(FFTValAverage[0]); i++)
	{
		if (FFTValAverage[i] > MaxVal && (float)(i)* FFTClock / FFTPoints >= 300)
		{
			MaxVal = FFTValAverage[i];
			MaxIndex = i;
		}
	}
	PeakFreq[0] = (float)(MaxIndex)* FFTClock / FFTPoints;
}

void SetFilterFreq(void)
{
	u32 Freqs[4];
	Freqs[0] = ((u32)1 << 31) * PeakFreq[0] / 80.0e6;
	Freqs[1] = Freqs[0];
	Freqs[2] = Freqs[0];
	Freqs[3] = Freqs[0];
	FPGASPIPort_Transmit(Freqs, sizeof(Freqs));
}

void ReceiverFilter_Process(void)
{
	ReteriveFFT();
	SearchSignals();
	SetFilterFreq();
}
