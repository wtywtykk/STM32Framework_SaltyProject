#include "HAL\HCommon.h"
#include "HAL\FPGAParPort.h"
#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "Kernel\GUI\Shape\Line.h"
#include "Kernel\GUI\Shape\Circle.h"

#include "Driver\KeyBoard.h"
#include "HAL\StandardSPIPort.h"

#include "User\Oscilloscope.h"
#include "HAL\Beep.h"
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <arm_math.h>
#include "User\PointerDrawer.h"

#define WaveDraw_X 20
#define WaveDraw_Y 50

#define KEY_AmpDown 1
#define KEY_AmpUp 2
#define KEY_ACDCCoupling 3
#define KEY_MoveLeft 4
#define KEY_MoveRight 5
#define KEY_TimeLess 9
#define KEY_TimeMore 10
#define KEY_MoveUp 11
#define KEY_TriggerUp 12
#define KEY_Stop 13
#define KEY_BWAdd 17
#define KEY_BWSub 18
#define KEY_MoveDown 19
#define KEY_TriggerDown 20
#define KEY_TriggerMode 21
#define KEY_EquiSampling 25

void aTaskLauncher(void)
{
	u32 st = HAL_GetTick();
	u32 i = 0;
	FONTGROUP* FGs = NewReferenceSafe(new_noexcpt FONTGROUP("ASC12"));

	Oscilloscope Osc;
	while (1)
	{
		char buf[128];
		Osc.Do();
		i++;
		sprintf(buf, "Frame time:%ldus     ", 1000 * (HAL_GetTick() - st) / i);
		DrawStringHorizontal(g_LCDDC, FGs, buf, 700, 450, 0, 0, GREEN, BLACK);
	}

	FreeAndEraseReference(FGs);
}

u32 Oscilloscope::GetCurrentPrescaler(void)
{
	if (EquiSampling)
	{
		return EquivalentSamplingPrescaler;
	}
	else
	{
		return SamplePrescaler[SelectedTimeBase];
	}
}

Oscilloscope::Oscilloscope()
{
	UniGPIO_Handle MISO;
	UniGPIO_Handle MOSI;
	UniGPIO_Handle SCK;
	UniGPIO_Handle CS;
	StandardSPIPort_Init(0, &MISO, &MOSI, &SCK, &CS, NULL, NULL, NULL, NULL, NULL);
	LTC1446_Init(&OffsetDAC, &MISO, &MOSI, &SCK, &CS);
	StandardSPIPort_Init(1, &MISO, &MOSI, &SCK, &CS, NULL, NULL, NULL, NULL, NULL);
	LTC1446_Init(&TrigDAC, &MISO, &MOSI, &SCK, &CS);

	LTC1446_SetChannelAB(&OffsetDAC, 0, 0);
	LTC1446_SetChannelAB(&TrigDAC, 0, 0);

	GPIO_CPLD_InitPin(5, 0, true, &FrontEndACCoupling);
	GPIO_CPLD_InitPin(5, 1, true, &FrontEnd50Ohm);
	GPIO_CPLD_InitPin(5, 2, true, &FrontEndAttenuation);
	GPIO_CPLD_InitPin(5, 3, true, &IntermediateAmplifier);

	DrawLogo();
	WaveformDC = NewReferenceSafe(new_noexcpt CLIPPEDDC(g_LCDDC, WaveDraw_X, WaveDraw_Y, WaveDraw_X + DPOChannel::GetMinimumWidth(), WaveDraw_Y + DPOChannel::GetMinimumHeight(), true, false));
	TrigStatusDC = NewReferenceSafe(new_noexcpt CLIPPEDDC(g_LCDDC, 150, 0, 250, 50, false, false));
	TriggerInfoDC = NewReferenceSafe(new_noexcpt CLIPPEDDC(g_LCDDC, 280, 0, 450, 50, false, false));
	HorizontalInfoDC = NewReferenceSafe(new_noexcpt CLIPPEDDC(g_LCDDC, 480, 0, 700, 50, true, false));
	ChannelInfoDC = NewReferenceSafe(new_noexcpt CLIPPEDDC(g_LCDDC, WaveDraw_X, WaveDraw_Y + DPOChannel::GetMinimumHeight() + 5, 600, 480, true, false));

	FPGAAbstrast = new_noexcpt OscilloscopeFPGAAbstrast(this);

	Channels[0] = new_noexcpt DPOChannel(ChannelColors[0], WaveformDC);
	CurrentChannel = Channels[0];

	FPGAAbstrast->ForceUpdateFPGAConfig();
	SendGPIOConfigure();
	Channels[0]->SetEquiSamplingMode(EquiSampling);
}

