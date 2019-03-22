#pragma once

C_HEADER_BEGIN

#include "HAL\GPIO_32.h"
#include "HAL\GPIO_CPLD.h"

typedef void(*GPIOFUNC_SetHigh)(struct UniGPIO_Handle* Handle);
typedef void(*GPIOFUNC_SetLow)(struct UniGPIO_Handle* Handle);
typedef void(*GPIOFUNC_SetVal)(struct UniGPIO_Handle* Handle, bool Val);
typedef bool(*GPIOFUNC_Read)(struct UniGPIO_Handle* Handle);
typedef void(*GPIOFUNC_SetInput)(struct UniGPIO_Handle* Handle);
typedef void(*GPIOFUNC_SetOutput)(struct UniGPIO_Handle* Handle);

typedef struct UniGPIO_Handle
{
	GPIOFUNC_SetHigh SetHigh;
	GPIOFUNC_SetLow SetLow;
	GPIOFUNC_SetVal SetVal;
	GPIOFUNC_Read Read;
	GPIOFUNC_SetInput SetInput;
	GPIOFUNC_SetOutput SetOutput;
	union GPIO_Info
	{
		GPIO_32_InfoArea GPIO_32_Info;
		GPIO_CPLD_InfoArea GPIO_CPLD_Info;
	}GPIO_Info;
}UniGPIO_Handle;

static __inline__ void UniGPIO_SetHigh(UniGPIO_Handle* Handle)
{
	if (Handle) Handle->SetHigh(Handle);
}
static __inline__ void UniGPIO_SetLow(UniGPIO_Handle* Handle)
{
	if (Handle) Handle->SetLow(Handle);
}
static __inline__ void UniGPIO_SetVal(UniGPIO_Handle* Handle, bool Val)
{
	if (Handle) Handle->SetVal(Handle, Val);
}
static __inline__ bool UniGPIO_Read(UniGPIO_Handle* Handle)
{
	return Handle ? (Handle)->Read(Handle) : 0;
}
static __inline__ void UniGPIO_SetInput(UniGPIO_Handle* Handle)
{
	if (Handle) (Handle)->SetInput(Handle);
}
static __inline__ void UniGPIO_SetOutput(UniGPIO_Handle* Handle)
{
	if (Handle) (Handle)->SetOutput(Handle);
}

C_HEADER_END
