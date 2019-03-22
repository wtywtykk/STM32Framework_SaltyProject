#pragma once

#include "HAL\UniGPIO.h"
#include "HAL\UniSPI.h"

C_HEADER_BEGIN

typedef enum
{
	VCAL_CH0 = 0x0,
	CH1 = 0x1,
	CAL1 = 0xC,
	CAL2 = 0xD,
	CAL3 = 0xE,
	CAL4 = 0xF,
}PGA11x_Channels;

typedef struct
{
	UniGPIO_Handle CSpin;
	UniSPI_Handle SPI_Handle;
	u8 GainCode;
	u8 ChannelSel;
}PGA11x_Handle;

STATUS PGA11x_Init(PGA11x_Handle* Handle, UniGPIO_Handle* MOSIPin, UniGPIO_Handle* SCKPin, UniGPIO_Handle* CSPin);
void PGA11x_SetGain(PGA11x_Handle* Handle, u8 GainCode);
void PGA11x_SetChannel(PGA11x_Handle* Handle, PGA11x_Channels ChannelSel);

C_HEADER_END
