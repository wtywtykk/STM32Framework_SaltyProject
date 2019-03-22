#pragma once

C_HEADER_BEGIN

struct UniGPIO_Handle;

typedef struct
{
	u8 Pin;
	u8 Port;
	u16 PinMask;
	u32 PortBaseAddr;
}GPIO_CPLD_InfoArea;

STATUS GPIO_CPLD_Init(void);

void GPIO_CPLD_InitPin(u8 PortNum, u8 PinNum, bool Output, struct UniGPIO_Handle* Handle);

C_HEADER_END
