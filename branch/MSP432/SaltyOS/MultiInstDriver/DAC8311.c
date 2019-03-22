#include "HAL\HCommon.h"
#include "HAL\UniGPIO.h"
#include "HAL\UniSPI.h"
#include "DAC8311.h"

#define DAC8311_TransmitTimeout 10

STATUS DAC8311_Init(DAC8311_Handle* Handle, UniGPIO_Handle* MOSIPin, UniGPIO_Handle* SCKPin, UniGPIO_Handle* CSPin)
{
	SoftSPI_Init(&Handle->SPI_Handle, NULL, MOSIPin, SCKPin, 8, false, false, 1, 0);

	Handle->CSpin = *CSPin;
	UniGPIO_SetHigh(CSPin);

	return S_OK;
}

void DAC8311_SetVal(DAC8311_Handle* Handle, u16 Val)
{
	UniSPI_TransmitWord(&Handle->SPI_Handle, &Handle->CSpin, Val, DAC8311_TransmitTimeout);
}
