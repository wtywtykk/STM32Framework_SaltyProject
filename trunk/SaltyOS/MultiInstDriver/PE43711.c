#include "HAL\HCommon.h"
#include "HAL\UniGPIO.h"
#include "MultiInstDriver\PE43711.h"

#define PE43711_Delay 0

STATUS PE43711_Init(PE43711_Handle* Handle, UniGPIO_Handle* SIPin, UniGPIO_Handle* CLKPin, UniGPIO_Handle* LEPin)
{
	Handle->SI = *SIPin;
	Handle->CLK = *CLKPin;
	Handle->LE = *LEPin;

	UniGPIO_SetOutput(SIPin);
	UniGPIO_SetOutput(CLKPin);
	UniGPIO_SetOutput(LEPin);

	UniGPIO_SetLow(SIPin);
	UniGPIO_SetLow(CLKPin);
	UniGPIO_SetLow(LEPin);

	return S_OK;
}

void PE43711_SetAttenuation(PE43711_Handle* Handle, float Att)
{
	u8 IntAtt;
	u8 i;

	assert(Att >= 0 - 0.0001 && Att <= 31.75 + 0.0001);//In case of float point error

	if (Att < 0.0)
	{
		Att = 0;
	}
	if (Att > 31.75)
	{
		Att = 31.75;
	}

	IntAtt = Att * 4 + 0.5;
	IntAtt &= 0x7F;

	for (i = 0; i < 8; i++)
	{
		UniGPIO_SetVal(&Handle->SI, IntAtt & 0x01);
		HAL_Delay(PE43711_Delay);
		UniGPIO_SetHigh(&Handle->CLK);
		HAL_Delay(PE43711_Delay);
		UniGPIO_SetLow(&Handle->CLK);
		IntAtt >>= 1;
	}

	HAL_Delay(PE43711_Delay);
	UniGPIO_SetHigh(&Handle->LE);
	HAL_Delay(PE43711_Delay);
	UniGPIO_SetLow(&Handle->LE);
}
