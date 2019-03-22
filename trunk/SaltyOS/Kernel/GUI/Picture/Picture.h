#pragma once

#include "Kernel\GUI\GUICommon.h"
#include "Kernel\Common\KObject.h"
#include "Kernel\GUI\DC\DC.h"

class PICTURE :public KOBJECT
{
protected:
	GUIPOS Width;
	GUIPOS Height;
public:
	virtual ~PICTURE(void);
	virtual void Draw(DC* dc, GUIPOS X, GUIPOS Y) = 0;
	virtual PIXEL GetPixel(GUIPOS X, GUIPOS Y) = 0;
	virtual GUIPOS GetWidth(void);
	virtual GUIPOS GetHeight(void);
};
