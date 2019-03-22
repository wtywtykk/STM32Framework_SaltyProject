#include "FontGroup.h"
#include <stdlib.h>

FONTGROUP::FONTGROUP(pcstr FontList)
{
	Index = NULL;
	FontCount = GetFontListCount(FontList);
	if (FontCount)
	{
		Index = (const FONTINDEX**)malloc(sizeof(FONTINDEX*) * FontCount);

		if (Index)
		{
			FillIndexFromList(FontList);

			if (FontCount == 0 || !CheckAscRangeOverlap())
			{
				free(Index);
				Index = NULL;
				FontCount = 0;
			}
		}
		else
		{
			FontCount = 0;
		}
	}
}

FONTGROUP::~FONTGROUP()
{
	free(Index);
}

const FONTINDEX * FONTGROUP::GetFontIndex(u16 Char)
{
	u8 i;
	for (i = 0; i < FontCount; i++)
	{
		if (Index[i]->AscLBound <= Char && Index[i]->AscUBound >= Char)
		{
			return Index[i];
		}
	}
	return NULL;
}

u8 FONTGROUP::GetFontListCount(pcstr FontList)
{
	u8 FontCount = 0;

	for (; *FontList; FontList++)
	{
		if (*FontList == ';')
		{
			FontCount++;
		}
	}

	if (*(FontList - 1) != ';')
	{
		FontCount++;
	}

	return FontCount;
}

pcstr FONTGROUP::GetNextNameFromList(pcstr FontList, char Buffer[8])
{
	u8 i = 0;
	while (1)
	{
		if (*FontList == ';' || *FontList == 0 || i == 8)
		{
			break;
		}
		else
		{
			Buffer[i] = *FontList;
			i++;
			FontList++;
		}
	}
	if (i < 8)
	{
		Buffer[i] = 0;
	}

	if (*FontList == ';')
	{
		FontList++;
	}
	else if (*FontList != 0)
	{
		while (*FontList != ';' && *FontList != 0)
		{
			FontList++;
		}
	}
	return FontList;
}

void FONTGROUP::FillIndexFromList(pcstr FontList)
{
	char NameBuf[8];
	pcstr CurListPos = FontList;
	u8 ActualCount = 0;
	for (u8 i = 0; i < FontCount; i++)
	{
		CurListPos = GetNextNameFromList(CurListPos, NameBuf);
		Index[ActualCount] = GetIndexAddress(NameBuf);
		if (Index[ActualCount])
		{
			ActualCount++;
		}
	}
	FontCount = ActualCount;
}

bool FONTGROUP::CheckAscRangeOverlap(void)
{
	for (u8 i = 0; i < FontCount; i++)
	{
		for (u8 j = i + 1; j < FontCount; j++)
		{
			if (!(Index[i]->AscUBound <= Index[j]->AscLBound ||
				Index[j]->AscUBound <= Index[i]->AscLBound))
			{
				return false;
			}
		}
	}
	return true;
}
