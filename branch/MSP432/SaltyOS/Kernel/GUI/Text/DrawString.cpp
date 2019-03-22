#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontAddressing.h"

void DrawCharData(DC* dc, u8* CharData, GUIPOS X, GUIPOS Y, GUIPOS Width, GUIPOS Height, PIXEL ForeColor, PIXEL BackColor, bool Trans)
{
	u16 i, j;
	u8 BitCounter = 0, CurByte = *CharData;
	for (i = 0; i < Height; i++)
	{
		for (j = 0; j < Width; j++)
		{
			if (CurByte & 0x80)
			{
				if (Trans)
				{
					dc->SetPixel(X + i, Y + j, ForeColor);
				}
				else
				{
					dc->SetPixel(X + j, Y + i, ForeColor);
				}
			}
			else
			{
				if (BackColor != TransparentColorKey)
				{
					if (Trans)
					{
						dc->SetPixel(X + i, Y + j, BackColor);
					}
					else
					{
						dc->SetPixel(X + j, Y + i, BackColor);
					}
				}
			}
			CurByte <<= 1;
			BitCounter++;
			if (BitCounter == 8)
			{
				BitCounter = 0;
				CharData++;
				CurByte = *CharData;
			}
		}
		if (BitCounter)
		{
			BitCounter = 0;
			CharData++;
			CurByte = *CharData;
		}
	}
}

void DrawInvalidChar(DC* dc, GUIPOS X, GUIPOS Y, GUIPOS Width, GUIPOS Height, PIXEL ForeColor, PIXEL BackColor)
{
	dc->Fill(X, Y, X + Width, Y + Height, ForeColor);
}

u16 GetNextChar(pcstr* String)
{
	u16 Val;
	if (**String & 0x80)
	{
		Val = (**String) << 8 | *(*String + 1);
		if (*(*String + 1) != 0)
		{
			(*String) += 2;
		}
		else
		{
			//The string is incomplete
			(*String)++;
		}
		return Val;
	}
	else
	{
		Val = **String;
		(*String)++;
		return Val;
	}
}

void DrawStringHorizontal(DC* dc, FONTGROUP* Group, pcstr String, GUIPOS X, GUIPOS Y, GUIPOS Width, GUIPOS Height, PIXEL ForeColor, PIXEL BackColor)
{
	dc = NewReferenceSafe(dc);
	Group = NewReferenceSafe(Group);

	pcstr StrPtr = String;
	u16 CurChar;
	GUIPOS CurX = X;
	GUIPOS CurY = Y;
	GUIPOS EndX = Width ? X + Width : dc->GetWidth();
	GUIPOS EndY = Height ? Y + Height : dc->GetHeight();

	GUIPOS MaxLineHeight = 0;

	while (1)
	{
		CurChar = GetNextChar(&StrPtr);
		if (CurChar == 0)
		{
			break;
		}

		if (CurChar == '\n')
		{
			CurY += MaxLineHeight;
			MaxLineHeight = 0;
		}
		else if (CurChar == '\r')
		{
			CurX = X;
		}
		else
		{
			const FONTINDEX* Index = Group->GetFontIndex(CurChar);
			if (Index)
			{
				u32 CharDataAddress = GetStartAddress(Index) + GetAddressingOffset(Index, CurChar);
				GUIPOS CurWidth = Index->Width;
				GUIPOS CurHeight = Index->Height;

				if (CurX + CurWidth > EndX)
				{
					CurX = X;
					CurY += MaxLineHeight;
					MaxLineHeight = 0;
				}

				if (CurY + CurHeight > EndY)
				{
					break;
				}

				if (MaxLineHeight < CurHeight)
				{
					MaxLineHeight = CurHeight;
				}

				DrawCharData(dc, (u8*)CharDataAddress, CurX, CurY, CurWidth, CurHeight, ForeColor, BackColor, Index->StorageMode & Transposed);

				CurX += CurWidth;
			}
			else
			{
				DrawInvalidChar(dc, CurX, CurY, 32, 32, ForeColor, BackColor);
			}
		}
	}
	FreeAndEraseReference(Group);
	FreeAndEraseReference(dc);
}

void DrawStringVertical(DC* dc, FONTGROUP* Group, pcstr String, GUIPOS X, GUIPOS Y, GUIPOS Width, GUIPOS Height, PIXEL ForeColor, PIXEL BackColor)
{
	dc = NewReferenceSafe(dc);
	Group = NewReferenceSafe(Group);

	pcstr StrPtr = String;
	u16 CurChar;
	GUIPOS CurX = X;
	GUIPOS CurY = Y;
	GUIPOS EndX = Width ? X + Width : dc->GetWidth();
	GUIPOS EndY = Height ? Y + Height : dc->GetHeight();

	GUIPOS MaxLineWidth = 0;

	while (1)
	{
		CurChar = GetNextChar(&StrPtr);
		if (CurChar == 0)
		{
			break;
		}

		if (CurChar == '\n')
		{
			CurX += MaxLineWidth;
			MaxLineWidth = 0;
		}
		else if (CurChar == '\r')
		{
			CurY = Y;
		}
		else
		{
			const FONTINDEX* Index = Group->GetFontIndex(CurChar);
			if (Index)
			{
				u32 CharDataAddress = GetStartAddress(Index) + GetAddressingOffset(Index, CurChar);
				GUIPOS CurWidth = Index->Width;
				GUIPOS CurHeight = Index->Height;

				if (CurY + CurHeight > EndY)
				{
					CurY = Y;
					CurX += MaxLineWidth;
					MaxLineWidth = 0;
				}

				if (CurX + CurWidth > EndX)
				{
					break;
				}

				if (MaxLineWidth < CurWidth)
				{
					MaxLineWidth = CurWidth;
				}

				DrawCharData(dc, (u8*)CharDataAddress, CurX, CurY, CurWidth, CurHeight, ForeColor, BackColor, Index->StorageMode & Transposed);

				CurY += CurHeight;
			}
			else
			{
				DrawInvalidChar(dc, CurX, CurY, 32, 32, ForeColor, BackColor);
			}
		}
	}
	FreeAndEraseReference(Group);
	FreeAndEraseReference(dc);
}
