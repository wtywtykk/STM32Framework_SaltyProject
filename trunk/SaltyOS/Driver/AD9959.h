#pragma once

C_HEADER_BEGIN

STATUS AD9959_Init(void);
double AD9959_SetChannelFrequency(u8 Channel, double Freq);

C_HEADER_END
