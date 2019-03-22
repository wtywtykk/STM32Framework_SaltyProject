#pragma once

#include "User\LoadRecogniseCharacteristicProvider.h"

typedef struct
{
	float Average;
	float Variance;
}RandomizedLoadCharacteristicValue;

typedef struct
{
	RandomizedLoadCharacteristicValue Re;
	RandomizedLoadCharacteristicValue Im;
}RandomizedLoadCharacteristicHarmonicRecord;

typedef struct
{
	float Center;
	float Width;
	RandomizedLoadCharacteristicValue Area;
}RandomizedLoadCharacteristicSpectrumPeakRecord;

typedef struct
{
	RandomizedLoadCharacteristicValue Power;
	RandomizedLoadCharacteristicHarmonicRecord Harmonic[HarmonicCount];
	RandomizedLoadCharacteristicSpectrumPeakRecord SpectrumPeak[SpectrumPeakCount];
}RandomizedLoadCharacteristic;
