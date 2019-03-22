#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\DC\ClippedDC.h"
#include "Kernel\GUI\Shape\Line.h"
#include <math.h>

//************
//* 3D Wave  *
//*By LHF.LAB*
//************

#define W 20
#define H 20
#define speed 2.0
#define A 0.1
#define Length 2.0

typedef struct
{
	float x;
	float y;
	float z;
}VERTEX;

typedef struct
{
	VERTEX b;
	VERTEX e;
}Lines;

VERTEX p[W + 1][H + 1];
VERTEX v, s;
float n;
float x1, z1;
float d;
u16 WindowWidth;
u16 WindowHeight;

static void DrawLine3D(Lines &L, VERTEX &v, VERTEX &s, PIXEL Color);
static VERTEX SetPos(VERTEX &v, VERTEX &s, VERTEX &p);
static VERTEX ScreenRemap(VERTEX &v);

CLIPPEDDC* cdc;

void WaveInit(void)
{
	v.z = 3;
	v.y = -0.1;
	s.z = 1;
	cdc = NewReferenceSafe(new_noexcpt CLIPPEDDC(g_LCDDC, 0, 0, g_LCDDC->GetWidth() / 1, g_LCDDC->GetHeight() / 1, true, true));
	WindowWidth = cdc->GetWidth();
	WindowHeight = cdc->GetHeight();
}

void WaveRender(void)
{
	static bool Initialized = false;
	if (!Initialized)
	{
		Initialized = true;
		WaveInit();
	}

	cdc->Fill(0, 0, WindowWidth, WindowHeight, BLACK);

	v.y = -1.7 - sinf(n / 10) / 2;
	s.z = 9 - sinf(n / 10) * 5;

	n = n + 0.1;

	float sinn = sinf(n / 10 * 3.14);
	float cosn = cosf(n / 10 * 3.14);
	for (u16 x = 0; x <= W; x++)
	{
		for (u16 y = 0; y <= H; y++)
		{
			//描点
			d = sqrtf((x - W / 2) * (x - W / 2) + (y - H / 2) * (y - H / 2));
			p[x][y].x = (float)x / W - 0.5;
			p[x][y].y = -1 + sinf((d - n * speed) / Length) * A;
			p[x][y].z = (float)y / H - 0.5;

			//视角变换
			x1 = sinn * p[x][y].x + cosn * p[x][y].z;
			z1 = cosn * p[x][y].x - sinn * p[x][y].z;
			p[x][y].x = x1;
			p[x][y].z = z1;
		}
	}

	//画线
	for (u16 x = 0; x < W; x++)
	{
		for (u16 y = 0; y < H; y++)
		{
			Lines L;
			L.b = p[x][y];
			L.e = p[x + 1][y];
			DrawLine3D(L, v, s, RED);
			L.b = p[x][y];
			L.e = p[x][y + 1];
			DrawLine3D(L, v, s, RED);
		}
	}
	cdc->Update();
}

//此函数在三维空间中做线
static void DrawLine3D(Lines &L, VERTEX &v, VERTEX &s, PIXEL Color)
{
	VERTEX b, e;
	VERTEX sb, se;
	b = SetPos(v, s, L.b);
	e = SetPos(v, s, L.e);
	sb = ScreenRemap(b);
	se = ScreenRemap(e);
	DrawLine(cdc, sb.x, sb.y, se.x, se.y, Color);
}

//此函数投影三维坐标系中的点P到平面中
//v：观察者的三维坐标 s：屏幕位置（平行于xoy平面，只对z值有效）
static VERTEX SetPos(VERTEX &v, VERTEX &s, VERTEX &p)
{
	VERTEX Ret;
	Ret.x = (p.x - v.x) / (p.z + v.z) * (v.z - s.z);
	Ret.y = -(p.y - v.y) / (p.z + v.z) * (v.z - s.z);
	return Ret;
}

static VERTEX ScreenRemap(VERTEX &v)
{
	VERTEX Ret;
	Ret.x = (v.x + 1) / 2 * WindowWidth;
	Ret.y = (v.y) / 2 * WindowHeight;
	return Ret;
}
