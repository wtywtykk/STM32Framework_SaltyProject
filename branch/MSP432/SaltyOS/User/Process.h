#pragma once

void Process_Init(void);
void Process(void);
float GetFrequency(u8 Index);
float GetAmplitude(u8 Index);
float GetRMS(void);
float GetDC(void);
float GetReconstructRMS(void);
float GetReconstructPKPK(void);
void ReconstructWave(float Buf[], u32 Len, float Normalize);

extern float FFTBuffer[SAMPLE_LENGTH / 2][2];
extern float FFTMag[SAMPLE_LENGTH / 2];

#define MaxHarmonic 25
