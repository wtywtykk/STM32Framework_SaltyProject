#pragma once

#include "HAL\UniGPIO.h"
#include "HAL\UniSPI.h"

C_HEADER_BEGIN

typedef struct
{
	UniGPIO_Handle CS;
	UniSPI_Handle SPI_Handle;
	u16 ChannelA;
	u16 ChannelB;
}LTC1446_Handle;

STATUS LTC1446_Init(LTC1446_Handle* Handle, UniGPIO_Handle* MISOPin, UniGPIO_Handle* MOSIPin, UniGPIO_Handle* SCKPin, UniGPIO_Handle* CSPin);
void LTC1446_SetChannelA(LTC1446_Handle* Handle, u16 Val);
void LTC1446_SetChannelB(LTC1446_Handle* Handle, u16 Val);
void LTC1446_SetChannelAB(LTC1446_Handle* Handle, u16 ValA, u16 ValB);

C_HEADER_END
