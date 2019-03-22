#include "HAL\HCommon.h"
#include "HAL\UniGPIO.h"
#include "HAL\UniSPI.h"
#include "Driver\W25Qxx_Reg.h"
#include <string.h>

/*Modify those if you want to use other SPI ports*/
/************************************************************************************/
#define W25Qxx_SPI_INSTANCE SPI1
#define W25Qxx_SPI_AF GPIO_AF5_SPI1
#define W25Qxx_SPI_CLOCK_SPEED 42000000//42MHz
#define W25Qxx_SPI_TIMEOUT 10
#define W25Qxx_SPI_CS_PORT GPIOA
#define W25Qxx_SPI_CS_PIN GPIO_PIN_4
#define W25Qxx_SPI_SCK_PORT GPIOA
#define W25Qxx_SPI_SCK_PIN	GPIO_PIN_5
#define W25Qxx_SPI_MISO_PORT GPIOA
#define W25Qxx_SPI_MISO_PIN GPIO_PIN_6
#define W25Qxx_SPI_MOSI_PORT GPIOA
#define W25Qxx_SPI_MOSI_PIN GPIO_PIN_7
/************************************************************************************/

bool W25Qxx_Initialized = false;

UniGPIO_Handle W25Qxx_CS;
UniSPI_Handle W25Qxx_SPI_Handle;

u32 W25Qxx_ChipSize = 0;
pstr W25Qxx_ChipName = NULL;

STATUS W25Qxx_SPIInit(void);
u32 CombineCommAddr(u8 Cmd, u32 Addr);
STATUS W25Qxx_ReadID(u8* ManufacturerID, u8* DeviceID);
u8 W25Qxx_ReadSR1(void);
void W25Qxx_WriteSR1(u8 Val);
void W25Qxx_Wait_Busy(void);
void W25Qxx_Write_Enable(void);
void W25Qxx_Write_Disable(void);

STATUS W25Qxx_Init(void)
{
	u8 ManufacturerID;
	u8 DeviceID;

	if (W25Qxx_Initialized)
	{
		return S_OK;
	}

	if (W25Qxx_SPIInit() != S_OK)
	{
		return S_FAIL;
	}

	if (W25Qxx_ReadID(&ManufacturerID, &DeviceID) != S_OK)
	{
		return S_FAIL;
	}

	switch (DeviceID)
	{
	case W25Q80_DeviceID:
		W25Qxx_ChipSize = 8 * 1024 * 1024 / 8;
		W25Qxx_ChipName = "W25Q80";
		break;
	case W25Q16_DeviceID:
		W25Qxx_ChipSize = 16 * 1024 * 1024 / 8;
		W25Qxx_ChipName = "W25Q16";
		break;
	case W25Q32_DeviceID:
		W25Qxx_ChipSize = 32 * 1024 * 1024 / 8;
		W25Qxx_ChipName = "W25Q32";
		break;
	case W25Q64_DeviceID:
		W25Qxx_ChipSize = 64 * 1024 * 1024 / 8;
		W25Qxx_ChipName = "W25Q64";
		break;
	case W25Q128_DeviceID:
		W25Qxx_ChipSize = 128 * 1024 * 1024 / 8;
		W25Qxx_ChipName = "W25Q128";
		break;
	default:
		W25Qxx_ChipSize = 0;
		W25Qxx_ChipName = "Unknown";
		break;
	}

	W25Qxx_Initialized = true;

	return S_OK;
}

STATUS W25Qxx_ChipErase(void)
{
	STATUS Ret = S_FAIL;
	W25Qxx_Wait_Busy();
	W25Qxx_Write_Enable();
	Ret = W25Qxx_SPI_Handle.TransmitWord(&W25Qxx_SPI_Handle, &W25Qxx_CS, W25Qxx_CMD_ChipErase, W25Qxx_SPI_TIMEOUT);
	W25Qxx_Wait_Busy();
	return Ret;
}

