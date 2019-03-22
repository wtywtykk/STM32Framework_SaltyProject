#pragma once

C_HEADER_BEGIN

STATUS FPGASPIPort_Init(void);
STATUS FPGASPIPort_Transmit(void* Buffer, u16 Size);
STATUS FPGASPIPort_Receive(void* Buffer, u16 Size);
void FPGASPIPort_Reset(void);
bool FPGASPIPort_ReadIO2(void);

C_HEADER_END