Oscilloscope::~Oscilloscope()
{
	delete Channels[0];
	delete FPGAAbstrast;
	FreeAndEraseReference(ChannelInfoDC);
	FreeAndEraseReference(HorizontalInfoDC);
	FreeAndEraseReference(TriggerInfoDC);
	FreeAndEraseReference(TrigStatusDC);
	FreeAndEraseReference(WaveformDC);
}

void Oscilloscope::Do(void)
{
	bool UpdateSuccessful = false;
	ScanKey();
	if (Running)
	{
		UpdateSuccessful = UpdateWaveform();
		if (TrigMode == TrigMode_Single && UpdateSuccessful)
		{
			Running = false;
		}
	}
	ActiveSamplingRateAdjustment();
	UpdateTriggerStatus(DecodeTriggerStatus(FPGAAbstrast->IsLastTimeTriggered(), UpdateSuccessful));
	UpdateTriggerInfo();
	UpdateHorizontalInfo();
	UpdateChannelInfo();
}

void Oscilloscope::DrawLogo(void)
{
	FONTGROUP* FGLogo = NewReferenceSafe(new_noexcpt FONTGROUP("ASC48"));
	DrawStringHorizontal(g_LCDDC, FGLogo, "SALTY", 0, 0, 0, 50, 0xFE60, BLACK);
	FreeAndEraseReference(FGLogo);
}

Oscilloscope::TriggerStatus Oscilloscope::DecodeTriggerStatus(bool AutoTGd, bool UpdateSuccessful)
{
	if (Running)
	{
		switch (TrigMode)
		{
		case TrigMode_Single:
			return UpdateSuccessful ? TrigStatus_Trigged : TrigStatus_Wait;
		case TrigMode_Auto:
			return (AutoTGd && UpdateSuccessful) ? TrigStatus_Trigged : TrigStatus_Auto;
		case TrigMode_Normal:
			return UpdateSuccessful ? TrigStatus_Trigged : TrigStatus_Wait;
		default:
			return TrigStatus_Stop;
		}
	}
	else
	{
		return TrigStatus_Stop;
	}
}

void Oscilloscope::UpdateTriggerStatus(TriggerStatus Status)
{
	static u32 FlashCounter = 0;
	static bool FlashHighLight = true;
	FONTGROUP* FGTrig = NewReferenceSafe(new_noexcpt FONTGROUP("ASC48"));
	if (FlashCounter < HAL_GetTick())
	{
		FlashCounter = HAL_GetTick() + 1000;
		FlashHighLight = !FlashHighLight;
	}
	switch (Status)
	{
	case TrigStatus_Auto:
		DrawStringHorizontal(TrigStatusDC, FGTrig, "AUTO", 0, 1, 0, 0, FlashHighLight ? GREEN : 0x0320, BLACK);
		break;
	case TrigStatus_Run:
		DrawStringHorizontal(TrigStatusDC, FGTrig, "RUN ", 0, 1, 0, 0, GREEN, BLACK);
		break;
	case TrigStatus_Stop:
		DrawStringHorizontal(TrigStatusDC, FGTrig, "STOP", 0, 1, 0, 0, RED, BLACK);
		break;
	case TrigStatus_Trigged:
		DrawStringHorizontal(TrigStatusDC, FGTrig, "T'D ", 0, 1, 0, 0, GREEN, BLACK);
		break;
	case TrigStatus_Wait:
		DrawStringHorizontal(TrigStatusDC, FGTrig, "WAIT", 0, 1, 0, 0, FlashHighLight ? GREEN : 0x0320, BLACK);
		break;
	default:
		break;
	}
	FreeAndEraseReference(FGTrig);
	TrigStatusDC->Update();
}

void Oscilloscope::UpdateTriggerInfo(void)
{
	FONTGROUP* FGTriggerInfo = NewReferenceSafe(new_noexcpt FONTGROUP("ASC48"));
	switch (TrigMode)
	{
	case TrigMode_Single:
		DrawStringHorizontal(TriggerInfoDC, FGTriggerInfo, "Single", 0, 1, 0, 0, GREEN, BLACK);
		break;
	case TrigMode_Auto:
		DrawStringHorizontal(TriggerInfoDC, FGTriggerInfo, "AutoTg", 0, 1, 0, 0, GREEN, BLACK);
		break;
	case TrigMode_Normal:
		DrawStringHorizontal(TriggerInfoDC, FGTriggerInfo, "NormTg", 0, 1, 0, 0, GREEN, BLACK);
		break;
	}
	FreeAndEraseReference(FGTriggerInfo);
	TriggerInfoDC->Update();
}

