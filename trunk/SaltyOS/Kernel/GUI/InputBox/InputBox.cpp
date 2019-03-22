#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\Window\Window.h"
#include "Kernel\GUI\Window\ScreenWindow.h"
#include "Kernel\GUI\Menu\Menu.h"
#include "Kernel\GUI\Menu\GlobalMenu.h"
#include "Kernel\GUI\Picture\FlashFSPic.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "Kernel\GUI\Text\DrawString.h"
#include <string.h>
#include <malloc.h>

#define InputBox_Background "InpBox.SP"

pstr m_InpBuf = NULL;
u32 m_BufLen = 0;
MenuStruct InputMenu;
bool MenuSelected = false;
u32 MenuSelectIndex = 0;

class INPUTBOX_WIN_EVENT_HANDLER :public WINEVENT
{
private:
	virtual void OnDestroy(WINDOW* Win);
	virtual bool OnKeyPress(WINDOW* Win, KEYCODE Key);
	virtual bool OnPaint(WINDOW* Win);
};

void InputMenuCallback(struct MenuItemStruct* MenuItem, MenuItemMessage Msg, u32 Param)
{
	MenuSelected = true;
	MenuSelectIndex = MenuItem->Tag;
}

WINDOW* InputPrepare(pstr Buf, u32 BufLen, pcstr* Units, u32 UnitCount)
{
	WINDOW* ScrWin = SCREENWINDOW::GetScreenWindow();
	GUIPOS ScrWidth = 0;
	GUIPOS ScrHeight = 0;
	FLASHFSPIC BackGround(InputBox_Background);
	GUIPOS PicWidth = BackGround.GetWidth();
	GUIPOS PicHeight = BackGround.GetHeight();
	WINDOW* Win = NULL;
	GUIPOS WinX;
	GUIPOS WinY;
	ScrWin->GetWindowPos(NULL, NULL, &ScrWidth, &ScrHeight);
	FreeAndEraseReference(ScrWin);
	WinX = (ScrWidth - PicWidth) / 2;
	WinY = (ScrHeight * 3 / 4) - (PicHeight / 2);
	Win = new_noexcpt WINDOW(NULL, WinX, WinY, PicWidth, PicHeight, true);
	if (Win)
	{
		INPUTBOX_WIN_EVENT_HANDLER* EventHandler = new_noexcpt INPUTBOX_WIN_EVENT_HANDLER();
		if (EventHandler)
		{
			Win->LinkEventHandler(EventHandler);
			Win->SetCaption("InputBox");
		}
		else
		{
			PostMessage(Win, WM_DESTROY, 0, 0);
			Win = NULL;
		}
	}
	m_InpBuf = Buf;
	*Buf = 0;
	m_BufLen = BufLen;
	MenuSelected = false;
	MenuSelectIndex = 0;
	InputMenu.ItemCount = UnitCount;
	InputMenu.Items = (MenuItemStruct*)malloc(sizeof(MenuItemStruct) * UnitCount);
	if (InputMenu.Items)
	{
		MenuItemStruct* MIS = InputMenu.Items;
		for (u32 i = 0; i < InputMenu.ItemCount; i++)
		{
			MIS->CallBack = InputMenuCallback;
			MIS->Caption = *(Units + i);
			MIS->Enabled = true;
			MIS->Style = ButtonItem;
			MIS->SubCaption = 0;
			MIS->Tag = i;
			MIS++;
		}
	}
	InputMenu.CallBack = NULL;
	InputMenu.MenuCaption = "ÊäÈëÊý¾Ý";
	return Win;
}

void InputBox(pstr Buf, u32 BufLen, pcstr* Units, u32 UnitCount, u32* SelectedMenu)
{
	WINDOW* Win = InputPrepare(Buf, BufLen, Units, UnitCount);
	MENU* GlobalMenu = GetGlobalMenu();
	GlobalMenu->EnterMenu(&InputMenu);
	while (MenuSelected == false)
	{
		DoMessageLoop();
	}
	if (SelectedMenu)
	{
		*SelectedMenu = MenuSelectIndex;
	}
	GlobalMenu->ExitMenu();
	FreeAndEraseReference(GlobalMenu);
	free(InputMenu.Items);
	InputMenu.ItemCount = 0;
	InputMenu.Items = NULL;
	m_BufLen = 0;
	m_InpBuf = NULL;
	PostMessage(Win, WM_DESTROY, 0, 0);
}

void INPUTBOX_WIN_EVENT_HANDLER::OnDestroy(WINDOW * Win)
{
}

bool INPUTBOX_WIN_EVENT_HANDLER::OnKeyPress(WINDOW * Win, KEYCODE Key)
{
	u32 LengthOfStrInBuf = strlen(m_InpBuf);
	if (LengthOfStrInBuf < m_BufLen - 1)
	{
		switch (Key)
		{
		case KEY_1:
			m_InpBuf[LengthOfStrInBuf] = '1';
			m_InpBuf[LengthOfStrInBuf + 1] = 0;
			break;
		case KEY_2:
			m_InpBuf[LengthOfStrInBuf] = '2';
			m_InpBuf[LengthOfStrInBuf + 1] = 0;
			break;
		case KEY_3:
			m_InpBuf[LengthOfStrInBuf] = '3';
			m_InpBuf[LengthOfStrInBuf + 1] = 0;
			break;
		case KEY_4:
			m_InpBuf[LengthOfStrInBuf] = '4';
			m_InpBuf[LengthOfStrInBuf + 1] = 0;
			break;
		case KEY_5:
			m_InpBuf[LengthOfStrInBuf] = '5';
			m_InpBuf[LengthOfStrInBuf + 1] = 0;
			break;
		case KEY_6:
			m_InpBuf[LengthOfStrInBuf] = '6';
			m_InpBuf[LengthOfStrInBuf + 1] = 0;
			break;
		case KEY_7:
			m_InpBuf[LengthOfStrInBuf] = '7';
			m_InpBuf[LengthOfStrInBuf + 1] = 0;
			break;
		case KEY_8:
			m_InpBuf[LengthOfStrInBuf] = '8';
			m_InpBuf[LengthOfStrInBuf + 1] = 0;
			break;
		case KEY_9:
			m_InpBuf[LengthOfStrInBuf] = '9';
			m_InpBuf[LengthOfStrInBuf + 1] = 0;
			break;
		case KEY_0:
			m_InpBuf[LengthOfStrInBuf] = '0';
			m_InpBuf[LengthOfStrInBuf + 1] = 0;
			break;
		case KEY_DOT:
			m_InpBuf[LengthOfStrInBuf] = '.';
			m_InpBuf[LengthOfStrInBuf + 1] = 0;
			break;
		case KEY_BACK:
			if (LengthOfStrInBuf)
			{
				m_InpBuf[LengthOfStrInBuf - 1] = 0;
			}
			break;
		default:
			return false;
			break;
		}
	}
	PostMessage(Win, WM_PAINT, 0, 0);
	return true;
}

bool INPUTBOX_WIN_EVENT_HANDLER::OnPaint(WINDOW * Win)
{
	DC* DrawingDC = Win->GetDC();
	FLASHFSPIC BackGround(InputBox_Background);
	BackGround.Draw(DrawingDC, 0, 0);
	FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC48;HZK48S;HZK48T"));
	DrawStringHorizontal(DrawingDC, FG, m_InpBuf, 10, 20, 0, 0, WHITE, TransparentColorKey);
	FreeAndEraseReference(FG);
	FreeAndEraseReference(DrawingDC);
	return false;
}
