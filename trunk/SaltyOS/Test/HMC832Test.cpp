#include "Kernel\Common\KCommon.h"
#include "MultiInstDriver\HMC832.h"
#include "Kernel\GUI\DC\LCDDC.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\FontGroup.h"
#include <stdio.h>

HMC832_Handle HMC832TestHandle;

void HMC832Test(void)
{
	FONTGROUP* FGs = NewReferenceSafe(new_noexcpt FONTGROUP("ASC16"));
	char sbuf[128];
	static bool Inited = false;
	if (!Inited)
	{
		Inited = true;
		HMC832_Init(&HMC832TestHandle, 0);
		HMC832_GenericReg_SetRDIV(&HMC832TestHandle, 1);
		HMC832_GenericReg_SetINTG(&HMC832TestHandle, 153);
		HMC832_GenericReg_SetNbrOfChannelsPrefPD(&HMC832TestHandle, 0);
		HMC832_GenericReg_SetFRAC(&HMC832TestHandle, 0x0);
		HMC832_DeltaSigma_SetFracEnable(&HMC832TestHandle, true);
		HMC832_VCO_OutputDivider_Set(&HMC832TestHandle, 2);
		HMC832_ChargePump_SetGain(&HMC832TestHandle, 0x40, 0x40);
		HMC832_PhaseDetector_SetEnables(&HMC832TestHandle, true, true);
		HMC832_PhaseDetector_SetForce(&HMC832TestHandle, false, false);
		HMC832_PhaseDetector_SetCSPMode(&HMC832TestHandle, 3);
		HMC832_LockDetect_AutomaticRelockOneTry(&HMC832TestHandle, true);
		HMC832_LockDetect_DigitalTimerFrequencyControl(&HMC832TestHandle, 3);
		HMC832_LockDetect_DigitalWindowDuration(&HMC832TestHandle, 2);
		HMC832_LockDetect_MaxCounter(&HMC832TestHandle, 7);
		HMC832_LockDetect_WindowType(&HMC832TestHandle, true);
		HMC832_VCO_Configuration_SetMuteMode(&HMC832TestHandle, 0);
		HMC832_VCO_OutputPowerControl_SetOutputStageGainControl(&HMC832TestHandle, 11);
		//HMC832_AutoCalibration_SetAutocalibrationDisable(&HMC832TestHandle, true);
		//HMC832_AutoCalibration_SetVTUNEResolution(&HMC832TestHandle, 7);
		//HMC832_AutoCalibration_SetFSM_VSPIClockSelect(&HMC832TestHandle, 3);
		HMC832_UpdateAllRegs(&HMC832TestHandle);
		HMC832_WriteReg(&HMC832TestHandle, 0x3);
	}
	for (u32 i = 0; i < HMC832_RegCount; i++)
	{
		sprintf(sbuf, "R%X= Wr %lX  Rd %lX   ", (int)i, HMC832TestHandle.Regs[i], HMC832_ReadReg(&HMC832TestHandle, i));
		DrawStringHorizontal(g_LCDDC, FGs, sbuf, 0, 16 * i, 0, 0, WHITE, BLACK);
	}
	for (u32 i = 0; i < HMC832_VCORegCount; i++)
	{
		sprintf(sbuf, "VR%X= %X   ", (int)i, HMC832TestHandle.VCORegs[i]);
		DrawStringHorizontal(g_LCDDC, FGs, sbuf, 400, 16 * i, 0, 0, WHITE, BLACK);
	}
	bool LockState = HMC832_IsLocked(&HMC832TestHandle);
	DrawStringHorizontal(g_LCDDC, FGs, LockState ? "Locked   " : "Unlocked   ", 0, 350, 0, 0, LockState ? GREEN : RED, BLACK);
	if (!LockState)
	{
		HMC832_WriteReg(&HMC832TestHandle, 0x3);
	}
	FreeAndEraseReference(FGs);
}
