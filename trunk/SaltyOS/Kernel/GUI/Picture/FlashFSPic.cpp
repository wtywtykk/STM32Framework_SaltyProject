#include "Kernel\GUI\GUICommon.h"
#include "Kernel\GUI\DC\DC.h"
#include "Kernel\FlashFS\FlashFS.h"
#include "Kernel\GUI\Picture\FlashFSPic.h"
#include <assert.h>
#include <malloc.h>
#include <string.h>

FLASHFSPIC::FLASHFSPIC(pcstr PicFileName)
{
	GUIPOS PicSize[2];
	assert(PicFileName != NULL);
	FileName = (pstr)malloc(sizeof(char) * strlen(PicFileName));
	strcpy(FileName, PicFileName);
	if (FlashFS_Read(FileName, PicSize, 0, sizeof(PicSize), NULL) != S_OK)
	{
		free(FileName);
		FileName = NULL;
		Width = 0;
		Height = 0;
	}
	else
	{
		Width = PicSize[0];
		Height = PicSize[1];
	}
}

FLASHFSPIC::~FLASHFSPIC(void)
{
	free(FileName);
}

STATUS FLASHFSPIC::GetPixels(u32 PixelAddr, PIXEL * Buffer, u32 PixelCount)
{
	return FlashFS_Read(FileName, Buffer, sizeof(GUIPOS) * 2 + sizeof(PIXEL) * PixelAddr, sizeof(PIXEL) * PixelCount, NULL);
}
