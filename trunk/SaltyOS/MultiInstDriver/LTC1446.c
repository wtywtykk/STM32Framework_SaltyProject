#include "HAL\HCommon.h"
#include "HAL\UniGPIO.h"
#include "HAL\UniSPI.h"
#include "LTC1446.h"

#define LTC1446_TransmitTimeout 10

STATUS LTC1446_Init(LTC1446_Handle* Handle, UniGPIO_Handle* MISOPin, UniGPIO_Handle* MOSIPin, UniGPIO_Handle* SCKPin, UniGPIO_Handle* CSPin)
{
	SoftSPI_Init(&Handle->SPI_Handle, MISOPin, MOSIPin, SCKPin, 8, false, false, 1, 0);

	Handle->CS = *CSPin;
	UniGPIO_SetHigh(CSPin);

	return S_OK;
}

void LTC1446_Update(LTC1446_Handle* Handle)
{
	u8 CombinedVal[3];
	CombinedVal[0] = Handle->ChannelA >> 4;
	CombinedVal[1] = Handle->ChannelA << 4 | Handle->ChannelB >> 8;
	CombinedVal[2] = Handle->ChannelB;
	UniSPI_TransmitBytes(&Handle->SPI_Handle, &Handle->CS, CombinedVal, sizeof(CombinedVal), LTC1446_TransmitTimeout);
}

void LTC1446_SetChannelA(LTC1446_Handle* Handle, u16 Val)
{
	Handle->ChannelA = Val & 0x0FFF;
	LTC1446_Update(Handle);
}

void LTC1446_SetChannelB(LTC1446_Handle* Handle, u16 Val)
{
	Handle->ChannelB = Val & 0x0FFF;
	LTC1446_Update(Handle);
}

void LTC1446_SetChannelAB(LTC1446_Handle* Handle, u16 ValA, u16 ValB)
{
	Handle->ChannelA = ValA & 0x0FFF;
	Handle->ChannelB = ValB & 0x0FFF;
	LTC1446_Update(Handle);
}
