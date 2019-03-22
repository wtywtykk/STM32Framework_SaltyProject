#pragma once

C_HEADER_BEGIN

#include "HAL\HardSPI.h"
#include "HAL\SoftSPI.h"

typedef STATUS(*SPIFUNC_TransmitWord)(struct UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, u16 Data, u32 TimeOut);
typedef STATUS(*SPIFUNC_TransmitBytes)(struct UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, void* Data, u16 Size, u32 TimeOut);
typedef STATUS(*SPIFUNC_TransmitReceive)(struct UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, void* Data, u16 Size, u32 TimeOut);
typedef STATUS(*SPIFUNC_MemRead)(struct UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, u32 Address, u16 AddrSize, void* Buffer, u16 Size, u32 TimeOut);
typedef STATUS(*SPIFUNC_MemWrite)(struct UniSPI_Handle* SPI_Handle, UniGPIO_Handle* CSPin, u32 Address, u16 AddrSize, void* Buffer, u16 Size, u32 TimeOut);
typedef void(*SPIFUNC_Free)(struct UniSPI_Handle* SPI_Handle);

typedef struct UniSPI_Handle
{
	SPIFUNC_TransmitWord TransmitWord;
	SPIFUNC_TransmitBytes TransmitBytes;
	SPIFUNC_TransmitReceive TransmitReceive;
	SPIFUNC_MemRead MemRead;
	SPIFUNC_MemWrite MemWrite;
	SPIFUNC_Free Free;
	union SPI_Info
	{
		HardSPI_InfoArea HardSPI_Info;
		SoftSPI_InfoArea SoftSPI_Info;
	}SPI_Info;
}UniSPI_Handle;

//Make the calls function-like
#define UniSPI_TransmitWord(SPI_Handle, CSPin, Data, TimeOut) (SPI_Handle)->TransmitWord((SPI_Handle), (CSPin), (Data), (TimeOut))
#define UniSPI_TransmitBytes(SPI_Handle, CSPin, Data, Size, TimeOut) (SPI_Handle)->TransmitBytes((SPI_Handle), (CSPin), (Data), (Size), (TimeOut))
#define UniSPI_TransmitReceive(SPI_Handle, CSPin, Data, Size, TimeOut) (SPI_Handle)->TransmitReceive((SPI_Handle), (CSPin), (Data),(Size), (TimeOut))
#define UniSPI_MemRead(SPI_Handle, CSPin, Address, AddrSize, Buffer, Size, TimeOut) (SPI_Handle)->MemRead((SPI_Handle), (CSPin), (Address), (AddrSize), (Buffer), (Size), (TimeOut))
#define UniSPI_MemWrite(SPI_Handle, CSPin, Address, AddrSize, Buffer, Size, TimeOut) (SPI_Handle)->MemWrite((SPI_Handle), (CSPin), (Address), (AddrSize), (Buffer), (Size),(TimeOut))
#define UniSPI_Free(SPI_Handle) (SPI_Handle)->Free(SPI_Handle)

C_HEADER_END
