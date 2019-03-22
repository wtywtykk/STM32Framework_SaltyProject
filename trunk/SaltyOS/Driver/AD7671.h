#pragma once

C_HEADER_BEGIN

STATUS AD7671_Init(void);
void AD7671_Standby(void);
void AD7671_Wakeup(void);
void AD7671_SetImpulseMode(void);
void AD7671_SetWarpMode(void);
void AD7671_SetNormalMode(void);
void AD7671_SetParallel(void);
void AD7671_SetFormatBinary(void);
void AD7671_SetFormatTwosComp(void);
void AD7671_SetSampleDivideFactor(u16 DivideFactor);
u16 AD7671_GetBnaryResult(void);
s16 AD7671_GetTwosCompResult(void);
STATUS AD7671_SetAutoMode(void);
STATUS AD7671_SetClockedMode(void);
STATUS AD7671_SetClkDiv(u16 Factor);

C_HEADER_END
