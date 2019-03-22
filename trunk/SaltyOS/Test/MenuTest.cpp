#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\Window\ScreenWindow.h"
#include "Kernel\GUI\Menu\Menu.h"

MENU* TestMenu = NULL;

MenuStruct Menu1;
MenuStruct Menu2;
MenuItemStruct MI[13];

#include <stdio.h>

void MenuCB(struct MenuItemStruct* MenuItem, MenuItemMessage Msg, u32 Param)
{
	printf("%ld\n\r", MenuItem->Tag);
}

void MenuTest(void)
{
	if (TestMenu == NULL)
	{
		WINDOW* ScrWin = SCREENWINDOW::GetScreenWindow();
		GUIPOS ScrHeight;
		ScrWin->GetWindowPos(NULL, NULL, NULL, &ScrHeight);
		TestMenu = NewReferenceSafe(new_noexcpt MENU(600, 0, ScrHeight));

		Menu1.ItemCount = 13;
		Menu1.Items = MI;
		Menu1.MenuCaption = "²Ëµ¥Ò»";
		Menu1.CallBack = NULL;

		Menu2.ItemCount = 13;
		Menu2.Items = MI;
		Menu2.MenuCaption = "²Ëµ¥·¡";
		Menu2.CallBack = NULL;

		for (u8 i = 0; i < 13; i++)
		{
			MI[i].Caption = "MI";
			MI[i].Enabled = true;
			MI[i].CallBack = MenuCB;
			MI[i].Style = BlankItem;
			MI[i].SubCaption = "MIS";
			MI[i].Tag = i;
		}
		MI[0].Caption = "MI0";
		MI[1].Caption = "MI1";
		MI[2].Caption = "MI2";
		MI[3].Caption = "MI3";
		MI[4].Caption = "MI4";
		MI[5].Caption = "MI5";
		MI[6].Caption = "MI6";
		MI[7].Caption = "MI7";
		MI[8].Caption = "MI8";
		MI[9].Caption = "MI9";
		MI[10].Caption = "MI10";
		MI[0].Style = ButtonItem;
		MI[1].Style = PopupItem;
		MI[3].Style = ReturnItem;
		MI[5].Style = SubMenuItem;
		MI[7].Style = TurnItem;
		TestMenu->EnterMenu(&Menu1);
		TestMenu->EnterMenu(&Menu2);
	}
}