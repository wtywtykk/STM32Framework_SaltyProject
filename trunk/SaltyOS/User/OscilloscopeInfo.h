#pragma once

#include "User\OscilloscopeFPGAAbstrast.h"
#include "User\DPOChannel.h"

#define FPGAClock 100000000
#define SamplingClock 100000000
#define MinSamplingPeriod (1.0 / SamplingClock)

class OscilloscopeInfo
{
protected:
	typedef enum
	{
		TrigStatus_Auto,
		TrigStatus_Run,
		TrigStatus_Stop,
		TrigStatus_Trigged,
		TrigStatus_Wait,
	}TriggerStatus;

	typedef enum
	{
		TrigMode_Single = 0x00,
		TrigMode_Auto = 0x80,
		TrigMode_Normal = 0x40,
	}TriggerMode;

	const u32 TimeBase[3 * 9] = {
		1,2,5,//1-5ns
		10,20,50,//10-50ns
		100,200,500,//100-500ns
		1000,2000,5000,//1-5us
		10000,20000,50000,//10-50us
		100000,200000,500000,//100-500us
		1000000,2000000,5000000,//1-5ms
		10000000,20000000,50000000,//10-50ms
		100000000,200000000,500000000,//100-500ms
	};
	const u32 SamplePrescaler[3 * 9] = {
		//Equivalent sampling
		0,0,0,//1-5ns
		0,0,0,//10-50ns
		0,/*Real time sampling*/0,2,//100-500ns
		4,9,24,//1-5us
		49,99,249,//10-50us
		499,999,2499,//100-500us
		4999,9999,24999,//1-5ms
		49999,99999,249999,//10-50ms
		499999,999999,2499999,//100-500ms
	};
	bool Running = true;
	TriggerMode TrigMode = TrigMode_Auto;

	float TriggerPosition = 0.5;
	float TriggerVoltage = 0.0;
	u8 SelectedTimeBase = 9;

	u32 GetCurrentPrescaler(void);
private:
	bool EquiSampling = true;
	const PIXEL ChannelColors[4] = { YELLOW,CYAN,MAGENTA,0x03FF };
	u32 EquivalentSamplingPrescaler = 0;

	class OscilloscopeFPGAAbstrast* FPGAAbstrast;
public:
	OscilloscopeInfo();
	~OscilloscopeInfo();
private:
};
