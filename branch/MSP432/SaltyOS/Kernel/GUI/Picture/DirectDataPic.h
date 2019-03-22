#pragma once

#include "Kernel\GUI\GUICommon.h"
#include "Kernel\GUI\Picture\Picture.h"
#include "Kernel\GUI\DC\DC.h"

class DIRECTDATAPIC :public PICTURE
{
	const PIXEL* Data;
public:
	DIRECTDATAPIC(GUIPOS PicWidth, GUIPOS PicHeight, const PIXEL* PicData);
	virtual ~DIRECTDATAPIC(void);
	virtual void Draw(DC* dc, GUIPOS X, GUIPOS Y);
	virtual PIXEL GetPixel(GUIPOS X, GUIPOS Y);
private:
	bool CheckCoord(GUIPOS X, GUIPOS Y);
	void DrawWithNativeClip(DC* dc, GUIPOS X, GUIPOS Y);
	void DrawWithoutNativeClip(DC* dc, GUIPOS X, GUIPOS Y);
	void DrawWithNegativeCoord(DC* dc, GUIPOS X, GUIPOS Y);
};