void Oscilloscope::UpdateHorizontalInfo(void)
{
	FONTGROUP* FGHorizontalInfo = NewReferenceSafe(new_noexcpt FONTGROUP("ASC48"));
	char buf[128];
	u32 TimeBaseValue = TimeBase[SelectedTimeBase];
	pcstr TimeUnit = "";
	if (TimeBaseValue >= 1000000)
	{
		TimeBaseValue /= 1000000;
		TimeUnit = "ms";
	}
	else if (TimeBaseValue >= 1000)
	{
		TimeBaseValue /= 1000;
		TimeUnit = "us";
	}
	else
	{
		TimeBaseValue /= 1;
		TimeUnit = "ns";
	}
	sprintf(buf, "H %ld %s %s ", TimeBaseValue, TimeUnit, EquiSampling ? "Eq" : "Re");
	HorizontalInfoDC->Fill(0, 0, HorizontalInfoDC->GetWidth(), HorizontalInfoDC->GetHeight(), BLACK);
	DrawStringHorizontal(HorizontalInfoDC, FGHorizontalInfo, buf, 0, 0, 0, 0, WHITE, BLACK);
	FreeAndEraseReference(FGHorizontalInfo);
	HorizontalInfoDC->Update();
}

bool Oscilloscope::UpdateWaveform(void)
{
	bool BackgroundCleared = false;
	bool Updated = false;
	for (u8 i = 0; i < 1; i++)
	{
		u32 BufLength = Channels[0]->GetDataCountToTransmit();
		u16* Buf = (u16*)malloc(BufLength * sizeof(u16));
		if (Buf)
		{
			u32 ReadSize = 0;
			if (FPGAAbstrast->ReteriveValue(Buf, BufLength, &ReadSize))
			{
				if (!BackgroundCleared)
				{
					CurrentChannel->DrawGrid();
				}
				u32 RefCnt;
				u32 UnkCnt;
				FPGAAbstrast->GetFrequencyMeterValue(&RefCnt, &UnkCnt, NULL);
				Channels[0]->SamplingPeriod = (1.0 / SamplingClock) * (FPGAAbstrast->GetCurrentPrescaler() + 1);
				Channels[0]->WavePeriod = RefCnt * 1.0 / FPGAClock / UnkCnt;
				Channels[0]->ProcessData(Buf, ReadSize);
				if (TimeBase[SelectedTimeBase] > 10000000)
				{
					Channels[0]->EnablePhosphor = false;
				}
				else
				{
					Channels[0]->EnablePhosphor = true;
				}
				Channels[0]->TriggerPosition = TriggerPosition;
				Channels[0]->FPGATriggerPosition = FPGAAbstrast->GetCurrentTriggerPosition();
				Channels[0]->WholeTime = 1e-9 * TimeBase[SelectedTimeBase] * WaveDraw_DivCountX;
				Channels[0]->Draw();

				//DrawHorizontalPointerToRight(WaveformDC, "1", 1, 1, 20, 20, YELLOW, BLACK, NULL);

				Updated = true;
			}
			free(Buf);
		}
	}
	if (Updated)
	{
		CurrentChannel->DrawTrigger();
		DisplayFrequencyMeter();
		WaveformDC->Update();
		return true;
	}
	else
	{
		return false;
	}
}

void Oscilloscope::DisplayFrequencyMeter(void)
{
	u32 Ref;
	u32 Unk;
	u32 High;
	float Freq;
	float DutyCycle;
	char Buf[64];
	FPGAAbstrast->GetFrequencyMeterValue(&Ref, &Unk, &High);
	Freq = (float)FPGAClock * Unk / Ref;
	DutyCycle = (float)High / Ref;
	printf("Duty=%f\n\r", DutyCycle * 100.0);
	if (Freq > 15.0)
	{
		const pcstr UnitTable[3] = { "Hz","KHz","MHz" };
		u8 UnitIndex = 0;
		while (Freq >= 1000.0 && UnitIndex < 3 - 1)
		{
			UnitIndex++;
			Freq /= 1000.0;
		}
		sprintf(Buf, "%f %s", Freq, UnitTable[UnitIndex]);
	}
	else
	{
		strcpy(Buf, "<15Hz");
	}
	FONTGROUP* FGFreq = NewReferenceSafe(new_noexcpt FONTGROUP("ASC24"));
	DrawStringHorizontal(WaveformDC, FGFreq, Buf, WaveformDC->GetWidth() - 200, 10, 0, 0, WHITE, BLACK);
	FreeAndEraseReference(FGFreq);
}

