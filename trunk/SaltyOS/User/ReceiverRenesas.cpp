#include "Kernel\Common\KCommon.h"
#include "HAL\UniGPIO.h"

u32 Data = 0;
u32 Data_Latched = 0;
UniGPIO_Handle Renesas_DATA_Handle;
UniGPIO_Handle Renesas_CLK_Handle;
UniGPIO_Handle Renesas_CS_Handle;

void ReceiverRenesas_Init(void)
{
	GPIO_InitTypeDef InitStruct;
	InitStruct.Alternate = 0;
	InitStruct.Mode = GPIO_MODE_INPUT;
	InitStruct.Pull = GPIO_PULLDOWN;
	InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	InitStruct.Pin = GPIO_PIN_1;
	GPIO_32_InitPin(GPIOC, &InitStruct, &Renesas_DATA_Handle);

	InitStruct.Pin = GPIO_PIN_2;
	InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_32_InitPin(GPIOC, &InitStruct, &Renesas_CLK_Handle);
	HAL_NVIC_EnableIRQ(EXTI2_IRQn);

	InitStruct.Pin = GPIO_PIN_3;
	InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_32_InitPin(GPIOC, &InitStruct, &Renesas_CS_Handle);
	HAL_NVIC_EnableIRQ(EXTI3_IRQn);
}

extern "C"
{
	void GPIO_EXTI2_Callback(void)//CLK,falling edge
	{
		Data <<= 1;
		Data |= UniGPIO_Read(&Renesas_DATA_Handle) ? 0x1 : 0x0;
	}

	void GPIO_EXTI3_Callback(void)//CS,rising edge
	{
		Data_Latched = Data;
	}
}

u32 ReceiverRenesas_GetInfo(void)
{
	return Data_Latched;
}

float ReceiverRenesas_GetTotalGain(void)
{
	u32 RecvVal = ReceiverRenesas_GetInfo();
	u16 LNAGain = RecvVal >> 16;
	float AGCVolt = (RecvVal & 0xFFFF) / 1000.0 / 3.0;
	float AGCGain;
	if (AGCVolt > 1.4)
	{
		AGCVolt = 1.4;
	}
	AGCGain = -40 + 55 / 1.2 * AGCVolt / 1470.0 * 470.0;
	//printf("%d %f %f\n\r", LNAGain, AGCGain, AGCVolt);
	return AGCGain + LNAGain;
}
