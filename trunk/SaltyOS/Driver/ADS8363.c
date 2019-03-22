#include "HAL\HCommon.h"
#include "HAL\PeripheralBus.h"
#include "HAL\UniGPIO.h"
#include "Driver\ADS8363.h"

static bool ADS8363_Initialized = false;
static u16 ADS8363_ChipConfigWord = 0;

//Requires dedicated function block in cpld
STATUS ADS8363_Init(void)
{
	if (ADS8363_Initialized)
	{
		return S_OK;
	}
	PeripheralBus_Write(PeripheralBus_Config, PeripheralBus_Read(PeripheralBus_Config) | PeripheralBus_ConfigBit_DedicatedFunctionUsed);

	if (PeripheralBus_Read(AD8363_Offset_ID) == AD8363_IDValue)
	{
		PeripheralBus_Write(AD8363_Offset_Config, AD8363_ConfigBit_Reset);
		PeripheralBus_Write(AD8363_Offset_Config, 0);
		ADS8363_ChipConfigWord = 0x1020;
		PeripheralBus_Write(AD8363_Offset_Send, ADS8363_ChipConfigWord | AD8363_REGACCESS_SOFTRESET);
		PeripheralBus_Write(AD8363_Offset_Send, ADS8363_ChipConfigWord);

		ADS8363_Initialized = true;

		return S_OK;
	}
	return S_FAIL;
}

bool ADS8363_IsReady(void)
{
	if (PeripheralBus_Read(AD8363_Offset_Status) & AD8363_StatusBit_Ready)
	{
		return true;
	}
	else
	{
		return false;
	}
}

STATUS ADS8363_WaitReady(void)
{
	while (!(PeripheralBus_Read(AD8363_Offset_Status) & AD8363_StatusBit_Ready));
	return S_OK;
}

STATUS ADS8363_GetResult(s16* ChA, s16* ChB)
{
	while (!(PeripheralBus_Read(AD8363_Offset_Status) & AD8363_StatusBit_Ready));
	if (ChA)
	{
		*ChA = PeripheralBus_Read(AD8363_Offset_ChA);
	}
	if (ChB)
	{
		*ChB = PeripheralBus_Read(AD8363_Offset_ChB);
	}
	return S_OK;
}

STATUS ADS8363_SetChannel(u8 Index)
{
	assert(Index <= 3);
	ADS8363_ChipConfigWord = ADS8363_ChipConfigWord & ~AD8363_CHANNEL_MASK;
	ADS8363_ChipConfigWord |= (Index << AD8363_CHANNEL_SHIFT) & AD8363_CHANNEL_MASK;
	PeripheralBus_Write(AD8363_Offset_Send, ADS8363_ChipConfigWord);

	return S_OK;
}

STATUS ADS8363_SetPseudoDifferential(bool PseudoDiff)
{
	ADS8363_ChipConfigWord = ADS8363_ChipConfigWord & ~AD8363_PSEUDO_DIFFERENTIAL_MASK;
	if (PseudoDiff)
	{
		ADS8363_ChipConfigWord |= AD8363_PSEUDO_DIFFERENTIAL_MASK;
	}
	PeripheralBus_Write(AD8363_Offset_Send, ADS8363_ChipConfigWord);

	return S_OK;
}

STATUS ADS8363_SetREFDAC1(bool PowerDown, float Value)
{
	u16 Code = Value * 1024 / 2.5 - 1;
	assert(Value <= 2.5 && Value > 0);
	Code &= AD8363_REFDACVALUE_MASK;
	if (PowerDown)
	{
		Code |= AD8363_REFDACPOWERDOWN_MASK;
	}
	while (ADS8363_IsReady());
	ADS8363_WaitReady();
	PeripheralBus_Write(AD8363_Offset_Send, ADS8363_ChipConfigWord | AD8363_REGACCESS_REFDAC1);
	while (ADS8363_IsReady());
	ADS8363_WaitReady();
	PeripheralBus_Write(AD8363_Offset_Send, Code);
	while (ADS8363_IsReady());
	ADS8363_WaitReady();
	PeripheralBus_Write(AD8363_Offset_Send, ADS8363_ChipConfigWord);

	return S_OK;
}

STATUS ADS8363_SetREFDAC2(bool PowerDown, float Value)
{
	u16 Code = Value * 1024 / 2.5 - 1;
	assert(Value <= 2.5 && Value > 0);
	Code &= AD8363_REFDACVALUE_MASK;
	if (PowerDown)
	{
		Code |= AD8363_REFDACPOWERDOWN_MASK;
	}
	while (ADS8363_IsReady());
	ADS8363_WaitReady();
	PeripheralBus_Write(AD8363_Offset_Send, ADS8363_ChipConfigWord | AD8363_REGACCESS_REFDAC2);
	while (ADS8363_IsReady());
	ADS8363_WaitReady();
	PeripheralBus_Write(AD8363_Offset_Send, Code);
	while (ADS8363_IsReady());
	ADS8363_WaitReady();
	PeripheralBus_Write(AD8363_Offset_Send, ADS8363_ChipConfigWord);

	return S_OK;
}

STATUS ADS8363_SetREFCM(u16 Val)
{
	while (ADS8363_IsReady());
	ADS8363_WaitReady();
	PeripheralBus_Write(AD8363_Offset_Send, ADS8363_ChipConfigWord | AD8363_REGACCESS_REFCM);
	while (ADS8363_IsReady());
	ADS8363_WaitReady();
	PeripheralBus_Write(AD8363_Offset_Send, Val);
	while (ADS8363_IsReady());
	ADS8363_WaitReady();
	PeripheralBus_Write(AD8363_Offset_Send, ADS8363_ChipConfigWord);

	return S_OK;
}
