#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\Window\Window.h"
#include "Kernel\GUI\Window\WindowManager.h"
#include "Kernel\GUI\Window\MessageCode.h"
#include "Kernel\GUI\Window\ScreenWindow.h"
#include "Kernel\Input\Input.h"
#include <assert.h>
#include <queue>

typedef std::queue<MSG> MESSAGEQUEUE;

MESSAGEQUEUE* MsgQueue = NULL;
WINLIST WindowToDestroy;
WINDOW* FocusWindow = NULL;

STATUS WindowManager_Init(void)
{
	MsgQueue = new_noexcpt MESSAGEQUEUE;
	if (MsgQueue)
	{
		return S_OK;
	}
	else
	{
		return S_FAIL;
	}
}

void PostMessage(WINDOW* Win, MSGCODE MsgCode, u32 wParam, u32 lParam)
{
	if (Win)
	{
		MSG NewMsg;
		NewMsg.Win = NewReferenceSafe(Win);
		NewMsg.MsgCode = MsgCode;
		NewMsg.wParam = wParam;
		NewMsg.lParam = lParam;
		MsgQueue->push(NewMsg);
	}
}

void SetFocus(WINDOW* Win)
{
	PostMessage(FocusWindow, WM_KILLFOCUS, 0, 0);
	FocusWindow = Win;
	PostMessage(FocusWindow, WM_SETFOCUS, 0, 0);
}

bool PeekMessage(MSG* msg)
{
	if (!MsgQueue->empty())
	{
		*msg = MsgQueue->front();
		MsgQueue->pop();
		return true;
	}
	else
	{
		msg->Win = NULL;
		msg->MsgCode = WM_NULL;
		return false;
	}
}

bool DispatchMessage(MSG* msg)
{
	if (msg->Win)
	{
		bool Ret = msg->Win->WinProc(msg->Win, msg->MsgCode, msg->wParam, msg->lParam);
		FreeAndEraseReference(msg->Win);
		return Ret;
	}
	else
	{
		return false;
	}
}

STATUS WindowManager_RefreshUI(void)
{
	WINDOW* ScrWin = SCREENWINDOW::GetScreenWindow();
	PostMessage(ScrWin, WM_PAINT, 0, 0);
	FreeAndEraseReference(ScrWin);
	return S_OK;
}

void DoMessageLoop(void)
{
	MSG msg;
	if (PeekMessage(&msg))
	{
		DispatchMessage(&msg);
	}
	else
	{
		CheckInput();
	}
}
