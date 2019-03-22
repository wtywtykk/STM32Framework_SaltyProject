#include "HAL/HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "HAL\UniGPIO.h"
#include <arm_math.h>
#include "CurMeas.h"
#include "BoardIO.h"
#include "Key.h"
#include "Sample.h"

const u8 ForceGain = 0;
u8 Gain = 1;
bool OverRange = false;
bool Switching = false;

void AutoRange_Process(void)
{
	if (ForceGain)
	{
		Gain = ForceGain;
	}
	else
	{
		s16 Min = SampleBuffer[0];
		s16 Max = SampleBuffer[1];
		for (u32 i = 1; i < SAMPLE_LENGTH; i++)
		{
			if (SampleBuffer[i] < Min)
			{
				Min = SampleBuffer[i];
			}
			if (SampleBuffer[i] > Max)
			{
				Max = SampleBuffer[i];
			}
		}
		Switching = false;
		OverRange = false;
		if (Max > 32760 || Min < -32760)
		{
			if (Gain <= 1)
			{
				Gain = 1;
				OverRange = true;
			}
			else
			{
				Gain = Gain / 2;
				Switching = true;
			}
		}
		while (Max <16000 && Min >-16000)
		{
			if (Gain >= 64)
			{
				Gain = 64;
			}
			else
			{
				Gain = Gain * 2;
				Switching = true;
			}
			Max *= 2;
			Min *= 2;
		}
	}
	//BoardIO_SetPGA(0, 1);
	BoardIO_SetPGA(1, Gain);
}

float AutoRange_GetGain(void)
{
	return Gain;
}

bool AutoRange_IsOverRange(void)
{
	return OverRange;
}

bool AutoRange_IsSwitching(void)
{
	return Switching;
}
