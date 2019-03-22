#include "HAL/HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "HAL\UniGPIO.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\DC\ClippedDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "Kernel\GUI\Shape\Line.h"
#include "Kernel\GUI\Shape\Circle.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <arm_math.h>
#include "Sample.h"
#include "CurMeas.h"
#include "BoardIO.h"
#include "Process.h"
#include "Key.h"
#include "HAL/Tick.h"
#include "AutoRange.h"

#define INFO_X 0
#define INFO_Y 0
#define INFO_W 480
#define INFO_H 400

#define WAVE_X 0
#define WAVE_Y 400
#define WAVE_W 480
#define WAVE_H 200

#define SPEC_X 0
#define SPEC_Y 600
#define SPEC_W 480
#define SPEC_H 200

float OffsetDACVal = 0x3FFF / 2;

#define WaveDispBufLen 256
float WaveDispBuf[WaveDispBufLen];

#define SpecDispBufLen 512
float SpecDispBuf[SpecDispBufLen];

bool HighFreqMode = false;
const float StdFreq[2] = { 1000.0,10000.0 };
float CalibFreq[2] = { 1000.0,10000.0 };

void FreqDispFormat(float FreqIn, float& FreqOut, pcstr& Unit)
{
	if (FreqIn <= 0)
	{
		FreqOut = nanf("");
		Unit = "";
		return;
	}
	pcstr Units[] = { "Hz","kHz" };
	u32 i = 0;
	while (FreqIn > 1000.0)
	{
		FreqIn /= 1000.0;
		i++;
		if (i >= 2)
		{
			i = 1;
			break;
		}
	}
	FreqOut = FreqIn;
	Unit = Units[i];
}

void AmpDispFormat(float AmpIn, float& AmpOut, pcstr& Unit)
{
	if (AmpIn <= 0)
	{
		AmpOut = nanf("");
		Unit = "";
		return;
	}
	pcstr Units[] = { "uA","mA" ," A" };
	u32 i = 2;
	while (AmpIn < 1.0)
	{
		AmpIn *= 1000.0;
		i--;
		if (i == 0)
		{
			break;
		}
	}
	AmpOut = AmpIn;
	Unit = Units[i];
}

float FreqCalibTransform(float Val)
{
	if (HighFreqMode)
	{
		return Val * StdFreq[1] / CalibFreq[1];
	}
	else
	{
		return Val * StdFreq[0] / CalibFreq[0];
	}
}

void DrawSingleFrame(DC* dc, GUIPOS X, GUIPOS Y, GUIPOS W, GUIPOS H, pcstr Name)
{
	const u8 BondWidth = 10;
	for (u8 i = 0; i < BondWidth; i++)
	{
		u16 x = (255 * i / (BondWidth - 1)) << 8;
		PIXEL Color = (x & 0xF800) | ((x >> 5) & 0x07E0) | (x >> 11);
		DrawLine(dc, X + i, Y + i, X + W - i, Y + i, Color);
		DrawLine(dc, X + i, Y + H - i, X + W - i, Y + H - i, Color);
		DrawLine(dc, X + i, Y + i, X + i, Y + H - i, Color);
		DrawLine(dc, X + W - i, Y + i, X + W - i, Y + H - i, Color);
	}
	FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC16;HZK32"));
	DrawStringHorizontal(g_LCDDC, FG, Name, X + BondWidth, Y + BondWidth, W - 2 * BondWidth, 32, WHITE, OLIVE);
	FreeAndEraseReference(FG);
}

void DrawFrames(void)
{
	DrawSingleFrame(g_LCDDC, INFO_X, INFO_Y, INFO_W, INFO_H, "电流参数");
	DrawSingleFrame(g_LCDDC, WAVE_X, WAVE_Y, WAVE_W, WAVE_H, "波形");
	DrawSingleFrame(g_LCDDC, SPEC_X, SPEC_Y, SPEC_W, SPEC_H, "频谱");
}

float GetFreqNormalized(void)
{
	return FreqCalibTransform(GetFrequency(1));
}

float MeasRMSFit(float x)
{
	if (HighFreqMode)
	{
		return ((((3.415e-26  * x - 3.013e-20)  * x + 9.053e-15) * x - 1.069e-09)* x - 1.323e-05)* x + 32.97;
	}
	else
	{
		return ((((-4.571e-14  * x + 1.057e-10)  * x - 6.043e-08) * x - 2.618e-06)* x + 0.0002131)* x + 32.98;
	}
}

