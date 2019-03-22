#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "Driver\KeyBoard.h"
#include "Kernel\Input\KeyCode.h"
#include "Driver\LowLevelGraphic.h"
#include "Kernel\FlashFS\FlashFS.h"
#include "HAL\Beep.h"
#include <assert.h>

#define KeyCount 255
#define KeyArrayIndexMax KeyCount + 1
#define MapFileMagicNumber 0x11223344
const pcstr MapFileName = "Key.map";

typedef struct
{
	u8 DefaultScanCode;
	pcstr Description;
	KEYCODE Code;
}KeyDefinition;

KeyDefinition KeyDefs[] = {
	{ 1,"KEYM1",KEY_M1 },
	{ 2,"KEYM2",KEY_M2 },
	{ 3,"KEYM3",KEY_M3 },
	{ 4,"KEYM4",KEY_M4 },
	{ 5,"KEYM5",KEY_M5 },
	{ 6,"PageUp",KEY_UP },
	{ 7,"PageDown",KEY_DOWN },
	{ 8,"KEY1",KEY_1 },
	{ 9,"KEY2",KEY_2 },
	{ 10,"KEY3",KEY_3 },
	{ 11,"KEY4",KEY_4 },
	{ 12,"KEY5",KEY_5 },
	{ 13,"KEY6",KEY_6 },
	{ 14,"KEY7",KEY_7 },
	{ 15,"KEY8",KEY_8 },
	{ 16,"KEY9",KEY_9 },
	{ 17,"KEY0",KEY_0 },
	{ 18,"KEY_DOT",KEY_DOT },
	{ 19,"KEY_BACK",KEY_BACK },
	{ 20,"LeftEncoder",KEY_ENCL },
	{ 21,"RightEncoder",KEY_ENCR },
	{ 22,"Esc",KEY_ESC },
	{ 23,"Reserved",KEY_RESERVED },
};

KEYCODE KeyFunctionMap[KeyArrayIndexMax];

void KeyBoardMap_WaitForRemapInstruction(void);
void KeyBoardMap_Remap(void);
STATUS KeyBoardMap_SaveKeyMap(void);
STATUS KeyBoardMap_LoadKeyMap(void);
STATUS KeyBoardMap_LoadDefaultKeyMap(void);

STATUS KeyBoardMap_Init(void)
{
	for (u16 i = 0; i < KeyArrayIndexMax; i++)
	{
		KeyFunctionMap[i] = KEY_Invalid;
	}
	if (KeyBoardMap_LoadKeyMap() != S_OK)
	{
		KeyBoardMap_LoadDefaultKeyMap();
		KeyBoardMap_SaveKeyMap();
	}
	KeyBoardMap_WaitForRemapInstruction();
	return S_OK;
}

void KeyBoardMap_WaitForRemapInstruction(void)
{
	u32 EndTime;
	LLGraphic_DrawString("Press any key in 0.5s to start keyboard calibration.", 0, 0, 0xFFFF, 0x0000);
	EndTime = HAL_GetTick() + 100;
	while (HAL_GetTick() < EndTime)
	{
		KeyBoard_GetKey_Single();//Clear any pending keys
	}
	EndTime = HAL_GetTick() + 500;
	while (HAL_GetTick() < EndTime)
	{
		if (KeyBoard_GetKey_Single())
		{
			Beep(100);
			LLGraphic_DrawString("                                                    ", 0, 0, 0xFFFF, 0x0000);
			KeyBoardMap_Remap();
			break;
		}
	}
	LLGraphic_DrawString("                                                    ", 0, 0, 0xFFFF, 0x0000);
}

void KeyBoardMap_Remap(void)
{
	LLGraphic_DrawString("Keyboard calibration will start in 2 second.", 0, 0, 0xFFFF, 0x0000);
	LLGraphic_DrawString("Please release all keys.", 0, 16, 0xFFFF, 0x0000);
	HAL_Delay(2000);
	LLGraphic_DrawString("Please press key:                           ", 0, 0, 0xFFFF, 0x0000);
	LLGraphic_DrawString("                        ", 0, 16, 0xFFFF, 0x0000);
	for (u16 i = 0; i < KeyArrayIndexMax; i++)
	{
		KeyFunctionMap[i] = KEY_Invalid;
	}
	for (u16 i = 0; i < sizeof(KeyDefs) / sizeof(KeyDefinition); i++)
	{
		u8 KeyScanCode = 0;
		LLGraphic_DrawString(KeyDefs[i].Description, 0, 16, 0xFFFF, 0x0000);
		do
		{
			KeyScanCode = KeyBoard_GetKey_Single();
		} while (KeyScanCode == 0);
		Beep(100);
		if (KeyScanCode < KeyArrayIndexMax)
		{
			KeyFunctionMap[KeyScanCode] = KeyDefs[i].Code;
		}
		LLGraphic_DrawString(KeyDefs[i].Description, 0, 16, 0x0000, 0x0000);
	}
	LLGraphic_DrawString("Saving key map...                           ", 0, 0, 0xFFFF, 0x0000);
	KeyBoardMap_SaveKeyMap();
	LLGraphic_DrawString("                                            ", 0, 0, 0xFFFF, 0x0000);
}

STATUS KeyBoardMap_SaveKeyMap(void)
{
	u32 WrongMagicNumber = 0;
	u32 MagicNumber = MapFileMagicNumber;
	//First erase the original magic number to mark the file is incomplete.
	if (FlashFS_Write(MapFileName, &WrongMagicNumber, 0, 4, NULL) == S_OK)
	{
		//Write file contents.
		if (FlashFS_Write(MapFileName, KeyFunctionMap, 4, sizeof(KeyFunctionMap), NULL) == S_OK)
		{
			//Write correct magic number to mark the file is valid.
			if (FlashFS_Write(MapFileName, &MagicNumber, 0, 4, NULL) == S_OK)
			{
				return S_OK;
			}
		}
	}
	return S_FAIL;
}

STATUS KeyBoardMap_LoadKeyMap(void)
{
	u32 CurrentFileMagicNumber = 0;
	if (FlashFS_Read(MapFileName, &CurrentFileMagicNumber, 0, 4, NULL) == S_OK && CurrentFileMagicNumber == MapFileMagicNumber)
	{
		return FlashFS_Read(MapFileName, KeyFunctionMap, 4, sizeof(KeyFunctionMap), NULL);
	}
	else
	{
		return S_FAIL;
	}
}

STATUS KeyBoardMap_LoadDefaultKeyMap(void)
{
	for (u16 i = 0; i < KeyArrayIndexMax; i++)
	{
		KeyFunctionMap[i] = KEY_Invalid;
	}
	for (u16 i = 0; i < sizeof(KeyDefs) / sizeof(KeyDefinition); i++)
	{
		u8 DefaultScanCode = KeyDefs[i].DefaultScanCode;
		assert(DefaultScanCode != 0);
		assert(DefaultScanCode < KeyArrayIndexMax);
		if (DefaultScanCode != 0 && DefaultScanCode < KeyArrayIndexMax)
		{
			KeyFunctionMap[KeyDefs[i].DefaultScanCode] = KeyDefs[i].Code;
		}
	}
	return S_OK;
}

KEYCODE KeyBoardMap_GetKey(void)
{
	u8 KeyScanCode = KeyBoard_GetKey_Repeat();
	if (KeyScanCode < KeyArrayIndexMax)
	{
		return KeyFunctionMap[KeyScanCode];
	}
	else
	{
		return KEY_Invalid;
	}
}
