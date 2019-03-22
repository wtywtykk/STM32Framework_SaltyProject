#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Shape\Line.h"
#include <math.h>

void LineTest(void)
{
	static u16 i = 0;
	DrawLine(g_LCDDC, cos(i * 2 * 3.14 / 3600) * 150 + 200, sin(i * 2 * 3.14 / 3600) * 150 + 200, -cos(i * 2 * 3.14 / 3600) * 50 + 200, -sin(i * 2 * 3.14 / 3600) * 50 + 200, BLACK);
	DrawLine(g_LCDDC, cos(i * 2 * 3.14 / 3600 + 1) * 150 + 200, sin(i * 2 * 3.14 / 3600 + 1) * 150 + 200, -cos(i * 2 * 3.14 / 3600 + 1) * 50 + 200, -sin(i * 2 * 3.14 / 3600 + 1) * 50 + 200, BLACK);
	i++;
	if (i == 3600)
	{
		i = 0;
	}
	DrawLine(g_LCDDC, cos(i * 2 * 3.14 / 3600) * 150 + 200, sin(i * 2 * 3.14 / 3600) * 150 + 200, -cos(i * 2 * 3.14 / 3600) * 50 + 200, -sin(i * 2 * 3.14 / 3600) * 50 + 200, RED);
	DrawLine(g_LCDDC, cos(i * 2 * 3.14 / 3600 + 1) * 150 + 200, sin(i * 2 * 3.14 / 3600 + 1) * 150 + 200, -cos(i * 2 * 3.14 / 3600 + 1) * 50 + 200, -sin(i * 2 * 3.14 / 3600 + 1) * 50 + 200, GREEN);
}
