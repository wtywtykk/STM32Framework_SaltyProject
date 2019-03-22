#pragma once

#define LoadRecogniseSampleRate 1000000
#define LoadRecogniseSampleBufferSize 131072

#define LoadRecogniseSampleADCCurrentReference 2.5
#define LoadRecogniseSampleADCVoltageReference 2.5

void LoadRecogniseSampler_Init(void);
void LoadRecogniseSampler_Sample(void);
float* LoadRecogniseSampler_GetCurrentData(void);
float* LoadRecogniseSampler_GetVoltageData(void);
