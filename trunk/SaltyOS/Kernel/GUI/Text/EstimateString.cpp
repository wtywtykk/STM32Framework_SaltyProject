#include "Kernel\GUI\Text\EstimateString.h"
#include "Kernel\GUI\Text\FontAddressing.h"

u16 GetNextChar(pcstr* String);//In DrawSreing.cpp

void EstimateStringHorizontal(DC* dc, FONTGROUP* Group, pcstr String, GUIPOS X, GUIPOS Y, GUIPOS Width, GUIPOS Height, GUIPOS* EstimatedWidth, GUIPOS* EstimatedHeight)
{
	dc = NewReferenceSafe(dc);
	Group = NewReferenceSafe(Group);

	pcstr StrPtr = String;
	u16 CurChar;
	GUIPOS CurX = X;
	GUIPOS CurY = Y;
	GUIPOS EndX;
	GUIPOS EndY;

	GUIPOS MaxLineHeight = 0;

	GUIPOS EstWidth = 0;
	GUIPOS EstHeight = 0;

	if (dc)
	{
		EndX = Width ? X + Width : dc->GetWidth();
		EndY = Height ? Y + Height : dc->GetHeight();
	}
	else
	{
		EndX = Width ? X + Width : 32767;
		EndY = Height ? Y + Height : 32767;
	}

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

				if (EstWidth < CurX + CurWidth - X)
				{
					EstWidth = CurX + CurWidth - X;
				}
				if (EstHeight < CurY + CurHeight - Y)
				{
					EstHeight = CurY + CurHeight - Y;
				}

				CurX += CurWidth;
			}
		}
	}
	FreeAndEraseReference(Group);
	FreeAndEraseReference(dc);

	if (EstimatedWidth)
	{
		*EstimatedWidth = EstWidth;
	}
	if (EstimatedHeight)
	{
		*EstimatedHeight = EstHeight;
	}
}

void EstimateStringVertical(DC* dc, FONTGROUP* Group, pcstr String, GUIPOS X, GUIPOS Y, GUIPOS Width, GUIPOS Height, GUIPOS* EstimatedWidth, GUIPOS* EstimatedHeight)
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

	GUIPOS EstWidth = 0;
	GUIPOS EstHeight = 0;

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

				if (EstWidth < CurX + CurWidth - X)
				{
					EstWidth = CurX + CurWidth - X;
				}
				if (EstHeight < CurY + CurHeight - Y)
				{
					EstHeight = CurY + CurHeight - Y;
				}

				CurY += CurHeight;
			}
		}
	}
	FreeAndEraseReference(Group);
	FreeAndEraseReference(dc);

	if (EstimatedWidth)
	{
		*EstimatedWidth = EstWidth;
	}
	if (EstimatedHeight)
	{
		*EstimatedHeight = EstHeight;
	}
}
