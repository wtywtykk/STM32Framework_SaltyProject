#include "HCommon.h"
#include "HAL\UniGPIO.h"
#include "HAL\GPIO_CPLD.h"
#include "HAL\PeripheralBus.h"

#define GPIO_CPLD_MODE_INPUT 0x00
#define GPIO_CPLD_MODE_OUTPUT 0x01
#define GPIOModeMask 0x03

bool GPIO_CPLD_Initialized = false;

void GPIO_CPLD_SetHigh(UniGPIO_Handle* Handle);
void GPIO_CPLD_SetLow(UniGPIO_Handle* Handle);
void GPIO_CPLD_SetVal(UniGPIO_Handle* Handle, bool Val);
bool GPIO_CPLD_Read(UniGPIO_Handle* Handle);
void GPIO_CPLD_SetInput(UniGPIO_Handle* Handle);
void GPIO_CPLD_SetOutput(UniGPIO_Handle* Handle);

#define PortCount 8
#define PinPerPort 9

STATUS GPIO_CPLD_Init(void)
{
	u8 i;

	if (GPIO_CPLD_Initialized)
	{
		return S_OK;
	}

	for (i = 0; i < 8; i++)
	{
		u32 ConfigAddr;
		ConfigAddr = PeripheralBus_GPIOxBase(i) + PeripheralBus_GPIOOffset_Config;
		PeripheralBus_Write(ConfigAddr, PeripheralBus_GPIO_ConfigBit_Reset);
	}

	for (i = 0; i < 8; i++)
	{
		u32 ConfigAddr;
		ConfigAddr = PeripheralBus_GPIOxBase(i) + PeripheralBus_GPIOOffset_Config;
		PeripheralBus_Write(ConfigAddr, 0);
	}

	GPIO_CPLD_Initialized = true;

	return S_OK;
}

void GPIO_CPLD_InitPin(u8 PortNum, u8 PinNum, bool Output, UniGPIO_Handle* Handle)
{
	u32 DirAddr;
	if (Handle)
	{
		assert(PortNum < PortCount);
		assert(PinNum < PinPerPort);

		Handle->GPIO_Info.GPIO_CPLD_Info.Pin = PinNum;
		Handle->GPIO_Info.GPIO_CPLD_Info.PinMask = 1 << PinNum;
		Handle->GPIO_Info.GPIO_CPLD_Info.Port = PortNum;
		Handle->GPIO_Info.GPIO_CPLD_Info.PortBaseAddr = PeripheralBus_GPIOxBase(PortNum);

		Handle->SetHigh = &GPIO_CPLD_SetHigh;
		Handle->SetLow = &GPIO_CPLD_SetLow;
		Handle->SetVal = &GPIO_CPLD_SetVal;
		Handle->Read = &GPIO_CPLD_Read;
		Handle->SetInput = &GPIO_CPLD_SetInput;
		Handle->SetOutput = &GPIO_CPLD_SetOutput;
	}

	DirAddr = Handle->GPIO_Info.GPIO_CPLD_Info.PortBaseAddr + PeripheralBus_GPIOOffset_Direction;
	if (Output)
	{
		PeripheralBus_Write(DirAddr, PeripheralBus_Read(DirAddr) | Handle->GPIO_Info.GPIO_CPLD_Info.PinMask);
	}
	else
	{
		PeripheralBus_Write(DirAddr, PeripheralBus_Read(DirAddr) & ~Handle->GPIO_Info.GPIO_CPLD_Info.PinMask);
	}
}

void GPIO_CPLD_SetHigh(UniGPIO_Handle* Handle)
{
	if (Handle)
	{
		u32 SetAddr;
		SetAddr = Handle->GPIO_Info.GPIO_CPLD_Info.PortBaseAddr + PeripheralBus_GPIOOffset_Set;
		PeripheralBus_Write(SetAddr, Handle->GPIO_Info.GPIO_CPLD_Info.PinMask);
	}
}

void GPIO_CPLD_SetLow(UniGPIO_Handle* Handle)
{
	if (Handle)
	{
		u32 ClearAddr;
		ClearAddr = Handle->GPIO_Info.GPIO_CPLD_Info.PortBaseAddr + PeripheralBus_GPIOOffset_Clear;
		PeripheralBus_Write(ClearAddr, Handle->GPIO_Info.GPIO_CPLD_Info.PinMask);
	}
}

void GPIO_CPLD_SetVal(UniGPIO_Handle* Handle, bool Val)
{
	if (Val)
	{
		GPIO_CPLD_SetHigh(Handle);
	}
	else
	{
		GPIO_CPLD_SetLow(Handle);
	}
}

bool GPIO_CPLD_Read(UniGPIO_Handle* Handle)
{
	if (Handle)
	{
		u32 IODataAddr;
		IODataAddr = Handle->GPIO_Info.GPIO_CPLD_Info.PortBaseAddr + PeripheralBus_GPIOOffset_IOData;
		return (PeripheralBus_Read(IODataAddr) & Handle->GPIO_Info.GPIO_CPLD_Info.PinMask) ? true : false;
	}
	return false;
}

void GPIO_CPLD_SetInput(UniGPIO_Handle* Handle)
{
	if (Handle)
	{
		u32 DirAddr;
		DirAddr = Handle->GPIO_Info.GPIO_CPLD_Info.PortBaseAddr + PeripheralBus_GPIOOffset_Direction;
		PeripheralBus_Write(DirAddr, PeripheralBus_Read(DirAddr) & ~Handle->GPIO_Info.GPIO_CPLD_Info.PinMask);
	}
}

void GPIO_CPLD_SetOutput(UniGPIO_Handle* Handle)
{
	if (Handle)
	{
		u32 DirAddr;
		DirAddr = Handle->GPIO_Info.GPIO_CPLD_Info.PortBaseAddr + PeripheralBus_GPIOOffset_Direction;
		PeripheralBus_Write(DirAddr, PeripheralBus_Read(DirAddr) | Handle->GPIO_Info.GPIO_CPLD_Info.PinMask);
	}
}
