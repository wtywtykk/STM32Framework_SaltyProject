#include "Kernel\Common\KCommon.h"
#include "EquivalentSamplingDecoder.h"
#include <malloc.h>

float InvalidValue;

EquivalentSamplingDecoder::EquivalentSamplingDecoder(float * Buf, u32 Length)
{
	InvalidValue = NAN;
	Buffer = Buf;
	BufferLength = Length;
	Clear();
}

EquivalentSamplingDecoder::~EquivalentSamplingDecoder()
{
}

void EquivalentSamplingDecoder::SwitchBuffer(float * Buf, u32 Length)
{
	Buffer = Buf;
	BufferLength = Length;
	Clear();
}

void EquivalentSamplingDecoder::Clear()
{
	for (u32 i = 0; i < BufferLength; i++)
	{
		Buffer[i] = InvalidValue;
	}
	CurrentUnifiedSamplingTime = 0.0;
	DataCount = 0;
}

void EquivalentSamplingDecoder::ChangePeriod(float NewSamplingPeriod, float NewUnknownPeriod)
{
	float NewNormalizedSamplingPeriod = BufferLength * NewSamplingPeriod / NewUnknownPeriod;
	if (NormalizedSamplingPeriod != NewNormalizedSamplingPeriod)
	{
		NormalizedSamplingPeriod = NewNormalizedSamplingPeriod;
		Clear();
	}
}

void EquivalentSamplingDecoder::Process(float * Val, u32 Length)
{
	for (u32 i = 0; i < Length; i++)
	{
		if (IsValidValue(Buffer[(u32)CurrentUnifiedSamplingTime]))
		{
			Buffer[(u32)CurrentUnifiedSamplingTime] = (Buffer[(u32)CurrentUnifiedSamplingTime] + Val[i]) * 0.5;
		}
		else
		{
			Buffer[(u32)CurrentUnifiedSamplingTime] = Val[i];
		}
		CurrentUnifiedSamplingTime += NormalizedSamplingPeriod;
		while (CurrentUnifiedSamplingTime >= BufferLength)
		{
			CurrentUnifiedSamplingTime -= BufferLength;
		}
	}
	DataCount += Length;
}
#include <stdio.h>

bool EquivalentSamplingDecoder::AlignTrigger(float TriggerVal, float Hysteresis)
{
	u32 TrigPos = 0;
	float TrigPosf = TrigPos;
	bool TriggerFound = false;
	float TriggerValLow = TriggerVal - Hysteresis / 2;
	float TriggerValHigh = TriggerVal + Hysteresis / 2;
	u32 LastLowVal = 0;
	bool LowValFound = false;
	for (u32 i = 0; i < BufferLength; i++)
	{
		if (IsValidValue(Buffer[i]))
		{
			if (Buffer[i] <= TriggerValLow)
			{
				LastLowVal = i;
				LowValFound = true;
			}
			else
			{
				if (LowValFound)
				{
					for (u32 j = 1; j < BufferLength; j++)
					{
						u32 Index = LastLowVal + j;
						if (Index >= BufferLength)
						{
							Index -= BufferLength;
						}
						if (IsValidValue(Buffer[Index]) && Buffer[Index] >= TriggerValHigh)
						{
							TrigPosf = LastLowVal + (TriggerVal - Buffer[LastLowVal]) * ((float)(LastLowVal + j) - (float)LastLowVal) / (Buffer[Index] - Buffer[LastLowVal]);
							if (TrigPosf >= BufferLength)
							{
								TrigPosf -= BufferLength;
							}
							TriggerFound = true;
							break;
						}
					}
					if (TriggerFound)
					{
						break;
					}
					else
					{
						LowValFound = false;
					}
				}
			}
		}
	}
	TrigPos = TrigPosf;
	if (TriggerFound && TrigPos != 0)
	{
		float* NewBuffer = (float*)malloc(sizeof(float) * BufferLength);
		for (u32 i = 0; i < BufferLength; i++)
		{
			NewBuffer[i] = 0;
		}
		u32 j;

		CurrentUnifiedSamplingTime -= TrigPos;
		if (CurrentUnifiedSamplingTime < 0)
		{
			CurrentUnifiedSamplingTime += BufferLength;
		}
		if (CurrentUnifiedSamplingTime >= BufferLength)
		{
			CurrentUnifiedSamplingTime -= BufferLength;
		}

		j = TrigPos;
		for (u32 i = 0; i < BufferLength; i++)
		{
			NewBuffer[i] = Buffer[j];
			j++;
			if (j >= BufferLength)
			{
				j = 0;
			}
		}
		for (u32 i = 0; i < BufferLength; i++)
		{
			Buffer[i] = NewBuffer[i];
		}
		free(NewBuffer);
	}
	printf("align: %s\n\r", TriggerFound ? "ok" : "FAIL");
	return TriggerFound;
}

u32 EquivalentSamplingDecoder::GetDataCount(void)
{
	return DataCount;
}

bool EquivalentSamplingDecoder::IsValidValue(float Val)
{
	return !isnan(Val);
}
