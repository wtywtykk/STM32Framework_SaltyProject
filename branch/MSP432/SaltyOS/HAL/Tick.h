#pragma once

C_HEADER_BEGIN

STATUS Tick_Init(void);
void HAL_Delay(u32 Interval);
u32 HAL_GetTick(void);

C_HEADER_END
