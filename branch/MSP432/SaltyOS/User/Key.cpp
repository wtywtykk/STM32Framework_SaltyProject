#include "HAL\HCommon.h"
#include "HAL/UniGPIO.h"

bool Key_Initialized = false;

#define Key0Port GPIO_PORT_P2
#define Key0Pin GPIO_PIN1

#define Key1Port GPIO_PORT_P1
#define Key1Pin GPIO_PIN4

#define Key2Port GPIO_PORT_P1
#define Key2Pin GPIO_PIN5

#define Key3Port GPIO_PORT_P1
#define Key3Pin GPIO_PIN6

#define Key4Port GPIO_PORT_P1
#define Key4Pin GPIO_PIN7

UniGPIO_Handle Key0_Handle;
UniGPIO_Handle Key1_Handle;
UniGPIO_Handle Key2_Handle;
UniGPIO_Handle Key3_Handle;
UniGPIO_Handle Key4_Handle;

bool Key0Flag = false;
bool Key1Flag = false;
bool Key2Flag = false;
bool Key3Flag = false;
bool Key4Flag = false;

void Key0_Interrupt(void);
void Key1_Interrupt(void);

STATUS Key_Init(void)
{
	GPIO_InitTypeDef GPIOInit;

	GPIOInit.FuncSel = 0;
	GPIOInit.HighDrive = false;
	GPIOInit.InterruptEnable = true;
	GPIOInit.InterruptLowToHigh = false;
	GPIOInit.Output = false;
	GPIOInit.Pin = 0xFF;
	GPIOInit.Pull = true;

	GPIOInit.Pin = Key0Pin;
	GPIO_32_InitPin(Key0Port, &GPIOInit, &Key0_Handle);
	UniGPIO_SetHigh(&Key0_Handle);

	GPIOInit.Pin = Key1Pin;
	GPIO_32_InitPin(Key1Port, &GPIOInit, &Key1_Handle);
	UniGPIO_SetHigh(&Key1_Handle);

	GPIOInit.Pin = Key2Pin;
	GPIO_32_InitPin(Key2Port, &GPIOInit, &Key2_Handle);
	UniGPIO_SetHigh(&Key2_Handle);

	GPIOInit.Pin = Key3Pin;
	GPIO_32_InitPin(Key3Port, &GPIOInit, &Key3_Handle);
	UniGPIO_SetHigh(&Key3_Handle);

	GPIOInit.Pin = Key4Pin;
	GPIO_32_InitPin(Key4Port, &GPIOInit, &Key4_Handle);
	UniGPIO_SetHigh(&Key4_Handle);

	GPIO_registerInterrupt(Key0Port, Key0_Interrupt);
	GPIO_registerInterrupt(Key1Port, Key1_Interrupt);

	return S_OK;
}

void Key0_Interrupt(void)
{
	if (GPIO_getInterruptStatus(Key0Port, Key0Pin))
	{
		Key0Flag = true;
		GPIO_clearInterruptFlag(Key0Port, Key0Pin);
	}
}

void Key1_Interrupt(void)
{
	if (GPIO_getInterruptStatus(Key1Port, Key1Pin))
	{
		Key1Flag = true;
		GPIO_clearInterruptFlag(Key1Port, Key1Pin);
	}
	if (GPIO_getInterruptStatus(Key2Port, Key2Pin))
	{
		Key2Flag = true;
		GPIO_clearInterruptFlag(Key2Port, Key2Pin);
	}
	if (GPIO_getInterruptStatus(Key3Port, Key3Pin))
	{
		Key3Flag = true;
		GPIO_clearInterruptFlag(Key3Port, Key3Pin);
	}
	if (GPIO_getInterruptStatus(Key4Port, Key4Pin))
	{
		Key4Flag = true;
		GPIO_clearInterruptFlag(Key4Port, Key4Pin);
	}
}

s32 Key_GetKey(void)
{
	if (Key0Flag)
	{
		Key0Flag = false;
		return 0;
	}

	if (Key1Flag)
	{
		Key1Flag = false;
		return 1;
	}

	if (Key2Flag)
	{
		Key2Flag = false;
		return 2;
	}

	if (Key3Flag)
	{
		Key3Flag = false;
		return 3;
	}

	if (Key4Flag)
	{
		Key4Flag = false;
		return 4;
	}

	return -1;
}
