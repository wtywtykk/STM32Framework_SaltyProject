#include "HCommon.h"
#include "HAL\UniGPIO.h"
#include "HAL\GPIO_32.h"

#define GPIO_32_MODE_INPUT 0x00
#define GPIO_32_MODE_OUTPUT 0x01
#define GPIOModeMask 0x03

bool GPIO_32_Initialized = false;

void GPIO_32_SetHigh(UniGPIO_Handle* Handle);
void GPIO_32_SetLow(UniGPIO_Handle* Handle);
void GPIO_32_SetVal(UniGPIO_Handle* Handle, bool Val);
bool GPIO_32_Read(UniGPIO_Handle* Handle);
void GPIO_32_SetInput(UniGPIO_Handle* Handle);
void GPIO_32_SetOutput(UniGPIO_Handle* Handle);

STATUS GPIO_32_Init(void)
{
	if (GPIO_32_Initialized)
	{
		return S_OK;
	}

	//Enable all gpio clocks
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();

	GPIO_32_Initialized = true;

	return S_OK;
}

void GPIO_32_InitPin(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_Init, UniGPIO_Handle* Handle)
{
	if (Handle)
	{
		u32 PinNum = 0;
		while ((GPIO_Init->Pin & (1 << PinNum)) == 0)
		{
			PinNum++;
		}

		assert(GPIO_Init->Pin == 1 << PinNum);//One handle can only represent one pin.

		GPIO_Init->Pin = 1 << PinNum;
		Handle->GPIO_Info.GPIO_32_Info.IDRAddr = PeripheralBitBandAddr(&GPIOx->IDR, PinNum);
		Handle->GPIO_Info.GPIO_32_Info.ODRAddr = PeripheralBitBandAddr(&GPIOx->ODR, PinNum);
		Handle->GPIO_Info.GPIO_32_Info.Port = GPIOx;
		Handle->GPIO_Info.GPIO_32_Info.Pin = PinNum;

		Handle->SetHigh = &GPIO_32_SetHigh;
		Handle->SetLow = &GPIO_32_SetLow;
		Handle->SetVal = &GPIO_32_SetVal;
		Handle->Read = &GPIO_32_Read;
		Handle->SetInput = &GPIO_32_SetInput;
		Handle->SetOutput = &GPIO_32_SetOutput;
	}

	HAL_GPIO_Init(GPIOx, GPIO_Init);
}

void GPIO_32_SetHigh(UniGPIO_Handle* Handle)
{
	if (Handle)
	{
		*Handle->GPIO_Info.GPIO_32_Info.ODRAddr = 1;
	}
}

void GPIO_32_SetLow(UniGPIO_Handle* Handle)
{
	if (Handle)
	{
		*Handle->GPIO_Info.GPIO_32_Info.ODRAddr = 0;
	}
}

void GPIO_32_SetVal(UniGPIO_Handle* Handle, bool Val)
{
	if (Handle)
	{
		*Handle->GPIO_Info.GPIO_32_Info.ODRAddr = Val ? 1 : 0;
	}
}

bool GPIO_32_Read(UniGPIO_Handle* Handle)
{
	if (Handle)
	{
		return *Handle->GPIO_Info.GPIO_32_Info.IDRAddr;
	}
	return false;
}

void GPIO_32_SetInput(UniGPIO_Handle* Handle)
{
	if (Handle)
	{
		Handle->GPIO_Info.GPIO_32_Info.Port->MODER = (Handle->GPIO_Info.GPIO_32_Info.Port->MODER & ~(GPIOModeMask << Handle->GPIO_Info.GPIO_32_Info.Pin * 2)) | GPIO_32_MODE_INPUT;
	}
}

void GPIO_32_SetOutput(UniGPIO_Handle* Handle)
{
	if (Handle)
	{
		Handle->GPIO_Info.GPIO_32_Info.Port->MODER = (Handle->GPIO_Info.GPIO_32_Info.Port->MODER & ~(GPIOModeMask << Handle->GPIO_Info.GPIO_32_Info.Pin * 2)) | GPIO_32_MODE_OUTPUT;
	}
}
