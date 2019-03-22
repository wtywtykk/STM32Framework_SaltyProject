#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\Window\Window.h"
#include "Kernel\GUI\Window\ScreenWindow.h"
#include "Kernel\GUI\Window\WinEvent.h"
#include "Kernel\GUI\Window\WindowManager.h"
#include "Kernel\GUI\Menu\Menu.h"
#include "Kernel\GUI\Menu\GlobalMenu.h"
#include "Kernel\GUI\Text\DrawString.h"
#include <stdio.h>
#include "Kernel\GUI\InputBox\InputBox.h"
#include "MultiInstDriver\ADF4351.h"

WINDOW* FMGenControl_Win = NULL;
MenuStruct FMGenMenu;
MenuItemStruct FMGenMenuItem[1];
char FMGenMenuFreqBuf[128];

pcstr FMGenFreqSetOptions[] = {
	"MHz",
	"取消",
};

void FMGenUpdateMenuText(void);
void FMGenUpdateHardware(void);

class FMGenControl_EVENT :public WINEVENT
{
private:
	//Override those methods to handle messages
	virtual bool OnPaint(WINDOW* Win);
};

ADF4351_Handle FMGenADF4351Handle;
float FMGen_Freq = 100;

void FMGen_PLLInit(void)
{
	UniGPIO_Handle MOSIPin;
	UniGPIO_Handle SCKPin;
	UniGPIO_Handle LEPin;
	UniGPIO_Handle CEPin;
	UniGPIO_Handle LDPin;
	UniGPIO_Handle PDBRFPin;
	UniGPIO_Handle MuxOutPin;
	GPIO_CPLD_InitPin(0, 6, true, &MOSIPin);
	GPIO_CPLD_InitPin(0, 8, true, &SCKPin);
	GPIO_CPLD_InitPin(0, 0, true, &LEPin);
	GPIO_CPLD_InitPin(0, 1, true, &CEPin);
	GPIO_CPLD_InitPin(0, 3, false, &LDPin);
	GPIO_CPLD_InitPin(0, 4, true, &PDBRFPin);
	GPIO_CPLD_InitPin(0, 7, false, &MuxOutPin);
	ADF4351_Init(&FMGenADF4351Handle, 5.1, &MOSIPin, &SCKPin, &LEPin, &CEPin, &LDPin, &PDBRFPin, &MuxOutPin);
	ADF4351_SetPDFrequency(&FMGenADF4351Handle, 50000000.0, 1000000.0);
	ADF4351_PFD_ChargePump_Param CPParam;
	CPParam.AntibacklashPulseWidth = ABP_6ns_FRAC_N;
	CPParam.BandSelect = true;
	CPParam.ChargeCancelation = true;
	CPParam.ClkDividerMode = ClkDivOff;
	CPParam.ClockDivider = 20;
	CPParam.CSREnable = false;
	CPParam.Current = 0.3;
	CPParam.FeedBackSelect = FeedBack_Fundamental;
	CPParam.Polarity = true;
	CPParam.TriState = false;
	ADF4351_SetPFD_ChargePumpParam(&FMGenADF4351Handle, &CPParam);
	ADF4351_SetMuxOut(&FMGenADF4351Handle, DGND);
	ADF4351_SetModulus(&FMGenADF4351Handle, 4000);
	ADF4351_SetOutputAFrequency(&FMGenADF4351Handle, 50000000.0, FMGen_Freq * 1000000.0, true);
	ADF4351_Update(&FMGenADF4351Handle);
}

void FMGenMenuCallback(struct MenuItemStruct* MenuItem, MenuItemMessage Msg, u32 Param)
{
	if (Msg == ItemPress)
	{
		switch (MenuItem->Tag)
		{
		case 0:
		{
			char Buf[255];
			u32 SelOption = 0;
			InputBox(Buf, 255, FMGenFreqSetOptions, 2, &SelOption);
			if (SelOption == 0)
			{
				sscanf(Buf, "%f", &FMGen_Freq);
				if (FMGen_Freq < 80)
				{
					FMGen_Freq = 80;
				}
				if (FMGen_Freq > 120.0)
				{
					FMGen_Freq = 120.0;
				}
				FMGenUpdateMenuText();
				FMGenUpdateHardware();
				PostMessage(FMGenControl_Win, WM_PAINT, 0, 0);
			}
		}
		break;
		default:
			break;
		}
	}
}

void FMGenUpdateMenuText(void)
{
	MENU* GlobalMenu = GetGlobalMenu();

	FMGenMenuItem[0].Caption = "发射频率";
	FMGenMenuItem[0].Enabled = true;
	FMGenMenuItem[0].CallBack = FMGenMenuCallback;
	FMGenMenuItem[0].Style = PopupItem;
	FMGenMenuItem[0].SubCaption = FMGenMenuFreqBuf;
	sprintf(FMGenMenuFreqBuf, "%1.3fM", FMGen_Freq);
	FMGenMenuItem[0].Tag = 0;

	GlobalMenu->UpdateItems();
	FreeAndEraseReference(GlobalMenu);
}

void FMGenUpdateHardware(void)
{
	ADF4351_SetOutputAFrequency(&FMGenADF4351Handle, 50000000.0, FMGen_Freq * 1000000.0, true);
	ADF4351_Update(&FMGenADF4351Handle);
}

void FMGenCreateMenu(void)
{
	MENU* GlobalMenu = GetGlobalMenu();

	FMGenMenu.ItemCount = sizeof(FMGenMenuItem) / sizeof(FMGenMenuItem[0]);
	FMGenMenu.Items = FMGenMenuItem;
	FMGenMenu.MenuCaption = "调频信号源";
	FMGenMenu.CallBack = NULL;

	FMGenUpdateMenuText();

	GlobalMenu->EnterMenu(&FMGenMenu);
	FreeAndEraseReference(GlobalMenu);
}

void FMGenCreateWin(void)
{
	WINDOW* ScrWin = SCREENWINDOW::GetScreenWindow();
	GUIPOS ScrWidth = 0;
	GUIPOS ScrHeight = 0;
	ScrWin->GetWindowPos(NULL, NULL, &ScrWidth, &ScrHeight);
	FreeAndEraseReference(ScrWin);
	FMGenControl_Win = new_noexcpt WINDOW(NULL, 0, 0, ScrWidth - MENU::GetMenuWidth(), ScrHeight, true);
	WINEVENT* Event = new_noexcpt FMGenControl_EVENT();
	FMGenControl_Win->LinkEventHandler(Event);
	FMGenControl_Win->SetCaption("FMGenControlWin");
}

void fffTaskLauncher(void)
{
	FMGen_PLLInit();
	FMGenCreateWin();
	FMGenCreateMenu();
	FMGenUpdateHardware();
	while (1)
	{
		DoMessageLoop();
	}
}

bool FMGenControl_EVENT::OnPaint(WINDOW * Win)
{
	DC* DrawingDC = Win->GetDC();
	FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC48;HZK48S;HZK48T"));

	DrawingDC->Fill(0, 0, DrawingDC->GetWidth(), DrawingDC->GetHeight(), BLACK);

	char sbuf[128];
	sprintf(sbuf, "载波频率: %f MHz     ", FMGen_Freq);
	DrawStringHorizontal(DrawingDC, FG, sbuf, 10, 10, 0, 0, WHITE, BLACK);

	FreeAndEraseReference(FG);
	FreeAndEraseReference(DrawingDC);
	return false;
}
