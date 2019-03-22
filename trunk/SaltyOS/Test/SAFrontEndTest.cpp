#include "HAL\HCommon.h"
#include "Kernel\GUI\Window\Window.h"
#include "Kernel\GUI\Window\WinEvent.h"
#include "Kernel\GUI\Window\WindowManager.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Driver\SAFrontEnd.h"

WINDOW* SAFrontEndTest_Win = NULL;

class SAFrontEnd_EVENT :public WINEVENT
{
private:
	//Override those methods to handle messages
	virtual bool OnKeyPress(WINDOW* Win, KEYCODE Key);
	virtual bool OnPaint(WINDOW* Win);
	virtual bool OnEncoder(WINDOW* Win, u8 EncoderIndex, s32 Val);
};

void SAFrontEndTest_CreateWin(void)
{
	SAFrontEndTest_Win = new_noexcpt WINDOW(NULL, 20, 20, 500, 300, true);
	WINEVENT* Event = new_noexcpt SAFrontEnd_EVENT();
	SAFrontEndTest_Win->LinkEventHandler(Event);
	SAFrontEndTest_Win->SetCaption("SAFrontEndTestWin");
}

void SAFrontEndTest(void)
{
	static bool Created = false;
	if (!Created)
	{
		Created = true;
		SAFrontEnd_Init();
		SAFrontEndTest_CreateWin();
	}
	DoMessageLoop();
}

bool SAFrontEnd_EVENT::OnKeyPress(WINDOW * Win, KEYCODE Key)
{
	if (Key == KEY_1)
	{
		SetWindowProp(Win, "LNA1", !GetWindowProp(Win, "LNA1"));
		PostMessage(Win, WM_PAINT, 0, 0);
	}
	if (Key == KEY_2)
	{
		SetWindowProp(Win, "LNA2", !GetWindowProp(Win, "LNA2"));
		PostMessage(Win, WM_PAINT, 0, 0);
	}
	return true;
}

bool SAFrontEnd_EVENT::OnPaint(WINDOW * Win)
{
	DC* DrawingDC = Win->GetDC();
	FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC48"));
	char sbuf[128];
	bool LNA1 = (s32)GetWindowProp(Win, "LNA1");
	bool LNA2 = (s32)GetWindowProp(Win, "LNA2");
	s32 EncVal = (s32)GetWindowProp(Win, "EncVal");
	if ((EncVal / 2) * 0.25 > 31.75)
	{
		EncVal = 2 * 31.75 / 0.25;
	}
	if (EncVal < 0)
	{
		EncVal = 0;
	}
	SetWindowProp(Win, "EncVal", EncVal);
	sprintf(sbuf, "LNA1: %s LNA2: %s     ", LNA1 ? "ON" : "OFF", LNA2 ? "ON" : "OFF");
	DrawStringHorizontal(DrawingDC, FG, sbuf, 0, 0, 0, 0, BLACK, WHITE);
	sprintf(sbuf, "DSA: %f     ", (EncVal / 2) * 0.25);
	DrawStringHorizontal(DrawingDC, FG, sbuf, 0, 50, 0, 0, BLACK, WHITE);
	SAFrontEnd_EnableLNA1(LNA1);
	SAFrontEnd_EnableLNA2(LNA2);
	SAFrontEnd_SetDSA((EncVal / 2) * 0.25);
	FreeAndEraseReference(FG);
	FreeAndEraseReference(DrawingDC);
	return false;
}

bool SAFrontEnd_EVENT::OnEncoder(WINDOW * Win, u8 EncoderIndex, s32 Val)
{
	if (EncoderIndex == 0)
	{
		SetWindowProp(Win, "EncVal", (s32)GetWindowProp(Win, "EncVal") + Val);
		PostMessage(Win, WM_PAINT, 0, 0);
		return true;
	}
	else
	{
		return false;
	}
}
