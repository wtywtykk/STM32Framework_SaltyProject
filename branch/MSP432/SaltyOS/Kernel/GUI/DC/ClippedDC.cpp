#include "Kernel\GUI\GUICommon.h"
#include "Kernel\Common\KObject.h"
#include "Kernel\GUI\DC\DC.h"
#include "ClippedDC.h"
#include <assert.h>
#include <stdlib.h>

CLIPPEDDC::CLIPPEDDC(DC * dc, GUIPOS X1, GUIPOS Y1, GUIPOS X2, GUIPOS Y2, bool BufferIfPossible, bool InitWithOrigContent)
{
	assert(dc != NULL);
	ParentDC = NewReferenceSafe(dc);
	if (X1 > X2)
	{
		GUIPOS t = X1;
		X1 = X2;
		X2 = t;
	}
	if (Y1 > Y2)
	{
		GUIPOS t = Y1;
		Y1 = Y2;
		Y2 = t;
	}
	SourceX = X1;
	SourceY = Y1;
	Width = X2 - X1;
	Height = Y2 - Y1;
	assert(Width != 0);
	if (Width == 0)
	{
		Width = 1;
	}
	assert(Height != 0);
	if (Height == 0)
	{
		Height = 1;
	}
	CurrentX = 0;
	CurrentY = 0;
	if (BufferIfPossible)
	{
		Buffer = (PIXEL*)malloc(sizeof(PIXEL) * Width * Height);
	}
	else
	{
		Buffer = NULL;
	}
	if (InitWithOrigContent)
	{
		CopySource();
	}
	if (Buffer == NULL && X1 == 0 && Y1 == 0 && X2 == dc->GetWidth() && Y2 == dc->GetHeight())
	{
		FullyTransparent = true;
	}
	else
	{
		FullyTransparent = false;
	}
}

CLIPPEDDC::~CLIPPEDDC(void)
{
	Update();
	free(Buffer);
	Buffer = NULL;
	FreeAndEraseReference(ParentDC);
}

void CLIPPEDDC::Fill(GUIPOS X1, GUIPOS Y1, GUIPOS X2, GUIPOS Y2, PIXEL Color)
{
	if (FullyTransparent)
	{
		ParentDC->Fill(X1, Y1, X2, Y2, Color);
	}
	else
	{
		if (X1 < 0)
		{
			X1 = 0;
		}
		if (Y1 < 0)
		{
			Y1 = 0;
		}
		if (X2 > Width)
		{
			X2 = Width;
		}
		if (Y2 > Height)
		{
			Y2 = Height;
		}
		if (X1 < X2 && Y1 < Y2)
		{
			if (Buffer)
			{
				for (GUIPOS y = Y1; y < Y2; y++)
				{
					PIXEL* LineBase = Buffer + y * Width;
					for (GUIPOS x = X1; x < X2; x++)
					{
						*(LineBase + x) = Color;
					}
				}
			}
			else
			{
				ParentDC->Fill(SourceX + X1, SourceY + Y1, SourceX + X2, SourceY + Y2, Color);
			}
		}
	}
}

void CLIPPEDDC::SetPos(GUIPOS X, GUIPOS Y)
{
	if (FullyTransparent)
	{
		ParentDC->SetPos(X, Y);
	}
	else
	{
		if (CheckCoord(X, Y))
		{
			CurrentX = X;
			CurrentY = Y;
		}
	}
}

void CLIPPEDDC::SequenceWrite(PIXEL Color)
{
	if (FullyTransparent)
	{
		ParentDC->SequenceWrite(Color);
	}
	else
	{
		if (Buffer)
		{
			Buffer[CurrentX + CurrentY * Width] = Color;
		}
		else
		{
			ParentDC->SetPixel(SourceX + CurrentX, SourceY + CurrentY, Color);
		}
		AddressIncreasement();
	}
}

void CLIPPEDDC::SetPixel(GUIPOS X, GUIPOS Y, PIXEL Color)
{
	if (FullyTransparent)
	{
		ParentDC->SetPixel(X, Y, Color);
	}
	else
	{
		if (CheckCoord(X, Y))
		{
			if (Buffer)
			{
				Buffer[X + Y * Width] = Color;
			}
			else
			{
				ParentDC->SetPixel(SourceX + X, SourceY + Y, Color);
			}
		}
	}
}

PIXEL CLIPPEDDC::GetPixel(GUIPOS X, GUIPOS Y)
{
	if (FullyTransparent)
	{
		return ParentDC->GetPixel(X, Y);
	}
	else
	{
		if (CheckCoord(X, Y))
		{
			if (Buffer)
			{
				return Buffer[X + Y * Width];
			}
			else
			{
				return ParentDC->GetPixel(SourceX + X, SourceY + Y);
			}
		}
		else
		{
			return 0;
		}
	}
}

PIXEL CLIPPEDDC::SequenceRead(void)
{
	if (FullyTransparent)
	{
		return ParentDC->SequenceRead();
	}
	else
	{
		PIXEL Res;
		if (Buffer)
		{
			Res = Buffer[CurrentX + CurrentY * Width];
		}
		else
		{
			Res = ParentDC->GetPixel(SourceX + CurrentX, SourceY + CurrentY);
		}
		AddressIncreasement();
		return Res;
	}
}

GUIPOS CLIPPEDDC::GetWidth(void)
{
	return Width;
}

GUIPOS CLIPPEDDC::GetHeight(void)
{
	return Height;
}

