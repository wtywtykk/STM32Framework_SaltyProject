#pragma once

#include "Kernel\Common\KCommon.h"

typedef u16 PIXEL;
typedef s16 GUIPOS;

const PIXEL BLACK = 0x0000;   // ��ɫ��    0,   0,   0
const PIXEL BLUE = 0x001F;    // ��ɫ��    0,   0, 255
const PIXEL GREEN = 0x07E0;   // ��ɫ��    0, 255,   0
const PIXEL CYAN = 0x07FF;    // ��ɫ��    0, 255, 255
const PIXEL RED = 0xF800;     // ��ɫ��  255,   0,   0
const PIXEL MAGENTA = 0xF81F; // Ʒ�죺  255,   0, 255
const PIXEL YELLOW = 0xFFE0;  // ��ɫ��  255, 255, 0
const PIXEL WHITE = 0xFFFF;   // ��ɫ��  255, 255, 255
const PIXEL NAVY = 0x000F;    // ����ɫ��  0,   0, 128
const PIXEL DGREEN = 0x03E0;  // ����ɫ��  0, 128,   0
const PIXEL DCYAN = 0x03EF;   // ����ɫ��  0, 128, 128
const PIXEL MAROON = 0x7800;  // ���ɫ��128,   0,   0
const PIXEL PURPLE = 0x780F;  // ��ɫ��  128,   0, 128
const PIXEL OLIVE = 0x7BE0;   // ����̣�128, 128,   0
const PIXEL LGRAY = 0xC618;   // �Ұ�ɫ��192, 192, 192
const PIXEL DGRAY = 0x7BEF;   // ���ɫ��128, 128, 128

const PIXEL TransparentColorKey = 0x0001;