void DispMeas(void)
{
	DC* CDC = NewReferenceSafe(new_noexcpt CLIPPEDDC(g_LCDDC, INFO_X, INFO_Y, INFO_X + INFO_W, INFO_Y + INFO_H, false, false));
	FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC16;HZK24K"));
	char buf[128];
	float Disp;
	pcstr Unit;
	AmpDispFormat(GetRMS() * 35.37 / MeasRMSFit(GetFreqNormalized()), Disp, Unit);
	sprintf(buf, "有效值 %f %s     ", Disp, Unit);
	DrawStringHorizontal(g_LCDDC, FG, buf, 20, 50, 0, 0, WHITE, BLACK);

	AmpDispFormat(GetRMS() * 2.0 * sqrtf(2.0) * 35.37 / MeasRMSFit(GetFreqNormalized()), Disp, Unit);
	sprintf(buf, "峰峰值 %f %s     ", Disp, Unit);
	DrawStringHorizontal(g_LCDDC, FG, buf, 20, 50 + 30, 0, 0, WHITE, BLACK);

	FreqDispFormat(GetFreqNormalized(), Disp, Unit);
	sprintf(buf, "频率    %f %s     ", Disp, Unit);
	DrawStringHorizontal(g_LCDDC, FG, buf, 20, 50 + 30 * 2, 0, 0, WHITE, BLACK);

	AmpDispFormat(GetReconstructRMS() / 13.85382 * 35.39, Disp, Unit);
	sprintf(buf, "R有效值 %f %s     ", Disp, Unit);
	DrawStringHorizontal(g_LCDDC, FG, buf, 20, 50 + 30 * 3, 0, 0, WHITE, BLACK);

	AmpDispFormat(GetReconstructPKPK() / 39.149 * 100, Disp, Unit);
	sprintf(buf, "R峰峰值 %f %s     ", Disp, Unit);
	DrawStringHorizontal(g_LCDDC, FG, buf, 20, 50 + 30 * 4, 0, 0, WHITE, BLACK);

	DrawStringHorizontal(g_LCDDC, FG, "谐波", 270 - 32, 20, 0, 0, WHITE, BLACK);
	DrawStringHorizontal(g_LCDDC, FG, "幅度", 310, 20, 0, 0, WHITE, BLACK);
	for (u8 i = 1; i < 22; i++)
	{
		sprintf(buf, "%02d", i);
		DrawStringHorizontal(g_LCDDC, FG, buf, 270, 20 + 25 + 16 * (i - 1), 0, 0, WHITE, BLACK);
		float Amp = GetAmplitude(i);
		if (Amp >= 0)
		{
			Amp /= MeasRMSFit(i * GetFreqNormalized());
			Amp = Amp * 49.9585 * 1000 / 591.4;
			AmpDispFormat(Amp, Disp, Unit);
			sprintf(buf, "%4.4f %s   ", Disp, Unit);
		}
		else
		{
			strcpy(buf, "------      ");
		}
		DrawStringHorizontal(g_LCDDC, FG, buf, 310, 20 + 25 + 16 * (i - 1), 0, 0, WHITE, BLACK);
	}
	FreeAndEraseReference(FG);
	FreeAndEraseReference(CDC);
}

void DispWave(void)
{
	DC* CDC = NewReferenceSafe(new_noexcpt CLIPPEDDC(g_LCDDC, WAVE_X + 10, WAVE_Y + 10, WAVE_X + WAVE_W - 10, WAVE_Y + WAVE_H - 10, false, false));
	u32 i;
	GUIPOS LX = 0;
	GUIPOS LY = 0;
	for (i = 0; i < WaveDispBufLen * 2; i++)
	{
		GUIPOS X = i * (WAVE_W - 20) / WaveDispBufLen / 2;
		GUIPOS Y = (WAVE_H - 20) * (1.0 - (0.5 + WaveDispBuf[i % WaveDispBufLen] / 2.0 / 2.0));
		if (i)
		{
			DrawLine(CDC, X, Y, LX, LY, BLACK);
		}
		LX = X;
		LY = Y;
	}
	ReconstructWave(WaveDispBuf, WaveDispBufLen, true);
	for (i = 0; i < WaveDispBufLen * 2; i++)
	{
		GUIPOS X = i * (WAVE_W - 20) / WaveDispBufLen / 2;
		GUIPOS Y = (WAVE_H - 20) * (1.0 - (0.5 + WaveDispBuf[i % WaveDispBufLen] / 2.0 / 2.0));
		if (i)
		{
			DrawLine(CDC, X, Y, LX, LY, YELLOW);
		}
		LX = X;
		LY = Y;
	}
	FreeAndEraseReference(CDC);
}

