#include "HAL/HCommon.h"
#include "CurMeas.h"
#include "Sample.h"

#define DMA_BlockSize 1024

s16 ConvDownBuffer[2][DMA_BlockSize];

s16 SampleBuffer[SAMPLE_LENGTH];
__attribute__((aligned(1024)))uint8_t controlTable[256];
volatile u32 SampleProgress = 0;
u8 ChannelSelect = 0;
float RealSampleFreq = 1.0;
bool ConvDownMode = false;

void SampleCompleteInterrupt(void)
{
	SampleProgress += DMA_BlockSize;
	if (SampleProgress < SAMPLE_LENGTH)
	{
		if (DMA_getChannelAttribute(DMA_CHANNEL_7) & UDMA_ATTR_ALTSELECT)
		{
			DMA_setChannelControl(UDMA_PRI_SELECT | DMA_CH7_ADC12C, UDMA_SIZE_16 | UDMA_SRC_INC_NONE | UDMA_DST_INC_16 | UDMA_ARB_1);
			DMA_setChannelTransfer(UDMA_PRI_SELECT | DMA_CH7_ADC12C, UDMA_MODE_PINGPONG, (void*)&ADC14->rMEM0, (u16*)SampleBuffer + SampleProgress, DMA_BlockSize);
		}
		else
		{
			DMA_setChannelControl(UDMA_ALT_SELECT | DMA_CH7_ADC12C, UDMA_SIZE_16 | UDMA_SRC_INC_NONE | UDMA_DST_INC_16 | UDMA_ARB_1);
			DMA_setChannelTransfer(UDMA_ALT_SELECT | DMA_CH7_ADC12C, UDMA_MODE_PINGPONG, (void*)&ADC14->rMEM0, (u16*)SampleBuffer + SampleProgress, DMA_BlockSize);
		}
	}
}

void Sample_Init(void)
{
	ADC14_enableModule();
	ADC14_initModule(ADC_CLOCKSOURCE_SMCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1, ADC_NOROUTE);

	ADC14_setResultFormat(ADC_SIGNED_BINARY);
	ADC14_setResolution(ADC_14BIT);
	ADC14_setPowerMode(ADC_UNRESTRICTED_POWER_MODE);

	/* Configuring GPIOs (P55 A0 P54 A1) */
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN5, GPIO_TERTIARY_MODULE_FUNCTION);
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);
	//Ref
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN6, GPIO_TERTIARY_MODULE_FUNCTION);
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN7, GPIO_TERTIARY_MODULE_FUNCTION);

	/* Configuring ADC Memory */
	ADC14_configureSingleSampleMode(ADC_MEM0, true);
	ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_EXTPOS_VREFNEG_EXTNEG, ADC_INPUT_A1, ADC_NONDIFFERENTIAL_INPUTS);
	ADC14_setSampleHoldTrigger(ADC_TRIGGER_SOURCE1, false);

	/* Configuring DMA module */
	DMA_enableModule();
	DMA_setControlBase(controlTable);

	/* Assigning/Enabling Interrupts */
	DMA_assignInterrupt(DMA_INT1, DMA_CHANNEL_7);
	Interrupt_enableInterrupt(INT_DMA_INT1);
	DMA_assignChannel(DMA_CH7_ADC12C);
	DMA_clearInterruptFlag(DMA_CHANNEL_7);

	DMA_registerInterrupt(INT_DMA_INT1, SampleCompleteInterrupt);

	DMA_disableChannel(DMA_CHANNEL_7);

	Sample_SetSampleFrequency(1000000);
};

void Sample_SetSampleFrequency(float Freq)
{
	Timer_A_PWMConfig TimConfig;
	ADC14_disableConversion();
	TimConfig.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
	TimConfig.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
	TimConfig.compareOutputMode = TIMER_A_OUTPUTMODE_SET_RESET;
	TimConfig.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
	TimConfig.dutyCycle = 1;
	if (Freq <= 900000)
	{
		TimConfig.timerPeriod = CS_getSMCLK() / Freq;
		Timer_A_generatePWM(TIMER_A0_BASE, &TimConfig);

		RealSampleFreq = CS_getSMCLK() / TimConfig.timerPeriod;

		if (Freq < 100000)
		{
			ADC14_setSampleHoldTime(ADC_PULSE_WIDTH_32, ADC_PULSE_WIDTH_32);
		}
		else
		{
			ADC14_setSampleHoldTime(ADC_PULSE_WIDTH_8, ADC_PULSE_WIDTH_8);
		}
		ADC14_enableSampleTimer(ADC_MANUAL_ITERATION);
	}
	else
	{
		TimConfig.timerPeriod = 100;
		Timer_A_generatePWM(TIMER_A0_BASE, &TimConfig);

		ADC14_setSampleHoldTime(ADC_PULSE_WIDTH_8, ADC_PULSE_WIDTH_8);
		ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
		RealSampleFreq = 1000000;
	}
}

float Sample_GetRealFrequency(void)
{
	return RealSampleFreq;
}

void Sample_SelectChannel(u8 Ch)
{
	ADC14_disableConversion();
	if (Ch == 0)
	{
		ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_EXTPOS_VREFNEG_EXTNEG, ADC_INPUT_A0, ADC_NONDIFFERENTIAL_INPUTS);
		ChannelSelect = 0;
	}
	else
	{
		ADC14_configureConversionMemory(ADC_MEM1, ADC_VREFPOS_EXTPOS_VREFNEG_EXTNEG, ADC_INPUT_A1, ADC_NONDIFFERENTIAL_INPUTS);
		ChannelSelect = 1;
	}
}

u8 Sample_GetCurChannel(void)
{
	return ChannelSelect;
}

void Sample_SetupDMAChannels(void)
{
	DMA_disableChannelAttribute(DMA_CH7_ADC12C, UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST | UDMA_ATTR_HIGH_PRIORITY | UDMA_ATTR_REQMASK);

	SampleProgress = 0;
	DMA_setChannelControl(UDMA_PRI_SELECT | DMA_CH7_ADC12C, UDMA_SIZE_16 | UDMA_SRC_INC_NONE | UDMA_DST_INC_16 | UDMA_ARB_1);
	DMA_setChannelTransfer(UDMA_PRI_SELECT | DMA_CH7_ADC12C, UDMA_MODE_PINGPONG, (void*)&ADC14->rMEM0, (u16*)SampleBuffer + SampleProgress, DMA_BlockSize);

	SampleProgress += DMA_BlockSize;
	DMA_setChannelControl(UDMA_ALT_SELECT | DMA_CH7_ADC12C, UDMA_SIZE_16 | UDMA_SRC_INC_NONE | UDMA_DST_INC_16 | UDMA_ARB_1);
	DMA_setChannelTransfer(UDMA_ALT_SELECT | DMA_CH7_ADC12C, UDMA_MODE_PINGPONG, (void*)&ADC14->rMEM0, (u16*)SampleBuffer + SampleProgress, DMA_BlockSize);

	DMA_enableChannel(DMA_CHANNEL_7);
}

void Sample_StartSample(void)
{
	ADC14_disableConversion();
	DMA_disableChannel(DMA_CHANNEL_7);
	ADC14_clearInterruptFlag(ADC_INT0);
	Sample_SetupDMAChannels();
	ADC14_enableConversion();
}

bool Sample_IsSampleCompleted(void)
{
	bool SampleComplete = !DMA_isChannelEnabled(DMA_CHANNEL_7);
	return SampleComplete;
}

u8 Sample_GetProgress(void)
{
	return 100 * SampleProgress / SAMPLE_LENGTH;
}
