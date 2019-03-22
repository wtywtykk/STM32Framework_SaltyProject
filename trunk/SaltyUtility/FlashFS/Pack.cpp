// Pack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <malloc.h>
#include <list>
#include <assert.h>

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
	FileRecord Record;
	char* Data;
}FileRecordAndData;

typedef list<FileRecordAndData> FileListType;
FileListType FileList;

void FillNameHash(FileRecord* Record)
{
	u16 Result = 0;
	pstr Name = Record->Name;
	while (*Name)
	{
		Result ^= *(u16*)Name;
		if (*(Name + 1) == 0)
		{
			break;
		}
		Name += 2;
	}
	Record->NameHash = Result;
}

void FillChecksum(FileRecord* Record)
{
	static_assert(sizeof(FileRecord) % sizeof(Record->Checksum) == 0, "FileRecord must be aligned to u16 to calculate the checksum");
	u16 ChecksumResult = 0;
	u16* DataPtr = (u16*)Record;
	Record->Checksum = 0;
	for (u16 i = 0; i < sizeof(FileRecord); i += sizeof(u16))
	{
		ChecksumResult ^= *DataPtr;
		DataPtr++;
	}
	Record->Checksum = ChecksumResult;
}

void GetDataAndFillRecord(FileRecordAndData* RecAndData, pstr FileName)
{
	//So lazy can't move....so there are no cleanups.....
	FILE* DataFile;
	long FileSize;
	fopen_s(&DataFile, FileName, "rb");
	if (DataFile == NULL)
	{
		cout << "Can not open " << FileName << endl;
		abort();
	}
	//Get file size
	fseek(DataFile, 0L, SEEK_END);
	FileSize = ftell(DataFile);
	rewind(DataFile);
	if (FileSize == 0)
	{
		cout << "The size of " << FileName << " is zero" << endl;
		abort();
	}

	memset(RecAndData->Record.Name, 0xFFFFFFFF, 16);
	strncpy_s(RecAndData->Record.Name, 16, FileName, _TRUNCATE);
	FillNameHash(&RecAndData->Record);
	RecAndData->Record.Size = FileSize;

	RecAndData->Data = (char*)malloc(FileSize);
	fread_s(RecAndData->Data, FileSize, sizeof(char), FileSize, DataFile);
	fclose(DataFile);
}

void WalkThoughAndCalculateAddress(void)
{
	u32 RecordSize = FileList.size() * sizeof(FileRecord);
	u32 DataAddr = RecordSize;
	for (FileListType::iterator it = FileList.begin(); it != FileList.end(); it++)
	{
		(*it).Record.Start = DataAddr;
		DataAddr += (*it).Record.Size;
	}
}

void WritePackFile(void)
{
	FILE* PackFile;
	_tfopen_s(&PackFile, _T("FlashFSPack.bin"), _T("wb+"));
	if (PackFile)
	{
		for (FileListType::iterator it = FileList.begin(); it != FileList.end(); it++)
		{
			FillChecksum(&(*it).Record);
			fwrite(&(*it).Record, sizeof(FileRecord), 1, PackFile);
		}
		for (FileListType::iterator it = FileList.begin(); it != FileList.end(); it++)
		{
			fwrite((*it).Data, sizeof(char), (*it).Record.Size, PackFile);
		}

		fclose(PackFile);
	}
	else
	{
		cout << "unable to open output file" << endl;
	}
}

int main()
{
#define PathBufferSize 256
	char ListBuf[PathBufferSize];
	FILE* ListFile;
	_tfopen_s(&ListFile, _T("List.txt"), _T("r"));
	if (ListFile)
	{
		while (fscanf_s(ListFile, "%s\n\r", ListBuf, PathBufferSize) == 1)
		{
			FileRecordAndData RecAndData;
			cout << "Peocessing " << ListBuf << endl;
			memset(&RecAndData, 0, sizeof(RecAndData));
			GetDataAndFillRecord(&RecAndData, ListBuf);
			FileList.push_back(RecAndData);
		}
		{
			//Push the termination record
			FileRecordAndData RecAndData;
			memset(&RecAndData, 0, sizeof(RecAndData));
			FileList.push_back(RecAndData);
		}

		cout << "Update addressed" << endl;
		WalkThoughAndCalculateAddress();
		cout << "Writing output" << endl;
		WritePackFile();

		fclose(ListFile);
	}
	else
	{
		cout << "unable to find list file" << endl;
	}
	system("pause");
	return 0;
}
