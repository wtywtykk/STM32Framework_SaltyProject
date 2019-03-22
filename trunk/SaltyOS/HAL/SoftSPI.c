#include "HCommon.h"
#include "HAL\UniGPIO.h"
#include "UniSPI.h"
#include "SoftSPI.h"

STATUS SoftSPI_TransmitWord(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, u16 Data, u32 TimeOut);
STATUS SoftSPI_TransmitBytes(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, void* Data, u16 Size, u32 TimeOut);
STATUS SoftSPI_TransmitReceive(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, void* Data, u16 Size, u32 TimeOut);
STATUS SoftSPI_MemRead(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, u32 Address, u16 AddrSize, void* Buffer, u16 Size, u32 TimeOut);
STATUS SoftSPI_MemWrite(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, u32 Address, u16 AddrSize, void* Buffer, u16 Size, u32 TimeOut);
void SoftSPI_Free(UniSPI_Handle* SPI_Handle);

//CPOL=0;CPHA=0
u16 SoftSPI_TransmitReceiveWord00(SoftSPI_InfoArea* Info, u16 SendData)
{
	u8 i;
	u16 RecvVal = 0;
	u16 HighestBitMask = 1 << (Info->DataSize - 1);
	assert(Info->CPOL == false && Info->CPHA == false);
	for (i = 0; i < Info->DataSize; i++)
	{
		UniGPIO_SetVal(Info->MOSI, SendData & HighestBitMask);
		SendData <<= 1;
		if (Info->IntervalBeforeEdge1)
		{
			HAL_Delay(Info->IntervalBeforeEdge1);
		}
		RecvVal <<= 1;
		RecvVal |= UniGPIO_Read(Info->MISO);
		UniGPIO_SetHigh(&Info->SCKStore);
		if (Info->IntervalBeforeEdge2)
		{
			HAL_Delay(Info->IntervalBeforeEdge2);
		}
		UniGPIO_SetLow(&Info->SCKStore);
	}
	return RecvVal;
}

//CPOL=0;CPHA=1
u16 SoftSPI_TransmitReceiveWord01(SoftSPI_InfoArea* Info, u16 SendData)
{
	u8 i;
	u16 RecvVal = 0;
	u16 HighestBitMask = 1 << (Info->DataSize - 1);
	assert(Info->CPOL == false && Info->CPHA == true);
	for (i = 0; i < Info->DataSize; i++)
	{
		UniGPIO_SetVal(Info->MOSI, SendData & HighestBitMask);
		SendData <<= 1;
		UniGPIO_SetHigh(&Info->SCKStore);
		if (Info->IntervalBeforeEdge1)
		{
			HAL_Delay(Info->IntervalBeforeEdge1);
		}
		RecvVal <<= 1;
		RecvVal |= UniGPIO_Read(Info->MISO);
		UniGPIO_SetLow(&Info->SCKStore);
		if (Info->IntervalBeforeEdge2)
		{
			HAL_Delay(Info->IntervalBeforeEdge2);
		}
	}
	return RecvVal;
}

//CPOL=1;CPHA=0
u16 SoftSPI_TransmitReceiveWord10(SoftSPI_InfoArea* Info, u16 SendData)
{
	u8 i;
	u16 RecvVal = 0;
	u16 HighestBitMask = 1 << (Info->DataSize - 1);
	assert(Info->CPOL == true && Info->CPHA == false);
	for (i = 0; i < Info->DataSize; i++)
	{
		UniGPIO_SetVal(Info->MOSI, SendData & HighestBitMask);
		SendData <<= 1;
		if (Info->IntervalBeforeEdge1)
		{
			HAL_Delay(Info->IntervalBeforeEdge1);
		}
		RecvVal <<= 1;
		RecvVal |= UniGPIO_Read(Info->MISO);
		UniGPIO_SetLow(&Info->SCKStore);
		if (Info->IntervalBeforeEdge2)
		{
			HAL_Delay(Info->IntervalBeforeEdge2);
		}
		UniGPIO_SetHigh(&Info->SCKStore);
	}
	return RecvVal;
}

