#pragma once

#define AD9959_CSR_Addr 0x00
#define AD9959_CSR_Len 1
#define AD9959_ChannelEnable_Shift 4
#define AD9959_ChannelEnable_Mask (0x0F << AD9959_ChannelEnable_Shift)
#define AD9959_ChannelEnable_Ch0 0x01
#define AD9959_ChannelEnable_Ch1 0x02
#define AD9959_ChannelEnable_Ch2 0x04
#define AD9959_ChannelEnable_Ch3 0x08
#define AD9959_IOMode_Shift 1
#define AD9959_IOMode_Mask (0x03 << AD9959_IOMode_Shift)
#define AD9959_IOMode_2Wire1Bit 0x00
#define AD9959_IOMode_3Wire1Bit 0x01
#define AD9959_IOMode_2Bit 0x02
#define AD9959_IOMode_3Bit 0x03
#define AD9959_LSBFirst_Shift 1
#define AD9959_LSBFirst_Mask (0x03 << AD9959_LSBFirst_Shift)

#define AD9959_FR1_Addr 0x01
#define AD9959_FR1_Len 3
#define AD9959_VCOGainControl_Shift 23
#define AD9959_VCOGainControl_Mask (0x000001 << AD9959_VCOGainControl_Shift)
#define AD9959_PLLDivider_Shift 18
#define AD9959_PLLDivider_Mask (0x001F << AD9959_PLLDivider_Shift)
#define AD9959_ChargePumpControl_Shift 16
#define AD9959_ChargePumpControl_Mask (0x000003 << AD9959_ChargePumpControl_Shift)
#define AD9959_ChargePumpCurrent75uA 0
#define AD9959_ChargePumpCurrent100uA 01
#define AD9959_ChargePumpCurrent125uA 2
#define AD9959_ChargePumpCurrent150uA 3
#define AD9959_ProfilePinConfig_Shift 12
#define AD9959_ProfilePinConfig_Mask (0x000007 << AD9959_ProfilePinConfig_Shift)
#define AD9959_RampUpRampDown_Shift 10
#define AD9959_RampUpRampDown_Mask (0x000003 << AD9959_RampUpRampDown_Shift)
#define AD9959_ModulationLevel_Shift 8
#define AD9959_ModulationLevel_Mask (0x000003 << AD9959_ModulationLevel_Shift)
#define AD9959_RefClockPowerdown_Shift 7
#define AD9959_RefClockPowerdown_Mask (0x000001 << AD9959_RefClockPowerdown_Shift)
#define AD9959_ExtPowerdownMode_Shift 6
#define AD9959_ExtPowerdownMode_Mask (0x000001 << AD9959_ExtPowerdownMode_Shift)
#define AD9959_SYNCCLKDisable_Shift 5
#define AD9959_SYNCCLKDisable_Mask (0x000001 << AD9959_SYNCCLKDisable_Shift)
#define AD9959_DACRefPowerdown_Shift 4
#define AD9959_DACRefPowerdown_Mask (0x000001 << AD9959_DACRefPowerdown_Shift)
#define AD9959_ManualHardSync_Shift 1
#define AD9959_ManualHardSync_Mask (0x000001 << AD9959_ManualHardSync_Shift)
#define AD9959_ManualSoftSync_Shift 0
#define AD9959_ManualSoftSync_Mask (0x000001 << AD9959_ManualSoftSync_Shift)

#define AD9959_FR2_Addr 0x02
#define AD9959_FR2_Len 2
#define AD9959_AllChanAutoClearSweepAcc_Shift 15
#define AD9959_AllChanAutoClearSweepAcc_Mask (0x0001 << AD9959_AllChanAutoClearSweepAcc_Shift)
#define AD9959_AllChanClearSweepAcc_Shift 14
#define AD9959_AllChanClearSweepAcc_Mask (0x0001 << AD9959_AllChanClearSweepAcc_Shift)
#define AD9959_AllChanAutoClearPhaseAcc_Shift 13
#define AD9959_AllChanAutoClearPhaseAcc_Mask (0x0001 << AD9959_AllChanAutoClearPhaseAcc_Shift)
#define AD9959_AllChanClearPhaseAcc_Shift 12
#define AD9959_AllChanClearPhaseAcc_Mask (0x0001 << AD9959_AllChanClearPhaseAcc_Shift)
#define AD9959_AutoSyncEnable_Shift 7
#define AD9959_AutoSyncEnable_Mask (0x0001 << AD9959_AutoSyncEnable_Shift)
#define AD9959_SyncMasterEnable_Shift 6
#define AD9959_SyncMasterEnable_Mask (0x0001 << AD9959_SyncMasterEnable_Shift)
#define AD9959_SyncStatus_Shift 5
#define AD9959_SyncStatus_Mask (0x0001 << AD9959_SyncStatus_Shift)
#define AD9959_SyncMask_Shift 4
#define AD9959_SyncMask_Mask (0x0001 << AD9959_SyncMask_Shift)
#define AD9959_SystemClockOffset_Shift 0
#define AD9959_SystemClockOffset_Mask (0x0003 << AD9959_SystemClockOffset_Shift)

