#include "HAL\HCommon.h"
#include "Kernel\GUI\Window\Window.h"
#include "Kernel\GUI\Window\WinEvent.h"
#include "Kernel\GUI\Window\WindowManager.h"
#include "Kernel\GUI\Text\DrawString.h"

WINDOW* Win = NULL;
WINEVENT* Event = NULL;

KEYCODE LastKey = KEY_Invalid;

class MYEVENT :public WINEVENT
{
private:
	//Override those methods to handle messages
	virtual bool OnKeyPress(WINDOW* Win, KEYCODE Key);
	virtual bool OnPaint(WINDOW* Win);
	virtual bool OnEncoder(WINDOW* Win, u8 EncoderIndex, s32 Val);
};

void WindowTest_CreateWin(void)
{
	Win = new_noexcpt WINDOW(NULL, 200, 20, 300, 300, true);
	Event = new_noexcpt MYEVENT();
	Win->LinkEventHandler(Event);
	Win->SetCaption("TestWin");
}

void WindowTest(void)
{
	static bool Created = false;
	if (!Created)
	{
		Created = true;
		WindowTest_CreateWin();
	}
	DoMessageLoop();
}

bool MYEVENT::OnKeyPress(WINDOW * Win, KEYCODE Key)
{
	//printf("TestWin:KeyPress %d\n\r", (u16)Key);
	LastKey = Key;
	PostMessage(Win, WM_PAINT, 0, 0);
	return true;
}

bool MYEVENT::OnPaint(WINDOW * Win)
{
	DC* DrawingDC = Win->GetDC();
	switch (LastKey)
	{
	default:
		DrawingDC->Fill(10, 20, 100, 200, RED);
		break;
	case KEY_1:
		DrawingDC->Fill(10, 20, 100, 200, GREEN);
		break;
	case KEY_2:
		DrawingDC->Fill(10, 20, 100, 200, BLUE);
		break;
	}
	FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC48"));
	char numbuf[128];
	sprintf(numbuf, "%ld   ", (s32)GetWindowProp(Win, "EncVal"));
	DrawStringHorizontal(DrawingDC, FG, numbuf, 0, 0, 0, 0, BLACK, WHITE);
	FreeAndEraseReference(FG);
	FreeAndEraseReference(DrawingDC);
	return false;
}

bool MYEVENT::OnEncoder(WINDOW * Win, u8 EncoderIndex, s32 Val)
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
