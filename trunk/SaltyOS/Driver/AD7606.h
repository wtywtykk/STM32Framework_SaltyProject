#pragma once

C_HEADER_BEGIN

STATUS AD7606_Init(void);
void AD7606_Standby(void);
void AD7606_Wakeup(void);
void AD7606_ConvertA(void);
void AD7606_ConvertB(void);
void AD7606_ConvertBoth(void);
bool AD7606_IsBusy(void);
void AD7606_Wait(void);
s16 AD7606_GetResult(u16 Index);

C_HEADER_END
