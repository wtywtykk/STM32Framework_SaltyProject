#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\Window\Window.h"
#include "Kernel\GUI\Window\ScreenWindow.h"
#include "Kernel\GUI\Window\WinEvent.h"
#include "Kernel\GUI\Window\WindowManager.h"
#include "Kernel\GUI\Menu\Menu.h"
#include "Kernel\GUI\Menu\GlobalMenu.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Driver\SAFrontEnd.h"
#include "HAL\StandardSPIPort.h"
#include "MultiInstDriver\LTC1446.h"
#include "MultiInstDriver\HMC832.h"
#include <stdio.h>
#include "Kernel\GUI\InputBox\InputBox.h"

void ReceiverFilter_Process(void);
void ReceiverRenesas_Init(void);
u32 ReceiverRenesas_GetInfo(void);
float ReceiverRenesas_GetTotalGain(void);

const u32 AGCRefreshInterval = 1000;
const u16 PLLRDIV = 4;
const float PLLPhaseDetectorFreq = 168e6 / PLLRDIV;
const float IF1 = 824.0e6;
const float IF2 = 10.7e6;

WINDOW* ReveiverControl_Win = NULL;
LTC1446_Handle AGCLevelDAC_Handle;
HMC832_Handle HMC832LO1;
HMC832_Handle HMC832LO2;
UniGPIO_Handle PostFilterHandle;
UniGPIO_Handle PostAGCHandle;
UniGPIO_Handle PostAGCHiGainHandle;

MenuStruct ReceiverMenu;
MenuItemStruct RecMenuItem[6];
char MenuFreqBuf[128];
//频率
//自适应滤波器

float RecvFreq = 280e6;
bool PostFilter = true;
bool PostAGC = true;
//----------BACKUP SETTINGS--------------
bool LNA1Set = false;
bool LNA2Set = false;
//----------BACKUP SETTINGS--------------
u16 OutputAmpitude = 1900;
char MenuOutAmpBuf[128];

pcstr FreqSetOptions[] = {
	"MHz",
	"取消",
};

pcstr OutAmptSetOptions[] = {
	"确认",
	"取消",
};

void UpdateMenuText(void);
void UpdateHardware(void);

class ReveiverControl_EVENT :public WINEVENT
{
private:
	//Override those methods to handle messages
	virtual bool OnKeyPress(WINDOW* Win, KEYCODE Key);
	virtual bool OnPaint(WINDOW* Win);
};

void LocalOscInitSingle832(HMC832_Handle* Handle, u8 PortNum)
{
	HMC832_Init(Handle, PortNum);
	HMC832_GenericReg_SetRDIV(Handle, PLLRDIV);
	HMC832_GenericReg_SetINTG(Handle, 240);
	HMC832_GenericReg_SetNbrOfChannelsPrefPD(Handle, 0);
	HMC832_GenericReg_SetFRAC(Handle, 0x0);
	HMC832_DeltaSigma_SetFracEnable(Handle, true);
	HMC832_VCO_OutputDivider_Set(Handle, 4);
	HMC832_ChargePump_SetGain(Handle, 0x30, 0x30);
	HMC832_ChargePump_SetOffset(Handle, 50, true, false);
	HMC832_PhaseDetector_SetEnables(Handle, true, true);
	HMC832_PhaseDetector_SetForce(Handle, false, false);
	HMC832_PhaseDetector_SetCSPMode(Handle, 3);
	HMC832_LockDetect_AutomaticRelockOneTry(Handle, true);
	HMC832_LockDetect_DigitalTimerFrequencyControl(Handle, 3);
	HMC832_LockDetect_DigitalWindowDuration(Handle, 2);
	HMC832_LockDetect_MaxCounter(Handle, 7);
	HMC832_LockDetect_WindowType(Handle, true);
	HMC832_VCO_Configuration_SetMuteMode(Handle, 0);
	HMC832_VCO_OutputPowerControl_SetOutputStageGainControl(Handle, 11);
	HMC832_UpdateAllRegs(Handle);
	HMC832_WriteReg(Handle, 0x3);
}

void Set832Freq(HMC832_Handle* Handle, float Freq)
{
	float FreqVCO;
	u32 Integer;
	u32 Frac;
	u8 Div = 1;
	while (Div * Freq < 1.5e9)
	{
		if (Div == 1)
		{
			Div = 2;
		}
		else
		{
			Div += 2;
		}
	}
	FreqVCO = Div * Freq;
	Integer = FreqVCO / PLLPhaseDetectorFreq;
	Frac = (FreqVCO - Integer * PLLPhaseDetectorFreq) / PLLPhaseDetectorFreq * (1L << 24);
	if (Frac >= (1 << 24))
	{
		Frac = 0;
	}
	HMC832_VCO_OutputDivider_Set(Handle, Div);
	HMC832_GenericReg_SetINTG(Handle, Integer);
	HMC832_GenericReg_SetFRAC(Handle, Frac);
	HMC832_WriteVCOReg(Handle, 0x2);
	HMC832_WriteReg(Handle, 0x3);
	HMC832_WriteReg(Handle, 0x4);
}

