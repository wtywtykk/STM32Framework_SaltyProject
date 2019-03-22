#pragma once

#include "Kernel\GUI\GUICommon.h"
#include "Kernel\Common\KObject.h"
#include "Kernel\GUI\DC\DC.h"

class LCDDC :public DC
{
private:
	enum LCDDCReadWriteState
	{
		Reading,
		Writing,
		Unknown
	}LCDState;
public:
	static STATUS InitLCDDC(void);
	LCDDC(void);
	virtual ~LCDDC(void);
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

extern DC* g_LCDDC;