void DispSpectrum(void)
{
	u32 i;
	u32 DispIndex = 0;
	float MagSum = 0;
	for (i = 0; i < SAMPLE_LENGTH / 2; i++)
	{
		u32 NewDispIndex = i * SpecDispBufLen / (SAMPLE_LENGTH / 2);
		if (NewDispIndex != DispIndex && DispIndex < SpecDispBufLen)
		{
			SpecDispBuf[DispIndex] = MagSum;
			MagSum = 0;
			DispIndex = NewDispIndex;
		}
		MagSum += FFTMag[i];
	}
	DC* CDC = NewReferenceSafe(new_noexcpt CLIPPEDDC(g_LCDDC, SPEC_X + 10, SPEC_Y + 45, SPEC_X + SPEC_W - 10, SPEC_Y + SPEC_H - 10, false, false));
	for (i = 0; i < SpecDispBufLen; i++)
	{
		GUIPOS X = i * (SPEC_W - 20) / SpecDispBufLen;
		GUIPOS Y = (SPEC_H - 55) * (1.5 - log10f(SpecDispBuf[i]) / 5);
		CDC->Fill(X, 0, X + 1, Y, BLACK);
		CDC->Fill(X, Y, X + 1, SPEC_H - 20, GREEN);
	}
	FreeAndEraseReference(CDC);
}

void DispProgress(bool Sampling)
{
	if (Sampling)
	{
		static u8 LastProgress = 0;
		u8 Progress = Sample_GetProgress();
		if (LastProgress != Progress)
		{
			GUIPOS x = Progress * g_LCDDC->GetWidth() / 100;
			g_LCDDC->Fill(0, g_LCDDC->GetHeight() - 10, x, g_LCDDC->GetHeight(), WHITE);
			g_LCDDC->Fill(x, g_LCDDC->GetHeight() - 10, g_LCDDC->GetWidth(), g_LCDDC->GetHeight(), BLACK);
			LastProgress = Progress;
		}
	}
	else
	{
		g_LCDDC->Fill(0, g_LCDDC->GetHeight() - 10, g_LCDDC->GetWidth(), g_LCDDC->GetHeight(), RED);
	}
}

void DisplayWarnings(void)
{
	FONTGROUP* FG = NULL;
	FG = NewReferenceSafe(new_noexcpt FONTGROUP("HZK32"));
	if (AutoRange_IsOverRange())
	{
		DrawStringHorizontal(g_LCDDC, FG, "超出量程", 50, 200, 0, 0, RED, BLACK);
	}
	else
	{
		DrawStringHorizontal(g_LCDDC, FG, "啊啊啊啊", 50, 200, 0, 0, BLACK, BLACK);
	}
	if (AutoRange_IsSwitching())
	{
		DrawStringHorizontal(g_LCDDC, FG, "量程改变", 50, 240, 0, 0, RED, BLACK);
	}
	else
	{
		DrawStringHorizontal(g_LCDDC, FG, "啊啊啊啊", 50, 240, 0, 0, BLACK, BLACK);
	}
	FreeAndEraseReference(FG);
}

