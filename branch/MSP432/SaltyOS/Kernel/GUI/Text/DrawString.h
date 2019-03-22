#pragma once

#include "Kernel\GUI\DC\DC.h"
#include "Kernel\GUI\Text\FontGroup.h"

void DrawStringHorizontal(DC* dc, FONTGROUP* Group, pcstr String, GUIPOS X, GUIPOS Y, GUIPOS Width, GUIPOS Height, PIXEL ForeColor, PIXEL BackColor);
void DrawStringVertical(DC* dc, FONTGROUP* Group, pcstr String, GUIPOS X, GUIPOS Y, GUIPOS Width, GUIPOS Height, PIXEL ForeColor, PIXEL BackColor);