STATUS W25Qxx_SectorErase(u32 Addr)
{
	u32 CommData;
	STATUS Ret = S_FAIL;
	Addr /= W25Qxx_SectorSize;
	Addr *= W25Qxx_SectorSize;
	CommData = CombineCommAddr(W25Qxx_CMD_SectorErase, Addr);
	W25Qxx_Wait_Busy();
	W25Qxx_Write_Enable();
	Ret = W25Qxx_SPI_Handle.TransmitBytes(&W25Qxx_SPI_Handle, &W25Qxx_CS, &CommData, sizeof(CommData), W25Qxx_SPI_TIMEOUT);
	W25Qxx_Wait_Busy();
	return Ret;
}

STATUS W25Qxx_Block32Erase(u32 Addr)
{
	u32 CommData;
	STATUS Ret = S_FAIL;
	Addr /= W25Qxx_SectorSize;
	Addr *= W25Qxx_SectorSize;
	CommData = CombineCommAddr(W25Qxx_CMD_BlockErase32, Addr);
	W25Qxx_Wait_Busy();
	W25Qxx_Write_Enable();
	Ret = W25Qxx_SPI_Handle.TransmitBytes(&W25Qxx_SPI_Handle, &W25Qxx_CS, &CommData, sizeof(CommData), W25Qxx_SPI_TIMEOUT);
	W25Qxx_Wait_Busy();
	return Ret;
}

STATUS W25Qxx_Block64Erase(u32 Addr)
{
	u32 CommData;
	STATUS Ret = S_FAIL;
	Addr /= W25Qxx_SectorSize;
	Addr *= W25Qxx_SectorSize;
	CommData = CombineCommAddr(W25Qxx_CMD_BlockErase64, Addr);
	W25Qxx_Wait_Busy();
	W25Qxx_Write_Enable();
	Ret = W25Qxx_SPI_Handle.TransmitBytes(&W25Qxx_SPI_Handle, &W25Qxx_CS, &CommData, sizeof(CommData), W25Qxx_SPI_TIMEOUT);
	W25Qxx_Wait_Busy();
	return Ret;
}

STATUS W25Qxx_PowerDown(void)
{
	STATUS Ret = S_FAIL;
	Ret = W25Qxx_SPI_Handle.TransmitWord(&W25Qxx_SPI_Handle, &W25Qxx_CS, W25Qxx_CMD_PowerDown, W25Qxx_SPI_TIMEOUT);
	HAL_Delay(1);
	return Ret;
}

STATUS W25Qxx_WakeUp(void)
{
	STATUS Ret = S_FAIL;
	Ret = W25Qxx_SPI_Handle.TransmitWord(&W25Qxx_SPI_Handle, &W25Qxx_CS, W25Qxx_CMD_ReleasePowerDown_ID, W25Qxx_SPI_TIMEOUT);
	HAL_Delay(1);
	return Ret;
}

STATUS W25Qxx_Read(u32 Addr, void* Buffer, u32 BufferSize)
{
	return W25Qxx_SPI_Handle.MemRead(&W25Qxx_SPI_Handle, &W25Qxx_CS, CombineCommAddr(W25Qxx_CMD_ReadData, Addr), 4, Buffer, BufferSize, W25Qxx_SPI_TIMEOUT);
}

STATUS W25Qxx_Program_Page(u32 Addr, void* Buffer, u16 BufferSize)
{
	STATUS Ret = S_FAIL;
	assert(BufferSize <= 256);
	W25Qxx_Write_Enable();
	Ret = W25Qxx_SPI_Handle.MemWrite(&W25Qxx_SPI_Handle, &W25Qxx_CS, CombineCommAddr(W25Qxx_CMD_PageProgram, Addr), 4, Buffer, BufferSize, W25Qxx_SPI_TIMEOUT);
	W25Qxx_Wait_Busy();
	return Ret;
}

