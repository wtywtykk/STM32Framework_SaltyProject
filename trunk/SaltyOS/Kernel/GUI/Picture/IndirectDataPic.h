#pragma once

#include "Kernel\GUI\GUICommon.h"
#include "Kernel\GUI\Picture\Picture.h"
#include "Kernel\GUI\DC\DC.h"

#define IndirectPicBufferLength 1024

class INDIRECTDATAPIC :public PICTURE
{
public:
	virtual void Draw(DC* dc, GUIPOS X, GUIPOS Y);
	virtual PIXEL GetPixel(GUIPOS X, GUIPOS Y);
private:
	bool CheckCoord(GUIPOS X, GUIPOS Y);
	virtual STATUS GetPixels(u32 PixelAddr, PIXEL* Buffer, u32 PixelCount) = 0;
};
