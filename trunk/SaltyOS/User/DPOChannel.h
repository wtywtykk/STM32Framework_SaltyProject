#pragma once

#include "User\EquivalentSamplingDecoder.h"

#define DPOLayer 3
#define DPODataCount 500
#define WaveDraw_TimeScale 3.5
#define WaveDraw_AmpitudeScale 1.5
#define WaveDraw_DivCountX 10
#define WaveDraw_PointsPerDivX 20
#define WaveDraw_PixelsPerDivX (WaveDraw_PointsPerDivX * WaveDraw_TimeScale)
#define WaveDraw_DivCountY 8
#define WaveDraw_PointsPerDivY 32
#define WaveDraw_PixelsPerDivY (WaveDraw_PointsPerDivY * WaveDraw_AmpitudeScale)
#define WaveDraw_Width (WaveDraw_DivCountX * WaveDraw_PixelsPerDivX)
#define WaveDraw_Height (WaveDraw_DivCountY * WaveDraw_PixelsPerDivY)
#define ADCFullScale 0x7FF

class DPOChannel
{
	friend class Oscilloscope;
	typedef struct
	{
		float Data[DPODataCount];
		u32 Length;
	}DPOWaveRecord;
	DC* m_DC;
	PIXEL DrawingColor;
	PIXEL ChannelColors[DPOLayer];
	DPOWaveRecord Data[DPOLayer];
	DPOWaveRecord* DataPtr[DPOLayer];
	EquivalentSamplingDecoder* EquiDecoder;
protected:
	bool ACCoupling = false;
	bool Input50Ohm = false;
	bool InputAttenuation = false;
	bool IntermediateAmplifier = false;
	bool EnablePhosphor = true;
	float TriggerPosition = 0.5;
	u8 FPGATriggerPosition = 0;
	float WholeTime = 1.0;
	float AmpitudeOffset = 0.0;
	float DisplayScale = 1.0;
	float AttenuationFactor = 1.0;
	float WavePeriod = 1.0;
	float SamplingPeriod = 1.0;
public:
	DPOChannel(PIXEL Color, DC* DrawingDC);
	~DPOChannel(void);
	void ProcessData(u16* Buf, u32 BufferLength);
	void Draw(void);
	void DrawGrid(void);
	static u16 GetMinimumWidth(void);
	static u16 GetMinimumHeight(void);
	void SetFullScaleAmpitude(float FullScale);
	void DrawTrigger(void);
	u32 GetDataCountToTransmit(void);
	void SetEquiSamplingMode(bool IsEquiSamplingMode);
	void Clear(void);
private:
	PIXEL DimColor(PIXEL OrigColor, u8 Weight);
	void DrawWaveformRealTimeSampling(DPOWaveRecord* DrawingData, PIXEL Color);
	void DrawWaveformEquivalentSampling(DPOWaveRecord* DrawingData, PIXEL Color);
	void TransformADCValueToVoltage(u16* ADCBuf, float* VoltBuf, u32 BufferLength);
};
