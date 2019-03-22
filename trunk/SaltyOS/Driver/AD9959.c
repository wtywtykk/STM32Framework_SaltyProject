#include "HAL\HCommon.h"
#include "HAL\UniGPIO.h"
#include "HAL\UniSPI.h"
#include "HAL\HardSPI.h"
#include "Driver\AD9959_Reg.h"

bool AD9959_Initialized = false;

UniSPI_Handle AD9959_SPI_Handle;

/*Modify those if you want to use other SPI ports*/
/************************************************************************************/
#define AD9959_SPI_INSTANCE SPI2
#define AD9959_SPI_AF GPIO_AF5_SPI2
#define AD9959_SPI_CLOCK_SPEED 10500000//10.5MHz
#define AD9959_SPI_TIMEOUT 10
#define AD9959_SPI_CS_PORT GPIOB
#define AD9959_SPI_CS_PIN GPIO_PIN_12
#define AD9959_SPI_SCK_PORT GPIOB
#define AD9959_SPI_SCK_PIN	GPIO_PIN_13
#define AD9959_SPI_MISO_PORT GPIOB
#define AD9959_SPI_MISO_PIN GPIO_PIN_14
#define AD9959_SPI_MOSI_PORT GPIOB
#define AD9959_SPI_MOSI_PIN GPIO_PIN_15

#define AD9959_RESET_PORT GPIOF
#define AD9959_RESET_PIN GPIO_PIN_6
#define AD9959_UPDATE_PORT GPIOF
#define AD9959_UPDATE_PIN GPIO_PIN_7
#define AD9959_IO1_PORT GPIOF
#define AD9959_IO1_PIN GPIO_PIN_8
#define AD9959_IO2_PORT GPIOF
#define AD9959_IO2_PIN GPIO_PIN_9
#define AD9959_IO3_PORT GPIOF
#define AD9959_IO3_PIN GPIO_PIN_10
#define AD9959_P0_PORT GPIOI
#define AD9959_P0_PIN GPIO_PIN_8
#define AD9959_P1_PORT GPIOI
#define AD9959_P1_PIN GPIO_PIN_9
#define AD9959_P2_PORT GPIOI
#define AD9959_P2_PIN GPIO_PIN_10
#define AD9959_P3_PORT GPIOI
#define AD9959_P3_PIN GPIO_PIN_11
/************************************************************************************/

UniGPIO_Handle AD9959_P0;
UniGPIO_Handle AD9959_P1;
UniGPIO_Handle AD9959_P2;
UniGPIO_Handle AD9959_P3;
UniGPIO_Handle AD9959_UPDATE;
UniGPIO_Handle AD9959_CS;
UniGPIO_Handle AD9959_RESET;
UniGPIO_Handle AD9959_IO1;
UniGPIO_Handle AD9959_IO2;
UniGPIO_Handle AD9959_IO3;

STATUS AD9959_RegInit(void);

#define AD9959_SetRegBits(x,Val,Shift,Mask) (((x) & ~Mask) | (((u32)(Val) << Shift) & Mask))
#define AD9959_GetRegBits(x,Shift,Mask) (((x) & Mask) >> Shift)

typedef struct
{
	u32 CFR;
	u32 CFTW;
	u16 CPOW;
	u32 ACR;
	u32 LSRR;
	u32 RDW;
	u32 FDW;
}AD9959ChannelRegStru;

typedef struct
{
	u8 CSR;
	u32 FR1;
	u16 FR2;
	AD9959ChannelRegStru Channel[4];
}AD9959RegStru;

AD9959RegStru AD9959Reg;

#define AD9959_RefFrequency 25e6
#define AD9959_SampleFrequency 500e6

