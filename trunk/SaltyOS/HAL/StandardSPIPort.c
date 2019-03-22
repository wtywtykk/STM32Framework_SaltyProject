#include "HAL\HCommon.h"
#include "HAL\UniGPIO.h"

#define PinNum_SIG0 0
#define PinNum_MOSI 1
#define PinNum_SIG1 2
#define PinNum_MISO 3
#define PinNum_SIG2 4
#define PinNum_SCK 5
#define PinNum_SIG3 6
#define PinNum_CS 7
#define PinNum_SIG4 8

void StandardSPIPort_Init(u8 PortNum, UniGPIO_Handle* MISOPin, UniGPIO_Handle* MOSIPin, UniGPIO_Handle* SCKPin, UniGPIO_Handle* CSPin, UniGPIO_Handle* SIG0, UniGPIO_Handle* SIG1, UniGPIO_Handle* SIG2, UniGPIO_Handle* SIG3, UniGPIO_Handle* SIG4)
{
	if (MISOPin)
	{
		GPIO_CPLD_InitPin(PortNum, PinNum_MISO, false, MISOPin);
	}
	if (MOSIPin)
	{
		GPIO_CPLD_InitPin(PortNum, PinNum_MOSI, true, MOSIPin);
	}
	if (SCKPin)
	{
		GPIO_CPLD_InitPin(PortNum, PinNum_SCK, true, SCKPin);
	}
	if (CSPin)
	{
		GPIO_CPLD_InitPin(PortNum, PinNum_CS, true, CSPin);
	}
	if (SIG0)
	{
		GPIO_CPLD_InitPin(PortNum, PinNum_SIG0, false, SIG0);
	}
	if (SIG1)
	{
		GPIO_CPLD_InitPin(PortNum, PinNum_SIG1, false, SIG1);
	}
	if (SIG2)
	{
		GPIO_CPLD_InitPin(PortNum, PinNum_SIG2, false, SIG2);
	}
	if (SIG3)
	{
		GPIO_CPLD_InitPin(PortNum, PinNum_SIG3, false, SIG3);
	}
	if (SIG4)
	{
		GPIO_CPLD_InitPin(PortNum, PinNum_SIG4, false, SIG4);
	}
}
