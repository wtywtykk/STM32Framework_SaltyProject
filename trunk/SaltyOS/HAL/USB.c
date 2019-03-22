#include "HCommon.h"
#include <usbd_core.h>
#include "usbd_desc.h"
#include <usbd_cdc.h>
#include "usbd_cdc_if.h"

USBD_HandleTypeDef USBD_Device;
static bool USB_Initialized = false;

extern PCD_HandleTypeDef hpcd;

STATUS USB_Init(void)
{
	if (USB_Initialized)
	{
		return S_OK;
	}

	if (USBD_Init(&USBD_Device, &VCP_Desc, 0) != USBD_OK)
	{
		return S_FAIL;
	}
	if (USBD_RegisterClass(&USBD_Device, &USBD_CDC) != USBD_OK)
	{
		return S_FAIL;
	}
	if (USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_USBCDC_fops) != USBD_OK)
	{
		return S_FAIL;
	}
	if (USBD_Start(&USBD_Device) != USBD_OK)
	{
		return S_FAIL;
	}

	USB_Initialized = 1;

	return S_OK;
}

void USB_Restart(void)
{
	USBD_Stop(&USBD_Device);
	USBD_Start(&USBD_Device);
}

void USB_IRQHandler(void)
{
	HAL_PCD_IRQHandler(&hpcd);
}
