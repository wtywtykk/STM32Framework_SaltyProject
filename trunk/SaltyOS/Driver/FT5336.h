#pragma once

C_HEADER_BEGIN

typedef enum
{
	EventMode,
	QueryMode,
}TouchUpdateMode;

typedef struct
{
	u16 X;
	u16 Y;
	u8 TouchID;
	u8 EventFlag;
	u8 Weight;
	u8 Area;
}TouchRawData;

STATUS Touch_Init(void);
STATUS Touch_Read(void);

C_HEADER_END
