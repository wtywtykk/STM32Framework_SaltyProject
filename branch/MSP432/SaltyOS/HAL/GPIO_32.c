#include "HCommon.h"
#include "HAL\UniGPIO.h"
#include "HAL\GPIO_32.h"

#define GPIO_32_MODE_INPUT 0x00
#define GPIO_32_MODE_OUTPUT 0x01
#define GPIOModeMask 0x03

bool GPIO_32_Initialized = false;

static const uint32_t GPIO_PORT_TO_BASE[] =
{ 0x00,
0x40004C00,
0x40004C01,
0x40004C20,
0x40004C21,
0x40004C40,
0x40004C41,
0x40004C60,
0x40004C61,
0x40004C80,
0x40004C81,
0x40004D20
};

#define OFS_IN		(0x0000)
#define OFS_OUT		(0x0002)
#define OFS_DIR		(0x0004)
#define OFS_REN		(0x0006)
#define OFS_DS		(0x0008)
#define OFS_SEL0	(0x000a)
#define OFS_SEL1	(0x000c)

void GPIO_32_SetHigh(void* Handle);
void GPIO_32_SetLow(void* Handle);
void GPIO_32_SetVal(void* Handle, bool Val);
bool GPIO_32_Read(void* Handle);
void GPIO_32_SetInput(void* Handle);
void GPIO_32_SetOutput(void* Handle);

STATUS GPIO_32_Init(void)
{
	if (GPIO_32_Initialized)
	{
		return S_OK;
	}

	GPIO_32_Initialized = true;

	return S_OK;
}

void GPIO_32_InitPin(u8 GPIOx, GPIO_InitTypeDef* GPIO_Init, UniGPIO_Handle* Handle)
{
	uint32_t baseAddress = GPIO_PORT_TO_BASE[GPIOx];

	if (Handle)
	{
		u32 PinNum = 0;
		while ((GPIO_Init->Pin & (1 << PinNum)) == 0)
		{
			PinNum++;
		}

		assert(GPIO_Init->Pin == 1 << PinNum);//One handle can only represent one pin.

		GPIO_Init->Pin = 1 << PinNum;
		Handle->GPIO_Info.GPIO_32_Info.IDRAddr = PeripheralBitBandAddr(baseAddress + OFS_IN, PinNum);
		Handle->GPIO_Info.GPIO_32_Info.ODRAddr = PeripheralBitBandAddr(baseAddress + OFS_OUT, PinNum);
		Handle->GPIO_Info.GPIO_32_Info.Port = GPIOx;
		Handle->GPIO_Info.GPIO_32_Info.Pin = 1 << PinNum;

		Handle->SetHigh = &GPIO_32_SetHigh;
		Handle->SetLow = &GPIO_32_SetLow;
		Handle->SetVal = &GPIO_32_SetVal;
		Handle->Read = &GPIO_32_Read;
		Handle->SetInput = &GPIO_32_SetInput;
		Handle->SetOutput = &GPIO_32_SetOutput;
	}

	if (GPIO_Init->Output)
	{
		HWREG16(baseAddress + OFS_DIR) |= GPIO_Init->Pin;
	}
	else
	{
		HWREG16(baseAddress + OFS_DIR) &= ~GPIO_Init->Pin;
	}
	if (GPIO_Init->Pull)
	{
		HWREG16(baseAddress + OFS_REN) |= GPIO_Init->Pin;
	}
	else
	{
		HWREG16(baseAddress + OFS_REN) &= ~GPIO_Init->Pin;
	}
	if (GPIO_Init->HighDrive)
	{
		HWREG16(baseAddress + OFS_DS) |= GPIO_Init->Pin;
	}
	else
	{
		HWREG16(baseAddress + OFS_DS) &= ~GPIO_Init->Pin;
	}
	if (GPIO_Init->FuncSel)
	{
		HWREG16(baseAddress + OFS_DS) |= GPIO_Init->Pin;
	}
	else
	{
		HWREG16(baseAddress + OFS_DS) &= ~GPIO_Init->Pin;
	}
	GPIO_interruptEdgeSelect(GPIOx, GPIO_Init->Pin, GPIO_Init->InterruptLowToHigh ? GPIO_LOW_TO_HIGH_TRANSITION : GPIO_HIGH_TO_LOW_TRANSITION);
	if (GPIO_Init->InterruptEnable)
	{
		GPIO_enableInterrupt(GPIOx, GPIO_Init->Pin);
	}
	else
	{
		GPIO_disableInterrupt(GPIOx, GPIO_Init->Pin);
	}
	switch (GPIO_Init->FuncSel)
	{
	default:
		HWREG16(baseAddress + OFS_PASEL0) &= ~GPIO_Init->Pin;
		HWREG16(baseAddress + OFS_PASEL1) &= ~GPIO_Init->Pin;
		break;
	case GPIO_PRIMARY_MODULE_FUNCTION:
		HWREG16(baseAddress + OFS_PASEL0) |= GPIO_Init->Pin;
		HWREG16(baseAddress + OFS_PASEL1) &= ~GPIO_Init->Pin;
		break;
	case GPIO_SECONDARY_MODULE_FUNCTION:
		HWREG16(baseAddress + OFS_PASEL0) &= ~GPIO_Init->Pin;
		HWREG16(baseAddress + OFS_PASEL1) |= GPIO_Init->Pin;
		break;
	case GPIO_TERTIARY_MODULE_FUNCTION:
		HWREG16(baseAddress + OFS_PASEL0) |= GPIO_Init->Pin;
		HWREG16(baseAddress + OFS_PASEL1) |= GPIO_Init->Pin;
		break;
	}
}

void GPIO_32_SetHigh(void* Handle)
{
	if (Handle)
	{
		*((UniGPIO_Handle*)Handle)->GPIO_Info.GPIO_32_Info.ODRAddr = 1;
	}
}

void GPIO_32_SetLow(void* Handle)
{
	if (Handle)
	{
		*((UniGPIO_Handle*)Handle)->GPIO_Info.GPIO_32_Info.ODRAddr = 0;
	}
}

void GPIO_32_SetVal(void* Handle, bool Val)
{
	if (Handle)
	{
		*((UniGPIO_Handle*)Handle)->GPIO_Info.GPIO_32_Info.ODRAddr = Val ? 1 : 0;
	}
}

bool GPIO_32_Read(void* Handle)
{
	if (Handle)
	{
		return *((UniGPIO_Handle*)Handle)->GPIO_Info.GPIO_32_Info.IDRAddr;
	}
}

void GPIO_32_SetInput(void* Handle)
{
	if (Handle)
	{
		uint32_t baseAddress = GPIO_PORT_TO_BASE[((UniGPIO_Handle*)Handle)->GPIO_Info.GPIO_32_Info.Port];
		HWREG16(baseAddress + OFS_DIR) &= ~(1 << ((UniGPIO_Handle*)Handle)->GPIO_Info.GPIO_32_Info.Pin);
	}
}

void GPIO_32_SetOutput(void* Handle)
{
	if (Handle)
	{
		uint32_t baseAddress = GPIO_PORT_TO_BASE[((UniGPIO_Handle*)Handle)->GPIO_Info.GPIO_32_Info.Port];
		HWREG16(baseAddress + OFS_DIR) |= 1 << ((UniGPIO_Handle*)Handle)->GPIO_Info.GPIO_32_Info.Pin;
	}
}
