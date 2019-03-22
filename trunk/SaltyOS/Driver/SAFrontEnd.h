#pragma once

C_HEADER_BEGIN

STATUS SAFrontEnd_Init(void);
void SAFrontEnd_EnableLNA1(bool En);
void SAFrontEnd_EnableLNA2(bool En);
void SAFrontEnd_SetDSA(float Att);

C_HEADER_END
