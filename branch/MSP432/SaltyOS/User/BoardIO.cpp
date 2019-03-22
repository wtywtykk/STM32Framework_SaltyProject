#include "Kernel\Common\KCommon.h"
#include "HAL\UniGPIO.h"
#include "MultiInstDriver/PGA11x.h"
#include "MultiInstDriver/DAC8311.h"

UniGPIO_Handle TRIG_AC1;
UniGPIO_Handle TRIG_SEL;
UniGPIO_Handle TG_DIN;
UniGPIO_Handle AC2;
UniGPIO_Handle SCLK2;
UniGPIO_Handle SDIO2;
UniGPIO_Handle CS2;
UniGPIO_Handle TRIG_AC2;
UniGPIO_Handle DAC_DIN1;
UniGPIO_Handle DAC_SCLK;
UniGPIO_Handle DAC_SYNC;
UniGPIO_Handle DAC_DIN2;
UniGPIO_Handle AC1;
UniGPIO_Handle SCLK1;
UniGPIO_Handle SDIO1;
UniGPIO_Handle CS1;

PGA11x_Handle PGA1;
PGA11x_Handle PGA2;

DAC8311_Handle DAC1;
DAC8311_Handle DAC2;

u16 DACs[3];
void BoardIO_UpdateDAC(void);

void BoardIO_InitPins(void)
{
	GPIO_InitTypeDef GPIOInit;

	GPIOInit.FuncSel = 0;
	GPIOInit.HighDrive = false;
	GPIOInit.InterruptEnable = false;
	GPIOInit.InterruptLowToHigh = false;
	GPIOInit.Output = true;
	GPIOInit.Pull = false;

	GPIOInit.Pin = GPIO_PIN0;
	GPIO_32_InitPin(1, &GPIOInit, &TRIG_AC1);
	UniGPIO_SetHigh(&TRIG_AC1);

	GPIOInit.Pin = GPIO_PIN1;
	GPIO_32_InitPin(1, &GPIOInit, &TRIG_SEL);
	UniGPIO_SetHigh(&TRIG_SEL);

	GPIOInit.Pin = GPIO_PIN2;
	GPIO_32_InitPin(1, &GPIOInit, &TG_DIN);
	UniGPIO_SetHigh(&TG_DIN);

	GPIOInit.Pin = GPIO_PIN2;
	GPIO_32_InitPin(4, &GPIOInit, &AC2);
	UniGPIO_SetHigh(&AC2);

	GPIOInit.Pin = GPIO_PIN3;
	GPIO_32_InitPin(4, &GPIOInit, &SCLK2);
	UniGPIO_SetHigh(&SCLK2);

	GPIOInit.Pin = GPIO_PIN4;
	GPIO_32_InitPin(4, &GPIOInit, &SDIO2);
	UniGPIO_SetHigh(&SDIO2);

	GPIOInit.Pin = GPIO_PIN5;
	GPIO_32_InitPin(4, &GPIOInit, &CS2);
	UniGPIO_SetHigh(&CS2);

	GPIOInit.Pin = GPIO_PIN6;
	GPIO_32_InitPin(4, &GPIOInit, &TRIG_AC2);
	UniGPIO_SetHigh(&TRIG_AC2);

	GPIOInit.Pin = GPIO_PIN0;
	GPIO_32_InitPin(5, &GPIOInit, &DAC_DIN1);
	UniGPIO_SetHigh(&DAC_DIN1);

	GPIOInit.Pin = GPIO_PIN1;
	GPIO_32_InitPin(5, &GPIOInit, &DAC_SCLK);
	UniGPIO_SetHigh(&DAC_SCLK);

	GPIOInit.Pin = GPIO_PIN2;
	GPIO_32_InitPin(5, &GPIOInit, &DAC_SYNC);
	UniGPIO_SetHigh(&DAC_SYNC);

	GPIOInit.Pin = GPIO_PIN3;
	GPIO_32_InitPin(5, &GPIOInit, &DAC_DIN2);
	UniGPIO_SetHigh(&DAC_DIN2);

	GPIOInit.Pin = GPIO_PIN0;
	GPIO_32_InitPin(7, &GPIOInit, &AC1);
	UniGPIO_SetHigh(&AC1);

	GPIOInit.Pin = GPIO_PIN1;
	GPIO_32_InitPin(7, &GPIOInit, &SCLK1);
	UniGPIO_SetHigh(&SCLK1);

	GPIOInit.Pin = GPIO_PIN2;
	GPIO_32_InitPin(7, &GPIOInit, &SDIO1);
	UniGPIO_SetHigh(&SDIO1);

	GPIOInit.Pin = GPIO_PIN3;
	GPIO_32_InitPin(7, &GPIOInit, &CS1);
	UniGPIO_SetHigh(&CS1);
}

