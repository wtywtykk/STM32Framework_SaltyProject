#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\DC\ClippedDC.h"
#include "Kernel\GUI\Shape\Line.h"
#include "Algorithm\MemCached\MemCached.h"
#include "Algorithm/Transform/FFT/FFT.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

u16 RFFTTest_WindowWidth;
u16 RFFTTest_WindowHeight;
#define Wave_Length 16384
float RFFTSrc[Wave_Length];
float RFFTSpec[Wave_Length / 2][2];

CLIPPEDDC* RFFTTest_cdc;

void RFFTTest(void)
{
	static float Freq = 10;
	static bool Initialized = false;
	if (!Initialized)
	{
		Initialized = true;
		RFFTTest_cdc = NewReferenceSafe(new_noexcpt CLIPPEDDC(g_LCDDC, 0, 0, g_LCDDC->GetWidth() / 1, g_LCDDC->GetHeight() / 1, false, false));
		RFFTTest_WindowWidth = RFFTTest_cdc->GetWidth();
		RFFTTest_WindowHeight = RFFTTest_cdc->GetHeight();
	}
	Freq += 1;

	for (u32 i = 0; i < Wave_Length; i++)
	{
		RFFTSrc[i] = sinf(Freq * i * 2 * 3.1416 / 1000);
	}

	RFFT_BitNormal(RFFTSrc, &RFFTSpec[0][0], Wave_Length);

	//RFFTTest_cdc->Fill(0, 0, RFFTTest_WindowWidth, RFFTTest_WindowHeight, BLACK);

	for (u32 i = 0; i < Wave_Length / 2 - 1; i += 1)
	{
		DrawLine(RFFTTest_cdc,
			i * RFFTTest_WindowWidth * 2 / Wave_Length,
			RFFTTest_WindowHeight * (0.5 - log(RFFTSpec[i][0] * RFFTSpec[i][0] + RFFTSpec[i][1] * RFFTSpec[i][1]) / 40),
			(i + 1) * RFFTTest_WindowWidth * 2 / Wave_Length,
			RFFTTest_WindowHeight * (0.5 - log(RFFTSpec[i + 1][0] * RFFTSpec[i + 1][0] + RFFTSpec[i + 1][1] * RFFTSpec[i + 1][1]) / 40), RED);
	}

	for (u32 i = 0; i < Wave_Length / 2 - 1; i += 1)
	{
		DrawLine(RFFTTest_cdc,
			i * RFFTTest_WindowWidth * 2 / Wave_Length,
			RFFTTest_WindowHeight * (0.5 - log(RFFTSpec[i][0] * RFFTSpec[i][0] + RFFTSpec[i][1] * RFFTSpec[i][1]) / 40),
			(i + 1) * RFFTTest_WindowWidth * 2 / Wave_Length,
			RFFTTest_WindowHeight * (0.5 - log(RFFTSpec[i + 1][0] * RFFTSpec[i + 1][0] + RFFTSpec[i + 1][1] * RFFTSpec[i + 1][1]) / 40), BLACK);
	}
	RFFTTest_cdc->Update();
}