STATUS W25Qxx_Program(u32 Addr, void* Buffer, u32 BufferSize)
{
	STATUS Ret = S_FAIL;
	u32 CurAddr = Addr;
	u8* CurBuf = (u8*)Buffer;
	u32 CurLen = 0;

	//align to page boundary
	if (CurAddr % W25Qxx_PageSize)
	{
		CurLen = W25Qxx_PageSize - CurAddr % W25Qxx_PageSize;
		Ret = W25Qxx_Program_Page(CurAddr, CurBuf, CurLen);
		if (Ret != S_OK)
		{
			return Ret;
		}
		CurAddr += CurLen;
		CurBuf += CurLen;
		BufferSize -= CurLen;
	}

	while (BufferSize)
	{
		if (BufferSize > W25Qxx_PageSize)
		{
			CurLen = W25Qxx_PageSize;
		}
		else
		{
			CurLen = BufferSize;
		}
		Ret = W25Qxx_Program_Page(CurAddr, CurBuf, CurLen);
		if (Ret != S_OK)
		{
			return Ret;
		}
		CurAddr += CurLen;
		CurBuf += CurLen;
		BufferSize -= CurLen;
	}
	return S_OK;
}

STATUS W25Qxx_Program_Safe(u32 Addr, void* Buffer, u32 BufferSize)
{
	STATUS Ret = S_FAIL;
	u32 CurAddr = Addr;
	u8* CurBuf = (u8*)Buffer;

	//align to page boundary
	//and for incomplete writes, we need to read original content, then erase and write back.
	if (CurAddr % W25Qxx_PageSize)
	{
		u8 ParticalWriteBuf[W25Qxx_SectorSize];
		u32 CurLen;
		u32 SectorStart = CurAddr - CurAddr % W25Qxx_SectorSize;
		Ret = W25Qxx_Read(SectorStart, ParticalWriteBuf, W25Qxx_SectorSize);
		if (Ret != S_OK)
		{
			return Ret;
		}
		Ret = W25Qxx_SectorErase(SectorStart);
		if (Ret != S_OK)
		{
			return Ret;
		}

		CurLen = W25Qxx_SectorSize - CurAddr % W25Qxx_SectorSize;
		if (CurLen > BufferSize)
		{
			CurLen = BufferSize;
		}
		memcpy(&ParticalWriteBuf[CurAddr - SectorStart], CurBuf, CurLen);

		Ret = W25Qxx_Program(SectorStart, ParticalWriteBuf, W25Qxx_SectorSize);
		if (Ret != S_OK)
		{
			return Ret;
		}
		CurAddr += CurLen;
		CurBuf += CurLen;
		BufferSize -= CurLen;
	}

	while (BufferSize >= W25Qxx_SectorSize)
	{
		Ret = W25Qxx_SectorErase(CurAddr);
		if (Ret != S_OK)
		{
			return Ret;
		}
		Ret = W25Qxx_Program(CurAddr, CurBuf, W25Qxx_SectorSize);
		if (Ret != S_OK)
		{
			return Ret;
		}
		CurAddr += W25Qxx_SectorSize;
		CurBuf += W25Qxx_SectorSize;
		BufferSize -= W25Qxx_SectorSize;
	}

	if (BufferSize)
	{
		u8 ParticalWriteBuf[W25Qxx_SectorSize];
		Ret = W25Qxx_Read(CurAddr, ParticalWriteBuf, W25Qxx_SectorSize);
		if (Ret != S_OK)
		{
			return Ret;
		}
		Ret = W25Qxx_SectorErase(CurAddr);
		if (Ret != S_OK)
		{
			return Ret;
		}
		memcpy(ParticalWriteBuf, CurBuf, BufferSize);
		Ret = W25Qxx_Program(CurAddr, ParticalWriteBuf, W25Qxx_SectorSize);
		if (Ret != S_OK)
		{
			return Ret;
		}
	}
	return S_OK;
}

u32 CombineCommAddr(u8 Cmd, u32 Addr)
{
	assert((Addr & 0xFF000000) == 0);
	return Cmd | (((Addr >> 16) & 0x000000FF) | (Addr & 0x0000FF00) | ((Addr << 16) & 0x00FF0000)) << 8;
}

STATUS W25Qxx_ReadID(u8* ManufacturerID, u8* DeviceID)
{
	u8 IDs[2];
	if (W25Qxx_SPI_Handle.MemRead(&W25Qxx_SPI_Handle, &W25Qxx_CS, CombineCommAddr(W25Qxx_CMD_Manufacturer_DeviveID, 0), 4, IDs, sizeof(IDs), W25Qxx_SPI_TIMEOUT) == S_OK)
	{
		if (ManufacturerID)
		{
			*ManufacturerID = IDs[0];
		}
		if (DeviceID)
		{
			*DeviceID = IDs[1];
		}
		return S_OK;
	}
	return S_FAIL;
}

