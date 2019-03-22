#pragma once

#include "Kernel\Common\KCommon.h"

typedef enum
{
	Unused,
	Normal,
	Delta,
}BodePlotter_CursorType;

typedef struct
{
	BodePlotter_CursorType Type;
	struct
	{
		double Freq;
	}NormalData;
	struct
	{
		u32 Cursors[2];
	}DeltaData;
}BodePlotter_Cursor;
