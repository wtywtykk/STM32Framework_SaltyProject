#include "Kernel\GUI\GUICommon.h"
#include "Kernel\Common\KObject.h"
#include "Kernel\GUI\DC\DC.h"

void DrawCircle(DC* dc, GUIPOS X0, GUIPOS Y0, GUIPOS Radius, PIXEL Color)
{
	//Midpoint circle algorithm
	//ÖÐµãÔ²Ëã·¨
	//https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
	GUIPOS X = Radius;
	GUIPOS Y = 0;
	GUIPOS err = 0;

	while (X >= Y)
	{
		dc->SetPixel(X0 + X, Y0 + Y, Color);
		dc->SetPixel(X0 + Y, Y0 + X, Color);
		dc->SetPixel(X0 - Y, Y0 + X, Color);
		dc->SetPixel(X0 - X, Y0 + Y, Color);
		dc->SetPixel(X0 - X, Y0 - Y, Color);
		dc->SetPixel(X0 - Y, Y0 - X, Color);
		dc->SetPixel(X0 + Y, Y0 - X, Color);
		dc->SetPixel(X0 + X, Y0 - Y, Color);

		if (err <= 0)
		{
			Y += 1;
			err += 2 * Y + 1;
		}
		if (err > 0)
		{
			X -= 1;
			err -= 2 * X + 1;
		}
	}
}