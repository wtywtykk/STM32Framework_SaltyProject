#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\Window\Window.h"
#include "Kernel\GUI\Picture\FlashFSPic.h"
#include "Kernel\GUI\Menu\Menu.h"
#include "Kernel\GUI\Menu\MenuItem.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\EstimateString.h"

const pcstr MenuPic_Blank = "MnuBlank.SP";
const pcstr MenuPic_Button_Selected = "MnuBtnS.SP";
const pcstr MenuPic_Button_UnSelected = "MnuBtnU.SP";
const pcstr MenuPic_Popup_SubCaption_Selected = "MnuPopDispS.SP";
const pcstr MenuPic_Popup_SubCaption_UnSelected = "MnuPopDispU.SP";
const pcstr MenuPic_Popup_Selected = "MnuPopNdS.SP";
const pcstr MenuPic_Popup_UnSelected = "MnuPopNdU.SP";
const pcstr MenuPic_Return = "MnuRet.SP";
const pcstr MenuPic_SubMenu_Selected = "MnuSubS.SP";
const pcstr MenuPic_SubMenu_UnSelected = "MnuSubU.SP";
const pcstr MenuPic_Turn_Selected = "MnuTurnCenS.SP";
const pcstr MenuPic_Turn_UnSelected = "MnuTurnCenU.SP";
const pcstr MenuPic_Turn_SubCaption_Selected = "MnuTurnCorS.SP";
const pcstr MenuPic_Turn_SubCaption_UnSelected = "MnuTurnCorU.SP";

const pcstr Menu_Caption_Font_NoSub = "ASC24;HZK24S;HZK24T";
const pcstr Menu_Caption_Font_WithSub = "ASC16;HZK16";
const pcstr Menu_SubCaption_Font = "ASC16;HZK16";

const PIXEL Menu_Caption_TextColor_Enabled = WHITE;
const PIXEL Menu_Caption_TextColor_Disabled = DGRAY;

const GUIPOS DefaultMenuItemWidth = 88;
const GUIPOS DefaultMenuItemHeight = 66;

const pcstr MenuItemClassWinPropName = "MICP";

class MENU_ITEM_WIN_EVENT_HANDLER :public WINEVENT
{
private:
	virtual void OnDestroy(WINDOW* Win);
	virtual bool OnKeyPress(WINDOW* Win, KEYCODE Key);
	virtual bool OnPaint(WINDOW* Win);
	virtual bool OnEncoder(WINDOW* Win, u8 EncoderIndex, s32 Val);
};

void MENU_ITEM_WIN_EVENT_HANDLER::OnDestroy(WINDOW * Win)
{
	MENUITEM* MenuItem = (MENUITEM*)GetWindowProp(Win, MenuItemClassWinPropName);
	FreeAndEraseReference(MenuItem);
}

bool MENU_ITEM_WIN_EVENT_HANDLER::OnKeyPress(WINDOW* Win, KEYCODE Key)
{
	MENUITEM* MenuItem = (MENUITEM*)GetWindowProp(Win, MenuItemClassWinPropName);
	if (MenuItem)
	{
		if (Key == MenuItem->SensitiveKey)
		{
			MenuItem->ParentMenu->SetSelectedItem(MenuItem->CurrentIndex);
			if (MenuItem->CurItem && MenuItem->CurItem->CallBack)
			{
				MenuItem->CurItem->CallBack(MenuItem->CurItem, ItemPress, 0);
			}
			return true;
		}
	}
	return false;
}

