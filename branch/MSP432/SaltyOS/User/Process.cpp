#include "HAL/HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "Algorithm/Transform/FFT/FFT.h"
#include "User/CurMeas.h"
#include "User/Sample.h"
#include <math.h>
#include <arm_math.h>
#include "User/Window.h"
#include "Process.h"
#include "Algorithm/Transform/TwiddleTable.h"
#include "User/AutoRange.h"

float FFTTimeBuffer[SAMPLE_LENGTH];
float FFTBuffer[SAMPLE_LENGTH / 2][2];
float FFTMag[SAMPLE_LENGTH / 2];

float HarmonicFrequency[MaxHarmonic] = { 0.0 };
float HarmonicAmplitude[MaxHarmonic] = { 0.0 };
float HarmonicPhase[MaxHarmonic] = { 0.0 };
float RMSVoltage = 0.0;
float DCVoltage = 0.0;
float ReconstructRMSVoltage = 0.0;
float ReconstructPKPKVoltage = 0.0;

void Process_Init(void)
{
}

void Transform(void)
{
	u32 i = 0;
	for (i = 0; i < SAMPLE_LENGTH; i++)
	{
		FFTTimeBuffer[i] = Window[i] * SampleBuffer[i];
	}
	RFFT_BitNormal(FFTTimeBuffer, &FFTBuffer[0][0], SAMPLE_LENGTH);
	for (i = 0; i < 3; i++)
	{
		FFTBuffer[i][0] = 0.0000001;
		FFTBuffer[i][1] = 0.0000000;
	}
	for (i = 0; i < SAMPLE_LENGTH / 2; i++)
	{
		FFTMag[i] = sqrtf(FFTBuffer[i][0] * FFTBuffer[i][0] + FFTBuffer[i][1] * FFTBuffer[i][1]);
	}
}

u32 GetPeakInRange(u32 RangeL, u32 RangeH)
{
	u32 i;
	float MaxVal = FFTMag[RangeL];
	u32 MaxIndex = RangeL;
	for (i = RangeL + 1; i < RangeH; i++)
	{
		if (FFTMag[i] > MaxVal)
		{
			MaxIndex = i;
			MaxVal = FFTMag[i];
		}
	}
	return MaxIndex;
}

float GetFreq(u32 Center)
{
	if (Center > 1 && Center < SAMPLE_LENGTH / 2 - 1)
	{
		double a7 = -0.0021186007064652;
		double a5 = 0.014688760383317;
		double a3 = -0.093186907863466;
		double a1 = 1.1429534026434;
		double coeff;
		double scoeff;
		double shift;
		coeff = (FFTMag[Center - 1] - FFTMag[Center + 1]) / FFTMag[Center];
		scoeff = coeff * coeff;
		shift = (((a7 * scoeff + a5) * scoeff + a3) * scoeff + a1) * coeff;
		return Sample_GetRealFrequency() * (Center - shift) / SAMPLE_LENGTH;
	}
	return 0;
}

float GetAmplitude(u32 Center)
{
	if (Center > 1 && Center < SAMPLE_LENGTH / 2 - 1)
	{
		double a6 = -0.018369569531081;
		double a4 = 0.086649736874094;
		double a2 = -0.27512989284594;
		double a0 = 0.74401633276214;
		double coeff;
		double scoeff;
		double res;
		coeff = (FFTMag[Center - 1] - FFTMag[Center + 1]) / FFTMag[Center];
		scoeff = coeff * coeff;
		res = (((a6 * scoeff + a4) * scoeff + a2) * scoeff + a0);
		return FFTMag[Center] / res * 3.0 / 0xFFFF / SAMPLE_LENGTH;
	}
	return 0;
}

float GetPhase(u32 Center)
{
	if (Center > 1 && Center < SAMPLE_LENGTH / 2 - 1)
	{
		double a7 = 0.0066553741789237;
		double a5 = -0.046143285176289;
		double a3 = 0.2927374367889;
		double a1 = -3.5904748545698;
		double coeff;
		double scoeff;
		double shift;
		coeff = (FFTMag[Center - 1] - FFTMag[Center + 1]) / FFTMag[Center];
		scoeff = coeff * coeff;
		shift = (((a7 * scoeff + a5) * scoeff + a3) * scoeff + a1) * coeff;
		return atan2f(FFTBuffer[Center][1], FFTBuffer[Center][0]) - shift;
	}
	return 0;
}

void MeasureFundamental(void)
{
	u32 SpecMaxIndex = 0;
	SpecMaxIndex = GetPeakInRange(0, SAMPLE_LENGTH / 2);
	HarmonicFrequency[1] = GetFreq(SpecMaxIndex);
	HarmonicAmplitude[1] = GetAmplitude(SpecMaxIndex);
	HarmonicPhase[1] = GetPhase(SpecMaxIndex);
}

