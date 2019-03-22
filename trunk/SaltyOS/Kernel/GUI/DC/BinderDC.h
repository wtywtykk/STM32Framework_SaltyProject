#pragma once

#include "Kernel\GUI\GUICommon.h"
#include "Kernel\Common\KObject.h"
#include "Kernel\GUI\DC\DC.h"

class BINDERDC :public DC
{
	DC* m_DC1;
	DC* m_DC2;
public:
	BINDERDC(DC* DC1, DC* DC2);
	virtual ~BINDERDC(void);
	virtual void Fill(GUIPOS X1, GUIPOS Y1, GUIPOS X2, GUIPOS Y2, PIXEL Color);
	virtual void SetPos(GUIPOS X, GUIPOS Y);
	virtual void SequenceWrite(PIXEL Color);
	virtual void SetPixel(GUIPOS X, GUIPOS Y, PIXEL Color);
	virtual PIXEL GetPixel(GUIPOS X, GUIPOS Y);
	virtual PIXEL SequenceRead(void);
	virtual GUIPOS GetWidth(void);
	virtual GUIPOS GetHeight(void);
	virtual bool SupportNativeClip(void);
	virtual void StartNativeClip(GUIPOS X1, GUIPOS Y1, GUIPOS X2, GUIPOS Y2);
	virtual void EndNativeClip(void);
	virtual void BlockWrite(const PIXEL* Data, u32 Length);
};
