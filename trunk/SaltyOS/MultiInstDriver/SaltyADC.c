#include "HAL\HCommon.h"
#include "HAL\UniGPIO.h"
#include "HAL\UniSPI.h"
#include "MultiInstDriver\SaltyADC.h"
#include <string.h>
#include <math.h>

#define ADF4351_TransmitTimeout 10
#define ADF4351_AppendRegControlBits(Index,x) (((x) & 0xFFFFFFF8) | ((Index) & 0x7))
#define ADF4351_SetRegBits(x,Val,Shift,Mask) (((x) & ~Mask) | (((u32)(Val) << Shift) & Mask))
#define ADF4351_GetRegBits(x,Shift,Mask) (((x) & Mask) >> Shift)

STATUS SaltyADC_Init(SaltyADC_Handle* Handle, UniGPIO_Handle* MISOPin, UniGPIO_Handle* MOSIPin, UniGPIO_Handle* SCKPin, UniGPIO_Handle* CSPin, UniGPIO_Handle* BUSYPin, UniGPIO_Handle* CONVPin)
{
	SoftSPI_Init(&Handle->SPI_Handle, MISOPin, MOSIPin, SCKPin, 8, false, false, 0, 0);

	Handle->BUSY = *BUSYPin;
	Handle->CONV = *CONVPin;
	Handle->CS = *CSPin;

	UniGPIO_SetInput(BUSYPin);
	UniGPIO_SetInput(CONVPin);
	UniGPIO_SetOutput(CSPin);

	UniGPIO_SetHigh(CSPin);

	return S_OK;
}

void SaltyADC_ConvertChannel(SaltyADC_Handle* Handle, u8 Channel)
{
}
