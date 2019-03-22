#include "HAL\HCommon.h"
#include <arm_math.h>

#define SincTableLength 512

float SincInterpolationTable_float[SincTableLength];
double SincInterpolationTable_double[SincTableLength];

STATUS SincInterpolation_Init(void)
{
	SincInterpolationTable_float[0] = 0.0;
	SincInterpolationTable_double[0] = 0.0;
	for (u16 x = 1; x < SincTableLength; x++)
	{
		double pix = PI * x;
		SincInterpolationTable_double[x] = sin(pix) / pix;
		SincInterpolationTable_float[x] = SincInterpolationTable_double[x];
	}
	return S_OK;
}

void SincInterpolation_Processfloat(float* Src, u32 Len, float* Dst)
{
	for (u32 i = 0; i < Len; i++)
	{
		Dst[i] = 0;
		for (u32 j = 0; j < SincTableLength; j++)
		{
			//if(j>)
		}
	}
}
