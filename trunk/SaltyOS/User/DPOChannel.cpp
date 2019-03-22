#include "HAL\HCommon.h"
#include "HAL\FPGAParPort.h"
#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "Kernel\GUI\Shape\Line.h"
#include "Kernel\GUI\Shape\Circle.h"
#include "Kernel\GUI\DC\ClippedDC.h"
#include "User\PointerDrawer.h"
#include "User\DPOChannel.h"
#include <malloc.h>

DPOChannel::DPOChannel(PIXEL Color, DC * DrawingDC)
{
	m_DC = NewReferenceSafe(DrawingDC);
	DrawingColor = Color;
	for (u8 i = 0; i < DPOLayer; i++)
	{
		ChannelColors[i] = DimColor(Color, DPOLayer - i);
		DataPtr[i] = &Data[i];
		Data[i].Length = 0;
	}
	EquiDecoder = NULL;
}

DPOChannel::~DPOChannel(void)
{
	if (EquiDecoder)
	{
		delete EquiDecoder;
		EquiDecoder = NULL;
	}
	FreeAndEraseReference(m_DC);
}

void DPOChannel::ProcessData(u16* Buf, u32 BufferLength)
{
	if (BufferLength)
	{
		if (DataPtr[0]->Length >= DPODataCount)
		{
			//Buffer0 is full
			//Shift the buffers
			DPOWaveRecord* t = DataPtr[DPOLayer - 1];
			for (u8 i = DPOLayer - 1; i > 0; i--)
			{
				DataPtr[i] = DataPtr[i - 1];
			}
			DataPtr[0] = t;
			DataPtr[0]->Length = 0;
			if (EquiDecoder)
			{
				EquiDecoder->SwitchBuffer(DataPtr[0]->Data, DPODataCount);
			}
		}
		if (EquiDecoder)
		{
			EquiDecoder->ChangePeriod(SamplingPeriod, WavePeriod);
			float* fBuf = (float*)malloc(sizeof(float) * BufferLength);
			TransformADCValueToVoltage(Buf, fBuf, BufferLength);
			EquiDecoder->Process(fBuf, BufferLength);
			free(fBuf);
			DataPtr[0]->Length = EquiDecoder->GetDataCount();
		}
		else
		{
			//Fill Buffer0
			if (BufferLength > DPODataCount - DataPtr[0]->Length)
			{
				BufferLength = DPODataCount - DataPtr[0]->Length;
			}
			TransformADCValueToVoltage(Buf, &DataPtr[0]->Data[DataPtr[0]->Length], BufferLength);
			DataPtr[0]->Length += BufferLength;
		}
	}
}

void DPOChannel::Draw(void)
{
	if (EquiDecoder)
	{
		EquiDecoder->AlignTrigger(0.0, 0.01);
		if (EnablePhosphor)
		{
			for (u16 i = 0; i < DPOLayer; i++)
			{
				DrawWaveformEquivalentSampling(DataPtr[DPOLayer - 1 - i], ChannelColors[DPOLayer - 1 - i]);
			}
		}
		else
		{
			DrawWaveformEquivalentSampling(DataPtr[0], ChannelColors[0]);
		}
	}
	else
	{
		if (EnablePhosphor)
		{
			for (u16 i = 0; i < DPOLayer; i++)
			{
				DrawWaveformRealTimeSampling(DataPtr[DPOLayer - 1 - i], ChannelColors[DPOLayer - 1 - i]);
			}
		}
		else
		{
			DrawWaveformRealTimeSampling(DataPtr[0], ChannelColors[0]);
		}
	}
}

void DPOChannel::DrawGrid(void)
{
	m_DC->Fill(0, 0, m_DC->GetWidth(), m_DC->GetHeight(), BLACK);

	for (u16 divx = 1; divx < WaveDraw_DivCountX; divx++)
	{
		bool Draw = false;
		for (u16 y = 0; y < WaveDraw_Height; y++)
		{
			if (Draw)
			{
				m_DC->SetPixel(divx * WaveDraw_PixelsPerDivX, y, DGRAY);
			}
			Draw = !Draw;
		}
	}

	for (u16 divy = 1; divy < WaveDraw_DivCountY; divy++)
	{
		bool Draw = false;
		for (u16 x = 0; x < WaveDraw_Width; x++)
		{
			if (Draw)
			{
				m_DC->SetPixel(x, divy * WaveDraw_PixelsPerDivY, DGRAY);
			}
			Draw = !Draw;
		}
	}

	for (u16 divx = 0; divx < WaveDraw_DivCountX; divx++)
	{
		for (u16 i = 0; i < 5; i++)
		{
			u16 x = divx * WaveDraw_PixelsPerDivX + i * WaveDraw_PixelsPerDivX / 5;
			DrawLine(m_DC, x, 0, x, 5, DGRAY);
			DrawLine(m_DC, x, WaveDraw_Height / 2 - 2, x, WaveDraw_Height / 2 + 2, DGRAY);
			DrawLine(m_DC, x, WaveDraw_Height - 5, x, WaveDraw_Height, DGRAY);
		}
	}

	for (u16 divy = 0; divy < WaveDraw_DivCountY; divy++)
	{
		for (u16 i = 0; i < 5; i++)
		{
			u16 y = divy * WaveDraw_PixelsPerDivY + i * WaveDraw_PixelsPerDivY / 5;
			DrawLine(m_DC, 0, y, 5, y, DGRAY);
			DrawLine(m_DC, WaveDraw_Width / 2 - 2, y, WaveDraw_Width / 2 + 2, y, DGRAY);
			DrawLine(m_DC, WaveDraw_Width - 5, y, WaveDraw_Width, y, DGRAY);
		}
	}
	DrawLine(m_DC, 0, 0, WaveDraw_Width, 0, LGRAY);
	DrawLine(m_DC, 0, 0, 0, WaveDraw_Height, LGRAY);
	DrawLine(m_DC, WaveDraw_Width, 0, WaveDraw_Width, WaveDraw_Height, LGRAY);
	DrawLine(m_DC, 0, WaveDraw_Height, WaveDraw_Width, WaveDraw_Height, LGRAY);
}

