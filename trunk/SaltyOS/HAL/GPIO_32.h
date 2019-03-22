#pragma once

#include "HAL\HCommon.h"

C_HEADER_BEGIN

struct UniGPIO_Handle;

typedef struct
{
	volatile u32* IDRAddr;
	volatile u32* ODRAddr;
	GPIO_TypeDef* Port;
	u32 Pin;
}GPIO_32_InfoArea;

STATUS GPIO_32_Init(void);

void GPIO_32_InitPin(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_Init, struct UniGPIO_Handle* Handle);

C_HEADER_END
