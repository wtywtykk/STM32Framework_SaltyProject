#pragma once

#include "HAL\UniGPIO.h"

C_HEADER_BEGIN

void StandardSPIPort_Init(u8 PortNum, UniGPIO_Handle* MISOPin, UniGPIO_Handle* MOSIPin, UniGPIO_Handle* SCKPin, UniGPIO_Handle* CSPin, UniGPIO_Handle* SIG0, UniGPIO_Handle* SIG1, UniGPIO_Handle* SIG2, UniGPIO_Handle* SIG3, UniGPIO_Handle* SIG4);

C_HEADER_END
