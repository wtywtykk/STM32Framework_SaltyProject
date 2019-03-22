#include "HAL\HCommon.h"
#include "HAL\UniGPIO.h"
#include "HAL\UniSPI.h"

#define TLV5617DeviceIndex (2)

#define CtrlBitR1	0x8000
#define CtrlBitSPD	0x4000
#define CtrlBitPWR	0x2000
#define CtrlBitR0	0x1000

#define OperWriteChBInstant	(0)
#define OperWriteBuffer		(CtrlBitR0)
#define OperWriteChAUpdateB	(CtrlBitR1)

static bool TLV5617_Initialized = false;
static u16 AdditionalControlBits;

STATUS TLV5617_Init(void)
{
	if (TLV5617_Initialized)
	{
		return S_OK;
	}

	//if (MuxSPI_Init() != S_OK)
	{
		return S_FAIL;
	}

	AdditionalControlBits = 0;
	TLV5617_Initialized = true;

	return S_OK;
}

void TLV5617_SetChannelA(u16 Value)
{
	if (Value > 0x3FF)
	{
		Value = 0x3FF;
	}
	//MuxSPI_SetDataSize(DataSize_16);
	//MuxSPI_Send(TLV5617DeviceIndex, Value << 2 | OperWriteChAUpdateB | AdditionalControlBits);
}

void TLV5617_SetChannelB(u16 Value)
{
	if (Value > 0x3FF)
	{
		Value = 0x3FF;
	}
	//MuxSPI_SetDataSize(DataSize_16);
	//MuxSPI_Send(TLV5617DeviceIndex, Value << 2 | OperWriteChBInstant | AdditionalControlBits);
}

void TLV5617_SetChannelAB(u16 ValueA, u16 ValueB)
{
	if (ValueA > 0x3FF)
	{
		ValueA = 0x3FF;
	}
	if (ValueB > 0x3FF)
	{
		ValueB = 0x3FF;
	}
	//MuxSPI_SetDataSize(DataSize_16);
	//MuxSPI_Send(TLV5617DeviceIndex, ValueA << 2 | OperWriteBuffer | AdditionalControlBits);
	//MuxSPI_Send(TLV5617DeviceIndex, ValueB << 2 | OperWriteChAUpdateB | AdditionalControlBits);
}

void TLV5617_SetSpeed(bool FastMode)
{
	AdditionalControlBits = FastMode ? CtrlBitSPD : 0;
}

void TLV5617_Shutdown(void)
{
	//MuxSPI_Send(TLV5617DeviceIndex, CtrlBitSPD);
}
