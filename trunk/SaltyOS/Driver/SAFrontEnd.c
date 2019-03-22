#include "HAL\HCommon.h"
#include "HAL\UniGPIO.h"

/*Modify those if you want to use other ports*/
/************************************************************************************/
#define SAFrontEnd_LNA_Port 3
#define SAFrontEnd_LNA_LNA1_Pin 0
#define SAFrontEnd_LNA_LNA2_Pin 1
#define SAFrontEnd_DSA_Port 4
#define SAFrontEnd_DSA_C025_Pin 0
#define SAFrontEnd_DSA_C05_Pin 1
#define SAFrontEnd_DSA_C1_Pin 2
#define SAFrontEnd_DSA_C2_Pin 3
#define SAFrontEnd_DSA_C4_Pin 4
#define SAFrontEnd_DSA_C8_Pin 5
#define SAFrontEnd_DSA_C16_Pin 6
#define SAFrontEnd_DSA_LE_Pin 8
/************************************************************************************/

UniGPIO_Handle SAFrontEnd_LNA_LNA1_Handle;
UniGPIO_Handle SAFrontEnd_LNA_LNA2_Handle;
UniGPIO_Handle SAFrontEnd_DSA_C025_Handle;
UniGPIO_Handle SAFrontEnd_DSA_C05_Handle;
UniGPIO_Handle SAFrontEnd_DSA_C1_Handle;
UniGPIO_Handle SAFrontEnd_DSA_C2_Handle;
UniGPIO_Handle SAFrontEnd_DSA_C4_Handle;
UniGPIO_Handle SAFrontEnd_DSA_C8_Handle;
UniGPIO_Handle SAFrontEnd_DSA_C16_Handle;
UniGPIO_Handle SAFrontEnd_DSA_LE_Handle;
bool SAFrontEnd_Initialized = false;

STATUS SAFrontEnd_Init(void)
{
	if (SAFrontEnd_Initialized)
	{
		return S_OK;
	}

	GPIO_CPLD_InitPin(SAFrontEnd_LNA_Port, SAFrontEnd_LNA_LNA1_Pin, true, &SAFrontEnd_LNA_LNA1_Handle);
	GPIO_CPLD_InitPin(SAFrontEnd_LNA_Port, SAFrontEnd_LNA_LNA2_Pin, true, &SAFrontEnd_LNA_LNA2_Handle);

	GPIO_CPLD_InitPin(SAFrontEnd_DSA_Port, SAFrontEnd_DSA_C025_Pin, true, &SAFrontEnd_DSA_C025_Handle);
	GPIO_CPLD_InitPin(SAFrontEnd_DSA_Port, SAFrontEnd_DSA_C05_Pin, true, &SAFrontEnd_DSA_C05_Handle);
	GPIO_CPLD_InitPin(SAFrontEnd_DSA_Port, SAFrontEnd_DSA_C1_Pin, true, &SAFrontEnd_DSA_C1_Handle);
	GPIO_CPLD_InitPin(SAFrontEnd_DSA_Port, SAFrontEnd_DSA_C2_Pin, true, &SAFrontEnd_DSA_C2_Handle);
	GPIO_CPLD_InitPin(SAFrontEnd_DSA_Port, SAFrontEnd_DSA_C4_Pin, true, &SAFrontEnd_DSA_C4_Handle);
	GPIO_CPLD_InitPin(SAFrontEnd_DSA_Port, SAFrontEnd_DSA_C8_Pin, true, &SAFrontEnd_DSA_C8_Handle);
	GPIO_CPLD_InitPin(SAFrontEnd_DSA_Port, SAFrontEnd_DSA_C16_Pin, true, &SAFrontEnd_DSA_C16_Handle);
	GPIO_CPLD_InitPin(SAFrontEnd_DSA_Port, SAFrontEnd_DSA_LE_Pin, true, &SAFrontEnd_DSA_LE_Handle);

	SAFrontEnd_Initialized = true;

	return S_OK;
}

void SAFrontEnd_EnableLNA1(bool En)
{
	UniGPIO_SetVal(&SAFrontEnd_LNA_LNA1_Handle, En);
}

void SAFrontEnd_EnableLNA2(bool En)
{
	UniGPIO_SetVal(&SAFrontEnd_LNA_LNA2_Handle, En);
}

void SAFrontEnd_SetDSA(float Att)
{
	u8 IntAtt = Att * 4 + 0.5;
	assert(Att >= 0 - 0.0001 && Att <= 31.75 + 0.0001);//In case of float point error
	UniGPIO_SetVal(&SAFrontEnd_DSA_C025_Handle, IntAtt & 0x1);
	UniGPIO_SetVal(&SAFrontEnd_DSA_C05_Handle, IntAtt & 0x2);
	UniGPIO_SetVal(&SAFrontEnd_DSA_C1_Handle, IntAtt & 0x4);
	UniGPIO_SetVal(&SAFrontEnd_DSA_C2_Handle, IntAtt & 0x8);
	UniGPIO_SetVal(&SAFrontEnd_DSA_C4_Handle, IntAtt & 0x10);
	UniGPIO_SetVal(&SAFrontEnd_DSA_C8_Handle, IntAtt & 0x20);
	UniGPIO_SetVal(&SAFrontEnd_DSA_C16_Handle, IntAtt & 0x40);
	HAL_Delay(1);
	UniGPIO_SetHigh(&SAFrontEnd_DSA_LE_Handle);
	HAL_Delay(1);
	UniGPIO_SetLow(&SAFrontEnd_DSA_LE_Handle);
}
