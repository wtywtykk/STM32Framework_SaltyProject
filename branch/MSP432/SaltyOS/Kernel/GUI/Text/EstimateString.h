#pragma once

#include "Kernel\GUI\DC\DC.h"
#include "Kernel\GUI\Text\FontGroup.h"

void EstimateStringHorizontal(DC* dc, FONTGROUP* Group, pcstr String, GUIPOS X, GUIPOS Y, GUIPOS Width, GUIPOS Height, GUIPOS* EstimatedWidth, GUIPOS* EstimatedHeight);
void EstimateStringVertical(DC* dc, FONTGROUP* Group, pcstr String, GUIPOS X, GUIPOS Y, GUIPOS Width, GUIPOS Height, GUIPOS* EstimatedWidth, GUIPOS* EstimatedHeight);
