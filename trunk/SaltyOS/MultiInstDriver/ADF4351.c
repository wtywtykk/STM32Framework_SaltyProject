#include "HAL\HCommon.h"
#include "HAL\UniGPIO.h"
#include "HAL\UniSPI.h"
#include "MultiInstDriver\ADF4351.h"
#include "MultiInstDriver\ADF4351Reg.h"
#include <string.h>
#include <math.h>

#define ADF4351_TransmitTimeout 10
#define ADF4351_AppendRegControlBits(Index,x) (((x) & 0xFFFFFFF8) | ((Index) & 0x7))
#define ADF4351_SetRegBits(x,Val,Shift,Mask) (((x) & ~Mask) | (((u32)(Val) << Shift) & Mask))
#define ADF4351_GetRegBits(x,Shift,Mask) (((x) & Mask) >> Shift)

STATUS ADF4351_Init(ADF4351_Handle* Handle, float ExtRset, UniGPIO_Handle* MOSIPin, UniGPIO_Handle* SCKPin, UniGPIO_Handle* LEPin, UniGPIO_Handle* CEPin, UniGPIO_Handle* LDPin, UniGPIO_Handle* PDBRFPin, UniGPIO_Handle* MuxOutPin)
{
	SoftSPI_Init(&Handle->SPI_Handle, NULL, MOSIPin, SCKPin, 8, false, false, 0, 0);

	Handle->Rset = ExtRset;
	Handle->LE = *LEPin;
	Handle->CE = *CEPin;
	Handle->LD = *LDPin;
	Handle->PDBRF = *PDBRFPin;
	Handle->MuxOut = *MuxOutPin;

	UniGPIO_SetOutput(LEPin);
	UniGPIO_SetOutput(CEPin);
	UniGPIO_SetInput(LDPin);
	UniGPIO_SetOutput(PDBRFPin);
	UniGPIO_SetInput(MuxOutPin);

	UniGPIO_SetLow(LEPin);
	UniGPIO_SetHigh(CEPin);
	UniGPIO_SetHigh(PDBRFPin);

	memset(Handle->Regs, 0, sizeof(Handle->Regs));
	Handle->Regs[4] = 0xA020FC;
	Handle->Regs[5] = 0x580005;

	return S_OK;
}

void ADF4351_UpdateReg(ADF4351_Handle* Handle, u8 RegIndex)
{
	typedef union
	{
		u8 u8Val[4];
		u32 u32Val;
	}TransmitValunion;
	TransmitValunion TransmitVal;
	u8 t;
	assert(RegIndex < ADF4351_RegCount);
	TransmitVal.u32Val = ADF4351_AppendRegControlBits(RegIndex, Handle->Regs[RegIndex]);
	t = TransmitVal.u8Val[0];
	TransmitVal.u8Val[0] = TransmitVal.u8Val[3];
	TransmitVal.u8Val[3] = t;
	t = TransmitVal.u8Val[1];
	TransmitVal.u8Val[1] = TransmitVal.u8Val[2];
	TransmitVal.u8Val[2] = t;
	UniSPI_TransmitBytes(&Handle->SPI_Handle, &Handle->LE, TransmitVal.u8Val, sizeof(TransmitVal), ADF4351_TransmitTimeout);
}

void ADF4351_SetReferenceParam(ADF4351_Handle* Handle, ADF4351_Reference_Param* Val)
{
	Handle->Regs[2] = ADF4351_SetRegBits(Handle->Regs[2], Val->Doubler ? 0xFFFFFFFF : 0, ADF4351_RefDouble_Shift, ADF4351_RefDouble_Mask);
	Handle->Regs[2] = ADF4351_SetRegBits(Handle->Regs[2], Val->Div2 ? 0xFFFFFFFF : 0, ADF4351_RDIV2_Shift, ADF4351_RDIV2_Mask);
	assert(Val->R <= (ADF4351_R_Mask >> ADF4351_R_Shift));
	Handle->Regs[2] = ADF4351_SetRegBits(Handle->Regs[2], Val->R, ADF4351_R_Shift, ADF4351_R_Mask);
}