void Oscilloscope::UpdateChannelInfo(void)
{
	FONTGROUP* FGChannelInfo = NewReferenceSafe(new_noexcpt FONTGROUP("ASC24"));
	char buf[128];
	sprintf(buf, "Ch%d %s", 1, Channels[0]->ACCoupling ? "AC" : "DC");
	ChannelInfoDC->Fill(0, 0, ChannelInfoDC->GetWidth(), ChannelInfoDC->GetHeight(), BLACK);
	DrawHorizontalPointerToRight(ChannelInfoDC, buf, 0, 0, 100, 30, YELLOW, BLACK, FGChannelInfo);
	FreeAndEraseReference(FGChannelInfo);
	ChannelInfoDC->Update();
}

void Oscilloscope::ScanKey(void)
{
	u8 Key = KeyBoard_GetKey_Repeat();
	if (Key)
	{
		switch (Key)
		{
		case KEY_TimeLess:
			if (SelectedTimeBase > 0)
			{
				SelectedTimeBase--;
			}
			break;
		case KEY_TimeMore:
			if (SelectedTimeBase < sizeof(TimeBase) / sizeof(TimeBase[0]) - 1)
			{
				SelectedTimeBase++;
			}
			break;
		case KEY_ACDCCoupling:
			CurrentChannel->ACCoupling = !CurrentChannel->ACCoupling;
			break;
		case KEY_Stop:
			Running = !Running;
			break;
		case KEY_MoveLeft:
			TriggerPosition -= 0.02;
			if (TriggerPosition < 0.0)
			{
				TriggerPosition = 0.0;
			}
			break;
		case KEY_MoveRight:
			TriggerPosition += 0.02;
			if (TriggerPosition > 1.0)
			{
				TriggerPosition = 1.0;
			}
			break;
		case KEY_TriggerMode:
			switch (TrigMode)
			{
			default:
			case TrigMode_Single:
				TrigMode = TrigMode_Auto;
				break;
			case TrigMode_Auto:
				TrigMode = TrigMode_Normal;
				break;
			case TrigMode_Normal:
				TrigMode = TrigMode_Single;
				break;
			}
			break;
		case KEY_EquiSampling:
			EquiSampling = !EquiSampling;
			break;
		default:
			break;
		}
		Channels[0]->SetEquiSamplingMode(EquiSampling);
		FPGAAbstrast->ForceUpdateFPGAConfig();
		SendGPIOConfigure();
		Beep(10);
	}
}

void Oscilloscope::SendGPIOConfigure(void)
{
	UniGPIO_SetVal(&FrontEndACCoupling, Channels[0]->ACCoupling);
	UniGPIO_SetVal(&FrontEnd50Ohm, Channels[0]->Input50Ohm);
	UniGPIO_SetVal(&FrontEndAttenuation, Channels[0]->InputAttenuation);
	UniGPIO_SetVal(&IntermediateAmplifier, Channels[0]->IntermediateAmplifier);
}

u32 Oscilloscope::CalcEquivalentSamplingPrescaler(float Period)
{
	u32 Maxn = 500 * Period / MinSamplingPeriod + 1;
	u32 BestPrescaler = 0;
	float Error = 99999.0;
	float RedundantPeriod = 1.0 / DPODataCount;
	if (Maxn < 50000)
	{
		for (u16 n = 1; n <= Maxn; n++)
		{
			float Ts = MinSamplingPeriod * n;
			float ThisError;
			while (Ts >= Period)
			{
				Ts -= Period;
			}
			ThisError = fabs(Ts / Period - RedundantPeriod);
			if (ThisError < Error)
			{
				BestPrescaler = n;
				Error = ThisError;
			}
		}
		//printf("BestPrescaler %d \n\r", BestPrescaler);
		if (BestPrescaler)
		{
			BestPrescaler--;
		}
	}
	else
	{
		BestPrescaler = 0;
	}
	return 0;
}

void Oscilloscope::ActiveSamplingRateAdjustment(void)
{
	if (EquiSampling)
	{
		u32 Ref;
		u32 Unk;
		float Period;
		FPGAAbstrast->GetFrequencyMeterValue(&Ref, &Unk, NULL);
		Period = Ref * 1.0 / FPGAClock / Unk;
		EquivalentSamplingPrescaler = CalcEquivalentSamplingPrescaler(Period);
	}
}
