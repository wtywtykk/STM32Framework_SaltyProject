#pragma once

#include "Kernel\GUI\GUICommon.h"
#include "Kernel\Common\KObject.h"
#include "Kernel\GUI\DC\ClippedDC.h"
#include "Kernel\GUI\Window\Window.h"
#include "Kernel\Input\KeyCode.h"

class SCREENWINDOW :public WINDOW
{
public:
	SCREENWINDOW(DC* ScreenDC, GUIPOS ScreenWidth, GUIPOS ScreenHeight, bool Buffered);
	virtual ~SCREENWINDOW(void);
	virtual void Move(GUIPOS NewX, GUIPOS NewY);
	virtual void Resize(GUIPOS NewWidth, GUIPOS NewHeight);
	static WINDOW* GetScreenWindow(void);
	static STATUS ScreenWindow_Init(void);
private:
	virtual void RecreateDC(void);
};
