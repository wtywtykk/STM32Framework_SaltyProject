#include "Kernel\GUI\GUICommon.h"
#include "Kernel\GUI\DC\DC.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Window\ScreenWindow.h"

SCREENWINDOW* Screen = NULL;

SCREENWINDOW::SCREENWINDOW(DC* ScreenDC, GUIPOS ScreenWidth, GUIPOS ScreenHeight, bool Buffered) :WINDOW(0, 0, ScreenWidth, ScreenHeight, Buffered)
{
	DrawingDC = NewReferenceSafe(new_noexcpt CLIPPEDDC(ScreenDC, 0, 0, ScreenWidth, ScreenHeight, Buffered, true));
	SetCaption("SCREEN");
}

SCREENWINDOW::~SCREENWINDOW(void)
{
}

void SCREENWINDOW::Move(GUIPOS NewX, GUIPOS NewY)
{
}

void SCREENWINDOW::Resize(GUIPOS NewWidth, GUIPOS NewHeight)
{
}

void SCREENWINDOW::RecreateDC(void)
{
}

WINDOW* SCREENWINDOW::GetScreenWindow(void)
{
	return NewReferenceSafe(Screen);
}

STATUS SCREENWINDOW::ScreenWindow_Init(void)
{
	Screen = NewReferenceSafe(new_noexcpt SCREENWINDOW(g_LCDDC, g_LCDDC->GetWidth(), g_LCDDC->GetHeight(), false));
	if (Screen)
	{
		Screen->MarkObjectStatic();
		return S_OK;
	}
	else
	{
		return S_FAIL;
	}
}
