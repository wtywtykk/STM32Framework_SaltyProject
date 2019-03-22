#include "Kernel\GUI\GUICommon.h"
#include "Kernel\Common\KObject.h"
#include "Kernel\GUI\DC\DC.h"

void DrawLine(DC* dc, GUIPOS X1, GUIPOS Y1, GUIPOS X2, GUIPOS Y2, PIXEL Color)
{
	//来自原子代码，不知道是什么算法。。。
	GUIPOS xerr = 0, yerr = 0, delta_x, delta_y, distance;
	GUIPOS incx, incy, uRow, uCol;
	delta_x = X2 - X1; //计算坐标增量
	delta_y = Y2 - Y1;
	uRow = X1;
	uCol = Y1;
	if (delta_x > 0)
	{
		incx = 1; //设置单步方向
	}
	else if (delta_x == 0)
	{
		incx = 0;//垂直线
	}
	else
	{
		incx = -1;
		delta_x = -delta_x;
	}
	if (delta_y > 0)
	{
		incy = 1;
	}
	else if (delta_y == 0)
	{
		incy = 0;//水平线
	}
	else
	{
		incy = -1;
		delta_y = -delta_y;
	}
	if (delta_x > delta_y)
	{
		distance = delta_x; //选取基本增量坐标轴
	}
	else
	{
		distance = delta_y;
	}
	for (u16 i = 0; i <= distance + 1; i++)//画线输出
	{
		dc->SetPixel(uRow, uCol, Color);
		xerr += delta_x;
		yerr += delta_y;
		if (xerr > distance)
		{
			xerr -= distance;
			uRow += incx;
		}
		if (yerr > distance)
		{
			yerr -= distance;
			uCol += incy;
		}
	}
}