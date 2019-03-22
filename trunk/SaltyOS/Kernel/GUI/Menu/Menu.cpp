#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\Window\ScreenWindow.h"
#include "Kernel\GUI\Window\Window.h"
#include "Kernel\GUI\Picture\FlashFSPic.h"
#include "Kernel\GUI\Menu\MenuItem.h"
#include "Kernel\GUI\Menu\Menu.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\EstimateString.h"
#include "Kernel\GUI\Shape\Line.h"
#include <stdio.h>

const pcstr MenuClassWinPropName = "MCP";

const GUIPOS PageHintHeight = 20;
const GUIPOS TabWidth = 30;
const PIXEL TabInactiveTextColor = DGRAY;
const PIXEL TabActiveTextColor = WHITE;
const PIXEL TabFrameColor = DGRAY;

const KEYCODE MenuKeys[] = { KEY_M1, KEY_M2, KEY_M3, KEY_M4, KEY_M5 };

class MENU_WIN_EVENT_HANDLER :public WINEVENT
{
private:
	virtual void OnDestroy(WINDOW* Win);
	virtual bool OnKeyPress(WINDOW* Win, KEYCODE Key);
	virtual bool OnPaint(WINDOW* Win);
};

void MENU_WIN_EVENT_HANDLER::OnDestroy(WINDOW * Win)
{
	MENU* Menu = (MENU*)GetWindowProp(Win, MenuClassWinPropName);
	FreeAndEraseReference(Menu);
}

bool MENU_WIN_EVENT_HANDLER::OnKeyPress(WINDOW* Win, KEYCODE Key)
{
	MENU* Menu = (MENU*)GetWindowProp(Win, MenuClassWinPropName);
	if (Menu && !Menu->MenuStack.empty())
	{
		switch (Key)
		{
		case KEY_UP:
			Menu->ShowPrevPage();
			return true;
		case KEY_DOWN:
			Menu->ShowNextPage();
			return true;
		default:
			return false;
		}
	}
	return false;
}

bool MENU_WIN_EVENT_HANDLER::OnPaint(WINDOW* Win)
{
	MENU* Menu = (MENU*)GetWindowProp(Win, MenuClassWinPropName);
	if (Menu)
	{
		GUIPOS MenuTabY = 0;
		DC* DrawingDC = Win->GetDC();
		GUIPOS WinHeight = 0;
		Win->GetWindowPos(NULL, NULL, NULL, &WinHeight);
		//Draw tab
		DrawingDC->Fill(Menu->MenuItemWidth, 0, Menu->MenuItemWidth + TabWidth, WinHeight, BLACK);
		DrawLine(DrawingDC, Menu->MenuItemWidth, 0, Menu->MenuItemWidth, WinHeight - 1, TabFrameColor);
		if (!Menu->MenuStack.empty())
		{
			FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC24;HZK24F;HZK24T"));
			for (MENU_STACK::iterator i = Menu->MenuStack.begin(); i < Menu->MenuStack.end(); i++)
			{
				GUIPOS TextHeight = 0;
				EstimateStringVertical(DrawingDC, FG, (*i)->MenuCaption, Menu->MenuItemWidth + 2, MenuTabY + 2, 0, 0, NULL, &TextHeight);
				if (i + 1 < Menu->MenuStack.end())
				{
					DrawStringVertical(DrawingDC, FG, (*i)->MenuCaption, Menu->MenuItemWidth + 2, MenuTabY + 2, 0, 0, TabInactiveTextColor, BLACK);
				}
				else
				{
					DrawStringVertical(DrawingDC, FG, (*i)->MenuCaption, Menu->MenuItemWidth + 2, MenuTabY + 2, 0, 0, TabActiveTextColor, BLACK);
				}

				if (MenuTabY == 0)
				{
					DrawLine(DrawingDC, Menu->MenuItemWidth, MenuTabY, Menu->MenuItemWidth + TabWidth - 1, MenuTabY, TabFrameColor);
				}
				DrawLine(DrawingDC, Menu->MenuItemWidth + TabWidth - 1, MenuTabY - TabWidth, Menu->MenuItemWidth + TabWidth - 1, MenuTabY + TextHeight, TabFrameColor);
				DrawLine(DrawingDC, Menu->MenuItemWidth + TabWidth - 1, MenuTabY + TextHeight, Menu->MenuItemWidth, MenuTabY + TextHeight + TabWidth, TabFrameColor);

				MenuTabY += TextHeight + TabWidth;
			}
			FreeAndEraseReference(FG);
			//Draw tab end
		}
		//Draw page
		char PageBuf[64];
		GUIPOS MenuItemEnd = Menu->MenuItemHeight * Menu->MenuItemPerScreen;
		GUIPOS TextWidth = 0;
		DrawingDC->Fill(0, MenuItemEnd, Menu->MenuItemWidth, WinHeight, BLACK);
		if (!Menu->MenuStack.empty())
		{
			FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC16"));
			sprintf(PageBuf, "Page%d/%d", Menu->MenuStack.back()->CurrentPage + 1, Menu->GetPageCount());
			EstimateStringHorizontal(DrawingDC, FG, PageBuf, 5, MenuItemEnd + 5, 0, 0, &TextWidth, NULL);
			DrawStringHorizontal(DrawingDC, FG, PageBuf, Menu->MenuItemWidth - TextWidth - 3, MenuItemEnd + 5, 0, 0, WHITE, BLACK);
			FreeAndEraseReference(FG);
			//Draw page end
		}
		FreeAndEraseReference(DrawingDC);
	}
	return false;
}

