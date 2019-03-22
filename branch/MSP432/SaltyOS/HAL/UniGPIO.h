#pragma once

C_HEADER_BEGIN

#include "HAL\GPIO_32.h"

typedef void(*GPIOFUNC_SetHigh)(void* Handle);
typedef void(*GPIOFUNC_SetLow)(void* Handle);
typedef void(*GPIOFUNC_SetVal)(void* Handle, bool Val);
typedef bool(*GPIOFUNC_Read)(void* Handle);
typedef void(*GPIOFUNC_SetInput)(void* Handle);
typedef void(*GPIOFUNC_SetOutput)(void* Handle);

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
	}GPIO_Info;
}UniGPIO_Handle;

//static __inline__ void UniGPIO_SetHigh(UniGPIO_Handle* Handle)
//{
//	if (Handle) Handle->SetHigh(Handle);
//}
//static __inline__ void UniGPIO_SetLow(UniGPIO_Handle* Handle)
//{
//	if (Handle) Handle->SetLow(Handle);
//}
//static __inline__ void UniGPIO_SetVal(UniGPIO_Handle* Handle, bool Val)
//{
//	if (Handle) Handle->SetVal(Handle, Val);
//}
//static __inline__ bool UniGPIO_Read(UniGPIO_Handle* Handle)
//{
//	return Handle ? (Handle)->Read(Handle) : 0;
//}
//static __inline__ void UniGPIO_SetInput(UniGPIO_Handle* Handle)
//{
//	if (Handle) (Handle)->SetInput(Handle);
//}
//static __inline__ void UniGPIO_SetOutput(UniGPIO_Handle* Handle)
//{
//	if (Handle) (Handle)->SetOutput(Handle);
//}
#define UniGPIO_SetHigh GPIO_32_SetHigh
#define UniGPIO_SetLow GPIO_32_SetLow
#define UniGPIO_SetVal GPIO_32_SetVal
#define UniGPIO_Read GPIO_32_Read
#define UniGPIO_SetInput GPIO_32_SetInput
#define UniGPIO_SetOutput GPIO_32_SetOutput

C_HEADER_END
