#include "Kernel\GUI\GUICommon.h"
#include "Kernel\GUI\DC\DC.h"
#include "Kernel\GUI\Picture\IndirectDataPic.h"
#include <stdlib.h>

void INDIRECTDATAPIC::Draw(DC * dc, GUIPOS X, GUIPOS Y)
{
	u32 DataAddr = 0;
	PIXEL PixelVal[IndirectPicBufferLength];
	u32 BufferCount = 0;
	if (GetPixels(DataAddr, PixelVal, IndirectPicBufferLength) == S_OK)
	{
		for (s16 y = 0; y < Height; y++)
		{
			for (s16 x = 0; x < Width; x++)
			{
				dc->SetPixel(X + x, Y + y, PixelVal[BufferCount]);
				BufferCount++;
				if (BufferCount == IndirectPicBufferLength)
				{
					DataAddr += IndirectPicBufferLength;
					BufferCount = 0;
					if (GetPixels(DataAddr, PixelVal, IndirectPicBufferLength) != S_OK)
					{
						return;
					}
				}
			}
		}
	}
}

PIXEL INDIRECTDATAPIC::GetPixel(GUIPOS X, GUIPOS Y)
{
	if (CheckCoord(X, Y))
	{
		PIXEL Val;
		if (GetPixels(Y * Width + X, &Val, 1) == S_OK)
		{
			return Val;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

bool INDIRECTDATAPIC::CheckCoord(GUIPOS X, GUIPOS Y)
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
