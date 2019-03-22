#pragma once

#include "Kernel\Common\KObject.h"
#include "Kernel\GUI\Window\Window.h"
#include "Kernel\GUI\Menu\Menu.h"
#include "Kernel\GUI\Misc\RECT.h"

class MENUITEM :public KOBJECT
{
	friend class MENU_ITEM_WIN_EVENT_HANDLER;
	WINDOW* Win = NULL;
	MenuItemStruct* CurItem = NULL;
	u8 CurrentIndex = 0;
	MENU* ParentMenu = NULL;
	KEYCODE SensitiveKey = KEY_Invalid;
public:
	MENUITEM(MENU* Menu, GUIPOS X, GUIPOS Y, KEYCODE Key);
	~MENUITEM();
	void Destroy();
	static void GetSize(GUIPOS* Width, GUIPOS* Height);
	void SetItem(MenuItemStruct* NewItem, u8 Index);
	void RefreshItem(void);
private:
	pcstr GetItemBackground(bool Selected);
	pcstr GetItemCaptionFont(void);
	void GetItemCaptionArea(RECT* Area);
	void GetItemSubCaptionArea(RECT* Area);
	bool IsSelected(void);
};