MENU::MENU(GUIPOS X, GUIPOS Y, GUIPOS Height)
{
	MENUITEM::GetSize(&MenuItemWidth, &MenuItemHeight);
	if (Height > PageHintHeight)
	{
		MenuItemPerScreen = (Height - PageHintHeight) / MenuItemHeight;
		if (MenuItemPerScreen == 0)
		{
			MenuItemPerScreen = 1;
		}
	}
	else
	{
		MenuItemPerScreen = 1;
	}
	if (MenuItemPerScreen > sizeof(MenuKeys) / sizeof(MenuKeys[0]))
	{
		MenuItemPerScreen = sizeof(MenuKeys) / sizeof(MenuKeys[0]);
	}

	Win = new_noexcpt WINDOW(NULL, X, Y, MenuItemWidth + TabWidth, Height, true);
	if (Win)
	{
		MENU_WIN_EVENT_HANDLER* MenuEventHandler = new_noexcpt MENU_WIN_EVENT_HANDLER();
		if (MenuEventHandler)
		{
			SetWindowProp(Win, MenuClassWinPropName, (u32)this);
			Win->LinkEventHandler(MenuEventHandler);
			Win->SetCaption("MenuWin");
			for (u8 i = 0; i < MenuItemPerScreen; i++)
			{
				MENUITEM* NewItem = NewReferenceSafe(new_noexcpt MENUITEM(this, 0, MenuItemHeight * i, MenuKeys[i]));
				if (NewItem)
				{
					DispItems.push_back(NewItem);
				}
			}
		}
		else
		{
			PostMessage(Win, WM_DESTROY, 0, 0);
			Win = NULL;
		}
	}
}

MENU::~MENU(void)
{
	SetWindowProp(Win, MenuClassWinPropName, (u32)NULL);
	PostMessage(Win, WM_DESTROY, 0, 0);
	Win = NULL;
	while (!DispItems.empty())
	{
		MENUITEM* Item = DispItems.back();
		DispItems.pop_back();
		FreeAndEraseReference(Item);
	}
}

GUIPOS MENU::GetMenuWidth(void)
{
	GUIPOS MenuItemWidth = 0;
	MENUITEM::GetSize(&MenuItemWidth, NULL);
	return MenuItemWidth + TabWidth;
}

void MENU::EnterMenu(MenuStruct * Menu)
{
	Menu->CurrentPage = 0;
	Menu->SelectedItem = INVALID_MENU_INDEX;
	MenuStack.push_back(Menu);
	UpdateItems();
	if (Menu->CallBack)
	{
		Menu->CallBack(Menu, MenuShow);
	}
}

