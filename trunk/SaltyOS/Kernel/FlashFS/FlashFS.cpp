#include "Kernel\Common\KCommon.h"
#include "Driver\W25Qxx.h"
#include <string.h>

#define CacheCount 16
#define CacheLife_Init 5
#define CacheLife_Min 0
#define CacheLife_Max 32

typedef struct
{
	u16 Checksum;
	u16 NameHash;
	char Name[32];
	u32 Start;
	u32 Size;
}FileRecord;

typedef struct
{
	FileRecord File;
	u8 CacheLife;
}CacheRecord;

CacheRecord* Cache[CacheCount];
FileRecord TempFileRecord;
bool FlashFS_Initialized = false;

STATUS FlashFS_Init(void)
{
	u8 i;

	if (FlashFS_Initialized)
	{
		return S_OK;
	}

	for (i = 0; i < CacheCount; i++)
	{
		Cache[i]->File.NameHash = 0;
		memset(Cache[i]->File.Name, 0, sizeof(Cache[i]->File.Name));
		Cache[i]->File.Start = 0;
		Cache[i]->File.Size = 0;
		Cache[i]->CacheLife = 0;
	}

	FlashFS_Initialized = true;

	return S_OK;
}

u16 CalcNameHash(pcstr Name)
{
	u16 Result = 0;
	while (*Name)
	{
		Result ^= *(u16*)Name;
		if (*(Name + 1) == 0)
		{
			break;
		}
		Name += 2;
	}
	return Result;
}

bool VerifyChecksum(FileRecord* Record)
{
	static_assert(sizeof(FileRecord) % sizeof(Record->Checksum) == 0, "FileRecord must be aligned to u16 to calculate the checksum");
	u16 ChecksumResult = 0;
	u16* DataPtr = (u16*)Record;
	for (u16 i = 0; i < sizeof(FileRecord); i += sizeof(u16))
	{
		ChecksumResult ^= *DataPtr;
		DataPtr++;
	}
	//The Checksum element is the XORed value of all OTHER elements.
	//If the Checksum matches, the result will be 0.
	if (ChecksumResult == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

STATUS FetchRecordFromFlash(u32 RecordIndex, FileRecord* Record)
{
	u16 Tries = 3;
	u32 RecordAddr = RecordIndex * sizeof(FileRecord);
	while (Tries)
	{
		if (W25Qxx_Read(RecordAddr, Record, sizeof(FileRecord)) == S_OK)
		{
			if (VerifyChecksum(Record))
			{
				return S_OK;
			}
		}
		Tries--;
	}
	return S_FAIL;
}

bool IsRecordMatch(FileRecord* Record, u16 NameHash, pcstr Name)
{
	if (Record->NameHash == NameHash)
	{
		if (strcmp(Record->Name, Name) == 0)
		{
			return true;
		}
	}
	return false;
}

STATUS FindRecordFromFlash(FileRecord* Record, u16 NameHash, pcstr Name)
{
	u32 RecordIndex = 0;
	do
	{
		if (FetchRecordFromFlash(RecordIndex, Record) != S_OK)
		{
			return false;
		}
		RecordIndex++;
	} while (IsRecordMatch(Record, NameHash, Name) == false && Record->Size != 0);
	if (Record->Size)
	{
		return S_OK;
	}
	else
	{
		return S_FAIL;
	}
}

FileRecord* FindRecord(pcstr Name)
{
	u16 FirstInvalidCache = 0xFFFF;
	FileRecord* File = NULL;
	u16 NameHash = CalcNameHash(Name);
	for (u16 i = 0; i < CacheCount; i++)
	{
		if (IsRecordMatch(&Cache[i]->File, NameHash, Name))
		{
			if (Cache[i]->CacheLife < CacheLife_Max)
			{
				Cache[i]->CacheLife++;
			}
			File = &Cache[i]->File;
		}
		else
		{
			if (Cache[i]->CacheLife > CacheLife_Min)
			{
				Cache[i]->CacheLife--;
			}
			if (Cache[i]->CacheLife == CacheLife_Min && FirstInvalidCache == 0xFFFF)
			{
				FirstInvalidCache = i;
			}
		}
	}
	if (File == NULL)
	{
		if (FindRecordFromFlash(&TempFileRecord, NameHash, Name) == S_OK)
		{
			if (FirstInvalidCache != 0xFFFF)
			{
				memcpy(&Cache[FirstInvalidCache]->File, &TempFileRecord, sizeof(FileRecord));
				Cache[FirstInvalidCache]->CacheLife = CacheLife_Init;
			}
			File = &TempFileRecord;
		}
	}
	return File;
}

STATUS FlashFS_Read(pcstr Name, void* Buf, u32 Start, u32 Size, u32* BytesRead)
{
	FileRecord* Rec = FindRecord(Name);
	if (Rec)
	{
		u32 RealSize = Size;
		if (Start + RealSize > Rec->Size)
		{
			RealSize = Rec->Size - Start;
		}
		W25Qxx_Read(Rec->Start + Start, Buf, RealSize);
		if (BytesRead)
		{
			*BytesRead = RealSize;
		}
		return S_OK;
	}
	return S_FAIL;
}

STATUS FlashFS_Write(pcstr Name, void* Buf, u32 Start, u32 Size, u32* BytesWritten)
{
	FileRecord* Rec = FindRecord(Name);
	if (Rec)
	{
		u32 RealSize = Size;
		if (Start + RealSize > Rec->Size)
		{
			RealSize = Rec->Size - Start;
		}
		W25Qxx_Program_Safe(Rec->Start + Start, Buf, RealSize);
		if (BytesWritten)
		{
			*BytesWritten = RealSize;
		}
		return S_OK;
	}
	return S_FAIL;
}
