#include "Kernel\Common\KCommon.h"
#include "MultiInstDriver\ADF4351.h"

ADF4351_Handle ADF4351TestHandle;

void ADF4351Test(void)
{
	static bool Inited = false;
	if (!Inited)
	{
		UniGPIO_Handle MOSIPin;
		UniGPIO_Handle SCKPin;
		UniGPIO_Handle LEPin;
		UniGPIO_Handle CEPin;
		UniGPIO_Handle LDPin;
		UniGPIO_Handle PDBRFPin;
		UniGPIO_Handle MuxOutPin;
		Inited = true;
		GPIO_CPLD_InitPin(0, 6, true, &MOSIPin);
		GPIO_CPLD_InitPin(0, 8, true, &SCKPin);
		GPIO_CPLD_InitPin(0, 0, true, &LEPin);
		GPIO_CPLD_InitPin(0, 1, true, &CEPin);
		GPIO_CPLD_InitPin(0, 3, false, &LDPin);
		GPIO_CPLD_InitPin(0, 4, true, &PDBRFPin);
		GPIO_CPLD_InitPin(0, 7, false, &MuxOutPin);
		ADF4351_Init(&ADF4351TestHandle, 5.1, &MOSIPin, &SCKPin, &LEPin, &CEPin, &LDPin, &PDBRFPin, &MuxOutPin);
		ADF4351_SetPDFrequency(&ADF4351TestHandle, 10000000.0, 1000000.0);
		ADF4351_PFD_ChargePump_Param CPParam;
		CPParam.AntibacklashPulseWidth = ABP_6ns_FRAC_N;
		CPParam.BandSelect = true;
		CPParam.ChargeCancelation = true;
		CPParam.ClkDividerMode = FastLockEnable;
		CPParam.ClockDivider = 20;
		CPParam.CSREnable = true;
		CPParam.Current = 0.3;
		CPParam.FeedBackSelect = FeedBack_Fundamental;
		CPParam.Polarity = true;
		CPParam.TriState = false;
		ADF4351_SetPFD_ChargePumpParam(&ADF4351TestHandle, &CPParam);
		ADF4351_SetMuxOut(&ADF4351TestHandle, DGND);
		ADF4351_SetModulus(&ADF4351TestHandle, 4000);
		//ADF4351_SetOutputAFrequency(&ADF4351TestHandle, 10000000.0, 800000000.0, true);
		ADF4351_SetOutputAFrequency(&ADF4351TestHandle, 10000000.0, 1000 * 1000000.0, true);
		ADF4351_Update(&ADF4351TestHandle);
	}
	//static float i = 100.0;
	//HAL_Delay(1000);
	//ADF4351_SetVCOFrequency(&ADF4351TestHandle, 10000000.0, i * 1000000 * 4);
	//ADF4351_SetOutputAFrequency(&ADF4351TestHandle, 10000000.0, i * 1000000.0, true);
	//ADF4351_SetOutputAFrequency(&ADF4351TestHandle, 10000000.0, 100.12345 * 1000000.0, true);
	//ADF4351_Update(&ADF4351TestHandle);
	//i += 10;
	//if (i > 200.0)
	//{
		//i = 100.0;
	//}
}
