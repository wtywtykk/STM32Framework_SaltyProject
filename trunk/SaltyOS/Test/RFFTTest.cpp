/*#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\DC\ClippedDC.h"
#include "Kernel\GUI\Shape\Line.h"
#include <arm_math.h>
#include "Algorithm\MemCached\MemCached.h"
#include "Algorithm\FFT\FFT.h"
#include <stdlib.h>

u16 RFFTTest_WindowWidth;
u16 RFFTTest_WindowHeight;
#define Wave_Length 4096
float RFFTSrc[Wave_Length];
float RFFTSpec[Wave_Length / 2][2];

CLIPPEDDC* RFFTTest_cdc;
arm_rfft_fast_instance_f32 RFFTInst;

void RFFTTestSrcLoadFunc(u32 StorageAddr, void* MemCachedAddr, u32 Size);
void RFFTTestSrcStoreFunc(void* MemCachedAddr, u32 StorageAddr, u32 Size);
FloatMemCache SrcObj(RFFTTestSrcLoadFunc, RFFTTestSrcStoreFunc, Wave_Length);
void RFFTTestSpecLoadFunc(u32 StorageAddr, void* MemCachedAddr, u32 Size);
void RFFTTestSpecStoreFunc(void* MemCachedAddr, u32 StorageAddr, u32 Size);
FloatMemCache SpecObj(NULL, RFFTTestSpecStoreFunc, Wave_Length);

void RFFTTest(void)
{
	static float Freq = 10;
	static bool Initialized = false;
	if (!Initialized)
	{
		Initialized = true;
		RFFTTest_cdc = NewReferenceSafe(new_noexcpt CLIPPEDDC(g_LCDDC, 0, 0, g_LCDDC->GetWidth() / 1, g_LCDDC->GetHeight() / 1, true, true));
		RFFTTest_WindowWidth = RFFTTest_cdc->GetWidth();
		RFFTTest_WindowHeight = RFFTTest_cdc->GetHeight();
		arm_rfft_fast_init_f32(&RFFTInst, Wave_Length);
	}
	Freq += 1;

	for (u32 i = 0; i < Wave_Length; i++)
	{
		RFFTSrc[i] = sinf(Freq * i * 2 * PI / 1000);
	}

	//arm_rfft_fast_f32(&RFFTInst, RFFTSrc, &RFFTSpec[0][0], 0);
	//RFFT_BitNormal(RFFTSrc, &RFFTSpec[0][0], Wave_Length);
	SrcObj.Sync();
	RFFT_MemCached_BitNormal(SrcObj, SpecObj, Wave_Length);
	SpecObj.Flush();

	RFFTTest_cdc->Fill(0, 0, RFFTTest_WindowWidth, RFFTTest_WindowHeight, BLACK);

	for (u32 i = 0; i < Wave_Length / 2 - 1; i += 1)
	{
		DrawLine(RFFTTest_cdc,
			i * RFFTTest_WindowWidth * 2 / Wave_Length,
			RFFTTest_WindowHeight * (0.5 - log(RFFTSpec[i][0] * RFFTSpec[i][0] + RFFTSpec[i][1] * RFFTSpec[i][1]) / 40),
			(i + 1) * RFFTTest_WindowWidth * 2 / Wave_Length,
			RFFTTest_WindowHeight * (0.5 - log(RFFTSpec[i + 1][0] * RFFTSpec[i + 1][0] + RFFTSpec[i + 1][1] * RFFTSpec[i + 1][1]) / 40), RED);
	}
	RFFTTest_cdc->Update();
}

void RFFTTestSrcLoadFunc(u32 StorageAddr, void* MemCachedAddr, u32 Size)
{
	memcpy(MemCachedAddr, &RFFTSrc[0] + StorageAddr, Size * sizeof(float));
}

void RFFTTestSrcStoreFunc(void* MemCachedAddr, u32 StorageAddr, u32 Size)
{
	memcpy(&RFFTSrc[0] + StorageAddr, MemCachedAddr, Size * sizeof(float));
}

void RFFTTestSpecLoadFunc(u32 StorageAddr, void* MemCachedAddr, u32 Size)
{
	memcpy(MemCachedAddr, &RFFTSpec[0][0] + StorageAddr, Size * sizeof(float));
}

void RFFTTestSpecStoreFunc(void* MemCachedAddr, u32 StorageAddr, u32 Size)
{
	memcpy(&RFFTSpec[0][0] + StorageAddr, MemCachedAddr, Size * sizeof(float));
}
*/