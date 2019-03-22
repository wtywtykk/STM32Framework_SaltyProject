#include "HAL\HCommon.h"
#include "HAL\PeripheralBus.h"

#define AD7671_NCMASK (1<<1)//AB for muti channel chips
#define AD7671_SPMASK (1<<2)
#define AD7671_IMPMASK (1<<3)
#define AD7671_WARPMASK (1<<4)
#define AD7671_PDMASK (1<<5)
#define AD7671_OB2CMASK (1<<6)
#define AD7671_AUTOMODEMASK (1<<7)

#define AD7671_BUSYMASK (1<<0)

#define AD7671_Address (2)
#define AD7671_DivideFactorAddress (3)
#define AD7671_StatusAddress (3)

static bool AD7671_Initialized = false;
static u16 AD7671_ControlBits = 0;

static void AD7671_UpdateControlBits(void);

STATUS AD7671_Init(void)
{
	if (AD7671_Initialized)
	{
		return S_OK;
	}

	AD7671_UpdateControlBits();

	AD7671_Initialized = true;

	return S_OK;
}

void AD7671_Standby(void)
{
	AD7671_ControlBits |= AD7671_PDMASK;
	AD7671_UpdateControlBits();
}

void AD7671_Wakeup(void)
{
	AD7671_ControlBits &= ~AD7671_PDMASK;
	AD7671_UpdateControlBits();
}

void AD7671_SetImpulseMode(void)
{
	AD7671_ControlBits &= ~AD7671_WARPMASK;
	AD7671_ControlBits |= AD7671_IMPMASK;
	AD7671_UpdateControlBits();
}

void AD7671_SetWarpMode(void)
{
	AD7671_ControlBits &= ~AD7671_IMPMASK;
	AD7671_ControlBits |= AD7671_WARPMASK;
	AD7671_UpdateControlBits();
}

void AD7671_SetNormalMode(void)
{
	AD7671_ControlBits &= ~AD7671_IMPMASK;
	AD7671_ControlBits &= ~AD7671_WARPMASK;
	AD7671_UpdateControlBits();
}

void AD7671_SetParallel(void)
{
	AD7671_ControlBits &= ~AD7671_SPMASK;
	AD7671_UpdateControlBits();
}

void AD7671_SetFormatBinary(void)
{
	AD7671_ControlBits |= AD7671_OB2CMASK;
	AD7671_UpdateControlBits();
}

void AD7671_SetFormatTwosComp(void)
{
	AD7671_ControlBits &= ~AD7671_OB2CMASK;
	AD7671_UpdateControlBits();
}

void AD7671_SetSampleDivideFactor(u16 DivideFactor)
{
	PeripheralBus_Write(AD7671_DivideFactorAddress, DivideFactor);
}

u16 AD7671_GetBnaryResult(void)
{
	u16 i = 0;
	while ((PeripheralBus_Read(AD7671_StatusAddress) & AD7671_BUSYMASK) && i++ < 40000);
	return PeripheralBus_Read(AD7671_Address);
}

s16 AD7671_GetTwosCompResult(void)
{
	u16 i = 0;
	while ((PeripheralBus_Read(AD7671_StatusAddress) & AD7671_BUSYMASK) && i++ < 40000);
	return PeripheralBus_Read(AD7671_Address);
}

STATUS AD7671_SetAutoMode(void)
{
	AD7671_ControlBits |= AD7671_AUTOMODEMASK;
	AD7671_UpdateControlBits();
	return S_OK;
}

STATUS AD7671_SetClockedMode(void)
{
	AD7671_ControlBits &= ~AD7671_AUTOMODEMASK;
	AD7671_UpdateControlBits();
	return S_OK;
}

STATUS AD7671_SetClkDiv(u16 Factor)
{
	assert(Factor <= 1023);
	PeripheralBus_Write(AD7671_DivideFactorAddress, Factor);
	return S_OK;
}

STATUS AD7671_StartDMA()
{
	assert(AD7671_ControlBits & AD7671_AUTOMODEMASK);
	assert(false);
	return S_OK;
}

static void AD7671_UpdateControlBits(void)
{
	PeripheralBus_Write(AD7671_Address, AD7671_ControlBits);
}
