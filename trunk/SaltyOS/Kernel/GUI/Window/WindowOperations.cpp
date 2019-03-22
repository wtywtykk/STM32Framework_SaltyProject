#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\Window\Window.h"
#include "Kernel\GUI\Window\WindowOperations.h"
#include <algorithm>
#include <string>

void BringToTop(WINDOW * Win)
{
	Win->Parent->ChildList.remove(Win);
	Win->Parent->ChildList.push_front(Win);
}

void BringToTopOf(WINDOW * Win, WINDOW * WinBefore)
{
	WINLIST::iterator WinIter = find(Win->Parent->ChildList.begin(), Win->Parent->ChildList.end(), WinBefore);
	if (WinIter != Win->Parent->ChildList.end())
	{
		Win->Parent->ChildList.remove(Win);
		Win->Parent->ChildList.insert(WinIter, Win);
	}
}

void SetWindowProp(WINDOW* Win, pcstr Key, u32 Data)
{
	Win->PropMap[Key] = Data;
}

u32 GetWindowProp(WINDOW* Win, pcstr Key)
{
	return Win->PropMap[Key];
}

void RemoveWindowProp(WINDOW * Win, pcstr Key)
{
	Win->PropMap.erase(Key);
}
