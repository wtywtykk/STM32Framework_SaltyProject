#pragma once

C_HEADER_BEGIN

struct UniSPI_Handle;

typedef struct
{
	SPI_HandleTypeDef HALHandle;
}HardSPI_InfoArea;

u8 HardSPI_GetSPIIndex(SPI_TypeDef* Instance);
STATUS HardSPI_Init(struct UniSPI_Handle* SPI_Handle, SPI_TypeDef* Instance, SPI_InitTypeDef* InitParams);
u8 HardSPI_GetPreScaler(u8 Index, u32 Speed);

C_HEADER_END
