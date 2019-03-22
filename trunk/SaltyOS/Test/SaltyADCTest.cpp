#include "Kernel\Common\KCommon.h"
#include "HAL\StandardSPIPort.h"
#include "MultiInstDriver\SaltyADC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "HAL\UniSPI.h"

SaltyADC_Handle SaltyADCTestHandle;

void SaltyADCTest(void)
{
	static bool Inited = false;
	if (!Inited)
	{
		UniGPIO_Handle MISOPin;
		UniGPIO_Handle MOSIPin;
		UniGPIO_Handle SCKPin;
		UniGPIO_Handle CSPin;
		UniGPIO_Handle BUSYPin;
		UniGPIO_Handle CONVPin;
		Inited = true;
		StandardSPIPort_Init(0, &MISOPin, &MOSIPin, &SCKPin, &CSPin, &BUSYPin, &CONVPin, NULL, NULL, NULL);
		SaltyADC_Init(&SaltyADCTestHandle, &MISOPin, &MOSIPin, &SCKPin, &CSPin, &BUSYPin, &CONVPin);
	}

	u8 Buf[5];

	Buf[0] = 0x81;
	Buf[1] = 0x0;
	Buf[2] = 0x0;
	Buf[3] = 0x0;
	Buf[4] = 0x2;
	UniSPI_TransmitReceive(&SaltyADCTestHandle.SPI_Handle, &SaltyADCTestHandle.CS, Buf, 5, 10);
	u32 u32Val = Buf[1] << 24 | Buf[2] << 16 | Buf[3] << 8 | Buf[4] << 0;
	FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC16"));
	char sBuf[128];
	sprintf(sBuf, "%x %lx     ", Buf[0], u32Val);
	DrawStringHorizontal(g_LCDDC, FG, sBuf, 0, 0, 0, 0, WHITE, BLACK);
	FreeAndEraseReference(FG);
}
