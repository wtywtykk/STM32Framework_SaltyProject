#pragma once

#define LoadRecogniseCurrentScale 10.988700564971751412429378531073
#define LoadRecogniseVoltageScale 231.79822322066782395588685795977

#define GridFrequency 50.0
#define LoadRecogniseFFTSize 131072

#define HarmonicCount 10
#define SpectrumPeakCount 10
#define SpectrumPeakRangeLower 10000.0
#define SpectrumPeakTransitionLength 10

typedef struct
{
	float Re;
	float Im;
}HarmonicRecord;

typedef struct
{
	float Center;
	float Width;
	float Area;
}SpectrumPeakRecord;

typedef struct
{
	float Power;
	HarmonicRecord Harmonic[HarmonicCount];
	bool SpectrumPeakAvailable;
	SpectrumPeakRecord SpectrumPeak[SpectrumPeakCount];
}LoadCharacteristic;

void LoadRecogniseCharacteristicProvider_Init(void);
void LoadRecogniseCharacteristicProvider_Scale(float Current[LoadRecogniseSampleBufferSize], float Voltage[LoadRecogniseSampleBufferSize]);
void LoadRecogniseCharacteristicProvider_CalcBasicCharacteristic(float Current[LoadRecogniseSampleBufferSize], float Voltage[LoadRecogniseSampleBufferSize]);
void LoadRecogniseCharacteristicProvider_GetBasicCharacteristic(float* pCurrentRMS, float* pVoltageRMS, float* pPower);
void LoadRecogniseCharacteristicProvider_CalcSpectrumCharacteristic(float Current[LoadRecogniseSampleBufferSize], float Voltage[LoadRecogniseSampleBufferSize]);
bool LoadRecogniseCharacteristicProvider_CheckStable(void);
void LoadRecogniseCharacteristicProvider_SynthesizeCharacteristicRecord(bool Invert, bool CalculateSpectrumPeaks);
void LoadRecogniseCharacteristicProvider_GetCharacteristicRecord(LoadCharacteristic* Char);
float LoadRecogniseCharacteristicProvider_GetSpectrumArea(float Center, float Width);
