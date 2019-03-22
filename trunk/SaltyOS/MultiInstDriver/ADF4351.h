#pragma once

#include "HAL\UniGPIO.h"
#include "HAL\UniSPI.h"

C_HEADER_BEGIN

#define ADF4351_RegCount 6

typedef struct
{
	UniGPIO_Handle LE;
	UniGPIO_Handle CE;
	UniGPIO_Handle LD;
	UniGPIO_Handle PDBRF;
	UniGPIO_Handle MuxOut;
	UniSPI_Handle SPI_Handle;
	u32 Regs[ADF4351_RegCount];
	float Rset;//In KOhm. Must be set whatever READ or WRITE
}ADF4351_Handle;

typedef enum
{
	Prescaler45 = 0x0,
	Prescaler89 = 0x1,
}ADF4351_Prescaler_Val;

typedef enum
{
	LowNoiseMode = 0x0,
	LowSpurMode = 0x3,
}ADF4351_LowNoiseSpurMode_Val;

typedef enum
{
	ThreeState = 0x0,
	DVDD = 0x1,
	DGND = 0x2,
	RCntOut = 0x3,
	NCntOut = 0x4,
	AnalogLockDetect = 0x5,
	DigitalLockDetect = 0x6,
}ADF4351_MuxOut_Val;

typedef enum
{
	Cyc40_FRAC_N = 0x0,
	Cyc5_INT_N = 0x1,
}ADF4351_LDF_Val;

typedef enum
{
	ABP_6ns_FRAC_N = 0x0,
	ABP_3ns_INT_N = 0x1,
}ADF4351_ABP_Val;

typedef enum
{
	ClkDivOff = 0x0,
	FastLockEnable = 0x1,
	ReSyncEnable = 0x2,
}ADF4351_ClkDivMode_Val;

typedef enum
{
	FeedBack_Divided = 0x0,
	FeedBack_Fundamental = 0x1,
}ADF4351_FeedBackSelect_Val;

typedef enum
{
	AuxOut_Divided = 0x0,
	AuxOut_Fundamental = 0x1,
}ADF4351_AuxOutputSelect_Val;

typedef enum
{
	Neg4 = 0x0,
	Neg1 = 0x1,
	Pos2 = 0x2,
	Pos5 = 0x3,
}ADF4351_OutputPower_Val;

typedef struct
{
	bool Doubler;
	bool Div2;
	u16 R;
}ADF4351_Reference_Param;

typedef struct
{
	ADF4351_Prescaler_Val Perscaler;
	ADF4351_LowNoiseSpurMode_Val LowNoiseSpur;
	bool MuteTillLockDetect;
}ADF4351_Misc_Param;

typedef struct
{
	float Current;//In mA
	bool Polarity;
	bool TriState;
	bool BandSelect;
	ADF4351_ABP_Val AntibacklashPulseWidth;
	bool ChargeCancelation;
	bool CSREnable;
	ADF4351_ClkDivMode_Val ClkDividerMode;
	u16 ClockDivider;
	ADF4351_FeedBackSelect_Val FeedBackSelect;
}ADF4351_PFD_ChargePump_Param;

typedef struct
{
	u8 BandSelectClockDivider;
	bool PowerDown;
}ADF4351_VCO_Param;

STATUS ADF4351_Init(ADF4351_Handle* Handle, float ExtRset, UniGPIO_Handle* MOSIPin, UniGPIO_Handle* SCKPin, UniGPIO_Handle* LEPin, UniGPIO_Handle* CEPin, UniGPIO_Handle* LDPin, UniGPIO_Handle* PDBRFPin, UniGPIO_Handle* MuxOutPin);
void ADF4351_SetReferenceParam(ADF4351_Handle* Handle, ADF4351_Reference_Param* Val);
void ADF4351_GetReferenceParam(ADF4351_Handle* Handle, ADF4351_Reference_Param* Val);
void ADF4351_SetPFD_ChargePumpParam(ADF4351_Handle* Handle, ADF4351_PFD_ChargePump_Param* Val);
void ADF4351_GetPFD_ChargePumpParam(ADF4351_Handle* Handle, ADF4351_PFD_ChargePump_Param* Val);
void ADF4351_SetVCOParam(ADF4351_Handle* Handle, ADF4351_VCO_Param* Val);
void ADF4351_GetVCOParam(ADF4351_Handle* Handle, ADF4351_VCO_Param* Val);
void ADF4351_SetMuxOut(ADF4351_Handle* Handle, ADF4351_MuxOut_Val Val);
void ADF4351_SetOutputPower(ADF4351_Handle* Handle, ADF4351_OutputPower_Val Val);
void ADF4351_SetAuxOutput(ADF4351_Handle* Handle, bool Enabled, ADF4351_AuxOutputSelect_Val Sel, ADF4351_OutputPower_Val Val);
void ADF4351_SetMiscParam(ADF4351_Handle* Handle, ADF4351_Misc_Param* Val);
void ADF4351_CounterReset(ADF4351_Handle* Handle);
void ADF4351_SetRFDivider(ADF4351_Handle* Handle, u8 Val);
u8 ADF4351_GetRFDivider(ADF4351_Handle* Handle);
void ADF4351_SetInteger(ADF4351_Handle* Handle, u16 Val);
void ADF4351_SetFractional(ADF4351_Handle* Handle, u16 Val);
void ADF4351_SetModulus(ADF4351_Handle* Handle, u16 Val);
u16 ADF4351_GetModulus(ADF4351_Handle* Handle);
void ADF4351_Update(ADF4351_Handle* Handle);

bool ADF4351_SetPDFrequency(ADF4351_Handle* Handle, float RefFreq, float PDFreq);
bool ADF4351_SetVCOFrequency(ADF4351_Handle* Handle, float RefFreq, float VCOFreq);
bool ADF4351_SetOutputAFrequency(ADF4351_Handle* Handle, float RefFreq, float OutFreq, bool CanModifyRFDiv);

C_HEADER_END
