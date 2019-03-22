#pragma once

C_HEADER_BEGIN

STATUS TLV5617_Init(void);
void TLV5617_SetChannelA(u16 Value);
void TLV5617_SetChannelB(u16 Value);
void TLV5617_SetChannelAB(u16 ValueA, u16 ValueB);
void TLV5617_SetSpeed(bool FastMode);
void TLV5617_Shutdown(void);

C_HEADER_END
