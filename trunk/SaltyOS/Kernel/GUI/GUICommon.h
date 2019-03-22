#pragma once

#include "Kernel\Common\KCommon.h"

typedef u16 PIXEL;
typedef s16 GUIPOS;

const PIXEL BLACK = 0x0000;   // 黑色：    0,   0,   0
const PIXEL BLUE = 0x001F;    // 蓝色：    0,   0, 255
const PIXEL GREEN = 0x07E0;   // 绿色：    0, 255,   0
const PIXEL CYAN = 0x07FF;    // 青色：    0, 255, 255
const PIXEL RED = 0xF800;     // 红色：  255,   0,   0
const PIXEL MAGENTA = 0xF81F; // 品红：  255,   0, 255
const PIXEL YELLOW = 0xFFE0;  // 黄色：  255, 255, 0
const PIXEL WHITE = 0xFFFF;   // 白色：  255, 255, 255
const PIXEL NAVY = 0x000F;    // 深蓝色：  0,   0, 128
const PIXEL DGREEN = 0x03E0;  // 深绿色：  0, 128,   0
const PIXEL DCYAN = 0x03EF;   // 深青色：  0, 128, 128
const PIXEL MAROON = 0x7800;  // 深红色：128,   0,   0
const PIXEL PURPLE = 0x780F;  // 紫色：  128,   0, 128
const PIXEL OLIVE = 0x7BE0;   // 橄榄绿：128, 128,   0
const PIXEL LGRAY = 0xC618;   // 灰白色：192, 192, 192
const PIXEL DGRAY = 0x7BEF;   // 深灰色：128, 128, 128

const PIXEL TransparentColorKey = 0x0001;