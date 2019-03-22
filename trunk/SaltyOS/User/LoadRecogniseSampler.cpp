#include "Kernel\Common\KCommon.h"
#include "Driver\ADS8363.h"
#include "User\LoadRecogniseSampler.h"
#include <stdlib.h>

float* SampleBuffer[2];

void LoadRecogniseSampler_Init(void)
{
	ADS8363_Init();
	ADS8363_SetChannel(0);
	ADS8363_SetPseudoDifferential(true);
	ADS8363_SetREFDAC1(false, LoadRecogniseSampleADCCurrentReference);
	ADS8363_SetREFDAC2(false, LoadRecogniseSampleADCVoltageReference);
	ADS8363_SetREFCM(0xFF0F);
	SampleBuffer[0] = (float*)malloc(sizeof(float) * LoadRecogniseSampleBufferSize);
	SampleBuffer[1] = (float*)malloc(sizeof(float) * LoadRecogniseSampleBufferSize);
}

void LoadRecogniseSampler_Sample(void)
{
	s16 VoltageData;
	s16 CurrentData;
	for (u32 i = 0; i < LoadRecogniseSampleBufferSize; i++)
	{
		while (ADS8363_IsReady());
		ADS8363_GetResult(&VoltageData, &CurrentData);
		SampleBuffer[0][i] = -CurrentData;
		SampleBuffer[1][i] = VoltageData;
	}
}

float* LoadRecogniseSampler_GetCurrentData(void)
{
	return SampleBuffer[0];
}

float* LoadRecogniseSampler_GetVoltageData(void)
{
	return SampleBuffer[1];
}
