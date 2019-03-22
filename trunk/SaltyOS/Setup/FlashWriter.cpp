#include "Kernel\Common\KCommon.h"
#include "Driver\LowLevelGraphic.h"
#include "Kernel\GUI\GUICommon.h"
#include "HAL\UART.h"
#include "Setup\FlashAbstract.h"
#include "Kernel\Power\Power.h"
#include <string.h>
#include <malloc.h>

/**************************************************************************
							INSTRUCTION FORMAT
	Connect:
		-u8 Target select
		-Reply:ConnectReply,InvalidInstruction
	IsReady:
		-No param
		-Reply:Ready,InvalidInstruction
	Erase:
		-u8 Operation type
		-u32 Address (if operation type is chip erase, this param is ignored)
		-Reply:No reply
	WriteBytes:
		-u32 Address
		-u32 Length
		-u8*n Data
		-Reply:No reply
	ReadBytes:
		-u32 Address
		-u32 Length
		-Reply:u8*n Data
	ReadInformationBlock:
		-No param
		-Reply:InformationStruct
	DisConnect:
		-No param
		-Reply:No reply
	Reset:
		-No param
		-Reply:No reply
***************************************************************************/

typedef enum
{
	DisConnected,
	Connected,
	Error,
}FlashWriterStatus;

typedef enum
{
	Detect = 0xA0,
	Connect = 0xA1,
	IsReady = 0xA2,
	Erase = 0xA3,
	WriteBytes = 0xA4,
	ReadBytes = 0xA5,
	CheckBytes = 0xA6,
	ReadInformationBlock = 0xA7,
	DisConnect = 0xB0,
	Reset = 0xB1,
}FlashWriterInstructions;

typedef enum
{
	EraseSector = 0,
	EraseBlock = 1,
	EraseChip = 2,
}FlashWriterWriteType;

typedef enum
{
	DetectReply = 0xC0,
	ConnectReply = 0xC1,
	Ready = 0xC2,
	ErrorOccured = 0xC3,
	InvalidInstruction = 0xD0,
	WrongStatus = 0xD1,
}FlashWriterReply;

FlashWriterStatus Status;
FlashIndex TargetIndex;

bool ProcessDetect(void);
bool ProcessConnect(void);
bool ProcessIsReady(void);
bool ProcessErase(void);
bool ProcessWriteBytes(void);
bool ProcessReadBytes(void);
bool ProcessCheckBytes(void);
bool ProcessReadInformationBlock(void);
bool ProcessDisConnect(void);
bool ProcessReset(void);
bool ProcessInvalid(void);

_Noreturn void EnterFlashWriterMode(void)
{
	LLGraphic_DrawString("Flash Writer mode Entered. Waiting for connection.", 0, 0, WHITE, BLACK);

	Status = DisConnected;
	while (1)
	{
		bool Ret = false;
		switch (UART_ReceiveByte())
		{
		case Detect:
			Ret = ProcessDetect();
			break;
		case Connect:
			Ret = ProcessConnect();
			break;
		case IsReady:
			Ret = ProcessIsReady();
			break;
		case Erase:
			Ret = ProcessErase();
			break;
		case WriteBytes:
			Ret = ProcessWriteBytes();
			break;
		case ReadBytes:
			Ret = ProcessReadBytes();
			break;
		case CheckBytes:
			Ret = ProcessCheckBytes();
			break;
		case ReadInformationBlock:
			Ret = ProcessReadInformationBlock();
			break;
		case DisConnect:
			Ret = ProcessDisConnect();
			break;
		case Reset:
			Ret = ProcessReset();
			break;
		default:
			Ret = ProcessInvalid();
			break;
		}
		if (!Ret)
		{
			UART_SendByte(WrongStatus);
		}
	}
}

bool ProcessDetect(void)
{
	UART_SendByte(DetectReply);

	return true;
}

