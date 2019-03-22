#pragma once

#include "Kernel\GUI\GUICommon.h"
#include "Kernel\Common\KObject.h"
#include "Kernel\GUI\DC\DC.h"

class CLIPPEDDC :public DC
{
	DC* ParentDC;
	GUIPOS SourceX;
	GUIPOS SourceY;
	GUIPOS Width;
	GUIPOS Height;
	GUIPOS CurrentX;
	GUIPOS CurrentY;
	PIXEL* Buffer;
	bool FullyTransparent;
public:
	CLIPPEDDC(DC * dc, GUIPOS X1, GUIPOS Y1, GUIPOS X2, GUIPOS Y2, bool BufferIfPossible, bool InitWithOrigContent);
	virtual ~CLIPPEDDC(void);
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
	void Update(void);
	bool IsActuallyBuffered(void);
private:
	void AddressIncreasement(void);
	bool CheckCoord(GUIPOS X, GUIPOS Y);
	void CopySource(void);
	void CopySourceWithNativeClip(void);
	void CopySourceWithoutNativeClip(void);
	void CopySourceWithNegativeCoord(void);
	void UpdateWithNativeClip(void);
	void UpdateWithoutNativeClip(void);
	void UpdateWithNegativeCoord(void);
};
