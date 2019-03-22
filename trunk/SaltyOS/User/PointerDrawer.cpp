#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\DC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "Kernel\GUI\Shape\Line.h"
#include "Kernel\GUI\Shape\Circle.h"
#include "Kernel\GUI\DC\ClippedDC.h"
#include <assert.h>
#include <string.h>

void DrawHorizontalPointerToRight(DC* TargetDC, pcstr Text, s16 X, s16 Y, u16 Width, u16 Height, PIXEL Color, PIXEL TextColor, FONTGROUP* Font)
{
	assert(Width >= Height / 2);
	CLIPPEDDC* ClipDC = NewReferenceSafe(new_noexcpt CLIPPEDDC(TargetDC, X, Y, X + Width, Y + Height, false, false));
	s16 SquareSize = Width - Height / 2;
	ClipDC->Fill(0, 0, SquareSize, Height, Color);
	for (u16 i = 1; i < Height / 2; i++)
	{
		ClipDC->Fill(SquareSize, i, SquareSize + i, i + 1, Color);
		ClipDC->Fill(SquareSize, Height - i - 1, SquareSize + i, Height - i, Color);
	}
	if (Text)
	{
		FONTGROUP* PointerTextFont;
		if (Font)
		{
			PointerTextFont = NewReferenceSafe(Font);
		}
		else
		{
			PointerTextFont = NewReferenceSafe(new_noexcpt FONTGROUP("ASC16"));
		}
		const FONTINDEX* FontIndex = PointerTextFont->GetFontIndex(*Text);
		DrawStringHorizontal(ClipDC, PointerTextFont, Text, SquareSize / 2 - strlen(Text) * FontIndex->Width / 2, Height / 2 - FontIndex->Height / 2, 0, 0, TextColor, Color);
		FreeAndEraseReference(PointerTextFont);
	}

	FONTGROUP* PointerTextFont = NewReferenceSafe(new_noexcpt FONTGROUP("ASC16"));
	FreeAndEraseReference(PointerTextFont);
	FreeAndEraseReference(ClipDC);
}

void DrawVerticalPointerToBottom(DC* TargetDC, pcstr Text, s16 X, s16 Y, u16 Width, u16 Height, PIXEL Color, PIXEL TextColor, FONTGROUP* Font)
{
	assert(Height >= Width / 2);
	CLIPPEDDC* ClipDC = NewReferenceSafe(new_noexcpt CLIPPEDDC(TargetDC, X, Y, X + Width, Y + Height, false, false));
	s16 SquareSize = Height - Width / 2;
	ClipDC->Fill(0, 0, Width, SquareSize, Color);
	for (u16 i = 1; i < Width / 2; i++)
	{
		ClipDC->Fill(i, SquareSize, i + 1, SquareSize + i, Color);
		ClipDC->Fill(Width - i - 1, SquareSize, Width - i, SquareSize + i, Color);
	}
	if (Text)
	{
		FONTGROUP* PointerTextFont;
		if (Font)
		{
			PointerTextFont = NewReferenceSafe(Font);
		}
		else
		{
			PointerTextFont = NewReferenceSafe(new_noexcpt FONTGROUP("ASC16"));
		}
		const FONTINDEX* FontIndex = PointerTextFont->GetFontIndex(*Text);
		DrawStringHorizontal(ClipDC, PointerTextFont, Text, Width / 2 - strlen(Text) * FontIndex->Width / 2, SquareSize / 2 - FontIndex->Height / 2, 0, 0, TextColor, Color);
		FreeAndEraseReference(PointerTextFont);
	}
	FreeAndEraseReference(ClipDC);
}