STATUS AD9959_InitPort(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef SPI_InitStruct;

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	GPIO_InitStruct.Pin = AD9959_SPI_CS_PIN;
	GPIO_32_InitPin(AD9959_SPI_CS_PORT, &GPIO_InitStruct, &AD9959_CS);

	UniGPIO_SetHigh(&AD9959_CS);

	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Alternate = AD9959_SPI_AF;

	GPIO_InitStruct.Pin = AD9959_SPI_SCK_PIN;
	GPIO_32_InitPin(AD9959_SPI_SCK_PORT, &GPIO_InitStruct, NULL);
	GPIO_InitStruct.Pin = AD9959_SPI_MISO_PIN;
	GPIO_32_InitPin(AD9959_SPI_MISO_PORT, &GPIO_InitStruct, NULL);
	GPIO_InitStruct.Pin = AD9959_SPI_MOSI_PIN;
	GPIO_32_InitPin(AD9959_SPI_MOSI_PORT, &GPIO_InitStruct, NULL);

	SPI_InitStruct.Mode = SPI_MODE_MASTER;
	SPI_InitStruct.Direction = SPI_DIRECTION_2LINES;
	SPI_InitStruct.DataSize = SPI_DATASIZE_8BIT;
	SPI_InitStruct.CLKPolarity = SPI_POLARITY_HIGH;
	SPI_InitStruct.CLKPhase = SPI_PHASE_2EDGE;
	SPI_InitStruct.NSS = SPI_NSS_SOFT;
	SPI_InitStruct.BaudRatePrescaler = HardSPI_GetPreScaler(HardSPI_GetSPIIndex(AD9959_SPI_INSTANCE), AD9959_SPI_CLOCK_SPEED);
	SPI_InitStruct.FirstBit = SPI_FIRSTBIT_MSB;
	SPI_InitStruct.TIMode = SPI_TIMODE_DISABLE;
	SPI_InitStruct.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	SPI_InitStruct.CRCPolynomial = 10;

	if (HardSPI_Init(&AD9959_SPI_Handle, AD9959_SPI_INSTANCE, &SPI_InitStruct) != S_OK)
	{
		return S_FAIL;
	}

	return S_OK;
}

STATUS AD9959_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	if (AD9959_Initialized)
	{
		return S_OK;
	}

	if (AD9959_InitPort() != S_OK)
	{
		return S_FAIL;
	}

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = 0;

	GPIO_InitStruct.Pin = AD9959_P0_PIN;
	GPIO_32_InitPin(AD9959_P0_PORT, &GPIO_InitStruct, &AD9959_P0);
	GPIO_InitStruct.Pin = AD9959_P1_PIN;
	GPIO_32_InitPin(AD9959_P1_PORT, &GPIO_InitStruct, &AD9959_P1);
	GPIO_InitStruct.Pin = AD9959_P2_PIN;
	GPIO_32_InitPin(AD9959_P2_PORT, &GPIO_InitStruct, &AD9959_P2);
	GPIO_InitStruct.Pin = AD9959_P3_PIN;
	GPIO_32_InitPin(AD9959_P3_PORT, &GPIO_InitStruct, &AD9959_P3);
	GPIO_InitStruct.Pin = AD9959_UPDATE_PIN;
	GPIO_32_InitPin(AD9959_UPDATE_PORT, &GPIO_InitStruct, &AD9959_UPDATE);
	GPIO_InitStruct.Pin = AD9959_RESET_PIN;
	GPIO_32_InitPin(AD9959_RESET_PORT, &GPIO_InitStruct, &AD9959_RESET);
	GPIO_InitStruct.Pin = AD9959_IO1_PIN;
	GPIO_32_InitPin(AD9959_IO1_PORT, &GPIO_InitStruct, &AD9959_IO1);
	GPIO_InitStruct.Pin = AD9959_IO2_PIN;
	GPIO_32_InitPin(AD9959_IO2_PORT, &GPIO_InitStruct, &AD9959_IO2);
	GPIO_InitStruct.Pin = AD9959_IO3_PIN;
	GPIO_32_InitPin(AD9959_IO3_PORT, &GPIO_InitStruct, &AD9959_IO3);

	UniGPIO_SetLow(&AD9959_P0);
	UniGPIO_SetLow(&AD9959_P1);
	UniGPIO_SetLow(&AD9959_P2);
	UniGPIO_SetLow(&AD9959_P3);
	UniGPIO_SetLow(&AD9959_UPDATE);
	UniGPIO_SetLow(&AD9959_RESET);
	UniGPIO_SetLow(&AD9959_IO1);
	UniGPIO_SetLow(&AD9959_IO2);
	UniGPIO_SetLow(&AD9959_IO3);

	UniGPIO_SetHigh(&AD9959_RESET);
	HAL_Delay(1);
	UniGPIO_SetLow(&AD9959_RESET);
	HAL_Delay(1);
	UniGPIO_SetHigh(&AD9959_RESET);
	HAL_Delay(1);
	UniGPIO_SetLow(&AD9959_RESET);
	HAL_Delay(1);

	if (AD9959_RegInit() != S_OK)
	{
		return S_FAIL;
	}

	AD9959_Initialized = true;

	return S_OK;
}

