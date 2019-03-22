#pragma once

STATUS FlashFS_Init(void);
STATUS FlashFS_Read(pcstr Name, void* Buf, u32 Start, u32 Size, u32* BytesRead);
STATUS FlashFS_Write(pcstr Name, void* Buf, u32 Start, u32 Size, u32* BytesWritten);
