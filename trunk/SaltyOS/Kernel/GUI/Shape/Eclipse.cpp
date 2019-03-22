#include "Kernel\GUI\GUICommon.h"
#include "Kernel\Common\KObject.h"
#include "Kernel\GUI\DC\DC.h"

inline void DrawEclipsePoints(DC* dc, GUIPOS X0, GUIPOS Y0, GUIPOS dX, GUIPOS dY, PIXEL Color)
{
	dc->SetPixel(X0 + dX, Y0 + dY, Color);
	dc->SetPixel(X0 - dX, Y0 + dY, Color);
	dc->SetPixel(X0 + dX, Y0 - dY, Color);
	dc->SetPixel(X0 - dX, Y0 - dY, Color);
}

void DrawEclipse(DC* dc, GUIPOS X0, GUIPOS Y0, GUIPOS RadiusX, GUIPOS RadiusY, PIXEL Color)
{
	//Midpoint circle algorithm
	//中点圆算法
	//计算机图形学(第三版）P93
	//BUG: 实际画图会比预期宽/高1像素
	if (RadiusX == 0 || RadiusY == 0)
	{
		return;
	}
	s32 RadXSqr = RadiusX * RadiusX;
	s32 RadYSqr = RadiusY * RadiusY;
	s32 RadXSqr2 = RadXSqr * 2;
	s32 RadYSqr2 = RadYSqr * 2;
	s32 err;
	GUIPOS X = 0;
	GUIPOS Y = RadiusY;
	s32 pX = 0;
	s32 pY = RadXSqr2 * Y;
	err = RadYSqr - RadXSqr * RadiusY + RadXSqr / 4;
	while (pX < pY)
	{
		DrawEclipsePoints(dc, X0, Y0, X, Y, Color);
		X++;
		pX += RadYSqr2;
		if (err < 0)
		{
			err += RadYSqr + pX;
		}
		else
		{
			Y--;
			pY -= RadXSqr2;
			err += RadYSqr + pX - pY;
		}
	}
	err = RadYSqr * (X * X + X) + RadXSqr * (Y - 1) * (Y - 1) - RadXSqr * RadYSqr;
	while (Y >= 0)
	{
		DrawEclipsePoints(dc, X0, Y0, X, Y, Color);
		Y--;
		pY -= RadXSqr2;
		if (err > 0)
		{
			err += RadXSqr - pY;
		}
		else
		{
			X++;
			pX += RadYSqr2;
			err += RadXSqr - pY + pX;
		}
	}
}
