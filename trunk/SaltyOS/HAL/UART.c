#include "HCommon.h"
#include "USB.h"
#include "usbd_cdc_if.h"

static bool UART_Initialized = false;

STATUS UART_Init(void)
{
	if (UART_Initialized)
	{
		return S_OK;
	}

	if (USB_Init() != S_OK)
	{
		return S_FAIL;
	}

	UART_Initialized = true;

	return S_OK;
}

void UART_SendByte(u8 Data)
{
	VCP_write(&Data, sizeof(Data));
}

void UART_Send(const void* Data, u32 Length)
{
	VCP_write(Data, Length);
}

u8 UART_ReceiveByte(void)
{
	u8 Data;
	while (VCP_read(&Data, 1) == 0);
	return Data;
}

void UART_Receive(void* Buffer, u32 Length)
{
	while (Length)
	{
		u32 NumOfBytesReceived = VCP_read(Buffer, Length);
		Buffer = (u8*)Buffer + NumOfBytesReceived;
		Length -= NumOfBytesReceived;
	}
}

bool UART_CheckAvailable(void)
{
	return VCP_getlen() ? true : false;
}
