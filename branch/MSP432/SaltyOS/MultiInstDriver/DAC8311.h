#pragma once

#include "HAL\UniGPIO.h"
#include "HAL\UniSPI.h"

C_HEADER_BEGIN

typedef struct
{
	UniGPIO_Handle CSpin;
	UniSPI_Handle SPI_Handle;
}DAC8311_Handle;

STATUS DAC8311_Init(DAC8311_Handle* Handle, UniGPIO_Handle* MOSIPin, UniGPIO_Handle* SCKPin, UniGPIO_Handle* CSPin);
void DAC8311_SetVal(DAC8311_Handle* Handle, u16 Val);

C_HEADER_END