void AD9959Write(u8 RegisterAddress, u8 RegLen, u32 RegisterData)
{
	u8 Buf[4];
	u32 RevVal;

	assert(RegLen >= 1 && RegLen <= 4);

	RevVal = __REV(RegisterData << (4 - RegLen) * 8);
	*(u32*)Buf = RevVal;
	UniSPI_MemWrite(&AD9959_SPI_Handle, &AD9959_CS, RegisterAddress, sizeof(u8), Buf, RegLen, AD9959_SPI_TIMEOUT);
}

u32 AD9959Read(u8 RegisterAddress, u8 RegLen)
{
	u8 Buf[4];

	assert(RegLen >= 1 && RegLen <= 4);

	UniSPI_MemRead(&AD9959_SPI_Handle, &AD9959_CS, 0x80 | RegisterAddress, sizeof(u8), Buf, RegLen, AD9959_SPI_TIMEOUT);

	return __REV(*(u32*)Buf) >> (4 - RegLen) * 8;
}

void AD9959_WriteChannel(u8 Index)
{
	u8 ChannelMask = 0;
	assert(Index < 4);
	switch (Index)
	{
	case 0:
		ChannelMask = AD9959_ChannelEnable_Ch0;
		break;
	case 1:
		ChannelMask = AD9959_ChannelEnable_Ch1;
		break;
	case 2:
		ChannelMask = AD9959_ChannelEnable_Ch2;
		break;
	case 3:
		ChannelMask = AD9959_ChannelEnable_Ch3;
		break;
	default:
		break;
	}
	AD9959Reg.CSR = AD9959_SetRegBits(AD9959Reg.CSR, ChannelMask, AD9959_ChannelEnable_Shift, AD9959_ChannelEnable_Mask);
	AD9959Write(AD9959_CSR_Addr, AD9959_CSR_Len, AD9959Reg.CSR);

	AD9959Write(AD9959_CFR_Addr, AD9959_CFR_Len, AD9959Reg.Channel[Index].CFR);
	AD9959Write(AD9959_CFTW_Addr, AD9959_CFTW_Len, AD9959Reg.Channel[Index].CFTW);
	AD9959Write(AD9959_CPOW_Addr, AD9959_CPOW_Len, AD9959Reg.Channel[Index].CPOW);
	AD9959Write(AD9959_ACR_Addr, AD9959_ACR_Len, AD9959Reg.Channel[Index].ACR);
	AD9959Write(AD9959_LSRR_Addr, AD9959_LSRR_Len, AD9959Reg.Channel[Index].LSRR);
	AD9959Write(AD9959_RDW_Addr, AD9959_RDW_Len, AD9959Reg.Channel[Index].RDW);
	AD9959Write(AD9959_FDW_Addr, AD9959_FDW_Len, AD9959Reg.Channel[Index].FDW);
}

