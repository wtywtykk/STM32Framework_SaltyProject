#pragma once

#include "User\LoadRecogniseContext.h"

#define LoadCount 5

void LoadRecogniseEngine_ExtractRandomalizedCharacteristic(RandomizedLoadCharacteristic* RandChar, LoadCharacteristic* Char, u8 Count);
void LoadRecogniseEngine_CheckStateChange(void);
bool LoadRecogniseEngine_GetState(u8 Index);
void LoadRecogniseEngine_Learn(u8 Index, LoadCharacteristic* Char, u8 Count);
void LoadRecogniseEngine_Remove(u8 Index);
void LoadRecogniseEngine_LoadData(void);
STATUS LoadRecogniseEngine_SaveData(void);
