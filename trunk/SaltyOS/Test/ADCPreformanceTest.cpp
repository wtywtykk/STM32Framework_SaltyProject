#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\DC\ClippedDC.h"
#include "Kernel\GUI\Shape\Line.h"
#include "Kernel\GUI\Text\DrawString.h"
#include <arm_math.h>
#include "HAL\FPGAParPort.h"

u16 ADCPreformanceTest_WindowWidth;
u16 ADCPreformanceTest_WindowHeight;
#define ADCPreformanceTest_SampleLength 4096
s16 ADCPreformanceTest_SrcS16[ADCPreformanceTest_SampleLength];
float ADCPreformanceTest_Src[ADCPreformanceTest_SampleLength];
float ADCPreformanceTest_WinFunc[ADCPreformanceTest_SampleLength];
float ADCPreformanceTest_Spec[ADCPreformanceTest_SampleLength / 2][2];

CLIPPEDDC* ADCPreformanceTest_cdc;

void ADCPreformanceTestInit(void)
{
	ADCPreformanceTest_cdc = NewReferenceSafe(new_noexcpt CLIPPEDDC(g_LCDDC, 0, 0, g_LCDDC->GetWidth() / 1, g_LCDDC->GetHeight() / 1, true, true));
	ADCPreformanceTest_WindowWidth = ADCPreformanceTest_cdc->GetWidth();
	ADCPreformanceTest_WindowHeight = ADCPreformanceTest_cdc->GetHeight();
	for (u32 i = 0; i < ADCPreformanceTest_SampleLength; i++)
	{
		float a0 = 0.42;
		float a1 = 0.5;
		float a2 = 0.08;
		float a3 = 0;
		ADCPreformanceTest_WinFunc[i] = a0 -
			a1 * cos(2 * M_PI * i / ADCPreformanceTest_SampleLength) +
			a2 * cos(4 * M_PI * i / ADCPreformanceTest_SampleLength) -
			a3 * cos(6 * M_PI * i / ADCPreformanceTest_SampleLength);
	}
}

void ADCPreformanceRender(void)
{
	arm_rfft_fast_instance_f32 FFTInst;
	static bool Initialized = false;
	if (!Initialized)
	{
		Initialized = true;
		ADCPreformanceTestInit();
	}

	if (FPGAParPort_WaitReady(1000) == S_OK)
	{
		u32 ReadSize = 0;
		ParPort_StartPipeline();
		ParPort_Read((u16*)ADCPreformanceTest_SrcS16, ADCPreformanceTest_SampleLength, &ReadSize, false);
		FPGAParPort_Reset();

		for (u32 i = 0; i < ADCPreformanceTest_SampleLength; i++)
		{
			ADCPreformanceTest_Src[i] = ADCPreformanceTest_SrcS16[i] / 4 * ADCPreformanceTest_WinFunc[i];
		}

		arm_rfft_fast_init_f32(&FFTInst, ADCPreformanceTest_SampleLength);
		arm_rfft_fast_f32(&FFTInst, ADCPreformanceTest_Src, &ADCPreformanceTest_Spec[0][0], 0);

		ADCPreformanceTest_cdc->Fill(0, 0, ADCPreformanceTest_WindowWidth, ADCPreformanceTest_WindowHeight, BLACK);

		for (u32 i = 0; i < ADCPreformanceTest_SampleLength / 2; i++)
		{
			ADCPreformanceTest_Spec[i][0] = log(ADCPreformanceTest_Spec[i][0] * ADCPreformanceTest_Spec[i][0] + ADCPreformanceTest_Spec[i][1] * ADCPreformanceTest_Spec[i][1]);
			ADCPreformanceTest_Spec[i][0] *= 20;
			if (!isnormal(ADCPreformanceTest_Spec[i][0]))
			{
				ADCPreformanceTest_Spec[i][0] = -9999999;
			}
		}

		for (u32 i = 0; i < ADCPreformanceTest_SampleLength / 2 - 1; i++)
		{
			const float MaxVal = 900.0;
			const float MinVal = 000.0;
			float YPos0 = ADCPreformanceTest_WindowHeight * (MaxVal - ADCPreformanceTest_Spec[i][0]) / (MaxVal - MinVal);
			float YPos1 = ADCPreformanceTest_WindowHeight * (MaxVal - ADCPreformanceTest_Spec[i + 1][0]) / (MaxVal - MinVal);
			DrawLine(ADCPreformanceTest_cdc,
				i * ADCPreformanceTest_WindowWidth * 2 / ADCPreformanceTest_SampleLength, YPos0,
				(i + 1) * ADCPreformanceTest_WindowWidth * 2 / ADCPreformanceTest_SampleLength, YPos1, RED);
		}
	}
	else
	{
		FONTGROUP* FGs = NewReferenceSafe(new_noexcpt FONTGROUP("ASC16"));
		DrawStringHorizontal(ADCPreformanceTest_cdc, FGs, "Unable to communicate with FPGA", 0, 0, 0, 0, RED, BLACK);
		FreeAndEraseReference(FGs);
	}
	ADCPreformanceTest_cdc->Update();
}