void ADF4351_GetReferenceParam(ADF4351_Handle* Handle, ADF4351_Reference_Param* Val)
{
	Val->Doubler = ADF4351_GetRegBits(Handle->Regs[2], ADF4351_RefDouble_Shift, ADF4351_RefDouble_Mask) ? true : false;
	Val->Div2 = ADF4351_GetRegBits(Handle->Regs[2], ADF4351_RDIV2_Shift, ADF4351_RDIV2_Mask) ? true : false;
	Val->R = ADF4351_GetRegBits(Handle->Regs[2], ADF4351_R_Shift, ADF4351_R_Mask);
}

void ADF4351_SetPFD_ChargePumpParam(ADF4351_Handle* Handle, ADF4351_PFD_ChargePump_Param* Val)
{
	u8 ChargePumpCurrentSetting = 0xF * Val->Current / (25.5 / Handle->Rset) + 0.5;
	if (ChargePumpCurrentSetting > 0xF)
	{
		ChargePumpCurrentSetting = 0xF;
	}
	Handle->Regs[2] = ADF4351_SetRegBits(Handle->Regs[2], ChargePumpCurrentSetting, ADF4351_ChargePumpCurrent_Shift, ADF4351_ChargePumpCurrent_Mask);
	Handle->Regs[2] = ADF4351_SetRegBits(Handle->Regs[2], Val->Polarity ? 0xFFFFFFFF : 0, ADF4351_PDPolarity_Shift, ADF4351_PDPolarity_Mask);
	Handle->Regs[2] = ADF4351_SetRegBits(Handle->Regs[2], Val->TriState ? 0xFFFFFFFF : 0, ADF4351_CPThreeState_Shift, ADF4351_CPThreeState_Mask);
	Handle->Regs[3] = ADF4351_SetRegBits(Handle->Regs[3], Val->BandSelect ? 0xFFFFFFFF : 0, ADF4351_BandSelectClockMode_Shift, ADF4351_BandSelectClockMode_Mask);
	Handle->Regs[3] = ADF4351_SetRegBits(Handle->Regs[3], Val->AntibacklashPulseWidth, ADF4351_ABP_Shift, ADF4351_ABP_Mask);
	Handle->Regs[3] = ADF4351_SetRegBits(Handle->Regs[3], Val->ChargeCancelation ? 0xFFFFFFFF : 0, ADF4351_ChargeCancel_Shift, ADF4351_ChargeCancel_Mask);
	Handle->Regs[3] = ADF4351_SetRegBits(Handle->Regs[3], Val->CSREnable ? 0xFFFFFFFF : 0, ADF4351_CSR_Shift, ADF4351_CSR_Mask);
	Handle->Regs[3] = ADF4351_SetRegBits(Handle->Regs[3], Val->ClkDividerMode, ADF4351_ClkDivMode_Shift, ADF4351_ClkDivMode_Mask);
	assert(Val->ClockDivider <= (ADF4351_ClockDivider_Mask >> ADF4351_ClockDivider_Shift));
	Handle->Regs[3] = ADF4351_SetRegBits(Handle->Regs[3], Val->ClockDivider, ADF4351_ClockDivider_Shift, ADF4351_ClockDivider_Mask);
	Handle->Regs[4] = ADF4351_SetRegBits(Handle->Regs[4], Val->FeedBackSelect, ADF4351_FeedBackSelect_Shift, ADF4351_FeedBackSelect_Mask);
}

void ADF4351_GetPFD_ChargePumpParam(ADF4351_Handle* Handle, ADF4351_PFD_ChargePump_Param* Val)
{
	u8 ChargePumpCurrentSetting;
	ChargePumpCurrentSetting = ADF4351_GetRegBits(Handle->Regs[2], ADF4351_ChargePumpCurrent_Shift, ADF4351_ChargePumpCurrent_Mask);
	Val->Current = ChargePumpCurrentSetting / 0xF * (25.5 / Handle->Rset);
	Val->Polarity = ADF4351_GetRegBits(Handle->Regs[2], ADF4351_PDPolarity_Shift, ADF4351_PDPolarity_Mask) ? true : false;
	Val->TriState = ADF4351_GetRegBits(Handle->Regs[2], ADF4351_CPThreeState_Shift, ADF4351_CPThreeState_Mask) ? true : false;
	Val->BandSelect = ADF4351_GetRegBits(Handle->Regs[3], ADF4351_BandSelectClockMode_Shift, ADF4351_BandSelectClockMode_Mask) ? true : false;
	Val->AntibacklashPulseWidth = ADF4351_GetRegBits(Handle->Regs[3], ADF4351_ABP_Shift, ADF4351_ABP_Mask);
	Val->ChargeCancelation = ADF4351_GetRegBits(Handle->Regs[3], ADF4351_ChargeCancel_Shift, ADF4351_ChargeCancel_Mask) ? true : false;
	Val->CSREnable = ADF4351_GetRegBits(Handle->Regs[3], ADF4351_CSR_Shift, ADF4351_CSR_Mask) ? true : false;
	Val->ClkDividerMode = ADF4351_GetRegBits(Handle->Regs[3], ADF4351_ClkDivMode_Shift, ADF4351_ClkDivMode_Mask);
	Val->ClockDivider = ADF4351_GetRegBits(Handle->Regs[3], ADF4351_ClockDivider_Shift, ADF4351_ClockDivider_Mask);
	Val->FeedBackSelect = ADF4351_GetRegBits(Handle->Regs[4], ADF4351_FeedBackSelect_Shift, ADF4351_FeedBackSelect_Mask);
}

