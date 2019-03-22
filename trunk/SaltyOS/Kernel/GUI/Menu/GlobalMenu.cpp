#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\Window\ScreenWindow.h"
#include "Kernel\GUI\Menu\Menu.h"

MENU* GlobalMenu = NULL;

STATUS GlobalMenu_Init(void)
{
	WINDOW* ScrWin = SCREENWINDOW::GetScreenWindow();
	GUIPOS ScrWidth;
	GUIPOS ScrHeight;
	ScrWin->GetWindowPos(NULL, NULL, &ScrWidth, &ScrHeight);
	GlobalMenu = NewReferenceSafe(new_noexcpt MENU(ScrWidth - MENU::GetMenuWidth(), 0, ScrHeight));
	if (GlobalMenu)
	{
		GlobalMenu->MarkObjectStatic();
		return S_OK;
	}
	else
	{
		return S_FAIL;
	}
}

MENU* GetGlobalMenu(void)
{
	return NewReferenceSafe(GlobalMenu);
}
