#pragma once

#include "HAL\UniGPIO.h"
#include "HAL\UniSPI.h"

C_HEADER_BEGIN

typedef struct
{
	UniGPIO_Handle BUSY;
	UniGPIO_Handle CONV;
	UniGPIO_Handle CS;
	UniSPI_Handle SPI_Handle;
}SaltyADC_Handle;

STATUS SaltyADC_Init(SaltyADC_Handle* Handle, UniGPIO_Handle* MISOPin, UniGPIO_Handle* MOSIPin, UniGPIO_Handle* SCKPin, UniGPIO_Handle* CSPin, UniGPIO_Handle* BUSYPin, UniGPIO_Handle* CONVPin);
void SaltyADC_ConvertChannel(SaltyADC_Handle* Handle, u8 Channel);
bool SaltyADC_IsBusy(SaltyADC_Handle* Handle);
bool SaltyADC_PeekResult(SaltyADC_Handle* Handle, float* Result);
float SaltyADC_GetResult(SaltyADC_Handle* Handle);

C_HEADER_END