u8 W25Qxx_ReadSR1(void)
{
	u8 CommData[2];

	CommData[0] = W25Qxx_CMD_ReadStatusReg1;
	CommData[1] = 0;

	if (W25Qxx_SPI_Handle.TransmitReceive(&W25Qxx_SPI_Handle, &W25Qxx_CS, CommData, sizeof(CommData), W25Qxx_SPI_TIMEOUT) == S_OK)
	{
		return CommData[1];
	}
	else
	{
		return 0;
	}
}

void W25Qxx_WriteSR1(u8 Val)
{
	u8 CommData[2];

	CommData[0] = W25Qxx_CMD_WriteStatusReg1;
	CommData[1] = Val;

	W25Qxx_SPI_Handle.TransmitBytes(&W25Qxx_SPI_Handle, &W25Qxx_CS, CommData, sizeof(CommData), W25Qxx_SPI_TIMEOUT);
}

void W25Qxx_Wait_Busy(void)
{
	while (W25Qxx_ReadSR1() & W25Qxx_SR1_BUSY);
}

void W25Qxx_Write_Enable(void)
{
	W25Qxx_SPI_Handle.TransmitWord(&W25Qxx_SPI_Handle, &W25Qxx_CS, W25Qxx_CMD_WriteEnable, W25Qxx_SPI_TIMEOUT);
}

void W25Qxx_Write_Disable(void)
{
	W25Qxx_SPI_Handle.TransmitWord(&W25Qxx_SPI_Handle, &W25Qxx_CS, W25Qxx_CMD_WriteDisable, W25Qxx_SPI_TIMEOUT);
}

STATUS W25Qxx_SPIInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef SPI_InitStruct;

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	GPIO_InitStruct.Pin = W25Qxx_SPI_CS_PIN;
	GPIO_32_InitPin(W25Qxx_SPI_CS_PORT, &GPIO_InitStruct, &W25Qxx_CS);

	UniGPIO_SetHigh(&W25Qxx_CS);

	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Alternate = W25Qxx_SPI_AF;

	GPIO_InitStruct.Pin = W25Qxx_SPI_SCK_PIN;
	GPIO_32_InitPin(W25Qxx_SPI_SCK_PORT, &GPIO_InitStruct, NULL);
	GPIO_InitStruct.Pin = W25Qxx_SPI_MISO_PIN;
	GPIO_32_InitPin(W25Qxx_SPI_MISO_PORT, &GPIO_InitStruct, NULL);
	GPIO_InitStruct.Pin = W25Qxx_SPI_MOSI_PIN;
	GPIO_32_InitPin(W25Qxx_SPI_MOSI_PORT, &GPIO_InitStruct, NULL);

	SPI_InitStruct.Mode = SPI_MODE_MASTER;
	SPI_InitStruct.Direction = SPI_DIRECTION_2LINES;
	SPI_InitStruct.DataSize = SPI_DATASIZE_8BIT;
	SPI_InitStruct.CLKPolarity = SPI_POLARITY_LOW;
	SPI_InitStruct.CLKPhase = SPI_PHASE_1EDGE;
	SPI_InitStruct.NSS = SPI_NSS_SOFT;
	SPI_InitStruct.BaudRatePrescaler = HardSPI_GetPreScaler(HardSPI_GetSPIIndex(W25Qxx_SPI_INSTANCE), W25Qxx_SPI_CLOCK_SPEED);
	SPI_InitStruct.FirstBit = SPI_FIRSTBIT_MSB;
	SPI_InitStruct.TIMode = SPI_TIMODE_DISABLE;
	SPI_InitStruct.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	SPI_InitStruct.CRCPolynomial = 10;

	if (HardSPI_Init(&W25Qxx_SPI_Handle, W25Qxx_SPI_INSTANCE, &SPI_InitStruct) != S_OK)
	{
		return S_FAIL;
	}

	return S_OK;
}
