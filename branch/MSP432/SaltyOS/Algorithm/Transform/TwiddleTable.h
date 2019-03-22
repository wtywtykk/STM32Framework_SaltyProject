#pragma once

#include "Kernel\Common\KCommon.h"

#define TwiddleTableSize 131072
extern const float TwiddleTable[TwiddleTableSize / 4];

__inline float GetTwiddleRe(u32 x)
{
	//cos
	if (x > TwiddleTableSize / 2)
	{
		x = TwiddleTableSize - x;
	}
	if (x < TwiddleTableSize / 4)
	{
		return TwiddleTable[x];
	}
	else if (x > TwiddleTableSize / 4)
	{
		return -TwiddleTable[TwiddleTableSize / 2 - x];
	}
	else
	{
		return 0.0;
	}
}

__inline float GetTwiddleIm(u32 x)
{
	//-sin
	return GetTwiddleRe((x + TwiddleTableSize / 4) % TwiddleTableSize);
}