u16 DPOChannel::GetMinimumWidth(void)
{
	return WaveDraw_Width + 1;
}

u16 DPOChannel::GetMinimumHeight(void)
{
	return WaveDraw_Height + 1;
}

void DPOChannel::SetFullScaleAmpitude(float FullScale)
{
	DisplayScale = FullScale;
}

void DPOChannel::DrawTrigger(void)
{
	DrawVerticalPointerToBottom(m_DC, "T", WaveDraw_Width * TriggerPosition - 10, 0, 20, 30, YELLOW, BLACK, NULL);
}

u32 DPOChannel::GetDataCountToTransmit(void)
{
	if (DPODataCount == DataPtr[0]->Length)
	{
		return DPODataCount;
	}
	else
	{
		return DPODataCount - DataPtr[0]->Length;
	}
}

void DPOChannel::SetEquiSamplingMode(bool IsEquiSamplingMode)
{
	if (IsEquiSamplingMode)
	{
		if (EquiDecoder == NULL)
		{
			Clear();
			EquiDecoder = new_noexcpt EquivalentSamplingDecoder(Data[0].Data, DPODataCount);
		}
	}
	else
	{
		if (EquiDecoder)
		{
			Clear();
			delete EquiDecoder;
			EquiDecoder = NULL;
		}
	}
}

void DPOChannel::Clear(void)
{
	for (u8 i = 0; i < DPOLayer; i++)
	{
		Data[i].Length = 0;
	}
}

PIXEL DPOChannel::DimColor(PIXEL OrigColor, u8 Weight)
{
	u16 BlueComponent = (OrigColor & BLUE) >> 0;
	u16 GreenComponent = (OrigColor & GREEN) >> 5;
	u16 RedComponent = (OrigColor & RED) >> (5 + 6);
	BlueComponent = BlueComponent * Weight / DPOLayer;
	GreenComponent = GreenComponent * Weight / DPOLayer;
	RedComponent = RedComponent * Weight / DPOLayer;
	BlueComponent &= 0x1F;
	GreenComponent &= 0x3F;
	RedComponent &= 0x1F;
	return RedComponent << (5 + 6) | GreenComponent << 5 | BlueComponent;
}

void DPOChannel::DrawWaveformRealTimeSampling(DPOWaveRecord* DrawingData, PIXEL Color)
{
	for (u16 i = 1; i < DrawingData->Length; i++)
	{
		DrawLine(m_DC
			, (i - 1) * WaveDraw_Width * SamplingPeriod / WholeTime //DrawTrigger
			, WaveDraw_Height / 2 - WaveDraw_Height / 2 * DisplayScale * (DrawingData->Data[i - 1] - AmpitudeOffset)
			, i * WaveDraw_Width * SamplingPeriod / WholeTime //DrawTrigger
			, WaveDraw_Height / 2 - WaveDraw_Height / 2 * DisplayScale * (DrawingData->Data[i] - AmpitudeOffset)
			, Color);
	}
}

void DPOChannel::DrawWaveformEquivalentSampling(DPOWaveRecord* DrawingData, PIXEL Color)
{
	float SinglePeriodWidth = WavePeriod / WholeTime * WaveDraw_Width;
	for (u16 i = 0; i < DPODataCount; i++)
	{
		if (EquivalentSamplingDecoder::IsValidValue(DrawingData->Data[i]))
		{
			float PointX = SinglePeriodWidth * (s16)i / DPODataCount + WaveDraw_Width * TriggerPosition;
			float PointY = WaveDraw_Height / 2 - WaveDraw_Height / 2 * DisplayScale * (DrawingData->Data[i] - AmpitudeOffset);
			float CurrentX;
			CurrentX = PointX;
			while (CurrentX >= 0)
			{
				m_DC->SetPixel(CurrentX, PointY, Color);
				CurrentX -= SinglePeriodWidth;
			}
			CurrentX = PointX;
			while (CurrentX <= WaveDraw_Width)
			{
				m_DC->SetPixel(CurrentX, PointY, Color);
				CurrentX += SinglePeriodWidth;
			}
		}
	}
}

void DPOChannel::TransformADCValueToVoltage(u16* ADCBuf, float* VoltBuf, u32 BufferLength)
{
	for (u16 i = 0; i < BufferLength; i++)
	{
		u16 Val = *(ADCBuf + i) & 0xFFF;
		s16 SignedVal = (s16)(Val << 4);
		SignedVal /= 1 << 4;
		VoltBuf[i] = SignedVal * AttenuationFactor / ADCFullScale;
	}
}