void BoardIO_InitDrivers(void)
{
	PGA11x_Init(&PGA1, &SDIO1, &SCLK1, &CS1);
	PGA11x_Init(&PGA2, &SDIO2, &SCLK2, &CS2);

	PGA11x_SetChannel(&PGA1, CH1);
	PGA11x_SetChannel(&PGA2, CH1);

	PGA11x_SetGain(&PGA1, 1);
	PGA11x_SetGain(&PGA2, 1);

	DACs[0] = 0x3FFF;
	DACs[1] = 0x3FFF;
	DACs[2] = 0x3FFF;
	BoardIO_UpdateDAC();
}

void BoardIO_Init(void)
{
	BoardIO_InitPins();
	BoardIO_InitDrivers();
}

void BoardIO_SetChannelAC(u8 Ch, bool AC)
{
	if (Ch == 0)
	{
		if (AC)
		{
			UniGPIO_SetLow(&AC1);
		}
		else
		{
			UniGPIO_SetHigh(&AC1);
		}
	}
	else
	{
		if (AC)
		{
			UniGPIO_SetLow(&AC2);
		}
		else
		{
			UniGPIO_SetHigh(&AC2);
		}
	}
}

void BoardIO_SetChannelTrigAC(u8 Ch, bool AC)
{
	if (Ch == 0)
	{
		if (AC)
		{
			UniGPIO_SetHigh(&TRIG_AC1);
		}
		else
		{
			UniGPIO_SetLow(&TRIG_AC1);
		}
	}
	else
	{
		if (AC)
		{
			UniGPIO_SetHigh(&TRIG_AC2);
		}
		else
		{
			UniGPIO_SetLow(&TRIG_AC2);
		}
	}
}

void BoardIO_SetDAC(u8 Ch, u16 Val)
{
	DACs[Ch] = Val;
	BoardIO_UpdateDAC();
}

void BoardIO_UpdateDAC(void)
{
	u8 i;
	u16 SBuf[3];
	for (i = 0; i < 3; i++)
	{
		SBuf[i] = DACs[i];
	}
	UniGPIO_SetHigh(&DAC_SCLK);
	UniGPIO_SetLow(&DAC_SYNC);
	for (i = 0; i < 16; i++)
	{
		UniGPIO_SetVal(&DAC_DIN1, (SBuf[0] & 0x8000) ? 1 : 0);
		SBuf[0] <<= 1;
		UniGPIO_SetVal(&DAC_DIN2, (SBuf[1] & 0x8000) ? 1 : 0);
		SBuf[1] <<= 1;
		UniGPIO_SetVal(&TG_DIN, (SBuf[2] & 0x8000) ? 1 : 0);
		SBuf[2] <<= 1;
		UniGPIO_SetLow(&DAC_SCLK);
		UniGPIO_SetHigh(&DAC_SCLK);
	}
	UniGPIO_SetHigh(&DAC_SYNC);
}

void BoardIO_SetPGA(u8 Ch, u8 Gain)
{
	u8 Reg = 0;
	u8 RegGain = 1;
	while (RegGain != Gain)
	{
		if (RegGain == 0)
		{
			return;
		}
		RegGain <<= 1;
		Reg++;
	}
	if (Ch == 0)
	{
		PGA11x_SetGain(&PGA1, Reg);
	}
	else
	{
		PGA11x_SetGain(&PGA2, Reg);
	}
}

void BoardIO_SetFilter(bool HighBW)
{
	UniGPIO_SetVal(&TRIG_AC1, HighBW);
}
