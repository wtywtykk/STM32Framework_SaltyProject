#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "HAL\UniGPIO.h"
#include "HAL\UniSPI.h"
#include <malloc.h>

#define FPGA_SPI_INSTANCE SPI3
#define FPGA_SPI_AF GPIO_AF6_SPI3
#define FPGA_SPI_CLOCK_SPEED 1000000//1MHz
#define FPGA_SPI_TIMEOUT 10
#define FPGA_SPI_CS_PORT GPIOA
#define FPGA_SPI_CS_PIN GPIO_PIN_15
#define FPGA_SPI_IO1_PORT GPIOG
#define FPGA_SPI_IO1_PIN GPIO_PIN_15
#define FPGA_SPI_IO2_PORT GPIOG
#define FPGA_SPI_IO2_PIN GPIO_PIN_14
#define FPGA_SPI_IO3_PORT GPIOG
#define FPGA_SPI_IO3_PIN GPIO_PIN_13
#define FPGA_SPI_SCK_PORT GPIOB
#define FPGA_SPI_SCK_PIN GPIO_PIN_3
#define FPGA_SPI_MISO_PORT GPIOB
#define FPGA_SPI_MISO_PIN GPIO_PIN_4
#define FPGA_SPI_MOSI_PORT GPIOB
#define FPGA_SPI_MOSI_PIN GPIO_PIN_5

UniSPI_Handle FPGASPI_Handle;
UniGPIO_Handle FPGA_SPI_CS;
UniGPIO_Handle FPGA_SPI_RESET;
UniGPIO_Handle FPGA_SPI_IO2;
UniGPIO_Handle FPGA_SPI_LATCH;

bool FPGASPIPort_Initialized = false;

STATUS FPGASPIPort_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef SPI_InitStruct;

	if (FPGASPIPort_Initialized)
	{
		return S_OK;
	}

	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pin = FPGA_SPI_IO1_PIN;
	GPIO_32_InitPin(FPGA_SPI_IO1_PORT, &GPIO_InitStruct, &FPGA_SPI_RESET);

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pin = FPGA_SPI_IO2_PIN;
	GPIO_32_InitPin(FPGA_SPI_IO2_PORT, &GPIO_InitStruct, &FPGA_SPI_IO2);

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pin = FPGA_SPI_IO3_PIN;
	GPIO_32_InitPin(FPGA_SPI_IO3_PORT, &GPIO_InitStruct, &FPGA_SPI_LATCH);

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pin = FPGA_SPI_CS_PIN;
	GPIO_32_InitPin(FPGA_SPI_CS_PORT, &GPIO_InitStruct, &FPGA_SPI_CS);

	UniGPIO_SetHigh(&FPGA_SPI_CS);

	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Alternate = FPGA_SPI_AF;

	GPIO_InitStruct.Pin = FPGA_SPI_SCK_PIN;
	GPIO_32_InitPin(FPGA_SPI_SCK_PORT, &GPIO_InitStruct, NULL);
	GPIO_InitStruct.Pin = FPGA_SPI_MISO_PIN;
	GPIO_32_InitPin(FPGA_SPI_MISO_PORT, &GPIO_InitStruct, NULL);
	GPIO_InitStruct.Pin = FPGA_SPI_MOSI_PIN;
	GPIO_32_InitPin(FPGA_SPI_MOSI_PORT, &GPIO_InitStruct, NULL);

	SPI_InitStruct.Mode = SPI_MODE_MASTER;
	SPI_InitStruct.Direction = SPI_DIRECTION_2LINES;
	SPI_InitStruct.DataSize = SPI_DATASIZE_8BIT;
	SPI_InitStruct.CLKPolarity = SPI_POLARITY_LOW;
	SPI_InitStruct.CLKPhase = SPI_PHASE_2EDGE;
	SPI_InitStruct.NSS = SPI_NSS_SOFT;
	SPI_InitStruct.BaudRatePrescaler = HardSPI_GetPreScaler(HardSPI_GetSPIIndex(FPGA_SPI_INSTANCE), FPGA_SPI_CLOCK_SPEED);
	SPI_InitStruct.FirstBit = SPI_FIRSTBIT_MSB;
	SPI_InitStruct.TIMode = SPI_TIMODE_DISABLE;
	SPI_InitStruct.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	SPI_InitStruct.CRCPolynomial = 10;

	if (HardSPI_Init(&FPGASPI_Handle, FPGA_SPI_INSTANCE, &SPI_InitStruct) != S_OK)
	{
		return S_FAIL;
	}

	FPGASPIPort_Initialized = true;

	return S_OK;
}

STATUS FPGASPIPort_Transmit(void* Buffer, u16 Size)
{
	u8* u8Buf = (u8*)Buffer;
	u8* ReversedBuf = (u8*)malloc(Size);
	u16 i;
	if (ReversedBuf)
	{
		STATUS Ret;
		for (i = 0; i < Size; i++)
		{
			ReversedBuf[Size - i - 1] = u8Buf[i];
		}
		UniGPIO_SetLow(&FPGA_SPI_LATCH);
		Ret = UniSPI_TransmitBytes(&FPGASPI_Handle, &FPGA_SPI_CS, ReversedBuf, Size, FPGA_SPI_TIMEOUT);
		free(ReversedBuf);
		if (Ret == S_OK)
		{
			UniGPIO_SetHigh(&FPGA_SPI_LATCH);
			UniGPIO_SetLow(&FPGA_SPI_LATCH);
			return S_OK;
		}
	}
	return S_FAIL;
}

STATUS FPGASPIPort_Receive(void* Buffer, u16 Size)
{
	u8* u8Buf = (u8*)Buffer;
	u8* ReversedBuf = (u8*)malloc(Size);
	u16 i;
	if (ReversedBuf)
	{
		STATUS Ret = S_FAIL;
		Ret = UniSPI_TransmitReceive(&FPGASPI_Handle, &FPGA_SPI_CS, ReversedBuf, Size, FPGA_SPI_TIMEOUT);
		for (i = 0; i < Size; i++)
		{
			u8Buf[i] = ReversedBuf[Size - i - 1];
		}
		free(ReversedBuf);
		return Ret;

	}
	return S_FAIL;
}

void FPGASPIPort_Reset(void)
{
	UniGPIO_SetHigh(&FPGA_SPI_RESET);
	HAL_Delay(1);
	UniGPIO_SetLow(&FPGA_SPI_RESET);
}

bool FPGASPIPort_ReadIO2(void)
{
	return UniGPIO_Read(&FPGA_SPI_IO2);
}
