#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\Window\Window.h"
#include "Kernel\GUI\Window\ScreenWindow.h"
#include "Kernel\GUI\Shape\Line.h"
#include "Kernel\GUI\Misc\RECT.h"
#include <assert.h>

WINDOW::WINDOW(GUIPOS WinX, GUIPOS WinY, GUIPOS WinWidth, GUIPOS WinHeight, bool Buffered)
{
	InitBasicInfo(WinX, WinY, WinWidth, WinHeight, Buffered);
}

WINDOW::WINDOW(WINDOW * ParentWindow, GUIPOS WinX, GUIPOS WinY, GUIPOS WinWidth, GUIPOS WinHeight, bool Buffered)
{
	InitBasicInfo(WinX, WinY, WinWidth, WinHeight, Buffered);
	if (ParentWindow)
	{
		Parent = NewReferenceSafe(ParentWindow);
	}
	else
	{
		Parent = SCREENWINDOW::GetScreenWindow();
	}
	RecreateDC();
	Parent->ChildList.push_front(NewReferenceSafe(this));
	DrawDefaultWindow();
	PostMessage(Parent, WM_PAINT, 0, 0);
}

WINDOW::~WINDOW(void)
{
	if (EventHandler)
	{
		FreeAndEraseReference(EventHandler);
	}
	if (DrawingDC)
	{
		FreeAndEraseReference(DrawingDC);
	}
}

void WINDOW::Move(GUIPOS NewX, GUIPOS NewY)
{
	X = NewX;
	Y = NewY;
	RecreateDC();
}

void WINDOW::Resize(GUIPOS NewWidth, GUIPOS NewHeight)
{
	Width = NewWidth;
	Height = NewHeight;
	RecreateDC();
}

void WINDOW::GetWindowPos(GUIPOS* PosX, GUIPOS* PosY, GUIPOS* PosWidth, GUIPOS* PosHeight)
{
	if (PosX)
	{
		*PosX = X;
	}
	if (PosY)
	{
		*PosY = Y;
	}
	if (PosWidth)
	{
		*PosWidth = Width;
	}
	if (PosHeight)
	{
		*PosHeight = Height;
	}
}

DC* WINDOW::GetDC(void)
{
	return NewReferenceSafe(DrawingDC);
}

void WINDOW::LinkEventHandler(WINEVENT* Handler)
{
	if (EventHandler)
	{
		FreeAndEraseReference(EventHandler);
	}
	EventHandler = NewReferenceSafe(Handler);
}

void WINDOW::SetCaption(pcstr NewCaption)
{
	Caption = NewCaption;
}

void WINDOW::InitBasicInfo(GUIPOS WinX, GUIPOS WinY, GUIPOS WinWidth, GUIPOS WinHeight, bool Buffered)
{
	X = WinX;
	Y = WinY;
	Width = WinWidth;
	Height = WinHeight;
	BufferEnabled = Buffered;
	Destroyed = false;
}

void WINDOW::Terminate(void)
{
	Destroyed = true;
	for (WINLIST::iterator Child = ChildList.begin(); Child != ChildList.end(); Child++)
	{
		PostMessage(*Child, WM_DESTROY, 0, 0);
	}
	PostMessage(Parent, WM_PAINT, 0, 0);
	if (Parent)
	{
		Parent->ChildList.remove(this);
		FreeAndEraseReference(Parent);
	}
	FreeReference();
}

void WINDOW::DrawDefaultWindow(void)
{
	DrawingDC->Fill(0, 0, Width, Height, DGRAY);

	DrawLine(DrawingDC, 0, 0, 0, Height - 1, RED);
	DrawLine(DrawingDC, 0, 0, Width - 1, 0, RED);
	DrawLine(DrawingDC, Width - 1, 0, Width - 1, Height - 1, RED);
	DrawLine(DrawingDC, 0, Height - 1, Width - 1, Height - 1, RED);

	DrawLine(DrawingDC, 0, 0, Width, Height, WHITE);
	DrawLine(DrawingDC, Width, 0, 0, Height, WHITE);
}

void WINDOW::Paint(bool ParentIssuedPaint)
{
	for (WINLIST::reverse_iterator Child = ChildList.rbegin(); Child != ChildList.rend(); Child++)
	{
		PostMessage(*Child, WM_PAINT, true, 0);
	}
	PostMessage(this, WM_ENDPAINT, ParentIssuedPaint, 0);
}

void WINDOW::PaintChildBefore(WINDOW* Win, bool ParentIssuedPaint)
{
	bool Before = false;
	RECT PaintRect;
	Win->GetWindowPos(&PaintRect.Left, &PaintRect.Top, &PaintRect.Right, &PaintRect.Bottom);
	PaintRect.Right += PaintRect.Left;
	PaintRect.Bottom += PaintRect.Top;
	for (WINLIST::reverse_iterator Child = ChildList.rbegin(); Child != ChildList.rend(); Child++)
	{
		if (Before)
		{
			RECT ChildRect;
			(*Child)->GetWindowPos(&ChildRect.Left, &ChildRect.Top, &ChildRect.Right, &ChildRect.Bottom);
			ChildRect.Right += ChildRect.Left;
			ChildRect.Bottom += ChildRect.Top;
			if (IsRectIntersect(&PaintRect, &ChildRect))
			{
				PostMessage(*Child, WM_PAINT, true, 0);
			}
		}
		if (*Child == Win)
		{
			Before = true;
		}
	}
	PostMessage(this, WM_ENDPAINT, ParentIssuedPaint, 0);
	FreeAndEraseReference(Win);
}

void WINDOW::EndPaint(bool ParentIssuedPaint)
{
	DrawingDC->Update();
	if (!ParentIssuedPaint)
	{
		PostMessage(Parent, WM_PAINTBEFORE, (u32)NewReferenceSafe(this), 0);
	}
}

void WINDOW::RecreateDC(void)
{
	if (DrawingDC)
	{
		FreeAndEraseReference(DrawingDC);
	}
	DC* ParentDC = Parent->GetDC();
	DrawingDC = NewReferenceSafe(new_noexcpt CLIPPEDDC(ParentDC, X, Y, X + Width, Y + Height, BufferEnabled, true));
	FreeAndEraseReference(ParentDC);
}

bool WINDOW::WinProc(WINDOW * Win, MSGCODE MsgCode, u32 wParam, u32 lParam)
{
	if (Destroyed)
	{
		return false;
	}
	if (EventHandler)
	{
		if (EventHandler->WinProc(Win, MsgCode, wParam, lParam))
		{
			return true;
		}
	}
	return WINEVENT::DefaultWinProc(Win, MsgCode, wParam, lParam);
}