//CPOL=1;CPHA=1
u16 SoftSPI_TransmitReceiveWord11(SoftSPI_InfoArea* Info, u16 SendData)
{
	u8 i;
	u16 RecvVal = 0;
	u16 HighestBitMask = 1 << (Info->DataSize - 1);
	assert(Info->CPOL == true && Info->CPHA == true);
	for (i = 0; i < Info->DataSize; i++)
	{
		UniGPIO_SetVal(Info->MOSI, SendData & HighestBitMask);
		SendData <<= 1;
		UniGPIO_SetLow(&Info->SCKStore);
		if (Info->IntervalBeforeEdge1)
		{
			HAL_Delay(Info->IntervalBeforeEdge1);
		}
		RecvVal <<= 1;
		RecvVal |= UniGPIO_Read(Info->MISO);
		UniGPIO_SetHigh(&Info->SCKStore);
		if (Info->IntervalBeforeEdge2)
		{
			HAL_Delay(Info->IntervalBeforeEdge2);
		}
	}
	return RecvVal;
}

u16 SoftSPI_TransmitReceiveWord(SoftSPI_InfoArea* Info, u16 SendData)
{
	if (Info->CPOL == false)
	{
		if (Info->CPHA == false)
		{
			return SoftSPI_TransmitReceiveWord00(Info, SendData);
		}
		else
		{
			return SoftSPI_TransmitReceiveWord01(Info, SendData);
		}
	}
	else
	{
		if (Info->CPHA == false)
		{
			return SoftSPI_TransmitReceiveWord10(Info, SendData);
		}
		else
		{
			return SoftSPI_TransmitReceiveWord11(Info, SendData);
		}
	}
}

STATUS SoftSPI_Init(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* MISOPin, UniGPIO_Handle* MOSIPin, UniGPIO_Handle* SCKPin, u8 DataSize, bool CPOL, bool CPHA, u8 IntervalBeforeEdge1, u8 IntervalBeforeEdge2)
{
	SPI_Handle->SPI_Info.SoftSPI_Info.CPHA = CPHA;
	SPI_Handle->SPI_Info.SoftSPI_Info.CPOL = CPOL;
	SPI_Handle->SPI_Info.SoftSPI_Info.DataSize = DataSize;
	SPI_Handle->SPI_Info.SoftSPI_Info.IntervalBeforeEdge1 = IntervalBeforeEdge1;
	SPI_Handle->SPI_Info.SoftSPI_Info.IntervalBeforeEdge2 = IntervalBeforeEdge2;
	if (MISOPin)
	{
		SPI_Handle->SPI_Info.SoftSPI_Info.MISOStore = *MISOPin;
		SPI_Handle->SPI_Info.SoftSPI_Info.MISO = &SPI_Handle->SPI_Info.SoftSPI_Info.MISOStore;
	}
	else
	{
		SPI_Handle->SPI_Info.SoftSPI_Info.MISO = NULL;
	}
	if (MOSIPin)
	{
		SPI_Handle->SPI_Info.SoftSPI_Info.MOSIStore = *MOSIPin;
		SPI_Handle->SPI_Info.SoftSPI_Info.MOSI = &SPI_Handle->SPI_Info.SoftSPI_Info.MOSIStore;
	}
	else
	{
		SPI_Handle->SPI_Info.SoftSPI_Info.MOSI = NULL;
	}
	assert(SCKPin);
	SPI_Handle->SPI_Info.SoftSPI_Info.SCKStore = *SCKPin;

	SPI_Handle->TransmitWord = &SoftSPI_TransmitWord;
	SPI_Handle->TransmitBytes = &SoftSPI_TransmitBytes;
	SPI_Handle->TransmitReceive = &SoftSPI_TransmitReceive;
	SPI_Handle->MemRead = &SoftSPI_MemRead;
	SPI_Handle->MemWrite = &SoftSPI_MemWrite;
	SPI_Handle->Free = &SoftSPI_Free;

	UniGPIO_SetInput(SPI_Handle->SPI_Info.SoftSPI_Info.MISO);
	UniGPIO_SetOutput(SPI_Handle->SPI_Info.SoftSPI_Info.MOSI);
	UniGPIO_SetOutput(&SPI_Handle->SPI_Info.SoftSPI_Info.SCKStore);

	UniGPIO_SetLow(SPI_Handle->SPI_Info.SoftSPI_Info.MISO);
	UniGPIO_SetVal(&SPI_Handle->SPI_Info.SoftSPI_Info.SCKStore, CPOL);

	return S_OK;
}

