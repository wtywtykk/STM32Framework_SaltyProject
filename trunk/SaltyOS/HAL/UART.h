#pragma once

C_HEADER_BEGIN

STATUS UART_Init(void);
void UART_SendByte(u8 Data);
void UART_Send(const void* Data, u32 Length);
u8 UART_ReceiveByte(void);
void UART_Receive(void* Buffer, u32 Length);
bool UART_CheckAvailable(void);

C_HEADER_END
