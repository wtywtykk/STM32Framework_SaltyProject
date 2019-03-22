#include "Kernel\GUI\GUICommon.h"
#include "Kernel\GUI\DC\DC.h"
#include "Kernel\GUI\Picture\DirectDataPic.h"
#include <assert.h>
#include <stdlib.h>

DIRECTDATAPIC::DIRECTDATAPIC(GUIPOS PicWidth, GUIPOS PicHeight, const PIXEL* PicData)
{
	assert(PicWidth > 0);
	assert(PicHeight > 0);
	assert(Data != NULL);
	Width = PicWidth;
	Height = PicHeight;
	Data = PicData;
}

DIRECTDATAPIC::~DIRECTDATAPIC(void)
{
}

void DIRECTDATAPIC::Draw(DC * dc, GUIPOS X, GUIPOS Y)
{
	if (X < 0 || Y < 0)
	{
		DrawWithNegativeCoord(dc, X, Y);
	}
	else
	{
		if (dc->SupportNativeClip())
		{
			DrawWithNativeClip(dc, X, Y);
		}
		else
		{
			DrawWithoutNativeClip(dc, X, Y);
		}
	}
}

PIXEL DIRECTDATAPIC::GetPixel(GUIPOS X, GUIPOS Y)
{
	if (CheckCoord(X, Y))
	{
		return Data[X + Y * Width];
	}
	else
	{
		return 0;
	}
}

bool DIRECTDATAPIC::CheckCoord(GUIPOS X, GUIPOS Y)
{
	if (X >= 0 && Y >= 0 && X < Width && Y < Height)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void DIRECTDATAPIC::DrawWithNativeClip(DC* dc, GUIPOS X, GUIPOS Y)
{
	dc->StartNativeClip(X, Y, X + Width, Y + Height);
	dc->BlockWrite(Data, Width * Height);
	dc->EndNativeClip();
}

void DIRECTDATAPIC::DrawWithoutNativeClip(DC* dc, GUIPOS X, GUIPOS Y)
{
	GUIPOS EndY = Y + Height;
	const PIXEL* BufCur = Data;
	for (GUIPOS CurY = Y; CurY < EndY; CurY++)
	{
		dc->SetPos(X, CurY);
		for (GUIPOS CurX = 0; CurX < Width; CurX++)
		{
			dc->SequenceWrite(*BufCur);
			BufCur++;
		}
	}
}

void DIRECTDATAPIC::DrawWithNegativeCoord(DC* dc, GUIPOS X, GUIPOS Y)
{
	GUIPOS CurY = Y;
	GUIPOS EndY = Y + Height;
	if (CurY < 0)
	{
		CurY = 0;
	}
	for (; CurY < EndY; CurY++)
	{
		GUIPOS CurX = X;
		GUIPOS EndX = X + Width;
		if (CurX < 0)
		{
			CurX = 0;
		}
		const PIXEL* BufCur = Data + (CurY - Y) * Width + (CurX - X);
		dc->SetPos(CurX, CurY);
		for (; CurX < EndX; CurX++)
		{
			dc->SequenceWrite(*BufCur);
			BufCur++;
		}
	}
}
