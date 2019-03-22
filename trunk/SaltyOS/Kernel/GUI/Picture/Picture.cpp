#include "Kernel\GUI\GUICommon.h"
#include "Kernel\GUI\Picture\Picture.h"

PICTURE::~PICTURE(void)
{
}

GUIPOS PICTURE::GetWidth(void)
{
	return Width;
}

GUIPOS PICTURE::GetHeight(void)
{
	return Height;
}
