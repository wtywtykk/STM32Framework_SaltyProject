#include "Kernel\Common\KCommon.h"
#include "Driver\KeyBoard.h"
#include "Kernel\Input\KeyBoardMap.h"
#include "Kernel\GUI\Window\ScreenWindow.h"

void CheckInput(void)
{
	WINDOW* ScreenWin = SCREENWINDOW::GetScreenWindow();
	KEYCODE KeyCode = KeyBoardMap_GetKey();
	if (KeyCode != KEY_Invalid)
	{
		PostMessage(ScreenWin, WM_KEYPRESS, KeyCode, 0);
	}

	for (u8 i = 0; i < 2; i++)
	{
		s32 EncoderVal = KeyBoard_GetEncoderVal(i);
		{
			if (EncoderVal != 0)
			{
				PostMessage(ScreenWin, WM_ENCODER, i, EncoderVal);
			}
		}
	}
	FreeAndEraseReference(ScreenWin);
}
