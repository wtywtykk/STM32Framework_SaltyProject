#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "HAL\FPGASPIPort.h"
#include <math.h>

static bool Inited = false;

double horner(double p[], int n, double x)
{
	double sum;
	sum = p[0];
	for (u8 i = 0; i < n; i++)
	{
		sum = p[i] + sum * x;
	}
	return sum;
}

void FFTFreqMeterTest(void)
{
	if (!Inited)
	{
		FPGASPIPort_Reset();
		Inited = true;
	}
	FONTGROUP* FGs = NewReferenceSafe(new_noexcpt FONTGROUP("ASC16"));
	char sbuf[256];
	u16 RVal[16] = { 0,0,0,0,0,0,0,0 };
	s16 sRVal[14] = { 0,0,0,0,0,0,0,0 };
	FPGASPIPort_Receive(RVal, sizeof(RVal));
	for (u8 i = 1; i < 15; i++)
	{
		sRVal[i - 1] = RVal[i] << 2;
	}

	sprintf(sbuf, "%6d     ", RVal[0]);
	DrawStringHorizontal(g_LCDDC, FGs, sbuf, 0, 0, 0, 0, WHITE, BLACK);
	for (u8 i = 0; i < 14; i++)
	{
		sprintf(sbuf, "%6d     ", sRVal[i]);
		DrawStringHorizontal(g_LCDDC, FGs, sbuf, 0, 16 + 16 * i, 0, 0, WHITE, BLACK);
	}
	double BaseFreq = (double)RVal[0] / 16384.0 * 100000000.0 / 1000000.0;
	sprintf(sbuf, "Base: %8.10f     ", BaseFreq);
	DrawStringHorizontal(g_LCDDC, FGs, sbuf, 300, 32, 0, 0, WHITE, BLACK);

	double Mags[7];
	for (u8 i = 0; i < 7; i++)
	{
		Mags[i] = sqrt((double)(sRVal[2 * i] * sRVal[2 * i] + sRVal[2 * i + 1] * sRVal[2 * i + 1]));
	}
	for (u8 i = 0; i < 7; i++)
	{
		sprintf(sbuf, "%6.6f     ", Mags[i]);
		DrawStringHorizontal(g_LCDDC, FGs, sbuf, 100, 16 * i, 0, 0, WHITE, BLACK);
	}
	//double PolyFitCoeff[] = { -0.002240791703420,0.0,0.014863003251604,0.0,-0.092909129008885,0.0,1.191812260891100,0.0 };
	double PolyFitCoeff[] = { -0.000131551883391,0,0.001897575019733,0,-0.024698647434355,0,0.738533168256980,0 };
	//double PolyFitRatio = (Mags[2] - Mags[4]) / Mags[3];
	double PolyFitRatio = (Mags[2] - Mags[4] + Mags[1] - Mags[5]) / Mags[3];
	double PolyFitResult = horner(PolyFitCoeff, 8, PolyFitRatio);
	sprintf(sbuf, "Offset: %8.10f     ", PolyFitResult);
	DrawStringHorizontal(g_LCDDC, FGs, sbuf, 300, 48, 0, 0, WHITE, BLACK);

	double FineFreq = (RVal[0] - PolyFitResult) / 16384.0 * 100000000.0 / 1000000.0;
	static double AveFreq = 0.0;
	double StdFreq = 12.3456789123;
	AveFreq = (AveFreq * 9.0 + FineFreq) / 10.0;
	sprintf(sbuf, "Fine: %8.10f     \n\rAverage: %8.10f     \n\rErr: %8.10e      ", FineFreq, AveFreq, (StdFreq - FineFreq) / StdFreq);
	DrawStringHorizontal(g_LCDDC, FGs, sbuf, 300, 64, 0, 0, WHITE, BLACK);

	FreeAndEraseReference(FGs);
}