void StartupCalibration(void)
{
	GUIPOS Width = g_LCDDC->GetWidth();
	GUIPOS Height = g_LCDDC->GetHeight();
	FONTGROUP* FG = NULL;
	BoardIO_SetPGA(1, 8);
	Sample_SelectChannel(1);
	Sample_SetSampleFrequency(1000000);
	FG = NewReferenceSafe(new_noexcpt FONTGROUP("HZK32"));
	DrawStringHorizontal(g_LCDDC, FG, "调节前端直偏调节电位器直到红线中心大致与绿线重合。\n\r点击屏幕进入测量模式。", 0, 0, 0, 0, WHITE, BLACK);
	FreeAndEraseReference(FG);

	while (Key_GetKey() != -1);
	while (Key_GetKey() == -1)
	{
		Sample_StartSample();
		while (!Sample_IsSampleCompleted());
		g_LCDDC->Fill(0, Height / 2, Width, Height / 2 + 1, GREEN);
		for (u32 i = 0; i < SAMPLE_LENGTH; i += 16)
		{
			GUIPOS X = i * Width / SAMPLE_LENGTH;
			GUIPOS Y = Height * (1.0 - (0.5 + SampleBuffer[i] / 32768.0));
			if (Y < 0)
			{
				Y = 0;
			}
			if (Y >= Height)
			{
				Y = Height - 1;
			}
			g_LCDDC->SetPixel(X, Y, RED);
		}
		for (u32 i = 0; i < SAMPLE_LENGTH; i += 16)
		{
			GUIPOS X = i * Width / SAMPLE_LENGTH;
			GUIPOS Y = Height * (1.0 - (0.5 + SampleBuffer[i] / 32768.0));
			if (Y < 0)
			{
				Y = 0;
			}
			if (Y >= Height)
			{
				Y = Height - 1;
			}
			g_LCDDC->SetPixel(X, Y, BLACK);
		}
	}
	g_LCDDC->Fill(0, 0, Width, 16, BLACK);
	FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC16"));
	DrawStringHorizontal(g_LCDDC, FG, "Loading...", 0, 0, 0, 0, WHITE, BLACK);
	FreeAndEraseReference(FG);
	g_LCDDC->Fill(0, 16, Width, Height, BLACK);
	g_LCDDC->Fill(0, 0, Width, 16, BLACK);
}

void CalibrateDC(void)
{
	OffsetDACVal -= 0.9  * GetDC() / 3.0 * 0x3FFF;
	if (OffsetDACVal > 0x3FFF)
	{
		OffsetDACVal = 0x3FFF;
	}
	if (OffsetDACVal < 0)
	{
		OffsetDACVal = 0;
	}
	BoardIO_SetDAC(1, OffsetDACVal);
}

void CalibKey(void)
{
	if (HighFreqMode)
	{
		CalibFreq[1] = GetFrequency(1);
		if (CalibFreq[1] > StdFreq[1] + 1000 || CalibFreq[1] < StdFreq[1] - 1000)
		{
			CalibFreq[1] = StdFreq[1];
		}
	}
	else
	{
		CalibFreq[0] = GetFrequency(1);
		if (CalibFreq[0] > StdFreq[0] + 100 || CalibFreq[0] < StdFreq[0] - 100)
		{
			CalibFreq[0] = StdFreq[0];
		}
	}
}

void ModeSwitchKey(void)
{
	HighFreqMode = !HighFreqMode;
}

void CheckKey(void)
{
	switch (Key_GetKey())
	{
	case 0:
		ModeSwitchKey();
		break;
	case 1:
		CalibKey();
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	}

}

void TaskLauncher(void)
{
	Key_Init();
	BoardIO_Init();
	Sample_Init();
	Process_Init();
	BoardIO_SetDAC(1, OffsetDACVal);
	BoardIO_SetPGA(0, 1);
	BoardIO_SetPGA(1, 1);
	Sample_SelectChannel(1);
	Sample_SetSampleFrequency(1000000);
	StartupCalibration();
	Sample_SetSampleFrequency(10000);

	CalibFreq[0] = StdFreq[0];
	CalibFreq[1] = StdFreq[1];

	DrawFrames();
	while (1)
	{
		CheckKey();
		FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP("HZK24K"));
		BoardIO_SetFilter(HighFreqMode);
		if (HighFreqMode)
		{
			Sample_SetSampleFrequency(1000000);
			DrawStringHorizontal(g_LCDDC, FG, "高频模式", 0, g_LCDDC->GetHeight() - 35, 0, 0, WHITE, BLACK);
		}
		else
		{
			Sample_SetSampleFrequency(7000);
			DrawStringHorizontal(g_LCDDC, FG, "低频模式", 0, g_LCDDC->GetHeight() - 35, 0, 0, WHITE, BLACK);
		}
		FreeAndEraseReference(FG);
		Sample_StartSample();
		while (!Sample_IsSampleCompleted())
		{
			DispProgress(true);
		}
		DispProgress(false);
		CalibrateDC();
		Process();
		DisplayWarnings();
		DispMeas();
		DispWave();
		DispSpectrum();
		AutoRange_Process();
	}
}
