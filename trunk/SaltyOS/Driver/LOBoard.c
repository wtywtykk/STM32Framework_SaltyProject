#include "HAL\HCommon.h"
#include "HAL\UniGPIO.h"
#include "HAL\StandardSPIPort.h"
#include "HAL\UniSPI.h"
#include "Driver\LOBoard.h"

#define LOBoard_TransmitTimeout 10

typedef union
{
	struct
	{
		u32 ControlWord;
		float Freq;
	}MOSIData;
	u8 MISOData[8];
}LOBoardSPIStruct;

#define LOBoard_CW_Reset (1<<0)
#define LOBoard_CW_ExtRef (1<<1)

UniGPIO_Handle LOBoard_MOSI;
UniGPIO_Handle LOBoard_MISO;
UniGPIO_Handle LOBoard_SCK;
UniGPIO_Handle LOBoard_CS;
UniGPIO_Handle LOBoard_SIG0;
UniSPI_Handle LOBoardSPI_Handel;
LOBoardSPIStruct LOBoardRegs;
bool LOBoard_Initialized = false;

STATUS LOBoard_Init(void)
{
	if (LOBoard_Initialized)
	{
		return S_OK;
	}

	LOBoardRegs.MOSIData.ControlWord = 0;
	LOBoardRegs.MOSIData.Freq = 0;

	StandardSPIPort_Init(3, &LOBoard_MISO, &LOBoard_MOSI, &LOBoard_SCK, &LOBoard_CS, &LOBoard_SIG0, NULL, NULL, NULL, NULL);
	SoftSPI_Init(&LOBoardSPI_Handel, &LOBoard_MISO, &LOBoard_MOSI, &LOBoard_SCK, 8, false, false, 2, 1);

	LOBoard_Initialized = true;

	return S_OK;
}

void LOBoard_UpdateReg(void)
{
	LOBoardSPIStruct CommBuf = LOBoardRegs;
	UniSPI_TransmitReceive(&LOBoardSPI_Handel, &LOBoard_CS, &CommBuf, sizeof(CommBuf), LOBoard_TransmitTimeout);
}

void LOBoard_SetFreq(float Freq)
{
	LOBoardRegs.MOSIData.Freq = Freq;
	LOBoard_UpdateReg();
}

void LOBoard_Reset(void)
{
	LOBoardRegs.MOSIData.ControlWord |= LOBoard_CW_Reset;
	LOBoard_UpdateReg();
	HAL_Delay(1000);
	LOBoardRegs.MOSIData.ControlWord &= ~LOBoard_CW_Reset;
	LOBoard_UpdateReg();
}

void LOBoard_SetExtRef(bool Val)
{
	if (Val)
	{
		LOBoardRegs.MOSIData.ControlWord |= LOBoard_CW_ExtRef;
	}
	else
	{
		LOBoardRegs.MOSIData.ControlWord &= ~LOBoard_CW_ExtRef;
	}
	LOBoard_UpdateReg();
}
