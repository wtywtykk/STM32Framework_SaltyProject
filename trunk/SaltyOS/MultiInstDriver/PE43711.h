#pragma once

#include "HAL\UniGPIO.h"

C_HEADER_BEGIN

typedef struct
{
	UniGPIO_Handle SI;
	UniGPIO_Handle CLK;
	UniGPIO_Handle LE;
}PE43711_Handle;

STATUS PE43711_Init(PE43711_Handle* Handle, UniGPIO_Handle* SIPin, UniGPIO_Handle* CLKPin, UniGPIO_Handle* LEPin);
void PE43711_SetAttenuation(PE43711_Handle* Handle, float Att);

C_HEADER_END
