#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"

void TextTest(void);
void ClippedDCTest(void);
void LineTest(void);
void WaveRender(void);
void CircleTest(void);
void EclipseTest(void);
void FT5336Test(void);
void LTC1446Test(void);
void AD7671Test(void);
void MemTest(void);
void W25QxxTest(void);
void ParPortTest(void);
void ZLG7290Test(void);
void FPGASPITest(void);
void PicTest(void);
void UsPosTest(void);
void CPLDGPIOTest(void);
void FlashFSTest(void);
void WindowTest(void);
void MenuTest(void);
void ADF4351Test(void);
void SaltyADCTest(void);
void HighPrecisionFreqMeterTest(void);
void FFTFreqMeterTest(void);
void SAFrontEndTest(void);
void LOBoardTest(void);
void HMC832Test(void);
void ADCPreformanceRender(void);
void ADS8363Test(void);
void FFTTest(void);
void RFFTTest(void);
void AD9959Test(void);

void RunTests(void)
{
	FONTGROUP* FGs = NewReferenceSafe(new_noexcpt FONTGROUP("ASC12"));
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
		//UsPosTest();
		//CPLDGPIOTest();
		//FlashFSTest();
		//WindowTest();
		//MenuTest();
		//ADF4351Test();
		//SaltyADCTest();
		//HighPrecisionFreqMeterTest();
		//FFTFreqMeterTest();
		//SAFrontEndTest();
		//LOBoardTest();
		//HMC832Test();
		//ADCPreformanceRender();
		//ADS8363Test();
		//FFTTest();
		//RFFTTest();
		AD9959Test();

		char buf[16];
		i++;
		sprintf(buf, "%.3fms ", (float)(HAL_GetTick() - st) / i);
		DrawStringHorizontal(g_LCDDC, FGs, buf, 300, 0, 300, 50, GREEN, RED);
	}
	FreeAndEraseReference(FGs);
}
