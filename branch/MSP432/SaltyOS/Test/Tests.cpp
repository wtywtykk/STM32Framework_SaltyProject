#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "HAL/Tick.h"
#include <stdio.h>

void TextTest(void);
void ClippedDCTest(void);
void LineTest(void);
void WaveRender(void);
void CircleTest(void);
void EclipseTest(void);
void FT5336Test(void);
void LTC1446Test(void);
void MemTest(void);
void PicTest(void);
//void FFTTest(void);
void RFFTTest(void);

void RunTests(void)
{
	FONTGROUP* FGs = NewReferenceSafe(new_noexcpt FONTGROUP("ASC16"));
	while (1)
	{
		u32 st = HAL_GetTick();
		u32 i = 0;
		//TextTest();
		//ClippedDCTest();
		//LineTest();
		//CircleTest();
		//EclipseTest();
		//WaveRender();
		//FT5336Test();
		//LTC1446Test();
		//AD7671Test();
		//MemTest();
		//W25QxxTest();
		//ParPortTest();
		//ZLG7290Test();
		//FPGASPITest();
		//PicTest();
		//FFTTest();
		RFFTTest();

		char buf[16];
		i++;
		sprintf(buf, "%.3fms ", (float)(HAL_GetTick() - st) / i);
		DrawStringHorizontal(g_LCDDC, FGs, buf, 300, 0, 300, 50, GREEN, RED);
	}
	FreeAndEraseReference(FGs);
}