void LocalOscInit(void)
{
	LocalOscInitSingle832(&HMC832LO1, 0);
	LocalOscInitSingle832(&HMC832LO2, 1);
}

void AGCInit(void)
{
	UniGPIO_Handle CS;
	UniGPIO_Handle MOSI;
	UniGPIO_Handle SCK;
	StandardSPIPort_Init(2, NULL, &MOSI, &SCK, &CS, NULL, NULL, NULL, NULL, NULL);
	LTC1446_Init(&AGCLevelDAC_Handle, NULL, &MOSI, &SCK, &CS);
}

void RecvMenuCallback(struct MenuItemStruct* MenuItem, MenuItemMessage Msg, u32 Param)
{
	if (Msg == ItemPress)
	{
		switch (MenuItem->Tag)
		{
		case 0:
		{
			char Buf[255];
			u32 SelOption = 0;
			InputBox(Buf, 255, FreqSetOptions, 2, &SelOption);
			if (SelOption == 0)
			{
				sscanf(Buf, "%f", &RecvFreq);
				RecvFreq *= 1.0e6;
				if (RecvFreq < 50e3)
				{
					RecvFreq = 50e3;
				}
				if (RecvFreq > 800.0e6)
				{
					RecvFreq = 800.0e6;
				}
				UpdateMenuText();
				UpdateHardware();
				PostMessage(ReveiverControl_Win, WM_PAINT, 0, 0);
			}
		}
		break;
		case 1:
			PostFilter = !PostFilter;
			UpdateMenuText();
			UpdateHardware();
			break;
		case 2:
		{
			char Buf[255];
			u32 SelOption = 0;
			InputBox(Buf, 255, OutAmptSetOptions, 2, &SelOption);
			if (SelOption == 0)
			{
				sscanf(Buf, "%hu", &OutputAmpitude);
				if (OutputAmpitude > 4095)
				{
					OutputAmpitude = 4095;
				}
				UpdateMenuText();
				UpdateHardware();
				PostMessage(ReveiverControl_Win, WM_PAINT, 0, 0);
			}
		}
		break;
		case 3:
			LNA1Set = !LNA1Set;
			UpdateMenuText();
			UpdateHardware();
			break;
		case 4:
			LNA2Set = !LNA2Set;
			UpdateMenuText();
			UpdateHardware();
			break;
		case 5:
			PostAGC = !PostAGC;
			UpdateMenuText();
			UpdateHardware();
			break;
		default:
			break;
		}
	}
}

void UpdateMenuText(void)
{
	MENU* GlobalMenu = GetGlobalMenu();

	RecMenuItem[0].Caption = "接收频率";
	RecMenuItem[0].Enabled = true;
	RecMenuItem[0].CallBack = RecvMenuCallback;
	RecMenuItem[0].Style = PopupItem;
	RecMenuItem[0].SubCaption = MenuFreqBuf;
	sprintf(MenuFreqBuf, "%1.3fM", RecvFreq / 1.0e6);
	RecMenuItem[0].Tag = 0;

	RecMenuItem[1].Caption = "滤波器";
	RecMenuItem[1].Enabled = true;
	RecMenuItem[1].CallBack = RecvMenuCallback;
	RecMenuItem[1].Style = ButtonItem;
	RecMenuItem[1].SubCaption = PostFilter ? "启用" : "关闭";
	RecMenuItem[1].Tag = 1;

	RecMenuItem[2] = RecMenuItem[1];
	RecMenuItem[2].Caption = "输出幅度";
	RecMenuItem[2].SubCaption = MenuOutAmpBuf;
	sprintf(MenuOutAmpBuf, "%d", OutputAmpitude);
	RecMenuItem[2].Tag = 2;

	RecMenuItem[3] = RecMenuItem[1];
	RecMenuItem[3].Caption = "备用LNA1";
	RecMenuItem[3].SubCaption = LNA1Set ? "启用" : "关闭";
	RecMenuItem[3].Tag = 3;

	RecMenuItem[4] = RecMenuItem[1];
	RecMenuItem[4].Caption = "备用LNA2";
	RecMenuItem[4].SubCaption = LNA2Set ? "启用" : "关闭";
	RecMenuItem[4].Tag = 4;

	RecMenuItem[5] = RecMenuItem[1];
	RecMenuItem[5].Caption = "输出AGC";
	RecMenuItem[5].SubCaption = PostAGC ? "启用" : "关闭";
	RecMenuItem[5].Tag = 5;

	GlobalMenu->UpdateItems();
	FreeAndEraseReference(GlobalMenu);
}

