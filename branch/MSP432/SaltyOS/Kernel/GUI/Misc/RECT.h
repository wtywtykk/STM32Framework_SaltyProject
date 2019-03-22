#pragma once

#include "Kernel\GUI\GUICommon.h"

typedef struct
{
	GUIPOS Left;
	GUIPOS Top;
	GUIPOS Right;
	GUIPOS Bottom;
}RECT;

bool IsRectIntersect(RECT* Rect1, RECT* Rect2);
