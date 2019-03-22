#include "HCommon.h"
#include "HAL\UniGPIO.h"
#include "UniSPI.h"
#include "HardSPI.h"

STATUS HardSPI_TransmitWord(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, u16 Data, u32 TimeOut);
STATUS HardSPI_TransmitBytes(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, void* Data, u16 Size, u32 TimeOut);
STATUS HardSPI_TransmitReceive(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, void* Data, u16 Size, u32 TimeOut);
STATUS HardSPI_MemRead(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, u32 Address, u16 AddrSize, void* Buffer, u16 Size, u32 TimeOut);
STATUS HardSPI_MemWrite(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, u32 Address, u16 AddrSize, void* Buffer, u16 Size, u32 TimeOut);
void HardSPI_Free(UniSPI_Handle* SPI_Handle);

u8 HardSPI_GetSPIWidthInBytes(SPI_HandleTypeDef* SPI_Handle);

u8 HardSPI_GetSPIIndex(SPI_TypeDef* Instance)
{
	switch ((u32)Instance)
	{
	case (u32)SPI1:
		return 1;
		break;
	case (u32)SPI2:
		return 2;
		break;
	case (u32)SPI3:
		return 3;
		break;
	default:
		assert(false);
		return 0;
		break;
	}
}

STATUS HardSPI_InitClock(SPI_TypeDef* Instance)
{
	switch (HardSPI_GetSPIIndex(Instance))
	{
	case 1:
		__HAL_RCC_SPI1_CLK_ENABLE();
		return S_OK;
		break;
	case 2:
		__HAL_RCC_SPI2_CLK_ENABLE();
		return S_OK;
		break;
	case 3:
		__HAL_RCC_SPI3_CLK_ENABLE();
		return S_OK;
		break;
	default:
		return S_FAIL;
		break;
	}
}

STATUS HardSPI_Init(UniSPI_Handle* SPI_Handle, SPI_TypeDef* Instance, SPI_InitTypeDef* InitParams)
{
	SPI_Handle->SPI_Info.HardSPI_Info.HALHandle.Instance = Instance;
	SPI_Handle->SPI_Info.HardSPI_Info.HALHandle.Init = *InitParams;

	SPI_Handle->Free = NULL;
	SPI_Handle->MemRead = NULL;
	SPI_Handle->MemWrite = NULL;
	SPI_Handle->TransmitBytes = NULL;
	SPI_Handle->TransmitReceive = NULL;
	SPI_Handle->TransmitWord = NULL;

	if (HardSPI_InitClock(Instance) != S_OK)
	{
		return S_FAIL;
	}

	if (HAL_SPI_Init(&SPI_Handle->SPI_Info.HardSPI_Info.HALHandle) != HAL_OK)
	{
		return S_FAIL;
	}

	SPI_Handle->TransmitWord = &HardSPI_TransmitWord;
	SPI_Handle->TransmitBytes = &HardSPI_TransmitBytes;
	SPI_Handle->TransmitReceive = &HardSPI_TransmitReceive;
	SPI_Handle->MemRead = &HardSPI_MemRead;
	SPI_Handle->MemWrite = &HardSPI_MemWrite;
	SPI_Handle->Free = &HardSPI_Free;

	return S_OK;
}

STATUS HardSPI_TransmitWord(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, u16 Data, u32 TimeOut)
{
	STATUS Ret = S_FAIL;

	UniGPIO_SetLow(CSPin);
	if (HAL_SPI_Transmit(&SPI_Handle->SPI_Info.HardSPI_Info.HALHandle, (u8*)&Data, 1, TimeOut) == HAL_OK)
	{
		Ret = S_OK;
	}
	UniGPIO_SetHigh(CSPin);

	return Ret;
}

STATUS HardSPI_TransmitBytes(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, void* Data, u16 Size, u32 TimeOut)
{
	STATUS Ret = S_FAIL;
	assert(Size % HardSPI_GetSPIWidthInBytes(&SPI_Handle->SPI_Info.HardSPI_Info.HALHandle) == 0);//Errors may occur if data are not aligned to spi width.

	UniGPIO_SetLow(CSPin);
	if (HAL_SPI_Transmit(&SPI_Handle->SPI_Info.HardSPI_Info.HALHandle, (u8*)Data, Size / HardSPI_GetSPIWidthInBytes(&SPI_Handle->SPI_Info.HardSPI_Info.HALHandle), TimeOut) == HAL_OK)
	{
		Ret = S_OK;
	}
	UniGPIO_SetHigh(CSPin);

	return Ret;
}

