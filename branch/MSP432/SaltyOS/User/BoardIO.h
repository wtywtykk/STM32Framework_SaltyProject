#pragma once

void BoardIO_Init(void);
void BoardIO_SetChannelAC(u8 Ch, bool AC);
void BoardIO_SetChannelTrigAC(u8 Ch, bool AC);
void BoardIO_SetDAC(u8 Ch, u16 Val);
void BoardIO_SetPGA(u8 Ch, u8 Gain);
void BoardIO_SetFilter(bool HighBW);
