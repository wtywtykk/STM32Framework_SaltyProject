#include "Kernel\Common\KCommon.h"
#include "MultiInstDriver\LTC1446.h"
#include "HAL\StandardSPIPort.h"

LTC1446_Handle LTC1446TestHandle;

void LTC1446Test(void)
{
	static bool Inited = false;
	static u16 i = 0;
	if (!Inited)
	{
		UniGPIO_Handle MISO;
		UniGPIO_Handle MOSI;
		UniGPIO_Handle SCK;
		UniGPIO_Handle CS;
		Inited = true;
		StandardSPIPort_Init(1, &MISO, &MOSI, &SCK, &CS, NULL, NULL, NULL, NULL, NULL);
		LTC1446_Init(&LTC1446TestHandle, &MISO, &MOSI, &SCK, &CS);
	}
	i++;
	LTC1446_SetChannelAB(&LTC1446TestHandle, i, 0x1000 - i);
}
