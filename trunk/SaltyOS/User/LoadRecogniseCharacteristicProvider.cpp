#include "Kernel\Common\KCommon.h"
#include "User\LoadRecogniseSampler.h"
#include "User\LoadRecogniseCharacteristicProvider.h"
#include "Algorithm\AlgorithmTypes.h"
#include "Algorithm\WindowFunction\WindowFunction.h"
#include "Algorithm\Transform\FFT\FFT.h"
#include "Algorithm\Transform\DFT\DFT.h"
#include <string.h>
#include <math.h>

#define StablePercentage 0.01
#define StableMinThreshold 0.002

float CurrentRMS = 0.0;
float VoltageRMS = 0.0;
float Power = 0.0;
float LastCurrent = 0.0;
float* FFTBuffer = NULL;
bool Stable = false;
float LastStableVoltageRe;
float LastStableVoltageIm;
float LastStablePower;
HarmonicRecord LastStableHarmonic[HarmonicCount];
float* LastStableBuffer = NULL;
LoadCharacteristic Characteristic;

void LoadRecogniseCharacteristicProvider_Init(void)
{
	FFTBuffer = (float*)malloc(sizeof(float) * LoadRecogniseFFTSize);
	LastStableBuffer = (float*)malloc(sizeof(float) * LoadRecogniseFFTSize / 2);
}

void LoadRecogniseCharacteristicProvider_Scale(float Current[LoadRecogniseSampleBufferSize], float Voltage[LoadRecogniseSampleBufferSize])
{
	for (u32 i = 0; i < LoadRecogniseSampleBufferSize; i++)
	{
		Current[i] *= LoadRecogniseSampleADCCurrentReference / 0x7FFF;
		Voltage[i] *= LoadRecogniseSampleADCVoltageReference / 0x7FFF;
	}
}

void LoadRecogniseCharacteristicProvider_CalcBasicCharacteristic(float Current[LoadRecogniseSampleBufferSize], float Voltage[LoadRecogniseSampleBufferSize])
{
	u8 CompleteCycles = floor((float)LoadRecogniseSampleBufferSize / LoadRecogniseSampleRate / (1.0 / GridFrequency));
	u32 CompleteCycleIndex = CompleteCycles * LoadRecogniseSampleRate / GridFrequency - 1;
	double CurrentSum = 0.0;
	double VoltageSum = 0.0;
	double CurrentSqrSum = 0.0;
	double VoltageSqrSum = 0.0;
	double PowerSum = 0.0;
	double CurrentAverage;
	double VoltageAverage;
	for (u32 i = 0; i < CompleteCycleIndex; i++)
	{
		float CurrentVal = Current[i];
		float VoltageVal = Voltage[i];
		CurrentSum += CurrentVal;
		VoltageSum += VoltageVal;
		CurrentSqrSum += CurrentVal * CurrentVal;
		VoltageSqrSum += VoltageVal * VoltageVal;
		PowerSum += CurrentVal * VoltageVal;
	}
	CurrentAverage = CurrentSum / CompleteCycleIndex;
	VoltageAverage = VoltageSum / CompleteCycleIndex;

	static double CurrentMS = 0;
	static double VoltageMS = 0;
	CurrentMS = CurrentSqrSum / CompleteCycleIndex - CurrentAverage * CurrentAverage;
	VoltageMS = VoltageSqrSum / CompleteCycleIndex - VoltageAverage * VoltageAverage;
	if (CurrentMS < 0.0)
	{
		CurrentMS = 0.0;
	}
	if (VoltageMS < 0.0)
	{
		VoltageMS = 0.0;
	}
	CurrentRMS = sqrtf(CurrentMS) * LoadRecogniseCurrentScale;
	VoltageRMS = sqrtf(VoltageMS) * LoadRecogniseVoltageScale;
	Power = (PowerSum / CompleteCycleIndex - CurrentAverage * VoltageAverage) * LoadRecogniseCurrentScale * LoadRecogniseVoltageScale;

	float StableThreshold = abs(Power * StablePercentage);
	if (StableThreshold < StableMinThreshold)
	{
		StableThreshold = StableMinThreshold;
	}
	if (abs(LastCurrent - CurrentRMS) < StableThreshold)
	{
		Stable = true;
	}
	else
	{
		Stable = false;
	}
	LastCurrent = CurrentRMS;
}

void LoadRecogniseCharacteristicProvider_GetBasicCharacteristic(float* pCurrentRMS, float* pVoltageRMS, float* pPower)
{
	if (pCurrentRMS)
	{
		*pCurrentRMS = CurrentRMS;
	}
	if (pVoltageRMS)
	{
		*pVoltageRMS = VoltageRMS;
	}
	if (pPower)
	{
		*pPower = Power;
	}
}