STATUS SoftSPI_TransmitWord(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, u16 Data, u32 TimeOut)
{
	UniGPIO_SetLow(CSPin);
	SoftSPI_TransmitReceiveWord(&SPI_Handle->SPI_Info.SoftSPI_Info, Data);
	UniGPIO_SetHigh(CSPin);
	return S_OK;
}

STATUS SoftSPI_TransmitBytes(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, void* Data, u16 Size, u32 TimeOut)
{
	STATUS Ret;
	UniGPIO_SetLow(CSPin);
	switch (SPI_Handle->SPI_Info.SoftSPI_Info.DataSize)
	{
	case 8:
	{
		u8* u8Data = (u8*)Data;
		while (Size)
		{
			SoftSPI_TransmitReceiveWord(&SPI_Handle->SPI_Info.SoftSPI_Info, *u8Data);
			u8Data++;
			Size--;
		}
		Ret = S_OK;
	}
	break;
	case 16:
	{
		u16* u16Data = (u16*)Data;
		while (Size)
		{
			SoftSPI_TransmitReceiveWord(&SPI_Handle->SPI_Info.SoftSPI_Info, *u16Data);
			u16Data++;
			assert(Size >= 2);
			if (Size < 2)
			{
				break;
			}
			Size -= 2;
		}
		Ret = S_OK;
	}
	break;
	default:
		assert(false);
		Ret = S_FAIL;
	}
	UniGPIO_SetHigh(CSPin);
	return Ret;
}

STATUS SoftSPI_TransmitReceive(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, void* Data, u16 Size, u32 TimeOut)
{
	STATUS Ret;
	UniGPIO_SetLow(CSPin);
	switch (SPI_Handle->SPI_Info.SoftSPI_Info.DataSize)
	{
	case 8:
	{
		u8* u8Data = (u8*)Data;
		while (Size)
		{
			u8 RecvVal = SoftSPI_TransmitReceiveWord(&SPI_Handle->SPI_Info.SoftSPI_Info, *u8Data);
			*u8Data = RecvVal;
			u8Data++;
			Size--;
		}
		Ret = S_OK;
	}
	break;
	case 16:
	{
		u16* u16Data = (u16*)Data;
		while (Size)
		{
			u16 RecvVal = SoftSPI_TransmitReceiveWord(&SPI_Handle->SPI_Info.SoftSPI_Info, *u16Data);
			*u16Data = RecvVal;
			u16Data++;
			assert(Size >= 2);
			if (Size < 2)
			{
				break;
			}
			Size -= 2;
		}
		Ret = S_OK;
	}
	break;
	default:
		assert(false);
		Ret = S_FAIL;
	}
	UniGPIO_SetHigh(CSPin);
	return Ret;
}

STATUS SoftSPI_MemRead(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, u32 Address, u16 AddrSize, void* Buffer, u16 Size, u32 TimeOut)
{
	STATUS Ret;
	UniGPIO_SetLow(CSPin);
	if (SoftSPI_TransmitBytes(SPI_Handle, NULL, &Address, AddrSize, TimeOut) == S_OK)
	{
		if (SoftSPI_TransmitReceive(SPI_Handle, NULL, Buffer, Size, TimeOut) == S_OK)
		{
			Ret = S_OK;
		}
		else
		{
			Ret = S_OK;
		}
	}
	else
	{
		Ret = S_OK;
	}
	UniGPIO_SetHigh(CSPin);
	return Ret;
}

STATUS SoftSPI_MemWrite(UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, u32 Address, u16 AddrSize, void* Buffer, u16 Size, u32 TimeOut)
{
	STATUS Ret;
	UniGPIO_SetLow(CSPin);
	if (SoftSPI_TransmitBytes(SPI_Handle, NULL, &Address, AddrSize, TimeOut) == S_OK)
	{
		if (SoftSPI_TransmitBytes(SPI_Handle, NULL, Buffer, Size, TimeOut) == S_OK)
		{
			Ret = S_OK;
		}
		else
		{
			Ret = S_OK;
		}
	}
	else
	{
		Ret = S_OK;
	}
	UniGPIO_SetHigh(CSPin);
	return Ret;
}

void SoftSPI_Free(UniSPI_Handle* SPI_Handle)
{
}
