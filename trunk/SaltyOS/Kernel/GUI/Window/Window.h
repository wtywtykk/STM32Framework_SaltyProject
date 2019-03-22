#pragma once

#include "Kernel\GUI\GUICommon.h"
#include "Kernel\Common\KObject.h"
#include "Kernel\GUI\DC\ClippedDC.h"
#include "Kernel\GUI\Window\MessageCode.h"
#include "Kernel\GUI\Window\WindowManager.h"
#include "Kernel\GUI\Window\WinEvent.h"

#include <list>
#include <string>
#include <map>

class WINDOW;
class WINEVENT;

typedef std::list<WINDOW*> WINLIST;
typedef std::map<std::string, u32> PROPMAP;

class WINDOW :public KOBJECT
{
	friend void BringToTop(WINDOW* Win);
	friend void BringToTopOf(WINDOW* Win, WINDOW* WinBefore);
	friend void SetWindowProp(WINDOW * Win, pcstr Key, u32 Data);
	friend u32 GetWindowProp(WINDOW * Win, pcstr Key);
	friend void RemoveWindowProp(WINDOW * Win, pcstr Key);
	friend bool DispatchMessage(MSG* msg);
	friend class WINEVENT;
	GUIPOS X;
	GUIPOS Y;
	GUIPOS Width;
	GUIPOS Height;
	WINDOW* Parent = NULL;
	bool BufferEnabled;
	bool Destroyed;
	WINLIST ChildList;
	WINEVENT* EventHandler = NULL;
	PROPMAP PropMap;
	pcstr Caption = NULL;
protected:
	CLIPPEDDC* DrawingDC = NULL;;
	WINDOW(GUIPOS WinX, GUIPOS WinY, GUIPOS WinWidth, GUIPOS WinHeight, bool Buffered);
public:
	WINDOW(WINDOW* ParentWindow, GUIPOS WinX, GUIPOS WinY, GUIPOS WinWidth, GUIPOS WinHeight, bool Buffered);
	virtual ~WINDOW(void);
	virtual void Move(GUIPOS NewX, GUIPOS NewY);
	virtual void Resize(GUIPOS NewWidth, GUIPOS NewHeight);
	void GetWindowPos(GUIPOS* PosX, GUIPOS* PosY, GUIPOS* PosWidth, GUIPOS* PosHeight);
	DC* GetDC(void);
	void LinkEventHandler(WINEVENT* Handler);
	void SetCaption(pcstr NewCaption);
private:
	void InitBasicInfo(GUIPOS WinX, GUIPOS WinY, GUIPOS WinWidth, GUIPOS WinHeight, bool Buffered);
	void Terminate(void);
	void DrawDefaultWindow(void);
	void Paint(bool ParentIssuedPaint);
	void PaintChildBefore(WINDOW* Win, bool ParentIssuedPaint);
	void EndPaint(bool ParentIssuedPaint);
	virtual void RecreateDC(void);
	bool WinProc(WINDOW* Win, MSGCODE MsgCode, u32 wParam, u32 lParam);
};
