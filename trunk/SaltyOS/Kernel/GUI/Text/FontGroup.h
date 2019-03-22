#pragma once

#include "Kernel\Common\KCommon.h"
#include "Kernel\Common\KObject.h"
#include "FontProvider.h"

class FONTGROUP :public KOBJECT
{
private:
	u8 FontCount;
	const FONTINDEX** Index;
public:
	FONTGROUP(pcstr FontList);
	~FONTGROUP();
	const FONTINDEX* GetFontIndex(u16 Char);
private:
	u8 GetFontListCount(pcstr FontList);
	pcstr GetNextNameFromList(pcstr FontList, char Buffer[8]);
	void FillIndexFromList(pcstr FontList);
	bool CheckAscRangeOverlap(void);
};
