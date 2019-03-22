#include "Kernel\GUI\Window\WinEvent.h"
#include "Kernel\GUI\Window\WindowManager.h"

bool WINEVENT::DefaultWinProc(WINDOW* Win, MSGCODE MsgCode, u32 wParam, u32 lParam)
{
	switch (MsgCode)
	{
	case WM_DESTROY:
		Win->Terminate();
		return true;
	case WM_CLOSE:
		PostMessage(Win, WM_DESTROY, wParam, lParam);
		return true;
	case WM_CLICK:
		for (WINLIST::iterator Child = Win->ChildList.begin(); Child != Win->ChildList.end(); Child++)
		{
			GUIPOS ClickX = wParam;
			GUIPOS ClickY = lParam;
			GUIPOS ChildLeft = (*Child)->X;
			GUIPOS ChildTop = (*Child)->Y;
			GUIPOS ChildRight = ChildLeft + (*Child)->Width;
			GUIPOS ChildBottom = ChildTop + (*Child)->Height;
			if (ClickX >= ChildLeft && ClickX < ChildRight && ClickY >= ChildTop && ClickY < ChildBottom)
			{
				PostMessage(*Child, MsgCode, ClickX - ChildLeft, ClickY - ChildTop);
			}
		}
		return true;
	case WM_KEYPRESS:
	case WM_ENCODER:
		for (WINLIST::iterator Child = Win->ChildList.begin(); Child != Win->ChildList.end(); Child++)
		{
			PostMessage(*Child, MsgCode, wParam, lParam);
		}
		return true;
	case WM_PAINT:
		Win->Paint(wParam);
		return true;
	case WM_PAINTBEFORE:
		Win->PaintChildBefore((WINDOW*)wParam, wParam);
		return true;
	case WM_ENDPAINT:
		Win->EndPaint(wParam);
		return true;
	default:
		return false;
	}
}

bool WINEVENT::WinProc(WINDOW * Win, MSGCODE MsgCode, u32 wParam, u32 lParam)
{
	switch (MsgCode)
	{
	case WM_NULL:
		return true;
	case WM_DESTROY:
		OnDestroy(Win);
		return false;
	case WM_CLOSE:
		return OnClose(Win);
	case WM_SETFOCUS:
		OnSetFocus(Win);
		return true;
	case WM_KILLFOCUS:
		OnKillFocus(Win);
		return true;
	case WM_CLICK:
		return OnClick(Win, (GUIPOS)wParam, (GUIPOS)lParam);
	case WM_KEYPRESS:
		return OnKeyPress(Win, (KEYCODE)wParam);
	case WM_PAINT:
		return OnPaint(Win);
	case WM_ENCODER:
		return OnEncoder(Win, wParam, (s32)lParam);
	default:
		return false;
	}
}
