#pragma once

#include "FontGroup.h"

u32 GetStartAddress(const FONTINDEX* Index);
u32 GetEndAddress(const FONTINDEX* Index);
u32 GetAddressingOffset(const FONTINDEX* Index, u16 Char);
