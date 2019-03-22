#pragma once

#include "Kernel\GUI\GUICommon.h"
#include "Kernel\GUI\Window\Window.h"

void BringToTop(WINDOW* Win);
void BringToTopOf(WINDOW* Win, WINDOW* WinBefore);
void SetWindowProp(WINDOW * Win, pcstr Key, u32 Data);
u32 GetWindowProp(WINDOW * Win, pcstr Key);
void RemoveWindowProp(WINDOW * Win, pcstr Key);