void UpdateHardware(void)
{
	Set832Freq(&HMC832LO1, RecvFreq + IF1);
	Set832Freq(&HMC832LO2, IF1 + IF2);
	SAFrontEnd_EnableLNA1(LNA1Set);
	SAFrontEnd_EnableLNA2(LNA2Set);
	SAFrontEnd_SetDSA(0);
	UniGPIO_SetVal(&PostFilterHandle, PostFilter);
	LTC1446_SetChannelAB(&AGCLevelDAC_Handle, OutputAmpitude, 1400);
	UniGPIO_SetVal(&PostAGCHandle, PostAGC);
	UniGPIO_SetVal(&PostAGCHiGainHandle, PostAGC && PostFilter);
}

void CreateRecvMenu(void)
{
	MENU* GlobalMenu = GetGlobalMenu();

	ReceiverMenu.ItemCount = sizeof(RecMenuItem) / sizeof(RecMenuItem[0]);
	ReceiverMenu.Items = RecMenuItem;
	ReceiverMenu.MenuCaption = "调幅信号处理";
	ReceiverMenu.CallBack = NULL;

	UpdateMenuText();

	GlobalMenu->EnterMenu(&ReceiverMenu);
	FreeAndEraseReference(GlobalMenu);
}

void CreateWin(void)
{
	WINDOW* ScrWin = SCREENWINDOW::GetScreenWindow();
	GUIPOS ScrWidth = 0;
	GUIPOS ScrHeight = 0;
	ScrWin->GetWindowPos(NULL, NULL, &ScrWidth, &ScrHeight);
	FreeAndEraseReference(ScrWin);
	ReveiverControl_Win = new_noexcpt WINDOW(NULL, 0, 0, ScrWidth - MENU::GetMenuWidth(), ScrHeight, true);
	WINEVENT* Event = new_noexcpt ReveiverControl_EVENT();
	ReveiverControl_Win->LinkEventHandler(Event);
	ReveiverControl_Win->SetCaption("ReveiverControlWin");
}

void RefreshAGCStatus(void)
{
	static u32 LastRefreshTime = 0;
	if (LastRefreshTime + AGCRefreshInterval < HAL_GetTick())
	{
		LastRefreshTime = HAL_GetTick();
		PostMessage(ReveiverControl_Win, WM_PAINT, 0, 0);
	}
}

void rrrTaskLauncher(void)
{
	LocalOscInit();
	AGCInit();
	ReceiverRenesas_Init();
	SAFrontEnd_Init();
	CreateWin();
	CreateRecvMenu();
	GPIO_CPLD_InitPin(7, 0, true, &PostFilterHandle);
	GPIO_CPLD_InitPin(7, 1, true, &PostAGCHandle);
	GPIO_CPLD_InitPin(7, 2, true, &PostAGCHiGainHandle);
	UpdateHardware();
	while (1)
	{
		RefreshAGCStatus();
		DoMessageLoop();
		ReceiverFilter_Process();
	}
}

bool ReveiverControl_EVENT::OnKeyPress(WINDOW * Win, KEYCODE Key)
{
	if (Key == KEY_RESERVED)
	{
	}
	return true;
}

bool ReveiverControl_EVENT::OnPaint(WINDOW * Win)
{
	DC* DrawingDC = Win->GetDC();
	FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC48;HZK48S;HZK48T"));

	DrawingDC->Fill(0, 0, DrawingDC->GetWidth(), DrawingDC->GetHeight(), BLACK);

	char sbuf[128];
	sprintf(sbuf, "载波频率: %f MHz     ", RecvFreq / 1000.0 / 1000.0);
	DrawStringHorizontal(DrawingDC, FG, sbuf, 10, 10, 0, 0, WHITE, BLACK);

	DrawStringHorizontal(DrawingDC, FG, "输入幅度", 10, 100, 0, 0, WHITE, BLACK);
	float CurrentDynamicRange = ReceiverRenesas_GetTotalGain();
	const float LowestDynamicRange = -34;
	const float HighestDynamicRange = 60;
	const GUIPOS DynamicProgressBarWidth = 600;
	float RealProgressBarWidth = DynamicProgressBarWidth * (CurrentDynamicRange - LowestDynamicRange) / (HighestDynamicRange - LowestDynamicRange);

	if (RealProgressBarWidth < 0)
	{
		RealProgressBarWidth = 0;
	}
	if (RealProgressBarWidth > DynamicProgressBarWidth)
	{
		RealProgressBarWidth = DynamicProgressBarWidth;
	}
	DrawingDC->Fill(8, 208, 8 + DynamicProgressBarWidth + 4, 238, WHITE);
	DrawingDC->Fill(8 + 2, 210, 8 + 2 + DynamicProgressBarWidth - RealProgressBarWidth, 236, DGRAY);

	FreeAndEraseReference(FG);
	FreeAndEraseReference(DrawingDC);
	return false;
}