void AD9959_Update(void)
{
	UniGPIO_SetHigh(&AD9959_UPDATE);
	UniGPIO_SetLow(&AD9959_UPDATE);
}

STATUS AD9959_RegInit(void)
{
	AD9959Reg.CSR = 0;
	AD9959Reg.CSR = AD9959_SetRegBits(AD9959Reg.CSR, AD9959_IOMode_2Wire1Bit, AD9959_IOMode_Shift, AD9959_IOMode_Mask);
	AD9959Reg.CSR = AD9959_SetRegBits(AD9959Reg.CSR, 0, AD9959_LSBFirst_Shift, AD9959_LSBFirst_Mask);

	AD9959Reg.FR1 = 0;
	AD9959Reg.FR1 = AD9959_SetRegBits(AD9959Reg.FR1, 1, AD9959_VCOGainControl_Shift, AD9959_VCOGainControl_Mask);
	AD9959Reg.FR1 = AD9959_SetRegBits(AD9959Reg.FR1, AD9959_SampleFrequency / AD9959_RefFrequency, AD9959_PLLDivider_Shift, AD9959_PLLDivider_Mask);
	AD9959Reg.FR1 = AD9959_SetRegBits(AD9959Reg.FR1, AD9959_ChargePumpCurrent75uA, AD9959_ChargePumpControl_Shift, AD9959_ChargePumpControl_Mask);

	AD9959Reg.FR2 = 0;

	AD9959Reg.Channel[0].CFR = 0;
	AD9959Reg.Channel[0].CFR = AD9959_SetRegBits(AD9959Reg.Channel[0].CFR, 3, AD9959_DACFullCurrent_Shift, AD9959_DACFullCurrent_Mask);

	AD9959Reg.Channel[0].CFTW = 0;

	AD9959Reg.Channel[0].CPOW = 0;

	AD9959Reg.Channel[0].ACR = 0;
	AD9959Reg.Channel[0].ACR = AD9959_SetRegBits(AD9959Reg.Channel[0].ACR, 0x3FF, AD9959_AmplitudeScale_Shift, AD9959_AmplitudeScale_Mask);

	AD9959Reg.Channel[0].LSRR = 0;

	AD9959Reg.Channel[0].RDW = 0;

	AD9959Reg.Channel[0].FDW = 0;

	AD9959Reg.Channel[1] = AD9959Reg.Channel[0];
	AD9959Reg.Channel[2] = AD9959Reg.Channel[0];
	AD9959Reg.Channel[3] = AD9959Reg.Channel[0];

	AD9959Write(AD9959_CSR_Addr, AD9959_CSR_Len, AD9959Reg.CSR);
	AD9959Write(AD9959_FR1_Addr, AD9959_FR1_Len, AD9959Reg.FR1);
	AD9959Write(AD9959_FR2_Addr, AD9959_FR2_Len, AD9959Reg.FR2);

	AD9959_WriteChannel(0);
	AD9959_WriteChannel(1);
	AD9959_WriteChannel(2);
	AD9959_WriteChannel(3);

	AD9959_Update();

	/*{
		u32 Val = 0;
		Val = AD9959Read(AD9959_CSR_Addr, AD9959_CSR_Len);
		Val = AD9959Read(AD9959_FR1_Addr, AD9959_FR1_Len);
		Val = AD9959Read(AD9959_FR2_Addr, AD9959_FR2_Len);
	}*/

	return S_OK;
}

double AD9959_SetChannelFrequency(u8 Channel, double Freq)
{
	u32 TurningWord = (u32)((u64)(Freq * ((u64)1 << 32) / AD9959_SampleFrequency));

	assert(Channel < 4);

	AD9959Reg.Channel[Channel].CFTW = TurningWord;
	AD9959_WriteChannel(Channel);
	AD9959_Update();

	return (double)TurningWord * AD9959_SampleFrequency / ((u64)1 << 32);
}
