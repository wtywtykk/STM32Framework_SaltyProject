#include "HAL\HCommon.h"
#include "HAL\UniGPIO.h"
#include "HAL\UniSPI.h"
#include "PGA11x.h"

#define PGA11x_CMD_READ 0x6A00
#define PGA11x_CMD_WRITE 0x2A00
#define PGA11x_CMD_NOP 0x0000
#define PGA11x_CMD_SDN_DIS_WRITE 0xE100
#define PGA11x_CMD_SDN_EN_WRITE 0xE1F1

#define PGA11x_TransmitTimeout 100

STATUS PGA11x_Init(PGA11x_Handle* Handle, UniGPIO_Handle* MOSIPin, UniGPIO_Handle* SCKPin, UniGPIO_Handle* CSPin)
{
	SoftSPI_Init(&Handle->SPI_Handle, NULL, MOSIPin, SCKPin, 16, false, false, 1, 1);

	Handle->CSpin = *CSPin;
	UniGPIO_SetHigh(CSPin);

	return S_OK;
}

void PGA11x_SetGain(PGA11x_Handle* Handle, u8 GainCode)
{
	Handle->GainCode = GainCode;
	PGA11x_Update(Handle);
}

void PGA11x_SetChannel(PGA11x_Handle* Handle, PGA11x_Channels ChannelSel)
{
	Handle->ChannelSel = ChannelSel;
	PGA11x_Update(Handle);
}

void PGA11x_Update(PGA11x_Handle* Handle)
{
	u16 Val = PGA11x_CMD_WRITE | (Handle->GainCode << 4) | Handle->ChannelSel;
	UniSPI_TransmitWord(&Handle->SPI_Handle, &Handle->CSpin, Val, PGA11x_TransmitTimeout);
}
