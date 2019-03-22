#pragma once

#include "Kernel\GUI\GUICommon.h"
#include "Kernel\GUI\Picture\IndirectDataPic.h"
#include "Kernel\GUI\DC\DC.h"

#define IndirectPicBufferLength 1024

class FLASHFSPIC :public INDIRECTDATAPIC
{
	pstr FileName = NULL;
public:
	FLASHFSPIC(pcstr PicFileName);
	~FLASHFSPIC(void);
private:
	virtual STATUS GetPixels(u32 PixelAddr, PIXEL* Buffer, u32 PixelCount);
};
