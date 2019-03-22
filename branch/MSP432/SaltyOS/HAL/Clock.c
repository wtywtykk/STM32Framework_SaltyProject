#include "HCommon.h"

static bool Clock_Initialized = false;

STATUS Clock_Init(void)
{
	PCM_setCoreVoltageLevel(PCM_VCORE1);
	PCM_setPowerState(PCM_AM_LDO_VCORE1);

	FlashCtl_setWaitState(FLASH_BANK0, 3);
	FlashCtl_setWaitState(FLASH_BANK1, 3);

	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_PJ, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
	CS_setExternalClockSourceFrequency(32768,26000000);
	//CS_startLFXT(CS_LFXT_DRIVE3);
	CS_startHFXT(false);
	CS_setReferenceOscillatorFrequency(CS_REFO_32KHZ);
	CS_enableClockRequest(CS_ACLK);
	CS_enableClockRequest(CS_HSMCLK);
	CS_enableClockRequest(CS_SMCLK);
	CS_enableClockRequest(CS_MCLK);
	CS_enableDCOExternalResistor();
	CS_setDCOFrequency(48000000);

	CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
	CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
	CS_initClockSignal(CS_HSMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);
	CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);
	CS_initClockSignal(CS_BCLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);

	Clock_Initialized = true;

	return S_OK;
}

