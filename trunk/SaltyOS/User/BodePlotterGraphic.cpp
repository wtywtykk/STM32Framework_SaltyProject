#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\DC.h"
#include "Kernel\GUI\Shape\Line.h"
#include "Kernel\GUI\Shape\Circle.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "User\BodePlotterGraphic.h"
#include <math.h>

BodePlotterGraphic::~BodePlotterGraphic(void)
{
	FreeAndEraseReference(DrawingDC);
}

void BodePlotterGraphic::AssignDC(DC* dc)
{
	FreeAndEraseReference(DrawingDC);
	DrawingDC = NewReferenceSafe(dc);
}

void BodePlotterGraphic::SetFreqParam(double StartFreq, double EndFreq, bool LogScanType)
{
	Start = StartFreq;
	End = EndFreq;
	LogScan = LogScanType;
}

void BodePlotterGraphic::SetAmptParam(double BaseAmpt, double AmptPerDiv, bool LogAmptType)
{
	Base = BaseAmpt;
	PerDiv = AmptPerDiv;
	LogAmpt = LogAmptType;
}

void BodePlotterGraphic::Draw(BodePlotterDataStore* LastFull, BodePlotterDataStore* CurrentData)
{
	DrawGrid();
	if (CurrentData)
	{
		double CurScanEnd = CurrentData->GetEndFreq();
		DrawDataStore(CurrentData, Start, CurScanEnd);
		if (LastFull)
		{
			DrawDataStore(LastFull, CurScanEnd, End);
		}
		DrawCircle(DrawingDC, FreqToCoord(CurScanEnd), AmptToCoord(CurrentData->GetData(CurrentData->GetFreqIndex(CurScanEnd))), 2, UpdateColor);
	}
	else
	{
		if (LastFull)
		{
			DrawDataStore(LastFull, Start, End);
		}
	}
}

void BodePlotterGraphic::DrawGrid(void)
{
	DrawingDC->Fill(0, 0, DrawingDC->GetWidth(), DrawingDC->GetHeight(), BLACK);

	for (u16 divx = 1; divx < DivCountX; divx++)
	{
		bool Draw = false;
		for (u16 y = 0; y < Height; y++)
		{
			if (Draw)
			{
				DrawingDC->SetPixel(divx * PixelsPerDivX, y, DGRAY);
			}
			Draw = !Draw;
		}
	}

	for (u16 divy = 1; divy < DivCountY; divy++)
	{
		bool Draw = false;
		for (u16 x = 0; x < Width; x++)
		{
			if (Draw)
			{
				DrawingDC->SetPixel(x, divy * PixelsPerDivY, DGRAY);
			}
			Draw = !Draw;
		}
	}

	for (u16 divx = 0; divx < DivCountX; divx++)
	{
		for (u16 i = 0; i < 5; i++)
		{
			u16 x = divx * PixelsPerDivX + i * PixelsPerDivX / 5;
			DrawLine(DrawingDC, x, 0, x, 5, DGRAY);
			DrawLine(DrawingDC, x, Height - 5, x, Height, DGRAY);
		}
	}

	for (u16 divy = 0; divy < DivCountY; divy++)
	{
		for (u16 i = 0; i < 5; i++)
		{
			u16 y = divy * PixelsPerDivY + i * PixelsPerDivY / 5;
			DrawLine(DrawingDC, 0, y, 5, y, DGRAY);
			DrawLine(DrawingDC, Width - 5, y, Width, y, DGRAY);
		}
	}
	DrawLine(DrawingDC, 0, 0, Width, 0, LGRAY);
	DrawLine(DrawingDC, 0, 0, 0, Height, LGRAY);
	DrawLine(DrawingDC, Width, 0, Width, Height, LGRAY);
	DrawLine(DrawingDC, 0, Height, Width, Height, LGRAY);
}

GUIPOS BodePlotterGraphic::FreqToCoord(double Freq)
{
	float Ret;
	if (LogScan)
	{
		Ret = Width * log(Freq - Start) / log(End - Start) + 0.5;
	}
	else
	{
		Ret = Width * (Freq - Start) / (End - Start) + 0.5;
	}
	if (Ret < 0)
	{
		Ret = 0;
	}
	if (Ret >= Width)
	{
		Ret = Width - 1;
	}
	return Ret;
}

GUIPOS BodePlotterGraphic::AmptToCoord(double Ampt)
{
	float Ret;
	if (LogAmpt)
	{
		Ret = PixelsPerDivY * (log(Ampt / Base)) / log(PerDiv) + 0.5;
	}
	else
	{
		Ret = Height - PixelsPerDivY * (Ampt / Base) / PerDiv + 0.5;
	}
	if (Ret < 0)
	{
		Ret = 0;
	}
	if (Ret >= Height)
	{
		Ret = Height - 1;
	}
	return Ret;
}

void BodePlotterGraphic::DrawDataStore(BodePlotterDataStore* DataStore, double StartFreq, double EndFreq)
{
	u32 StartIndex = DataStore->GetFreqIndex(StartFreq);
	u32 EndIndex = DataStore->GetFreqIndex(EndFreq);
	double DataStartFreq = DataStore->GetFreq(StartIndex);
	double DataEndFreq = DataStore->GetFreq(EndIndex);
	BodePlotterDataType Data;
	u32 i;

	Data = DataStore->GetData(StartIndex);
	DrawLine(DrawingDC, FreqToCoord(StartFreq), AmptToCoord(Data), FreqToCoord(DataStartFreq), AmptToCoord(Data), Color);

	for (i = StartIndex; i < EndIndex; i++)
	{
		DrawLine(DrawingDC, FreqToCoord(DataStore->GetFreq(i)), AmptToCoord(DataStore->GetData(i)), FreqToCoord(DataStore->GetFreq(i + 1)), AmptToCoord(DataStore->GetData(i + 1)), Color);
	}

	Data = DataStore->GetData(EndIndex);
	DrawLine(DrawingDC, FreqToCoord(DataEndFreq), AmptToCoord(Data), FreqToCoord(EndFreq), AmptToCoord(Data), Color);
}
