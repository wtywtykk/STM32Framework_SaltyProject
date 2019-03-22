#include "FontProvider.h"
#include "Driver\ASC16.h"
#include <string.h>
#include <EmbeddedResources.h>

typedef struct
{
	u32 FontCount;
	FONTINDEX Index[];
}FONTFLASHLAYOUT;

FONTINDEX EmbeddedFont[] = {
	{ "ASC16",8,16,16,0,127,StandardAddressing,(u32)&ASC16Font,((u32)&ASC16Font) + sizeof(ASC16Font) },
};

static bool IsIndexMatch(pcstr FontName, const FONTINDEX* Index);

const FONTINDEX* GetIndexAddress(pcstr FontName)
{
	const FONTFLASHLAYOUT* Flash = (const FONTFLASHLAYOUT*)&_binary_Resource_Pack_bin_start;

	for (u8 i = 0; i < sizeof(EmbeddedFont) / sizeof(FONTINDEX); i++)
	{
		if (IsIndexMatch(FontName, &EmbeddedFont[i]))
		{
			return &EmbeddedFont[i];
		}
	}

	if (Flash->FontCount != 0xFFFFFFFF)
	{
		for (u8 i = 0; i < Flash->FontCount; i++)
		{
			if (IsIndexMatch(FontName, &Flash->Index[i]))
			{
				return &Flash->Index[i];
			}
		}
	}

	return NULL;
}

static bool IsIndexMatch(pcstr FontName, const FONTINDEX* Index)
{
	if (strncmp(FontName, Index->Name, 8) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
