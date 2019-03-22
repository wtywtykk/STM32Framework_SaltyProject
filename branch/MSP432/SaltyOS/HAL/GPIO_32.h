#pragma once

#include "HAL\HCommon.h"

C_HEADER_BEGIN

struct UniGPIO_Handle;

typedef struct
{
	volatile u8* IDRAddr;
	volatile u8* ODRAddr;
	u8 Port;
	u32 Pin;
}GPIO_32_InfoArea;

typedef struct
{
	u32 Pin;
	bool Output;
	bool Pull;
	bool HighDrive;
	u8 FuncSel;
	bool InterruptLowToHigh;
	bool InterruptEnable;
}GPIO_InitTypeDef;

STATUS GPIO_32_Init(void);

void GPIO_32_InitPin(u8 GPIOx, GPIO_InitTypeDef* GPIO_Init, struct UniGPIO_Handle* Handle);
void GPIO_32_SetHigh(void* Handle);
void GPIO_32_SetLow(void* Handle);
void GPIO_32_SetVal(void* Handle, bool Val);
bool GPIO_32_Read(void* Handle);
void GPIO_32_SetInput(void* Handle);
void GPIO_32_SetOutput(void* Handle);

C_HEADER_END