bool MENU_ITEM_WIN_EVENT_HANDLER::OnPaint(WINDOW* Win)
{
	MENUITEM* MenuItem = (MENUITEM*)GetWindowProp(Win, MenuItemClassWinPropName);
	pcstr BackgroundName = MenuItem->GetItemBackground(MenuItem->IsSelected());
	DC* DrawingDC = Win->GetDC();
	if (BackgroundName)
	{
		FLASHFSPIC Pic(BackgroundName);
		Pic.Draw(DrawingDC, 0, 0);

		if (MenuItem->CurItem->Caption)
		{
			pcstr CaptionFont = MenuItem->GetItemCaptionFont();
			if (CaptionFont)
			{
				FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP(CaptionFont));
				RECT CaptionArea;
				GUIPOS EstWidth = 0;
				GUIPOS EstHeight = 0;
				PIXEL CaptionColor = MenuItem->CurItem->Enabled ? Menu_Caption_TextColor_Enabled : Menu_Caption_TextColor_Disabled;
				MenuItem->GetItemCaptionArea(&CaptionArea);
				EstimateStringHorizontal(DrawingDC, FG, MenuItem->CurItem->Caption, CaptionArea.Left, CaptionArea.Top, CaptionArea.Right - CaptionArea.Left, CaptionArea.Bottom - CaptionArea.Top, &EstWidth, &EstHeight);
				CaptionArea.Left += (CaptionArea.Right - CaptionArea.Left - EstWidth) / 2;
				CaptionArea.Top += (CaptionArea.Bottom - CaptionArea.Top - EstHeight) / 2;
				DrawStringHorizontal(DrawingDC, FG, MenuItem->CurItem->Caption, CaptionArea.Left, CaptionArea.Top, CaptionArea.Right - CaptionArea.Left, CaptionArea.Bottom - CaptionArea.Top, CaptionColor, TransparentColorKey);
				FreeAndEraseReference(FG);
			}
		}
		if (MenuItem->CurItem->SubCaption)
		{
			FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP(Menu_SubCaption_Font));
			RECT SubCaptionArea;
			GUIPOS EstWidth = 0;
			GUIPOS EstHeight = 0;
			PIXEL SubCaptionColor = MenuItem->CurItem->Enabled ? Menu_Caption_TextColor_Enabled : Menu_Caption_TextColor_Disabled;
			MenuItem->GetItemSubCaptionArea(&SubCaptionArea);
			EstimateStringHorizontal(DrawingDC, FG, MenuItem->CurItem->SubCaption, SubCaptionArea.Left, SubCaptionArea.Top, SubCaptionArea.Right - SubCaptionArea.Left, SubCaptionArea.Bottom - SubCaptionArea.Top, &EstWidth, &EstHeight);
			SubCaptionArea.Left += (SubCaptionArea.Right - SubCaptionArea.Left - EstWidth) / 2;
			SubCaptionArea.Top += (SubCaptionArea.Bottom - SubCaptionArea.Top - EstHeight) / 2;
			DrawStringHorizontal(DrawingDC, FG, MenuItem->CurItem->SubCaption, SubCaptionArea.Left, SubCaptionArea.Top, SubCaptionArea.Right - SubCaptionArea.Left, SubCaptionArea.Bottom - SubCaptionArea.Top, SubCaptionColor, TransparentColorKey);
			FreeAndEraseReference(FG);
		}
	}
	else
	{
		GUIPOS ItemWidth = 0;
		GUIPOS ItemHeight = 0;
		MenuItem->GetSize(&ItemWidth, &ItemHeight);
		DrawingDC->Fill(0, 0, ItemWidth, ItemHeight, BLACK);
	}
	FreeAndEraseReference(DrawingDC);
	return false;
}

bool MENU_ITEM_WIN_EVENT_HANDLER::OnEncoder(WINDOW * Win, u8 EncoderIndex, s32 Val)
{
	MENUITEM* MenuItem = (MENUITEM*)GetWindowProp(Win, MenuItemClassWinPropName);
	if (MenuItem)
	{
		if (MenuItem->CurItem && MenuItem->CurItem->CallBack)
		{
			MenuItem->CurItem->CallBack(MenuItem->CurItem, ItemTurn, Val);
		}
		return true;
	}
	return false;
}

MENUITEM::MENUITEM(MENU* Menu, GUIPOS X, GUIPOS Y, KEYCODE Key)
{
	GUIPOS MenuItemWidth;
	GUIPOS MenuItemHeight;
	GetSize(&MenuItemWidth, &MenuItemHeight);

	SensitiveKey = Key;

	ParentMenu = NewReferenceSafe(Menu);
	Win = new_noexcpt WINDOW(ParentMenu->Win, X, Y, MenuItemWidth, MenuItemHeight, false);
	if (Win)
	{
		MENU_ITEM_WIN_EVENT_HANDLER* ItemEventHandler = new_noexcpt MENU_ITEM_WIN_EVENT_HANDLER();
		if (ItemEventHandler)
		{
			SetWindowProp(Win, MenuItemClassWinPropName, (u32)this);
			Win->LinkEventHandler(ItemEventHandler);
			Win->SetCaption("MenuItemWin");
		}
		else
		{
			PostMessage(Win, WM_DESTROY, 0, 0);
			Win = NULL;
		}
	}
}

MENUITEM::~MENUITEM()
{
	FreeAndEraseReference(ParentMenu);
}

void MENUITEM::Destroy()
{
	PostMessage(Win, WM_DESTROY, 0, 0);
	Win = NULL;
}

void MENUITEM::GetSize(GUIPOS* Width, GUIPOS* Height)
{
	FLASHFSPIC MenuPicBlank(MenuPic_Blank);
	if (Width)
	{
		GUIPOS PicWidth = MenuPicBlank.GetWidth();
		if (PicWidth)
		{
			*Width = PicWidth;
		}
		else
		{
			*Width = DefaultMenuItemWidth;
		}
	}
	if (Height)
	{
		GUIPOS PicHeight = MenuPicBlank.GetHeight();
		if (PicHeight)
		{
			*Height = PicHeight;
		}
		else
		{
			*Height = DefaultMenuItemHeight;
		}
	}
}

void MENUITEM::SetItem(MenuItemStruct * NewItem, u8 Index)
{
	if (NewItem != CurItem || Index != CurrentIndex)
	{
		CurItem = NewItem;
		CurrentIndex = Index;
	}
}

