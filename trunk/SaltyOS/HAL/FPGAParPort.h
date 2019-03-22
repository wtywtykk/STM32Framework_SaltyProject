#pragma once

C_HEADER_BEGIN

STATUS FPGAParPort_Init(void);
STATUS ParPort_StartPipeline(void);
STATUS ParPort_Read(u16* Buffer, u32 BufferSizeInWord, u32* ReadSize, bool WaitForBusy);
STATUS FPGAParPort_WaitBusy(u32 TimeOut);
bool FPGAParPort_IsReady(void);
STATUS FPGAParPort_WaitReady(u32 TimeOut);
void FPGAParPort_Reset(void);
bool FPGAParPort_ReadIO4(void);

C_HEADER_END