bool CLIPPEDDC::SupportNativeClip(void)
{
	if (FullyTransparent)
	{
		return ParentDC->SupportNativeClip();
	}
	else
	{
		return false;
	}
}

void CLIPPEDDC::StartNativeClip(GUIPOS X1, GUIPOS Y1, GUIPOS X2, GUIPOS Y2)
{
	if (FullyTransparent)
	{
		ParentDC->StartNativeClip(X1, Y1, X2, Y2);
	}
	else
	{
		assert(false);
	}
}

void CLIPPEDDC::EndNativeClip(void)
{
	if (FullyTransparent)
	{
		ParentDC->EndNativeClip();
	}
	else
	{
		assert(false);
	}
}

void CLIPPEDDC::BlockWrite(const PIXEL* Data, u32 Length)
{
	if (FullyTransparent)
	{
		ParentDC->BlockWrite(Data, Length);
	}
	else
	{
		if (Buffer)
		{
			PIXEL* StartPtr = &Buffer[CurrentX + CurrentY * Width];
			while (Length--)
			{
				*(StartPtr++) = *(Data++);
			}
		}
		else
		{
			while (Length--)
			{
				SequenceWrite(*(Data++));
			}
		}
	}
}

void CLIPPEDDC::Update(void)
{
	if (!FullyTransparent && Buffer)
	{
		if (SourceX < 0 || SourceY < 0)
		{
			UpdateWithNegativeCoord();
		}
		else
		{
			if (ParentDC->SupportNativeClip())
			{
				UpdateWithNativeClip();
			}
			else
			{
				UpdateWithoutNativeClip();
			}
		}
	}
}

bool CLIPPEDDC::IsActuallyBuffered(void)
{
	return Buffer ? true : false;
}

void CLIPPEDDC::AddressIncreasement(void)
{
	CurrentX++;
	if (CurrentX >= Width)
	{
		CurrentX = 0;
		CurrentY++;
		if (CurrentY >= Height)
		{
			CurrentY = 0;
		}
	}
}

bool CLIPPEDDC::CheckCoord(GUIPOS X, GUIPOS Y)
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

void CLIPPEDDC::CopySource(void)
{
	if (SourceX < 0 || SourceY < 0)
	{
		UpdateWithNegativeCoord();
	}
	else
	{
		if (Buffer)
		{
			if (ParentDC->SupportNativeClip())
			{
				CopySourceWithNativeClip();
			}
			else
			{
				CopySourceWithoutNativeClip();
			}
		}
	}
}

void CLIPPEDDC::CopySourceWithNativeClip(void)
{
	ParentDC->StartNativeClip(SourceX, SourceY, SourceX + Width, SourceY + Height);
	PIXEL* EndCur = Buffer + Width * Height;
	for (PIXEL* BufCur = Buffer; BufCur < EndCur; BufCur++)
	{
		*BufCur = ParentDC->SequenceRead();
	}
	ParentDC->EndNativeClip();
}

void CLIPPEDDC::CopySourceWithoutNativeClip(void)
{
	GUIPOS EndY = SourceY + Height;
	PIXEL* BufCur = Buffer;
	for (GUIPOS y = SourceY; y < EndY; y++)
	{
		ParentDC->SetPos(SourceX, y);
		for (GUIPOS x = 0; x < Width; x++)
		{
			*BufCur = ParentDC->SequenceRead();
			BufCur++;
		}
	}
}

void CLIPPEDDC::CopySourceWithNegativeCoord(void)
{
	GUIPOS y = SourceY;
	GUIPOS EndY = SourceY + Height;
	if (y < 0)
	{
		y = 0;
	}
	for (; y < EndY; y++)
	{
		GUIPOS x = SourceX;
		GUIPOS EndX = SourceX + Width;
		if (x < 0)
		{
			x = 0;
		}
		PIXEL* BufCur = Buffer + (y - SourceY) * Width + (x - SourceX);
		ParentDC->SetPos(x, y);
		for (; x < EndX; x++)
		{
			*BufCur = ParentDC->SequenceRead();
			BufCur++;
		}
	}
}

void CLIPPEDDC::UpdateWithNativeClip(void)
{
	ParentDC->StartNativeClip(SourceX, SourceY, SourceX + Width, SourceY + Height);
	ParentDC->BlockWrite(Buffer, Width * Height);
	ParentDC->EndNativeClip();
}

void CLIPPEDDC::UpdateWithoutNativeClip(void)
{
	GUIPOS EndY = SourceY + Height;
	PIXEL* BufCur = Buffer;
	for (GUIPOS y = SourceY; y < EndY; y++)
	{
		ParentDC->SetPos(SourceX, y);
		for (GUIPOS x = 0; x < Width; x++)
		{
			ParentDC->SequenceWrite(*BufCur);
			BufCur++;
		}
	}
}

void CLIPPEDDC::UpdateWithNegativeCoord(void)
{
	GUIPOS y = SourceY;
	GUIPOS EndY = SourceY + Height;
	if (y < 0)
	{
		y = 0;
	}
	for (; y < EndY; y++)
	{
		GUIPOS x = SourceX;
		GUIPOS EndX = SourceX + Width;
		if (x < 0)
		{
			x = 0;
		}
		PIXEL* BufCur = Buffer + (y - SourceY) * Width + (x - SourceX);
		ParentDC->SetPos(x, y);
		for (; x < EndX; x++)
		{
			ParentDC->SequenceWrite(*BufCur);
			BufCur++;
		}
	}
}
