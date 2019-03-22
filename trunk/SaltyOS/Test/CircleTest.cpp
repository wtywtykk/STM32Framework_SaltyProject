#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Shape\Circle.h"
#include <stdlib.h>
#include <math.h>

void CircleTest(void)
{
	static struct
	{
		float XSpeed;
		float YSpeed;
		float X;
		float Y;
	}CirSta[30] = { 0 };
	u16 Width = g_LCDDC->GetWidth();
	u16 Height = g_LCDDC->GetHeight();
	//g_LCDDC->Fill(0, 0, Width, Height, BLACK);
	for (u16 i = 0; i < 30; i++)
	{
		DrawCircle(g_LCDDC, CirSta[i].X, CirSta[i].Y, 30, BLACK);
		if (CirSta[i].X < 0 || CirSta[i].X > Width || CirSta[i].Y < 0 || CirSta[i].Y > Height || fabs(CirSta[i].XSpeed) < 1 || fabs(CirSta[i].YSpeed) < 1)
		{
			if (rand() > RAND_MAX / 2)
			{
				CirSta[i].X = 0;
				CirSta[i].Y = (float)rand() * Height / RAND_MAX;
				CirSta[i].XSpeed = rand() * 40.0 / RAND_MAX + 10.0;
				CirSta[i].YSpeed = rand() * 30.0 / RAND_MAX - 15.0;
			}
			else
			{
				CirSta[i].X = Width;
				CirSta[i].Y = (float)rand() * Height / RAND_MAX;
				CirSta[i].XSpeed = -rand() * 40.0 / RAND_MAX - 10.0;
				CirSta[i].YSpeed = rand() * 30.0 / RAND_MAX - 15.0;
			}
		}
		CirSta[i].X += CirSta[i].XSpeed;
		CirSta[i].Y += CirSta[i].YSpeed;
		CirSta[i].YSpeed += 5;
		DrawCircle(g_LCDDC, CirSta[i].X, CirSta[i].Y, 30, GREEN);
	}
}
