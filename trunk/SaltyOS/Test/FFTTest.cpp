/*#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\DC\ClippedDC.h"
#include "Kernel\GUI\Shape\Line.h"
#include <arm_math.h>
#include "Algorithm\FFT\FFT.h"

u16 FFTTest_WindowWidth;
u16 FFTTest_WindowHeight;
#define Wave_Length 8192
float FFTSpec[Wave_Length][2];

CLIPPEDDC* FFTTest_cdc;
arm_cfft_radix2_instance_f32 FFTInst;

void FFTTestLoadFunc(u32 StorageAddr, void* MemCachedAddr, u32 Size);
void FFTTestStoreFunc(void* MemCachedAddr, u32 StorageAddr, u32 Size);
FloatMemCache FFTMemCacheObj(FFTTestLoadFunc, FFTTestStoreFunc, Wave_Length * 2);

void FFTTest(void)
{
	static float Freq = 10;
	static bool Initialized = false;
	if (!Initialized)
	{
		Initialized = true;
		FFTTest_cdc = NewReferenceSafe(new_noexcpt CLIPPEDDC(g_LCDDC, 0, 0, g_LCDDC->GetWidth() / 1, g_LCDDC->GetHeight() / 1, true, true));
		FFTTest_WindowWidth = FFTTest_cdc->GetWidth();
		FFTTest_WindowHeight = FFTTest_cdc->GetHeight();
		arm_cfft_radix2_init_f32(&FFTInst, Wave_Length, 0, 0);
	}
	Freq += 1;

	for (u32 i = 0; i < Wave_Length; i++)
	{
		FFTSpec[i][0] = sinf(Freq * i * 2 * PI / 1000);
		FFTSpec[i][1] = 0;
	}

	//arm_cfft_radix2_f32(&FFTInst, &FFTSpec[0][0]);
	//CFFT_BitNormal(&FFTSpec[0][0], Wave_Length);
	FFTMemCacheObj.Sync();
	CFFT_MemCached_BitNormal(FFTMemCacheObj, Wave_Length);
	FFTMemCacheObj.Flush();

	FFTTest_cdc->Fill(0, 0, FFTTest_WindowWidth, FFTTest_WindowHeight, BLACK);

	for (u32 i = 0; i < Wave_Length - 1; i += 1)
	{
		DrawLine(FFTTest_cdc,
			i * FFTTest_WindowWidth / Wave_Length,
			FFTTest_WindowHeight * (0.5 - log(FFTSpec[i][0] * FFTSpec[i][0] + FFTSpec[i][1] * FFTSpec[i][1]) / 40),
			(i + 1) * FFTTest_WindowWidth / Wave_Length,
			FFTTest_WindowHeight * (0.5 - log(FFTSpec[i + 1][0] * FFTSpec[i + 1][0] + FFTSpec[i + 1][1] * FFTSpec[i + 1][1]) / 40), RED);
	}
	FFTTest_cdc->Update();
}

void FFTTestLoadFunc(u32 StorageAddr, void* MemCachedAddr, u32 Size)
{
	memcpy(MemCachedAddr, &FFTSpec[0][0] + StorageAddr, Size * sizeof(float));
}

void FFTTestStoreFunc(void* MemCachedAddr, u32 StorageAddr, u32 Size)
{
	memcpy(&FFTSpec[0][0] + StorageAddr, MemCachedAddr, Size * sizeof(float));
}
*/