void MENU::ExitMenu(void)
{
	if (!MenuStack.empty())
	{
		MenuStruct* LastMenu = MenuStack.back();
		MenuStack.pop_back();
		if (LastMenu->CallBack)
		{
			LastMenu->CallBack(LastMenu, MenuClose);
		}
		UpdateItems();
	}
}

void MENU::ExitAll(void)
{
	while (!MenuStack.empty())
	{
		MenuStruct* LastMenu = MenuStack.back();
		MenuStack.pop_back();
		if (LastMenu->CallBack)
		{
			LastMenu->CallBack(LastMenu, MenuClose);
		}
	}
	UpdateItems();
}

void MENU::ShowPrevPage(void)
{
	MenuStruct* CurrentTopMenu = MenuStack.back();
	if (CurrentTopMenu->CurrentPage > 0)
	{
		CurrentTopMenu->CurrentPage--;
		UpdateItems();
	}
}

void MENU::ShowNextPage(void)
{
	MenuStruct* CurrentTopMenu = MenuStack.back();
	if (CurrentTopMenu->CurrentPage < GetPageCount() - 1)
	{
		CurrentTopMenu->CurrentPage++;
		UpdateItems();
	}
}

u8 MENU::GetSelectedItem(void)
{
	MenuStruct* CurrentTopMenu = MenuStack.back();
	return CurrentTopMenu->SelectedItem;
}

void MENU::SetSelectedItem(u8 ItemIndex)
{
	MenuStruct* CurrentTopMenu = MenuStack.back();
	if (CurrentTopMenu->SelectedItem != ItemIndex)
	{
		u8 ThisPageMin = MenuItemPerScreen * CurrentTopMenu->CurrentPage;
		u8 ThisPageMax = ThisPageMin + MenuItemPerScreen - 1;
		u8 PrevSelectedItem = CurrentTopMenu->SelectedItem;
		CurrentTopMenu->SelectedItem = ItemIndex;
		if (PrevSelectedItem >= ThisPageMin && PrevSelectedItem <= ThisPageMax)
		{
			DispItems[PrevSelectedItem - ThisPageMin]->RefreshItem();
		}
		if (CurrentTopMenu->SelectedItem >= ThisPageMin && CurrentTopMenu->SelectedItem <= ThisPageMax)
		{
			DispItems[CurrentTopMenu->SelectedItem - ThisPageMin]->RefreshItem();
		}
	}
}

u8 MENU::GetPageCount(void)
{
	if (!MenuStack.empty())
	{
		MenuStruct* CurrentMenu = MenuStack.back();
		u8 PageCount = CurrentMenu->ItemCount / MenuItemPerScreen;
		u8 LastPageItemCount = CurrentMenu->ItemCount % MenuItemPerScreen;
		if (LastPageItemCount)
		{
			PageCount++;
		}
		return PageCount;
	}
	else
	{
		return 0;
	}
}

void MENU::UpdateItems(void)
{
	if (!MenuStack.empty())
	{
		MenuStruct* CurrentTopMenu = MenuStack.back();
		u8 ItemIndex = MenuItemPerScreen * CurrentTopMenu->CurrentPage;
		for (u8 i = 0; i < MenuItemPerScreen; i++)
		{
			if (ItemIndex < CurrentTopMenu->ItemCount)
			{
				DispItems[i]->SetItem(CurrentTopMenu->Items + ItemIndex, ItemIndex);
			}
			else
			{
				DispItems[i]->SetItem(NULL, INVALID_MENU_INDEX);
			}
			ItemIndex++;
		}
		PostMessage(Win, WM_PAINT, 0, 0);
	}
	else
	{
		for (u8 i = 0; i < MenuItemPerScreen; i++)
		{
			DispItems[i]->SetItem(NULL, INVALID_MENU_INDEX);
		}
		PostMessage(Win, WM_PAINT, 0, 0);
	}
}
