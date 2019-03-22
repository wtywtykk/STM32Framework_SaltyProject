#pragma once

#include "Kernel\Common\KCommon.h"
#include "Kernel\Common\KObject.h"
#include "Kernel\GUI\Window\Window.h"
#include <vector>

#define INVALID_MENU_INDEX 255

typedef enum
{
	MenuShow,
	MenuClose,
}MenuMessage;

typedef enum
{
	ItemPress,
	ItemTurn,
}MenuItemMessage;

typedef void(*MenuItemCallBack)(struct MenuItemStruct* MenuItem, MenuItemMessage Msg, u32 Param);
typedef void(*MenuCallBack)(struct MenuStruct* Menu, MenuMessage Msg);

typedef enum
{
	BlankItem,
	ButtonItem,
	PopupItem,//Two types(With SubCaption/Without)
	ReturnItem,
	SubMenuItem,
	TurnItem,//Two types(With SubCaption/Without)
}MenuItemStyle;

typedef struct MenuItemStruct
{
	MenuItemCallBack CallBack;
	u32 Tag;
	MenuItemStyle Style;
	pcstr Caption;
	pcstr SubCaption;
	bool Enabled;
}MenuItemStruct;

typedef struct MenuStruct
{
	MenuCallBack CallBack;
	pcstr MenuCaption;
	u8 ItemCount;
	MenuItemStruct* Items;
	u8 CurrentPage;
	u8 SelectedItem;
}MenuStruct;

class MENUITEM;

typedef std::vector<MENUITEM*> MENU_ITEM_VECTOR;
typedef std::vector<MenuStruct*> MENU_STACK;

class MENU :public KOBJECT
{
	friend class MENUITEM;
	friend class MENU_WIN_EVENT_HANDLER;
	WINDOW* Win = NULL;
	MENU_ITEM_VECTOR DispItems;
	MENU_STACK MenuStack;
	u8 MenuItemPerScreen = 1;
	GUIPOS MenuItemWidth;
	GUIPOS MenuItemHeight;
public:
	MENU(GUIPOS X, GUIPOS Y, GUIPOS Height);
	~MENU(void);
	static GUIPOS GetMenuWidth(void);
	void EnterMenu(MenuStruct* Menu);
	void ExitMenu(void);
	void ExitAll(void);
	void ShowPrevPage(void);
	void ShowNextPage(void);
	u8 GetSelectedItem(void);
	void SetSelectedItem(u8 ItemIndex);
	void UpdateItems(void);
private:
	u8 GetPageCount(void);
};