STATUS HardSPI_TransmitReceive(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, void* Data, u16 Size, u32 TimeOut)
{
	STATUS Ret = S_FAIL;
	assert(Size % HardSPI_GetSPIWidthInBytes(&SPI_Handle->SPI_Info.HardSPI_Info.HALHandle) == 0);//Errors may occur if data are not aligned to spi width.

	UniGPIO_SetLow(CSPin);
	if (HAL_SPI_TransmitReceive(&SPI_Handle->SPI_Info.HardSPI_Info.HALHandle, (u8*)Data, (u8*)Data, Size / HardSPI_GetSPIWidthInBytes(&SPI_Handle->SPI_Info.HardSPI_Info.HALHandle), TimeOut) == HAL_OK)
	{
		Ret = S_OK;
	}
	UniGPIO_SetHigh(CSPin);

	return Ret;
}

STATUS HardSPI_MemRead(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, u32 Address, u16 AddrSize, void* Buffer, u16 Size, u32 TimeOut)
{
	STATUS Ret = S_FAIL;
	u8 SPIWidth = HardSPI_GetSPIWidthInBytes(&SPI_Handle->SPI_Info.HardSPI_Info.HALHandle);
	assert(AddrSize % SPIWidth == 0);//Errors may occur if data are not aligned to spi width.
	assert(Size % SPIWidth == 0);//Errors may occur if data are not aligned to spi width.

	UniGPIO_SetLow(CSPin);
	if (HAL_SPI_Transmit(&SPI_Handle->SPI_Info.HardSPI_Info.HALHandle, (u8*)&Address, AddrSize / SPIWidth, TimeOut) == HAL_OK)
	{
		if (HAL_SPI_Receive(&SPI_Handle->SPI_Info.HardSPI_Info.HALHandle, (u8*)Buffer, Size / SPIWidth, TimeOut) == HAL_OK)
		{
			Ret = S_OK;
		}
	}
	UniGPIO_SetHigh(CSPin);

	return Ret;
}

STATUS HardSPI_MemWrite(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, u32 Address, u16 AddrSize, void* Buffer, u16 Size, u32 TimeOut)
{
	STATUS Ret = S_FAIL;
	u32 SPIWidth = HardSPI_GetSPIWidthInBytes(&SPI_Handle->SPI_Info.HardSPI_Info.HALHandle);
	assert(AddrSize %SPIWidth == 0);//Errors may occur if data are not aligned to spi width.
	assert(Size % SPIWidth == 0);//Errors may occur if data are not aligned to spi width.

	UniGPIO_SetLow(CSPin);
	if (HAL_SPI_Transmit(&SPI_Handle->SPI_Info.HardSPI_Info.HALHandle, (u8*)&Address, AddrSize / SPIWidth, TimeOut) == HAL_OK)
	{
		if (HAL_SPI_Transmit(&SPI_Handle->SPI_Info.HardSPI_Info.HALHandle, (u8*)Buffer, Size / SPIWidth, TimeOut) == HAL_OK)
		{
			Ret = S_OK;
		}
	}
	UniGPIO_SetHigh(CSPin);

	return Ret;
}

void HardSPI_Free(UniSPI_Handle* SPI_Handle)
{
	assert(false);
	//not implemented
}

u8 HardSPI_GetPreScaler(u8 Index, u32 Speed)
{
	u8 PreScaler = 0;
	u32 PClk1 = Index == 1 ? HAL_RCC_GetPCLK2Freq() : HAL_RCC_GetPCLK1Freq();
	while (Speed * (1 << (PreScaler + 1)) < PClk1 && PreScaler < 8)
	{
		PreScaler++;
	}
	if (PreScaler > 7)
	{
		assert(PreScaler <= 7);
		PreScaler = 7;
	}
	return PreScaler << 3;
}

u8 HardSPI_GetSPIWidthInBytes(SPI_HandleTypeDef* SPI_Handle)
{
	switch (SPI_Handle->Init.DataSize)
	{
	case SPI_DATASIZE_8BIT:
		return 1;
	case SPI_DATASIZE_16BIT:
		return 2;
	default:
		return 1;
	}
}
