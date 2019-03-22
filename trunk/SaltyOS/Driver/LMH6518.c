#include "HAL\HCommon.h"
#include "HAL\UniGPIO.h"
#include "HAL\UniSPI.h"

#define LMH6518_Timeout 10

UniGPIO_Handle LMH6518_MOSI;
UniGPIO_Handle LMH6518_MISO;
UniGPIO_Handle LMH6518_SCK;
UniGPIO_Handle LMH6518_CS;

UniSPI_Handle LMH6518_SPI_Handle;

bool LMH6518_Initialized = false;

u16 ChannelA;
u16 ChannelB;

STATUS LMH6518_Init(void)
{
	if (LMH6518_Initialized)
	{
		return S_OK;
	}

	GPIO_CPLD_InitPin(4, 3, false, &LMH6518_MISO);
	GPIO_CPLD_InitPin(4, 1, true, &LMH6518_MOSI);
	GPIO_CPLD_InitPin(4, 5, true, &LMH6518_SCK);
	GPIO_CPLD_InitPin(4, 7, true, &LMH6518_CS);

	SoftSPI_Init(&LMH6518_SPI_Handle, &LMH6518_MISO, &LMH6518_MOSI, &LMH6518_SCK, 8, false, false, 1, 1);

	LMH6518_Initialized = true;

	return S_OK;
}

void LMH6518_Update(void)
{
	u8 CombinedVal[3];
	CombinedVal[0] = ChannelA >> 4;
	CombinedVal[1] = ChannelA << 4 | ChannelB >> 8;
	CombinedVal[2] = ChannelB;
	UniGPIO_SetLow(&LMH6518_CS);
	UniSPI_TransmitBytes(&LMH6518_SPI_Handle, &LMH6518_CS, CombinedVal, 3, LMH6518_Timeout);
	UniGPIO_SetHigh(&LMH6518_CS);
}