void LoadRecogniseCharacteristicProvider_CalcSpectrumCharacteristic(float Current[LoadRecogniseSampleBufferSize], float Voltage[LoadRecogniseSampleBufferSize])
{
	if (Stable)
	{
		u32 FundamentalPos = roundf(GridFrequency * LoadRecogniseFFTSize / LoadRecogniseSampleRate);
		ApplyWindow(Voltage, WindowFunction_Blackman, LoadRecogniseFFTSize);
		RFFT_BitNormal(Voltage, FFTBuffer, LoadRecogniseFFTSize);
		LastStableVoltageRe = FFTBuffer[FundamentalPos * 2];
		LastStableVoltageIm = FFTBuffer[FundamentalPos * 2 + 1];
		ApplyWindow(Current, WindowFunction_Blackman, LoadRecogniseFFTSize);
		RFFT_BitNormal(Current, FFTBuffer, LoadRecogniseFFTSize);
	}
}

bool LoadRecogniseCharacteristicProvider_CheckStable(void)
{
	return Stable;
}

void LoadRecogniseCharacteristicProvider_AddPeak(LoadCharacteristic* Characteristic, SpectrumPeakRecord* NewPeak)
{
	for (u8 i = 0; i < SpectrumPeakCount; i++)
	{
		if (Characteristic->SpectrumPeak[i].Area < 0.000001)
		{
			Characteristic->SpectrumPeak[i] = *NewPeak;
			return;
		}
	}
	u8 SmallestPeakIndex = 0;
	for (u8 i = 1; i < SpectrumPeakCount; i++)
	{
		if (Characteristic->SpectrumPeak[i].Area < Characteristic->SpectrumPeak[SmallestPeakIndex].Area)
		{
			SmallestPeakIndex = i;
		}
	}
	if (Characteristic->SpectrumPeak[SmallestPeakIndex].Area < NewPeak->Area)
	{
		Characteristic->SpectrumPeak[SmallestPeakIndex] = *NewPeak;
	}
}

void LoadRecogniseCharacteristicProvider_InitPeak(SpectrumPeakRecord* NewPeak, u32 LeftIndex, u32 RightIndex, bool Invert)
{
	float Area = 0;
	NewPeak->Center = (LeftIndex + RightIndex) / 2.0 * LoadRecogniseSampleRate / LoadRecogniseFFTSize;
	NewPeak->Width = (RightIndex - LeftIndex + 1) * LoadRecogniseSampleRate / LoadRecogniseFFTSize;
	for (u32 i = LeftIndex; i <= RightIndex; i++)
	{
		Area += FFTBuffer[i];
	}
	if (Invert)
	{
		NewPeak->Area = -Area;
	}
	else
	{
		NewPeak->Area = Area;
	}
}

