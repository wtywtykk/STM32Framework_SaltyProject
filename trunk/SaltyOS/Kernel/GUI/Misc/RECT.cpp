#include "Kernel\GUI\GUICommon.h"
#include "Kernel\GUI\Misc\RECT.h"

bool IsRectIntersect(RECT* Rect1, RECT* Rect2)
{
	if (Rect1->Right <= Rect1->Left || Rect1->Bottom <= Rect1->Top)
	{
		return false;
	}
	if (Rect2->Right <= Rect2->Left || Rect2->Bottom <= Rect2->Top)
	{
		return false;
	}
	if (Rect1->Right <= Rect2->Left || Rect1->Bottom <= Rect2->Top || Rect1->Left >= Rect2->Right || Rect1->Top >= Rect2->Bottom)
	{
		return false;
	}
	return true;
}
