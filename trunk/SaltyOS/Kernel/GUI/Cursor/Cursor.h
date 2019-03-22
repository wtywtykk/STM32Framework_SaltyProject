#pragma once

#include "Kernel\Common\KObject.h"
#include "Kernel\GUI\Window\Window.h"

class CURSOR :public KOBJECT
{
	s16 X;
	s16 Y;
public:
	CURSOR();
	~CURSOR();
	void Capture(Window* Win);
	void Release(void);
};