void LoadRecogniseCharacteristicProvider_SynthesizeCharacteristicRecord(bool Invert, bool CalculateSpectrumPeaks)
{
	if (Stable)
	{
		if (Invert)
		{
			Characteristic.Power = LastStablePower - Power;
		}
		else
		{
			Characteristic.Power = Power - LastStablePower;
		}
		LastStablePower = Power;

		float FundamentalMagitude = sqrtf(LastStableVoltageRe * LastStableVoltageRe + LastStableVoltageIm * LastStableVoltageIm);
		float RotateElementAngleRe = LastStableVoltageRe / FundamentalMagitude;
		float RotateElementAngleIm = -LastStableVoltageIm / FundamentalMagitude;
		float RotateRe = RotateElementAngleRe;
		float RotateIm = RotateElementAngleIm;
		for (u8 i = 0; i < HarmonicCount; i++)
		{
			float Freq = (i + 1) * GridFrequency;
			u32 Pos = roundf(Freq * LoadRecogniseFFTSize / LoadRecogniseSampleRate);
			HarmonicRecord HarmonicVal;
			HarmonicVal.Re = FFTBuffer[Pos * 2] * RotateRe - FFTBuffer[Pos * 2 + 1] * RotateIm;
			HarmonicVal.Im = FFTBuffer[Pos * 2] * RotateIm + FFTBuffer[Pos * 2 + 1] * RotateRe;

			float NextRotateRe = RotateRe * RotateElementAngleRe - RotateIm * RotateElementAngleIm;
			float NextRotateIm = RotateRe * RotateElementAngleIm + RotateIm * RotateElementAngleRe;

			RotateRe = NextRotateRe;
			RotateIm = NextRotateIm;

			if (Invert)
			{
				Characteristic.Harmonic[i].Re = LastStableHarmonic[i].Re - HarmonicVal.Re;
				Characteristic.Harmonic[i].Im = LastStableHarmonic[i].Im - HarmonicVal.Im;
			}
			else
			{
				Characteristic.Harmonic[i].Re = HarmonicVal.Re - LastStableHarmonic[i].Re;
				Characteristic.Harmonic[i].Im = HarmonicVal.Im - LastStableHarmonic[i].Im;
			}

			LastStableHarmonic[i] = HarmonicVal;
		}

		Characteristic.SpectrumPeakAvailable = CalculateSpectrumPeaks;
		for (u8 i = 0; i < SpectrumPeakCount; i++)
		{
			Characteristic.SpectrumPeak[i].Center = 0.0;
			Characteristic.SpectrumPeak[i].Width = 0.0;
			Characteristic.SpectrumPeak[i].Area = 0.0;
		}

		u32 SpectrumPeakLowerIndex = roundf(SpectrumPeakRangeLower * LoadRecogniseFFTSize / LoadRecogniseSampleRate);
		double SpectrumAverage = 0.0;
		for (u32 i = SpectrumPeakLowerIndex; i < LoadRecogniseFFTSize / 2; i++)
		{
			float LogMag = log(sqrt(FFTBuffer[i * 2] * FFTBuffer[i * 2] + FFTBuffer[i * 2 + 1] * FFTBuffer[i * 2 + 1]));
			FFTBuffer[i] = LogMag - LastStableBuffer[i];
			LastStableBuffer[i] = LogMag;
			SpectrumAverage += FFTBuffer[i];
		}
		SpectrumAverage /= LoadRecogniseFFTSize / 2 - SpectrumPeakLowerIndex;

		if (CalculateSpectrumPeaks)
		{
			u8 PeakTransitionCount = 0;
			bool CountingPeak = false;
			u32 PeakLeft = 0;
			u32 PeakRight = 0;
			for (u32 i = SpectrumPeakLowerIndex; i < LoadRecogniseFFTSize / 2; i++)
			{
				if ((!Invert && (FFTBuffer[i] > SpectrumAverage)) || (Invert && (FFTBuffer[i] < SpectrumAverage)))
				{
					if (CountingPeak)
					{
						PeakTransitionCount = 0;
					}
					else
					{
						PeakTransitionCount++;
					}
				}
				else
				{
					if (CountingPeak)
					{
						PeakTransitionCount++;
					}
					else
					{
						PeakTransitionCount = 0;
					}
				}
				if (PeakTransitionCount > SpectrumPeakTransitionLength)
				{
					if (CountingPeak)
					{
						SpectrumPeakRecord NewPeak;
						PeakRight = i;
						LoadRecogniseCharacteristicProvider_InitPeak(&NewPeak, PeakLeft - SpectrumPeakTransitionLength, PeakRight - SpectrumPeakTransitionLength, Invert);
						LoadRecogniseCharacteristicProvider_AddPeak(&Characteristic, &NewPeak);
						CountingPeak = false;
						PeakTransitionCount = 0;
					}
					else
					{
						PeakLeft = i;
						CountingPeak = true;
						PeakTransitionCount = 0;
					}
				}
			}
			if (CountingPeak)
			{
				SpectrumPeakRecord NewPeak;
				LoadRecogniseCharacteristicProvider_InitPeak(&NewPeak, PeakLeft - SpectrumPeakTransitionLength, LoadRecogniseFFTSize / 2 - 1, Invert);
				LoadRecogniseCharacteristicProvider_AddPeak(&Characteristic, &NewPeak);
			}
		}
	}
}

void LoadRecogniseCharacteristicProvider_GetCharacteristicRecord(LoadCharacteristic* Char)
{
	*Char = Characteristic;
}

float LoadRecogniseCharacteristicProvider_GetSpectrumArea(float Center, float Width)
{
	float Area = 0;
	u32 Left = roundf((Center - Width / 2.0) * LoadRecogniseFFTSize / LoadRecogniseSampleRate);
	u32 Right = roundf((Center + Width / 2.0) * LoadRecogniseFFTSize / LoadRecogniseSampleRate);
	if (Right >= LoadRecogniseFFTSize / 2 - 1)
	{
		Right = LoadRecogniseFFTSize / 2 - 1;
	}
	for (u32 i = Left; i <= Right; i++)
	{
		Area += FFTBuffer[i];
	}
	return Area;
}