STATUS IndexByteToFlashIndex(u8 IndexByte, FlashIndex* Index)
{
	switch (IndexByte)
	{
	case 0:
		*Index = SST;
		return S_OK;
		break;
	case 1:
		*Index = SPI;
		return S_OK;
		break;
	default:
		*Index = NullFlash;
		return S_FAIL;
		break;
	}
}

bool ProcessConnect(void)
{
	if (Status != DisConnected)
	{
		return false;
	}

	if (IndexByteToFlashIndex(UART_ReceiveByte(), &TargetIndex) != S_OK)
	{
		UART_SendByte(ErrorOccured);
	}
	else
	{
		Status = Connected;
		UART_SendByte(ConnectReply);
	}
	return true;
}

bool ProcessIsReady(void)
{
	switch (Status)
	{
	case Connected:
		UART_SendByte(Ready);
		break;
	case Error:
		UART_SendByte(ErrorOccured);
		break;
	default:
		return false;
		break;
	}
	return true;
}

bool ProcessErase(void)
{
	u8 OperationType;
	u32 Address;
	STATUS EraseStatus = S_FAIL;

	if (Status != Connected)
	{
		return false;;
	}

	OperationType = UART_ReceiveByte();
	UART_Receive(&Address, sizeof(Address));
	switch (OperationType)
	{
	case EraseSector:
		EraseStatus = FlashAbstract_SectorErase(TargetIndex, Address);
		break;
	case EraseBlock:
		EraseStatus = FlashAbstract_BlockErase(TargetIndex, Address);
		break;
	case EraseChip:
		EraseStatus = FlashAbstract_ChipErase(TargetIndex);
		break;
	default:
		break;
	}
	if (EraseStatus != S_OK)
	{
		Status = Error;
	}
	return true;
}

bool ProcessWriteBytes(void)
{
	u32 Address;
	u32 Length;
	u8* Buf = NULL;

	if (Status != Connected)
	{
		return false;;
	}

	UART_Receive(&Address, sizeof(Address));
	UART_Receive(&Length, sizeof(Length));

	if (Length)
	{
		Buf = (u8*)malloc(Length);

		if (Buf == NULL)
		{
			Status = Error;
			return true;
		}

		UART_Receive(Buf, Length);

		if (FlashAbstract_Program(TargetIndex, Address, Buf, Length) != S_OK)
		{
			Status = Error;
		}

		free(Buf);
		Buf = NULL;
	}

	return true;
}

bool ProcessReadBytes(void)
{
	u32 Address;
	u32 Length;

	if (Status != Connected)
	{
		return false;;
	}

	UART_Receive(&Address, sizeof(Address));
	UART_Receive(&Length, sizeof(Length));

	while (Length)
	{
		UART_SendByte(FlashAbstract_Readu8(TargetIndex, Address));
		Address++;
		Length--;
	}

	return true;
}

bool ProcessCheckBytes(void)
{
	u32 Address;
	u32 Length;
	u8 CheckSum = 0;

	if (Status != Connected)
	{
		return false;;
	}

	UART_Receive(&Address, sizeof(Address));
	UART_Receive(&Length, sizeof(Length));

	while (Length)
	{
		CheckSum ^= FlashAbstract_Readu8(TargetIndex, Address);
		Address++;
		Length--;
	}

	UART_SendByte(CheckSum);

	return true;
}

bool ProcessReadInformationBlock(void)
{
	FlashIndex Index;
	InformationStruct InfoStru;

	if (IndexByteToFlashIndex(UART_ReceiveByte(), &Index) != S_OK)
	{
		Index = NullFlash;
	}

	FlashAbstract_ReadInformationBlock(Index, &InfoStru);

	UART_Send(&InfoStru, sizeof(InfoStru));

	return true;
}

bool ProcessDisConnect(void)
{
	if (Status != Connected)
	{
		return false;;
	}

	Status = DisConnected;

	return true;
}

bool ProcessReset(void)
{
	KernelPowerDown();
	return false;
}

bool ProcessInvalid(void)
{
	UART_SendByte(InvalidInstruction);

	return true;
}
