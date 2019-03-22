#include "Kernel\Common\KCommon.h"
#include "User\OscilloscopeFPGAAbstrast.h"
#include "HAL\FPGAParPort.h"
#include "HAL\FPGASPIPort.h"
#include <string.h>

OscilloscopeFPGAAbstrast::OscilloscopeFPGAAbstrast(Oscilloscope* Osc)
{
	OscInst = Osc;
	memset(&CurrentConfig, 0, sizeof(CurrentConfig));
	memset(&NewConfig, 0, sizeof(NewConfig));
}

OscilloscopeFPGAAbstrast::~OscilloscopeFPGAAbstrast(void)
{
}

bool OscilloscopeFPGAAbstrast::ReteriveValue(u16* Buffer, u32 BufferSizeInWord, u32* ReadSize)
{
	bool ReteriveSuccess = false;
	switch (CommState)
	{
	default:
		CommState = FPGAState_Reset;
		break;
	case FPGAState_Sampling:
		if (FPGAParPort_IsReady())
		{
			Triggered = FPGAParPort_ReadIO4();
			UpdateFrequency();
			if (ParPort_StartPipeline())
			{
				if (ParPort_Read(Buffer, BufferSizeInWord, ReadSize, true) == S_OK)
				{
					CommState = FPGAState_Reset;
					ReteriveSuccess = true;
				}
				else
				{
					CommState = FPGAState_Transmiting;
					if (*ReadSize != 0)
					{
						ReteriveSuccess = true;
					}
					else
					{
						ReteriveSuccess = false;
					}
				}
			}
		}
		break;
	case FPGAState_Transmiting:
		if (ParPort_Read(Buffer, BufferSizeInWord, ReadSize, true) == S_OK)
		{
			CommState = FPGAState_Reset;
			ReteriveSuccess = true;
		}
		else
		{
			if (*ReadSize != 0)
			{
				ReteriveSuccess = true;
			}
			else
			{
				ReteriveSuccess = false;
			}
		}
		break;
		break;
	case FPGAState_Reset:
		CommState = FPGAState_Sampling;
		FPGASPIPort_Reset();
		ForceUpdateFPGAConfig();
		break;
	}
	return ReteriveSuccess;
}

void OscilloscopeFPGAAbstrast::UpdateFPGAConfig(void)
{
	NewConfig.B1 = OscInst->TrigMode;
	if (OscInst->TriggerPosition <= 0.0)
	{
		NewConfig.TrigPos = 0;
	}
	else if (OscInst->TriggerPosition >= 1.0)
	{
		NewConfig.TrigPos = DPODataCount;
	}
	else
	{
		NewConfig.TrigPos = DPODataCount * OscInst->TriggerPosition;
	}
	NewConfig.DivFactor = OscInst->GetCurrentPrescaler();
}

void OscilloscopeFPGAAbstrast::ForceUpdateFPGAConfig(void)
{
	UpdateFPGAConfig();
	CurrentConfig = NewConfig;
	FPGASPIPort_Transmit(&NewConfig, sizeof(NewConfig));
	FPGAParPort_Reset();
}

float OscilloscopeFPGAAbstrast::GetCurrentTriggerPosition(void)
{
	return (float)CurrentConfig.TrigPos / DPODataCount;
}

u32 OscilloscopeFPGAAbstrast::GetCurrentPrescaler(void)
{
	return CurrentConfig.DivFactor;
}

bool OscilloscopeFPGAAbstrast::IsLastTimeTriggered(void)
{
	return Triggered;
}

void OscilloscopeFPGAAbstrast::GetFrequencyMeterValue(u32* Ref, u32* Unknown, u32* High)
{
	if (Ref)
	{
		*Ref = FPGAResult.ReferenceCounter;
	}
	if (Unknown)
	{
		*Unknown = FPGAResult.UnknownCounter;
	}
	if (High)
	{
		*High = FPGAResult.HighCounter;
	}
}

void OscilloscopeFPGAAbstrast::UpdateFrequency(void)
{
	FPGASPIPort_Receive(&FPGAResult, sizeof(FPGAResult));
}
