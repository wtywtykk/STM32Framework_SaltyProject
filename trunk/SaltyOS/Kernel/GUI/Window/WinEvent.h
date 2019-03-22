#pragma once

#include "Kernel\Common\KObject.h"
#include "Kernel\GUI\Window\Window.h"
#include "Kernel\GUI\Window\MessageCode.h"
#include "Kernel\Input\KeyCode.h"
#include "Kernel\GUI\Menu\Menu.h"

class WINEVENT :public KOBJECT
{
public:
	static bool DefaultWinProc(WINDOW* Win, MSGCODE MsgCode, u32 wParam, u32 lParam);
	bool WinProc(WINDOW* Win, MSGCODE MsgCode, u32 wParam, u32 lParam);
private:
	//Override those methods to handle messages
	virtual void OnDestroy(WINDOW* Win) {};
	virtual bool OnClose(WINDOW* Win) { return false; };
	virtual void OnSetFocus(WINDOW* Win) {};
	virtual void OnKillFocus(WINDOW* Win) {};
	virtual bool OnClick(WINDOW* Win, GUIPOS X, GUIPOS Y) { return false; };
	virtual bool OnKeyPress(WINDOW* Win, KEYCODE Key) { return false; };
	virtual bool OnPaint(WINDOW* Win) { return false; };
	virtual bool OnEncoder(WINDOW* Win, u8 EncoderIndex, s32 Val) { return false; };
};
