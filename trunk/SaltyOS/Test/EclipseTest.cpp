#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Shape\Eclipse.h"

void EclipseTest(void)
{
	u16 Width = g_LCDDC->GetWidth();
	u16 Height = g_LCDDC->GetHeight();

	u16 sum = 200;
	static u16 cnt = 0;
	static bool Dir = true;
	u16 CenterX = Width / 2;
	u16 CenterY = Height / 2;
	if (Dir)
	{
		cnt++;
		if (cnt == sum)
		{
			Dir = false;
		}
	}
	else
	{
		cnt--;
		if (cnt == 0)
		{
			Dir = true;
		}
	}
	g_LCDDC->Fill(CenterX - sum, CenterY - sum, CenterX + sum, CenterY + sum, BLACK);
	g_LCDDC->Fill(CenterX - cnt, CenterY - (sum - cnt), CenterX + cnt, CenterY + (sum - cnt), DGRAY);
	DrawEclipse(g_LCDDC, CenterX, CenterY, cnt, sum - cnt, RED);
}