void MENUITEM::RefreshItem(void)
{
	PostMessage(Win, WM_PAINT, 0, 0);
}

pcstr MENUITEM::GetItemBackground(bool Selected)
{
	if (CurItem == NULL)
	{
		return NULL;
	}
	switch (CurItem->Style)
	{
	default:
	case BlankItem:
		return MenuPic_Blank;
	case ButtonItem:
		if (Selected)
		{
			return MenuPic_Button_Selected;
		}
		else
		{
			return MenuPic_Button_UnSelected;
		}
	case PopupItem:
		if (CurItem->SubCaption)
		{
			if (Selected)
			{
				return MenuPic_Popup_SubCaption_Selected;
			}
			else
			{
				return MenuPic_Popup_SubCaption_UnSelected;
			}
		}
		else
		{
			if (Selected)
			{
				return MenuPic_Popup_Selected;
			}
			else
			{
				return MenuPic_Popup_UnSelected;
			}
		}
	case ReturnItem:
		return MenuPic_Return;
	case SubMenuItem:
		if (Selected)
		{
			return MenuPic_SubMenu_Selected;
		}
		else
		{
			return MenuPic_SubMenu_UnSelected;
		}
	case TurnItem:
		if (CurItem->SubCaption)
		{
			if (Selected)
			{
				return MenuPic_Turn_SubCaption_Selected;
			}
			else
			{
				return MenuPic_Turn_SubCaption_UnSelected;
			}
		}
		else
		{
			if (Selected)
			{
				return MenuPic_Turn_Selected;
			}
			else
			{
				return MenuPic_Turn_UnSelected;
			}
		}
	}
}

pcstr MENUITEM::GetItemCaptionFont(void)
{
	if (CurItem == NULL)
	{
		return NULL;
	}
	switch (CurItem->Style)
	{
	default:
	case BlankItem:
		return NULL;
	case ReturnItem:
	case TurnItem:
		return Menu_Caption_Font_WithSub;
	case ButtonItem:
	case PopupItem:
		if (CurItem->SubCaption)
		{
			return Menu_Caption_Font_WithSub;
		}
		else
		{
			return Menu_Caption_Font_NoSub;
		}
	case SubMenuItem:
		return Menu_Caption_Font_NoSub;
	}
}

void MENUITEM::GetItemCaptionArea(RECT* Area)
{
	if (CurItem == NULL)
	{
		return;
	}
	switch (CurItem->Style)
	{
	default:
	case BlankItem:
		Area->Left = 0;
		Area->Top = 0;
		Area->Right = 0;
		Area->Bottom = 0;
		break;
	case ReturnItem:
	case TurnItem:
		Area->Left = 2;
		Area->Top = 4;
		Area->Right = 85;
		Area->Bottom = 22;
		break;
	case ButtonItem:
		if (CurItem->SubCaption)
		{
			Area->Left = 2;
			Area->Top = 4;
			Area->Right = 85;
			Area->Bottom = 22;
			break;
		}
		else
		{
			Area->Left = 5;
			Area->Top = 25;
			Area->Right = 82;
			Area->Bottom = 58;
			break;
		}
	case PopupItem:
		if (CurItem->SubCaption)
		{
			Area->Left = 2;
			Area->Top = 4;
			Area->Right = 85;
			Area->Bottom = 22;
			break;
		}
		else
		{
			Area->Left = 12;
			Area->Top = 24;
			Area->Right = 82;
			Area->Bottom = 57;
			break;
		}
	case SubMenuItem:
		Area->Left = 2;
		Area->Top = 4;
		Area->Right = 85;
		Area->Bottom = 47;
		break;
	}
}

void MENUITEM::GetItemSubCaptionArea(RECT * Area)
{
	if (CurItem == NULL)
	{
		return;
	}
	switch (CurItem->Style)
	{
	default:
	case BlankItem:
	case ReturnItem:
	case SubMenuItem:
		Area->Left = 0;
		Area->Top = 0;
		Area->Right = 0;
		Area->Bottom = 0;
		break;
	case TurnItem:
		Area->Left = 21;
		Area->Top = 25;
		Area->Right = 82;
		Area->Bottom = 58;
		break;
	case ButtonItem:
		Area->Left = 5;
		Area->Top = 24;
		Area->Right = 88;
		Area->Bottom = 57;
		break;
	case PopupItem:
		Area->Left = 11;
		Area->Top = 24;
		Area->Right = 82;
		Area->Bottom = 57;
		break;
	}
}

bool MENUITEM::IsSelected(void)
{
	if (CurrentIndex == INVALID_MENU_INDEX || ParentMenu->GetSelectedItem() == INVALID_MENU_INDEX)
	{
		return false;
	}
	else
	{
		if (ParentMenu->GetSelectedItem() == CurrentIndex)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