void ADF4351_SetVCOParam(ADF4351_Handle* Handle, ADF4351_VCO_Param* Val)
{
	Handle->Regs[4] = ADF4351_SetRegBits(Handle->Regs[4], Val->BandSelectClockDivider, ADF4351_8BitBandSelectClockDivider_Shift, ADF4351_8BitBandSelectClockDivider_Mask);
	Handle->Regs[4] = ADF4351_SetRegBits(Handle->Regs[4], Val->PowerDown ? 0xFFFFFFFF : 0, ADF4351_VCOPowerDown_Shift, ADF4351_VCOPowerDown_Mask);
}

void ADF4351_GetVCOParam(ADF4351_Handle* Handle, ADF4351_VCO_Param* Val)
{
	Val->BandSelectClockDivider = ADF4351_GetRegBits(Handle->Regs[4], ADF4351_8BitBandSelectClockDivider_Shift, ADF4351_8BitBandSelectClockDivider_Mask);
	Val->PowerDown = ADF4351_GetRegBits(Handle->Regs[4], ADF4351_VCOPowerDown_Shift, ADF4351_VCOPowerDown_Mask) ? true : false;
}

void ADF4351_SetMuxOut(ADF4351_Handle* Handle, ADF4351_MuxOut_Val Val)
{
	Handle->Regs[2] = ADF4351_SetRegBits(Handle->Regs[2], Val, ADF4351_MuxOut_Shift, ADF4351_MuxOut_Mask);
}

void ADF4351_SetOutputPower(ADF4351_Handle* Handle, ADF4351_OutputPower_Val Val)
{
	Handle->Regs[4] = ADF4351_SetRegBits(Handle->Regs[4], Val, ADF4351_RFOutputPower_Shift, ADF4351_RFOutputPower_Mask);
}

void ADF4351_SetAuxOutput(ADF4351_Handle* Handle, bool Enabled, ADF4351_AuxOutputSelect_Val Sel, ADF4351_OutputPower_Val Val)
{
	Handle->Regs[4] = ADF4351_SetRegBits(Handle->Regs[4], Sel, ADF4351_AuxOutputSelect_Shift, ADF4351_AuxOutputSelect_Mask);
	Handle->Regs[4] = ADF4351_SetRegBits(Handle->Regs[4], Enabled ? 0xFFFFFFFF : 0, ADF4351_AuxOutputEnable_Shift, ADF4351_AuxOutputEnable_Mask);
	Handle->Regs[4] = ADF4351_SetRegBits(Handle->Regs[4], Val, ADF4351_AuxOutputPower_Shift, ADF4351_AuxOutputPower_Mask);
}

void ADF4351_SetMiscParam(ADF4351_Handle* Handle, ADF4351_Misc_Param* Val)
{
	Handle->Regs[1] = ADF4351_SetRegBits(Handle->Regs[1], Val->Perscaler, ADF4351_Prescaler_Shift, ADF4351_Prescaler_Mask);
	Handle->Regs[2] = ADF4351_SetRegBits(Handle->Regs[2], Val->LowNoiseSpur, ADF4351_LowNoiseAndSpur_Shift, ADF4351_LowNoiseAndSpur_Mask);
	Handle->Regs[4] = ADF4351_SetRegBits(Handle->Regs[4], Val->MuteTillLockDetect, ADF4351_MTLD_Shift, ADF4351_MTLD_Mask);
}