#define AD9959_CFR_Addr 0x03
#define AD9959_CFR_Len 3
#define AD9959_AFPSel_Shift 22
#define AD9959_AFPSel_Mask (0x0003 << AD9959_AFPSel_Shift)
#define AD9959_LinerrSweepNoDwell_Shift 15
#define AD9959_LinerrSweepNoDwell_Mask (0x000001 << AD9959_LinerrSweepNoDwell_Shift)
#define AD9959_LinerrSweepEnable_Shift 14
#define AD9959_LinerrSweepEnable_Mask (0x000001 << AD9959_LinerrSweepEnable_Shift)
#define AD9959_LoadSRRAtUpdate_Shift 13
#define AD9959_LoadSRRAtUpdate_Mask (0x000001 << AD9959_LoadSRRAtUpdate_Shift)
#define AD9959_DACFullCurrent_Shift 8
#define AD9959_DACFullCurrent_Mask (0x000003 << AD9959_DACFullCurrent_Shift)
#define AD9959_DigitalPowerdown_Shift 7
#define AD9959_DigitalPowerdown_Mask (0x000001 << AD9959_DigitalPowerdown_Shift)
#define AD9959_DACPowerdown_Shift 6
#define AD9959_DACPowerdown_Mask (0x000001 << AD9959_DACPowerdown_Shift)
#define AD9959_MatchedPipeDelay_Shift 5
#define AD9959_MatchedPipeDelay_Mask (0x000001 << AD9959_MatchedPipeDelay_Shift)
#define AD9959_AutoClearSweepAcc_Shift 4
#define AD9959_AutoClearSweepAcc_Mask (0x000001 << AD9959_AutoClearSweepAcc_Shift)
#define AD9959_AutoSweepAcc_Shift 3
#define AD9959_AutoSweepAcc_Mask (0x000001 << AD9959_AutoSweepAcc_Shift)
#define AD9959_AutoClearPhaseAcc_Shift 2
#define AD9959_AutoClearPhaseAcc_Mask (0x000001 << AD9959_AutoClearPhaseAcc_Shift)
#define AD9959_ClearPhaseAcc_Shift 1
#define AD9959_ClearPhaseAcc_Mask (0x000001 << AD9959_ClearPhaseAcc_Shift)
#define AD9959_SineOutput_Shift 0
#define AD9959_SineOutput_Mask (0x000001 << AD9959_SineOutput_Shift)

#define AD9959_CFTW_Addr 0x04
#define AD9959_CFTW_Len 4

#define AD9959_CPOW_Addr 0x05
#define AD9959_CPOW_Len 2
#define AD9959_PhaseOffsetWord_Shift 0
#define AD9959_PhaseOffsetWord_Mask (0x3FFF << AD9959_PhaseOffsetWord_Shift)

#define AD9959_ACR_Addr 0x06
#define AD9959_ACR_Len 3
#define AD9959_AmplitudeRampRate_Shift 16
#define AD9959_AmplitudeRampRate_Mask (0x0000FF << AD9959_AmplitudeRampRate_Shift)
#define AD9959_StepSize_Shift 14
#define AD9959_StepSize_Mask (0x000003 << AD9959_StepSize_Shift)
#define AD9959_AmplitudeMultEnable_Shift 12
#define AD9959_AmplitudeMultEnable_Mask (0x000001 << AD9959_AmplitudeMultEnable_Shift)
#define AD9959_RampUpRampDownEnable_Shift 11
#define AD9959_RampUpRampDownEnable_Mask (0x000001 << AD9959_RampUpRampDownEnable_Shift)
#define AD9959_LoadARRAtUpdate_Shift 10
#define AD9959_LoadARRAtUpdate_Mask (0x000001 << AD9959_LoadARRAtUpdate_Shift)
#define AD9959_AmplitudeScale_Shift 0
#define AD9959_AmplitudeScale_Mask (0x0003FF << AD9959_AmplitudeScale_Shift)

#define AD9959_LSRR_Addr 0x07
#define AD9959_LSRR_Len 2
#define AD9959_FSRR_Shift 8
#define AD9959_FSRR_Mask (0x000F << AD9959_FSRR_Shift)
#define AD9959_RSRR_Shift 0
#define AD9959_RSRR_Mask (0x000F << AD9959_RSRR_Shift)

#define AD9959_RDW_Addr 0x08
#define AD9959_RDW_Len 4

#define AD9959_FDW_Addr 0x09
#define AD9959_FDW_Len 4