void MeasureHarmonic(void)
{
	u32 i;
	float FundamentalBase = HarmonicFrequency[1] / Sample_GetRealFrequency() * SAMPLE_LENGTH;
	for (i = 2; i < MaxHarmonic; i++)
	{
		u32 SpecMaxIndex = 0;
		u32 HarmonicCenter = FundamentalBase * i;
		if (HarmonicCenter == 0 || HarmonicCenter + 1 > SAMPLE_LENGTH / 2)
		{
			break;
		}
		SpecMaxIndex = HarmonicCenter;// GetPeakInRange(HarmonicCenter - 1, HarmonicCenter + 2);
		HarmonicFrequency[i] = GetFreq(SpecMaxIndex);
		HarmonicAmplitude[i] = GetAmplitude(SpecMaxIndex);
		HarmonicPhase[i] = GetPhase(SpecMaxIndex);
	}
	for (; i < MaxHarmonic; i++)
	{
		HarmonicFrequency[i] = -1;
		HarmonicAmplitude[i] = -1;
		HarmonicPhase[i] = 0;
	}
}

void AlignPhase(void)
{
	for (u32 i = 2; i < MaxHarmonic; i++)
	{
		HarmonicPhase[i] -= HarmonicPhase[1] * i;
	}
	HarmonicPhase[1] = 0;
}

void FreqDomainMeasure(void)
{
	MeasureFundamental();
	MeasureHarmonic();
	AlignPhase();
}

void TimeDomainMeasure(void)
{
	s32 Cycles = 0;
	u32 MeasureLength;
	float DCAverage = 0.0;
	float ACAverage = 0.0;
	while (Cycles * (1.0 / HarmonicFrequency[1]) <= SAMPLE_LENGTH * (1.0 / Sample_GetRealFrequency()))
	{
		Cycles++;
	}
	Cycles--;
	if (Cycles <= 0)
	{
		RMSVoltage = -1;
		return;
	}
	MeasureLength = Cycles * (1.0 / HarmonicFrequency[1]) * Sample_GetRealFrequency();
	if (MeasureLength > Sample_GetRealFrequency())
	{
		MeasureLength = Sample_GetRealFrequency();
	}
	for (u32 i = 0; i < MeasureLength; i++)
	{
		float Val = SampleBuffer[i];
		DCAverage += Val;
		ACAverage += Val * Val;
	}
	DCAverage /= MeasureLength;
	ACAverage /= MeasureLength;
	ACAverage -= DCAverage * DCAverage;
	arm_sqrt_f32(ACAverage, &RMSVoltage);
	RMSVoltage = RMSVoltage / 2.0 / 0xFFFF * 3.0;
	DCVoltage = DCAverage / 2.0 / 0xFFFF * 3.0;
}

void ReconstructMeasure(void)
{
	u32 Len = SAMPLE_LENGTH / 4;
	float Min = 0;
	float Max = 0;
	ReconstructWave(FFTTimeBuffer, Len, false);
	Min = FFTTimeBuffer[0];
	Max = Min;
	for (u32 i = 0; i < Len; i++)
	{
		float Val = FFTTimeBuffer[i];
		ReconstructRMSVoltage += Val * Val;
		if (Max < Val)
		{
			Max = Val;
		}
		if (Min > Val)
		{
			Min = Val;
		}
	}
	ReconstructRMSVoltage /= Len;
	arm_sqrt_f32(ReconstructRMSVoltage, &ReconstructRMSVoltage);
	ReconstructPKPKVoltage = Max - Min;
}

void Process(void)
{
	Transform();
	FreqDomainMeasure();
	TimeDomainMeasure();
	ReconstructMeasure();
}

float GetFrequency(u8 Index)
{
	return HarmonicFrequency[Index];
}

float GetAmplitude(u8 Index)
{
	return HarmonicAmplitude[Index] / AutoRange_GetGain();
}

float GetRMS(void)
{
	return RMSVoltage / AutoRange_GetGain();
}

float GetDC(void)
{
	return DCVoltage / AutoRange_GetGain();
}

float GetReconstructRMS(void)
{
	return ReconstructRMSVoltage / AutoRange_GetGain();
}

float GetReconstructPKPK(void)
{
	return ReconstructPKPKVoltage / AutoRange_GetGain();
}

void ReconstructWave(float Buf[], u32 Len, float Normalize)
{
	u32 i = 0;
	for (i = 0; i < Len; i++)
	{
		Buf[i] = 0;
	}
	for (i = 1; i < MaxHarmonic; i++)
	{
		float Amp = HarmonicAmplitude[i];
		float Pha = HarmonicPhase[i];
		float Fre = 2 * PI * i / Len;
		if (Amp > 0)
		{
			if (Normalize)
			{
				Amp /= HarmonicAmplitude[1];
			}
			for (u32 j = 0; j < Len; j++)
			{
				Buf[j] += Amp * arm_cos_f32(Fre * j + Pha);
			}
		}
	}
}
