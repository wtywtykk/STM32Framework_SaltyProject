#pragma once

#include "Kernel\GUI\Window\MessageCode.h"

typedef struct
{
	class WINDOW* Win;
	MSGCODE MsgCode;
	u32 wParam;
	u32 lParam;
}MSG;

STATUS WindowManager_Init(void);
void PostMessage(WINDOW* Win, MSGCODE MsgCode, u32 wParam, u32 lParam);
void SetFocus(WINDOW* Win);
bool PeekMessage(MSG* msg);
bool DispatchMessage(MSG* msg);
STATUS WindowManager_RefreshUI(void);
void DoMessageLoop(void);