void ADF4351_CounterReset(ADF4351_Handle* Handle)
{
	Handle->Regs[2] = ADF4351_SetRegBits(Handle->Regs[2], ADF4351_CounterReset_Mask, ADF4351_CounterReset_Shift, ADF4351_CounterReset_Mask);
	ADF4351_UpdateReg(Handle, 2);
	Handle->Regs[2] = ADF4351_SetRegBits(Handle->Regs[2], 0, ADF4351_CounterReset_Shift, ADF4351_CounterReset_Mask);
	ADF4351_UpdateReg(Handle, 2);
}

void ADF4351_SetRFDivider(ADF4351_Handle* Handle, u8 Val)
{
	u8 i;
	for (i = 0; i <= 6; i++)
	{
		if (1 << i == Val)
		{
			break;
		}
	}
	assert(i != 7);
	if (i == 7)
	{
		i = 6;
	}
	Handle->Regs[4] = ADF4351_SetRegBits(Handle->Regs[4], i, ADF4351_RFDividerSelect_Shift, ADF4351_RFDividerSelect_Mask);
}

u8 ADF4351_GetRFDivider(ADF4351_Handle * Handle)
{
	return 1 << ADF4351_GetRegBits(Handle->Regs[4], ADF4351_RFDividerSelect_Shift, ADF4351_RFDividerSelect_Mask);
}

void ADF4351_SetInteger(ADF4351_Handle* Handle, u16 Val)
{
	Handle->Regs[0] = ADF4351_SetRegBits(Handle->Regs[0], Val, ADF4351_Integer_Shift, ADF4351_Integer_Mask);
}

void ADF4351_SetFractional(ADF4351_Handle* Handle, u16 Val)
{
	assert(Val <= (ADF4351_Fractional_Mask >> ADF4351_Fractional_Shift));
	Handle->Regs[0] = ADF4351_SetRegBits(Handle->Regs[0], Val, ADF4351_Fractional_Shift, ADF4351_Fractional_Mask);
}

void ADF4351_SetModulus(ADF4351_Handle* Handle, u16 Val)
{
	assert(Val <= (ADF4351_Modulus_Mask >> ADF4351_Modulus_Shift));
	Handle->Regs[1] = ADF4351_SetRegBits(Handle->Regs[1], Val, ADF4351_Modulus_Shift, ADF4351_Modulus_Mask);
}

u16 ADF4351_GetModulus(ADF4351_Handle * Handle)
{
	return ADF4351_GetRegBits(Handle->Regs[1], ADF4351_Modulus_Shift, ADF4351_Modulus_Mask);
}

void ADF4351_SetPhaseAdjust(ADF4351_Handle* Handle, bool Val)
{
	Handle->Regs[1] = ADF4351_SetRegBits(Handle->Regs[1], Val ? 0xFFFFFFFF : 0, ADF4351_PhaseAdjust_Shift, ADF4351_PhaseAdjust_Mask);
}

void ADF4351_SetPreScaler(ADF4351_Handle* Handle, bool Val)
{
	Handle->Regs[1] = ADF4351_SetRegBits(Handle->Regs[1], Val ? 0xFFFFFFFF : 0, ADF4351_Prescaler_Shift, ADF4351_Prescaler_Mask);
}

void ADF4351_SetPhase(ADF4351_Handle* Handle, u16 Val)
{
	assert(Val <= (ADF4351_Phase_Mask >> ADF4351_Phase_Shift));
	Handle->Regs[1] = ADF4351_SetRegBits(Handle->Regs[1], 0, ADF4351_Phase_Shift, ADF4351_Phase_Mask);
}

void ADF4351_Update(ADF4351_Handle* Handle)
{
	ADF4351_UpdateReg(Handle, 5);
	ADF4351_UpdateReg(Handle, 4);
	ADF4351_UpdateReg(Handle, 3);
	ADF4351_UpdateReg(Handle, 2);
	ADF4351_UpdateReg(Handle, 1);
	ADF4351_UpdateReg(Handle, 0);
}

