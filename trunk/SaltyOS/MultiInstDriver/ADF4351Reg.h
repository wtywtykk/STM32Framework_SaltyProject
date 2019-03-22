#pragma once

#define ADF4351_Integer_Shift 15
#define ADF4351_Integer_Mask (0xFFFF << ADF4351_Integer_Shift)
#define ADF4351_Fractional_Shift 3
#define ADF4351_Fractional_Mask (0x0FFF << ADF4351_Fractional_Shift)

#define ADF4351_PhaseAdjust_Shift 28
#define ADF4351_PhaseAdjust_Mask (0x0001 << ADF4351_PhaseAdjust_Shift)
#define ADF4351_Prescaler_Shift 27
#define ADF4351_Prescaler_Mask (0x0001 << ADF4351_Prescaler_Shift)
#define ADF4351_Phase_Shift 15
#define ADF4351_Phase_Mask (0x0FFF << ADF4351_Phase_Shift)
#define ADF4351_Modulus_Shift 3
#define ADF4351_Modulus_Mask (0x0FFF << ADF4351_Modulus_Shift)

#define ADF4351_LowNoiseAndSpur_Shift 29
#define ADF4351_LowNoiseAndSpur_Mask (0x0003 << ADF4351_LowNoiseAndSpur_Shift)
#define ADF4351_MuxOut_Shift 26
#define ADF4351_MuxOut_Mask (0x0007 << ADF4351_MuxOut_Shift)
#define ADF4351_RefDouble_Shift 25
#define ADF4351_RefDouble_Mask (0x0001 << ADF4351_RefDouble_Shift)
#define ADF4351_RDIV2_Shift 24
#define ADF4351_RDIV2_Mask (0x0001 << ADF4351_RDIV2_Shift)
#define ADF4351_R_Shift 14
#define ADF4351_R_Mask (0x03FF << ADF4351_R_Shift)
#define ADF4351_DoubleBuffer_Shift 13
#define ADF4351_DoubleBuffer_Mask (0x0001 << ADF4351_DoubleBuffer_Shift)
#define ADF4351_ChargePumpCurrent_Shift 9
#define ADF4351_ChargePumpCurrent_Mask (0x000F << ADF4351_ChargePumpCurrent_Shift)
#define ADF4351_LDF_Shift 8
#define ADF4351_LDF_Mask (0x0001 << ADF4351_LDF_Shift)
#define ADF4351_LDP_Shift 7
#define ADF4351_LDP_Mask (0x0001 << ADF4351_LDP_Shift)
#define ADF4351_PDPolarity_Shift 6
#define ADF4351_PDPolarity_Mask (0x0001 << ADF4351_PDPolarity_Shift)
#define ADF4351_PowerDown_Shift 5
#define ADF4351_PowerDown_Mask (0x0001 << ADF4351_PowerDown_Shift)
#define ADF4351_CPThreeState_Shift 4
#define ADF4351_CPThreeState_Mask (0x0001 << ADF4351_CPThreeState_Shift)
#define ADF4351_CounterReset_Shift 3
#define ADF4351_CounterReset_Mask (0x0001 << ADF4351_CounterReset_Shift)

#define ADF4351_BandSelectClockMode_Shift 23
#define ADF4351_BandSelectClockMode_Mask (0x0001 << ADF4351_BandSelectClockMode_Shift)
#define ADF4351_ABP_Shift 22
#define ADF4351_ABP_Mask (0x0001 << ADF4351_ABP_Shift)
#define ADF4351_ChargeCancel_Shift 21
#define ADF4351_ChargeCancel_Mask (0x0001 << ADF4351_ChargeCancel_Shift)
#define ADF4351_CSR_Shift 18
#define ADF4351_CSR_Mask (0x0001 << ADF4351_CSR_Shift)
#define ADF4351_ClkDivMode_Shift 15
#define ADF4351_ClkDivMode_Mask (0x0001 << ADF4351_ClkDivMode_Shift)
#define ADF4351_ClockDivider_Shift 3
#define ADF4351_ClockDivider_Mask (0x0FFF << ADF4351_ClockDivider_Shift)

#define ADF4351_FeedBackSelect_Shift 23
#define ADF4351_FeedBackSelect_Mask (0x0001 << ADF4351_FeedBackSelect_Shift)
#define ADF4351_RFDividerSelect_Shift 20
#define ADF4351_RFDividerSelect_Mask (0x0007 << ADF4351_RFDividerSelect_Shift)
#define ADF4351_8BitBandSelectClockDivider_Shift 12
#define ADF4351_8BitBandSelectClockDivider_Mask (0x00FF << ADF4351_8BitBandSelectClockDivider_Shift)
#define ADF4351_VCOPowerDown_Shift 11
#define ADF4351_VCOPowerDown_Mask (0x0001 << ADF4351_VCOPowerDown_Shift)
#define ADF4351_MTLD_Shift 10
#define ADF4351_MTLD_Mask (0x0001 << ADF4351_MTLD_Shift)
#define ADF4351_AuxOutputSelect_Shift 9
#define ADF4351_AuxOutputSelect_Mask (0x0001 << ADF4351_AuxOutputSelect_Shift)
#define ADF4351_AuxOutputEnable_Shift 8
#define ADF4351_AuxOutputEnable_Mask (0x0001 << ADF4351_AuxOutputEnable_Shift)
#define ADF4351_AuxOutputPower_Shift 6
#define ADF4351_AuxOutputPower_Mask (0x0003 << ADF4351_AuxOutputPower_Shift)
#define ADF4351_RFOutputEnable_Shift 5
#define ADF4351_RFOutputEnable_Mask (0x0001 << ADF4351_RFOutputEnable_Shift)
#define ADF4351_RFOutputPower_Shift 3
#define ADF4351_RFOutputPower_Mask (0x0003 << ADF4351_RFOutputPower_Shift)

#define ADF4351_LDPinMode_Shift 22
#define ADF4351_LDPinMode_Mask (0x0003 << ADF4351_LDPinMode_Shift)
#define ADF4351_LDPinMode_Shift 22
#define ADF4351_LDPinMode_Mask (0x0003 << ADF4351_LDPinMode_Shift)
