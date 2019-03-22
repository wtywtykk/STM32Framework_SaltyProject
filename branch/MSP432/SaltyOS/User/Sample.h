#pragma once

#include "CurMeas.h"

void Sample_Init(void);
void Sample_SetSampleFrequency(float Freq);
float Sample_GetRealFrequency(void);
void Sample_SelectChannel(u8 Ch);
u8 Sample_GetCurChannel(void);
void Sample_StartSample(void);
bool Sample_IsSampleCompleted(void);
u8 Sample_GetProgress(void);

extern s16 SampleBuffer[SAMPLE_LENGTH];
