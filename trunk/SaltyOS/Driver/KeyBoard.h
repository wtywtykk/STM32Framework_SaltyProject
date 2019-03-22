#pragma once

C_HEADER_BEGIN

STATUS KeyBoard_Init(void);
u8 KeyBoard_GetKey_Single(void);
u8 KeyBoard_GetKey_Repeat(void);
s32 KeyBoard_GetEncoderVal(u8 Index);

C_HEADER_END
