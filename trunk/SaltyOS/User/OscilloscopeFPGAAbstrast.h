#pragma once

#include "User\Oscilloscope.h"

class OscilloscopeFPGAAbstrast
{
	typedef struct
	{
		u8 B1;//8
		u8 B2;//16
		u16 TrigPos;//32
		u32 DivFactor;//64
		u8 B5;//72
		u8 B6;//80
		u8 B7;//88
		u8 B8;//96
		u8 B9;//104
		u8 B10;//112
		u8 B11;//120
		u8 B12;//128
	}FPGAConfigStruct;

	typedef struct
	{
		u32 HighCounter;
		u32 UnknownCounter;
		u32 ReferenceCounter;
		u8 Padding[4];
	}FPGAResultStruct;

	typedef enum
	{
		FPGAState_Sampling,
		FPGAState_Transmiting,
		FPGAState_Reset,
	}FPGAState;

	FPGAState CommState = FPGAState_Reset;
	FPGAConfigStruct CurrentConfig;
	FPGAConfigStruct NewConfig;
	FPGAResultStruct FPGAResult;

	bool Triggered = false;

	class Oscilloscope* OscInst = NULL;
public:
	OscilloscopeFPGAAbstrast(class Oscilloscope* Osc);
	~OscilloscopeFPGAAbstrast(void);
	bool ReteriveValue(u16* Buffer, u32 BufferSizeInWord, u32* ReadSize);
	void UpdateFPGAConfig(void);
	void ForceUpdateFPGAConfig(void);
	float GetCurrentTriggerPosition(void);
	u32 GetCurrentPrescaler(void);
	bool IsLastTimeTriggered(void);
	void GetFrequencyMeterValue(u32* Ref, u32* Unknown, u32* High);
private:
	void UpdateFrequency(void);
};