bool ADF4351_SetPDFrequency(ADF4351_Handle* Handle, float RefFreq, float PDFreq)
{
	ADF4351_Reference_Param RefParam;
	float DivRatio = RefFreq / PDFreq;
	u16 DivRatioI;
	float RealPDFreq;
	if (RefFreq > 30000000)
	{
		RefParam.Doubler = false;
	}
	else
	{
		RefParam.Doubler = true;
		DivRatio *= 2;
	}
	if (DivRatio > 1023)
	{
		DivRatio /= 2.0;
		RefParam.Div2 = true;
	}
	else
	{
		RefParam.Div2 = false;
	}
	if (DivRatio > 1023 && RefParam.Doubler)
	{
		DivRatio /= 2.0;
		RefParam.Doubler = false;
	}
	if (DivRatio > 1023)
	{
		DivRatio = 1023;
	}
	DivRatioI = DivRatio + 0.5;
	if (RefParam.Div2 == false && DivRatioI % 2 == 0)
	{
		DivRatioI /= 2;
		RefParam.Div2 = true;
	}
	if (DivRatioI == 0)
	{
		DivRatioI = 1;
	}
	RefParam.R = DivRatioI;
	ADF4351_SetReferenceParam(Handle, &RefParam);

	RealPDFreq = RefFreq;
	if (RefParam.Doubler)
	{
		RealPDFreq *= 2.0;
	}
	if (RefParam.Div2)
	{
		RealPDFreq /= 2.0;
	}
	RealPDFreq /= RefParam.R;
	if (fabs(RealPDFreq - PDFreq) / PDFreq <= 0.000001)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ADF4351_SetVCOFrequency(ADF4351_Handle* Handle, float RefFreq, float VCOFreq)
{
	ADF4351_Reference_Param RefParam;
	u8 RFDivider;
	ADF4351_PFD_ChargePump_Param PFD_CP_Param;
	float RealPDFreq = RefFreq;
	float FreqRatio;
	u16 FreqRatioI;
	u16 Fractional;
	u16 Modulus;
	float RealFreq;
	ADF4351_GetReferenceParam(Handle, &RefParam);
	if (RefParam.Doubler)
	{
		RealPDFreq *= 2.0;
	}
	if (RefParam.Div2)
	{
		RealPDFreq /= 2.0;
	}
	RealPDFreq /= RefParam.R;
	ADF4351_GetPFD_ChargePumpParam(Handle, &PFD_CP_Param);
	RFDivider = ADF4351_GetRFDivider(Handle);
	switch (PFD_CP_Param.FeedBackSelect)
	{
	case FeedBack_Divided:
		FreqRatio = VCOFreq / RealPDFreq / RFDivider;
		break;
	default:
	case FeedBack_Fundamental:
		FreqRatio = VCOFreq / RealPDFreq;
		break;
	}
	if (FreqRatio > 65535.9)
	{
		FreqRatio = 65535.9;
	}
	FreqRatioI = FreqRatio;
	ADF4351_SetInteger(Handle, FreqRatioI);
	Modulus = ADF4351_GetModulus(Handle);
	Fractional = (FreqRatio - FreqRatioI) * Modulus + 0.5;
	if (Fractional >= Modulus)
	{
		Fractional = Modulus - 1;
	}
	ADF4351_SetFractional(Handle, Fractional);
	switch (PFD_CP_Param.FeedBackSelect)
	{
	case FeedBack_Divided:
		RealFreq = RealPDFreq * (FreqRatioI + (float)Fractional / Modulus) * RFDivider;
		break;
	default:
	case FeedBack_Fundamental:
		RealFreq = RealPDFreq * (FreqRatioI + (float)Fractional / Modulus);
		break;
	}
	if (fabs(RealFreq - VCOFreq) / VCOFreq <= 0.000001)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ADF4351_SetOutputAFrequency(ADF4351_Handle* Handle, float RefFreq, float OutFreq, bool CanModifyRFDiv)
{
	u8 RFDiv = 1;
	float VCOFreq;
	const float VCO_LowFreq = 2200000000.0;
	const float VCO_HighFreq = 4400000000.0;
	if (CanModifyRFDiv)
	{
		VCOFreq = OutFreq;
		while (VCOFreq < VCO_LowFreq)
		{
			VCOFreq *= 2.0;
			RFDiv *= 2;
			if (RFDiv == 64)
			{
				break;
			}
		}
		ADF4351_SetRFDivider(Handle, RFDiv);
	}
	else
	{
		RFDiv = ADF4351_GetRFDivider(Handle);
		VCOFreq = OutFreq * RFDiv;
	}
	if (VCOFreq > VCO_HighFreq)
	{
		VCOFreq = VCO_HighFreq;
	}
	if (ADF4351_SetVCOFrequency(Handle, RefFreq, VCOFreq))
	{
		if (fabs(VCOFreq / RFDiv - OutFreq) <= 0.000001)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
