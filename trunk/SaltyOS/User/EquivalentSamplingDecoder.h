#pragma once

#include <math.h>

class EquivalentSamplingDecoder
{
	float NormalizedSamplingPeriod = 1.0;
	float CurrentUnifiedSamplingTime = 0.0;
	u32 DataCount = 0;
	float* Buffer = NULL;
	u32 BufferLength = 0;
public:
	EquivalentSamplingDecoder(float* Buf, u32 Length);
	~EquivalentSamplingDecoder();
	void SwitchBuffer(float* Buf, u32 Length);
	void Clear();
	void ChangePeriod(float NewSamplingPeriod, float NewUnknownPeriod);
	void Process(float* Val, u32 Length);
	bool AlignTrigger(float TriggerVal, float Hysteresis);
	u32 GetDataCount(void);
	static bool IsValidValue(float Val);
};
