#pragma once

#include "Kernel\GUI\GUICommon.h"
#include "Kernel\Common\KObject.h"

class DC :public KOBJECT
{
public:
	virtual ~DC(void);
	virtual void Fill(GUIPOS X1, GUIPOS Y1, GUIPOS X2, GUIPOS Y2, PIXEL Color) = 0;
	virtual void SetPos(GUIPOS X, GUIPOS Y) = 0;
	virtual void SequenceWrite(PIXEL Color) = 0;
	virtual void SetPixel(GUIPOS X, GUIPOS Y, PIXEL Color) = 0;
	virtual PIXEL GetPixel(GUIPOS X, GUIPOS Y) = 0;
	virtual PIXEL SequenceRead(void) = 0;
	virtual GUIPOS GetWidth(void) = 0;
	virtual GUIPOS GetHeight(void) = 0;
	virtual bool SupportNativeClip(void) = 0;
	virtual void StartNativeClip(GUIPOS X1, GUIPOS Y1, GUIPOS X2, GUIPOS Y2) = 0;
	virtual void EndNativeClip(void) = 0;
	virtual void BlockWrite(const PIXEL* Data, u32 Length) = 0;
};
