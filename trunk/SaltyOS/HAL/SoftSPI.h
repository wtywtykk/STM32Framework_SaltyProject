#pragma once

C_HEADER_BEGIN

typedef struct
{
	UniGPIO_Handle* MISO;
	UniGPIO_Handle* MOSI;
	UniGPIO_Handle MISOStore;
	UniGPIO_Handle MOSIStore;
	UniGPIO_Handle SCKStore;
	u8 DataSize;
	bool CPOL;
	bool CPHA;
	u8 IntervalBeforeEdge1;
	u8 IntervalBeforeEdge2;
}SoftSPI_InfoArea;

STATUS SoftSPI_Init(struct UniSPI_Handle* SPI_Handle, UniGPIO_Handle* MISOPin, UniGPIO_Handle* MOSIPin, UniGPIO_Handle* SCKPin, u8 DataSize, bool CPOL, bool CPHA, u8 IntervalBeforeEdge1, u8 IntervalBeforeEdge2);

C_HEADER_END
