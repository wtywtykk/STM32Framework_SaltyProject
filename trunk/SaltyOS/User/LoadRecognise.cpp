#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\Window\Window.h"
#include "Kernel\GUI\Window\ScreenWindow.h"
#include "Kernel\GUI\Window\WinEvent.h"
#include "Kernel\GUI\Window\WindowManager.h"
#include "Kernel\GUI\Menu\Menu.h"
#include "Kernel\GUI\Menu\GlobalMenu.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "Kernel\GUI\Text\EstimateString.h"
#include "HAL\StandardSPIPort.h"
#include <stdio.h>
#include "User\LoadRecogniseSampler.h"
#include "User\LoadRecogniseCharacteristicProvider.h"
#include "User\LoadRecogniseEngine.h"
#include "Kernel\GUI\Picture\FlashFSPic.h"
#include "Kernel\GUI\Shape\Line.h"
#include "HAL\Beep.h"

WINDOW* LoadRecognise_Win = NULL;

MenuStruct LoadRecogniseMenu;
MenuItemStruct LoadRecogniseMenuItem[2];
MenuStruct PowerOnConfirmMenu;
MenuItemStruct PowerOnConfirmMenuItem[2];
MenuStruct LearnMenu;
MenuItemStruct LearnMenuItem[LoadCount * 2 + 1];
char LearnMenuItemText[LoadCount * 2][16];
MenuStruct LearnStepMenu;
MenuItemStruct LearnStepMenuItem[2];

void LoadRecogniseUpdateMenuText(void);
void LoadRecogniseUpdateHardware(void);

bool LoadRecogniseOutputEnable = true;
bool Learn = false;
u8 LearnChannel = 0;
u8 LearnStep = 0;
#define LearnCharisticCount 10
LoadCharacteristic LearnCharacteristic[LearnCharisticCount];

UniGPIO_Handle LoadRecogniseOutputRelayHandle;

#define LoadBoxBackgroundOn "LoadON.SP"
#define LoadBoxBackgroundOff "LoadOFF.SP"

bool LoadRecogniseLearnProcess(void);

class LoadRecognise_EVENT :public WINEVENT
{
private:
	//Override those methods to handle messages
	virtual bool OnKeyPress(WINDOW* Win, KEYCODE Key);
	virtual bool OnPaint(WINDOW* Win);
};

void LoadRecogniseMenuCallback(struct MenuItemStruct* MenuItem, MenuItemMessage Msg, u32 Param)
{
	if (Msg == ItemPress)
	{
		switch (MenuItem->Tag)
		{
		case 0:
			if (LoadRecogniseOutputEnable)
			{
				LoadRecogniseOutputEnable = false;
				LoadRecogniseUpdateMenuText();
				LoadRecogniseUpdateHardware();
			}
			else
			{
				MENU * GlobalMenu = GetGlobalMenu();
				GlobalMenu->EnterMenu(&PowerOnConfirmMenu);
				FreeAndEraseReference(GlobalMenu);
			}
			break;
		case 1:
		{
			MENU * GlobalMenu = GetGlobalMenu();
			GlobalMenu->EnterMenu(&LearnMenu);
			FreeAndEraseReference(GlobalMenu);
		}
		break;
		default:
			break;
		}
	}
}

void PowerOnConfirmMenuCallback(struct MenuItemStruct* MenuItem, MenuItemMessage Msg, u32 Param)
{
	if (Msg == ItemPress)
	{
		switch (MenuItem->Tag)
		{
		case 0:
		{
			MENU * GlobalMenu = GetGlobalMenu();
			GlobalMenu->ExitMenu();
			FreeAndEraseReference(GlobalMenu);
			LoadRecogniseOutputEnable = true;
			LoadRecogniseUpdateMenuText();
			LoadRecogniseUpdateHardware();
		}
		break;
		case 1:
		{
			MENU * GlobalMenu = GetGlobalMenu();
			GlobalMenu->ExitMenu();
			FreeAndEraseReference(GlobalMenu);
		}
		break;
		default:
			break;
		}
	}
}

void LearnMenuCallback(struct MenuItemStruct* MenuItem, MenuItemMessage Msg, u32 Param)
{
	if (Msg == ItemPress)
	{
		if (MenuItem->Tag < LoadCount)
		{
			Learn = true;
			LearnChannel = MenuItem->Tag;
			LearnStep = 0;
			MENU * GlobalMenu = GetGlobalMenu();
			GlobalMenu->EnterMenu(&LearnStepMenu);
			FreeAndEraseReference(GlobalMenu);
			PostMessage(LoadRecognise_Win, WM_PAINT, 0, 0);
		}
		else if (MenuItem->Tag < LoadCount * 2)
		{
			LoadRecogniseEngine_Remove(MenuItem->Tag - LoadCount);
		}
		else
		{
			LoadRecogniseEngine_SaveData();
			Beep(100);
			MENU * GlobalMenu = GetGlobalMenu();
			GlobalMenu->ExitMenu();
			FreeAndEraseReference(GlobalMenu);
			Learn = false;
		}
	}
}

void LearnStepMenuCallback(struct MenuItemStruct* MenuItem, MenuItemMessage Msg, u32 Param)
{
	if (Msg == ItemPress)
	{
		switch (MenuItem->Tag)
		{
		case 0:
		{
			Beep(100);
			while (!LoadRecogniseLearnProcess());
			LoadRecogniseCharacteristicProvider_CalcSpectrumCharacteristic(LoadRecogniseSampler_GetCurrentData(), LoadRecogniseSampler_GetVoltageData());
			LoadRecogniseCharacteristicProvider_SynthesizeCharacteristicRecord(LearnStep % 2 == 0 ? true : false, true);
			LoadRecogniseCharacteristicProvider_GetCharacteristicRecord(&LearnCharacteristic[LearnStep]);
			Beep(100);

			PostMessage(LoadRecognise_Win, WM_PAINT, 0, 0);

			LearnStep++;
			if (LearnStep == LearnCharisticCount)
			{
				LoadRecogniseEngine_Learn(LearnChannel, &LearnCharacteristic[1], LearnCharisticCount - 1);
				MENU * GlobalMenu = GetGlobalMenu();
				GlobalMenu->ExitMenu();
				FreeAndEraseReference(GlobalMenu);
			}
		}
		break;
		case 1:
		{
			MENU * GlobalMenu = GetGlobalMenu();
			GlobalMenu->ExitMenu();
			FreeAndEraseReference(GlobalMenu);
			PostMessage(LoadRecognise_Win, WM_PAINT, 0, 0);
		}
		break;
		default:
			break;
		}
	}
}

void LoadRecogniseUpdateMenuText(void)
{
	MENU* GlobalMenu = GetGlobalMenu();

	LoadRecogniseMenuItem[0].SubCaption = LoadRecogniseOutputEnable ? "输出" : "断开";

	GlobalMenu->UpdateItems();
	FreeAndEraseReference(GlobalMenu);
}

void LoadRecogniseUpdateHardware(void)
{
	UniGPIO_SetVal(&LoadRecogniseOutputRelayHandle, LoadRecogniseOutputEnable);
}

void CreateLoadRecogniseMenu(void)
{
	MENU* GlobalMenu = GetGlobalMenu();

	LoadRecogniseMenu.ItemCount = sizeof(LoadRecogniseMenuItem) / sizeof(LoadRecogniseMenuItem[0]);
	LoadRecogniseMenu.Items = LoadRecogniseMenuItem;
	LoadRecogniseMenu.MenuCaption = "单相用电器分析监测";
	LoadRecogniseMenu.CallBack = NULL;

	LoadRecogniseMenuItem[0].Caption = "输出开关";
	LoadRecogniseMenuItem[0].Enabled = true;
	LoadRecogniseMenuItem[0].CallBack = LoadRecogniseMenuCallback;
	LoadRecogniseMenuItem[0].Style = ButtonItem;
	LoadRecogniseMenuItem[0].SubCaption = LoadRecogniseOutputEnable ? "输出" : "断开";
	LoadRecogniseMenuItem[0].Tag = 0;

	LoadRecogniseMenuItem[1].Caption = "学习";
	LoadRecogniseMenuItem[1].Enabled = true;
	LoadRecogniseMenuItem[1].CallBack = LoadRecogniseMenuCallback;
	LoadRecogniseMenuItem[1].Style = ButtonItem;
	LoadRecogniseMenuItem[1].SubCaption = NULL;
	LoadRecogniseMenuItem[1].Tag = 1;

	PowerOnConfirmMenu.ItemCount = sizeof(PowerOnConfirmMenuItem) / sizeof(PowerOnConfirmMenuItem[0]);
	PowerOnConfirmMenu.Items = PowerOnConfirmMenuItem;
	PowerOnConfirmMenu.MenuCaption = "确认接通电源？";
	PowerOnConfirmMenu.CallBack = NULL;

	PowerOnConfirmMenuItem[0].Caption = "确认";
	PowerOnConfirmMenuItem[0].Enabled = true;
	PowerOnConfirmMenuItem[0].CallBack = PowerOnConfirmMenuCallback;
	PowerOnConfirmMenuItem[0].Style = ButtonItem;
	PowerOnConfirmMenuItem[0].SubCaption = NULL;
	PowerOnConfirmMenuItem[0].Tag = 0;

	PowerOnConfirmMenuItem[1].Caption = "取消";
	PowerOnConfirmMenuItem[1].Enabled = true;
	PowerOnConfirmMenuItem[1].CallBack = PowerOnConfirmMenuCallback;
	PowerOnConfirmMenuItem[1].Style = ReturnItem;
	PowerOnConfirmMenuItem[1].SubCaption = NULL;
	PowerOnConfirmMenuItem[1].Tag = 1;

	LearnMenu.ItemCount = sizeof(LearnMenuItem) / sizeof(LearnMenuItem[0]);
	LearnMenu.Items = LearnMenuItem;
	LearnMenu.MenuCaption = "学习负载";
	LearnMenu.CallBack = NULL;

	for (u8 i = 0; i < LoadCount; i++)
	{
		sprintf(LearnMenuItemText[i], "学习%d", i);
		LearnMenuItem[i].Caption = LearnMenuItemText[i];
		LearnMenuItem[i].Enabled = true;
		LearnMenuItem[i].CallBack = LearnMenuCallback;
		LearnMenuItem[i].Style = ButtonItem;
		LearnMenuItem[i].SubCaption = NULL;
		LearnMenuItem[i].Tag = i;

		sprintf(LearnMenuItemText[LoadCount + i], "删除%d", i);
		LearnMenuItem[LoadCount + i].Caption = LearnMenuItemText[LoadCount + i];
		LearnMenuItem[LoadCount + i].Enabled = true;
		LearnMenuItem[LoadCount + i].CallBack = LearnMenuCallback;
		LearnMenuItem[LoadCount + i].Style = ButtonItem;
		LearnMenuItem[LoadCount + i].SubCaption = NULL;
		LearnMenuItem[LoadCount + i].Tag = LoadCount + i;
	}
	LearnMenuItem[2 * LoadCount].Caption = "完成";
	LearnMenuItem[2 * LoadCount].Enabled = true;
	LearnMenuItem[2 * LoadCount].CallBack = LearnMenuCallback;
	LearnMenuItem[2 * LoadCount].Style = ReturnItem;
	LearnMenuItem[2 * LoadCount].SubCaption = NULL;
	LearnMenuItem[2 * LoadCount].Tag = 2 * LoadCount;

	LearnStepMenu.ItemCount = sizeof(LearnStepMenuItem) / sizeof(LearnStepMenuItem[0]);
	LearnStepMenu.Items = LearnStepMenuItem;
	LearnStepMenu.MenuCaption = "采集特征";
	LearnStepMenu.CallBack = NULL;

	LearnStepMenuItem[0].Caption = "下一步";
	LearnStepMenuItem[0].Enabled = true;
	LearnStepMenuItem[0].CallBack = LearnStepMenuCallback;
	LearnStepMenuItem[0].Style = ButtonItem;
	LearnStepMenuItem[0].SubCaption = NULL;
	LearnStepMenuItem[0].Tag = 0;

	LearnStepMenuItem[1].Caption = "取消";
	LearnStepMenuItem[1].Enabled = true;
	LearnStepMenuItem[1].CallBack = LearnStepMenuCallback;
	LearnStepMenuItem[1].Style = ReturnItem;
	LearnStepMenuItem[1].SubCaption = NULL;
	LearnStepMenuItem[1].Tag = 1;

	LoadRecogniseUpdateMenuText();

	GlobalMenu->EnterMenu(&LoadRecogniseMenu);
	FreeAndEraseReference(GlobalMenu);
}

void LoadRecogniseCreateWin(void)
{
	WINDOW* ScrWin = SCREENWINDOW::GetScreenWindow();
	GUIPOS ScrWidth = 0;
	GUIPOS ScrHeight = 0;
	ScrWin->GetWindowPos(NULL, NULL, &ScrWidth, &ScrHeight);
	FreeAndEraseReference(ScrWin);
	LoadRecognise_Win = new_noexcpt WINDOW(NULL, 0, 0, ScrWidth - MENU::GetMenuWidth(), ScrHeight, false);
	WINEVENT* Event = new_noexcpt LoadRecognise_EVENT();
	LoadRecognise_Win->LinkEventHandler(Event);
	LoadRecognise_Win->SetCaption("LoadRecogniseWin");
	DC* DrawingDC = LoadRecognise_Win->GetDC();
	DrawingDC->Fill(0, 0, DrawingDC->GetWidth(), DrawingDC->GetHeight(), BLACK);
	FreeAndEraseReference(DrawingDC);
}

bool LoadRecogniseLearnProcess(void)
{
	static u8 Phase = 0;
	switch (Phase)
	{
	case 0:
		LoadRecogniseSampler_Sample();
		break;
	case 5:
		LoadRecogniseCharacteristicProvider_Scale(LoadRecogniseSampler_GetCurrentData(), LoadRecogniseSampler_GetVoltageData());
		break;
	case 10:
		LoadRecogniseCharacteristicProvider_CalcBasicCharacteristic(LoadRecogniseSampler_GetCurrentData(), LoadRecogniseSampler_GetVoltageData());
		break;
	case 15:
		PostMessage(LoadRecognise_Win, WM_PAINT, 0, 0);
		Phase = 0;
		return true;
		break;
	}
	Phase++;
	return false;
}

void LoadRecogniseProcess(void)
{
	static u8 Phase = 0;
	if (Learn)
	{
		Phase = 0;
		LoadRecogniseLearnProcess();
	}
	else
	{
		switch (Phase)
		{
		case 0:
			LoadRecogniseSampler_Sample();
			break;
		case 5:
			LoadRecogniseCharacteristicProvider_Scale(LoadRecogniseSampler_GetCurrentData(), LoadRecogniseSampler_GetVoltageData());
			break;
		case 10:
			LoadRecogniseCharacteristicProvider_CalcBasicCharacteristic(LoadRecogniseSampler_GetCurrentData(), LoadRecogniseSampler_GetVoltageData());
			{
				float CurrentRMS = 0.0;
				LoadRecogniseCharacteristicProvider_GetBasicCharacteristic(&CurrentRMS, NULL, NULL);
				if (CurrentRMS > 11.0)
				{
					LoadRecogniseOutputEnable = false;
					LoadRecogniseUpdateMenuText();
					LoadRecogniseUpdateHardware();
					Beep(1000);
				}
			}
			break;
		case 15:
			LoadRecogniseCharacteristicProvider_CalcSpectrumCharacteristic(LoadRecogniseSampler_GetCurrentData(), LoadRecogniseSampler_GetVoltageData());
			break;
		case 20:
			LoadRecogniseCharacteristicProvider_SynthesizeCharacteristicRecord(false, false);
			break;
		case 25:
			LoadRecogniseEngine_CheckStateChange();
			break;
		case 30:
			PostMessage(LoadRecognise_Win, WM_PAINT, 0, 0);
			Phase = 255;
			break;
		}
		Phase++;
	}
}

void lllllllllllTaskLauncher(void)
{
	LoadRecogniseSampler_Init();
	LoadRecogniseCharacteristicProvider_Init();
	LoadRecogniseEngine_LoadData();
	LoadRecogniseCreateWin();
	CreateLoadRecogniseMenu();
	GPIO_CPLD_InitPin(1, 0, true, &LoadRecogniseOutputRelayHandle);
	LoadRecogniseUpdateHardware();
	while (1)
	{
		LoadRecogniseProcess();
		DoMessageLoop();
	}
}

bool LoadRecognise_EVENT::OnKeyPress(WINDOW * Win, KEYCODE Key)
{
	return true;
}

void DrawLoadBox(DC* DrawingDC, GUIPOS X, GUIPOS Y, GUIPOS Width, GUIPOS Height, pstr Name, bool State)
{
	CLIPPEDDC* CDC = NewReferenceSafe(new_noexcpt CLIPPEDDC(DrawingDC, X, Y, X + Width, Y + Height, false, false));
	GUIPOS DrawWidth = CDC->GetWidth();
	GUIPOS DrawHeight = CDC->GetHeight();
	GUIPOS EstWidth = 0;
	GUIPOS EstHeight = 0;
	FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC48;HZK48S;HZK48T"));
	FLASHFSPIC BackGround(State ? LoadBoxBackgroundOn : LoadBoxBackgroundOff);
	//CDC->Fill(0, 0, DrawWidth, DrawHeight, DGRAY);
	BackGround.Draw(CDC, 0, 0);
	EstimateStringHorizontal(CDC, FG, Name, 0, 0, DrawWidth, DrawHeight, &EstWidth, &EstHeight);
	DrawStringHorizontal(CDC, FG, Name, (DrawWidth - EstWidth) / 2, (DrawHeight - EstHeight) / 2, 0, 0, State ? GREEN : DGREEN, TransparentColorKey);
	FreeAndEraseReference(FG);
	FreeAndEraseReference(CDC);
}

#include "Algorithm\AlgorithmTypes.h"
#include "User\LoadRecogniseSampler.h"
#include <math.h>
extern float* SampleBuffer[2];
extern float* FFTBuffer;

bool LoadRecognise_EVENT::OnPaint(WINDOW * Win)
{
	DC* DrawingDC = Win->GetDC();
	FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC48;HZK48S;HZK48T"));

	//DrawingDC->Fill(0, 0, DrawingDC->GetWidth(), DrawingDC->GetHeight(), BLACK);

	float CurrentRMS = 0.0;
	float VoltageRMS = 0.0;
	float Power = 0.0;
	char sbuf[128];
	LoadRecogniseCharacteristicProvider_GetBasicCharacteristic(&CurrentRMS, &VoltageRMS, &Power);
	sprintf(sbuf, "电流：     %-#8.3f  ", CurrentRMS);
	DrawStringHorizontal(DrawingDC, FG, sbuf, 10, 10 + 50 * 0, 0, 0, GREEN, BLACK);
	sprintf(sbuf, "电压：     %-#8.3f  ", VoltageRMS);
	DrawStringHorizontal(DrawingDC, FG, sbuf, 10, 10 + 50 * 1, 0, 0, YELLOW, BLACK);
	sprintf(sbuf, "有功功率： %-#8.3f  ", Power);
	DrawStringHorizontal(DrawingDC, FG, sbuf, 10, 10 + 50 * 2, 0, 0, RED, BLACK);
	sprintf(sbuf, "视在功率： %-#8.3f  ", CurrentRMS * VoltageRMS);
	DrawStringHorizontal(DrawingDC, FG, sbuf, 10, 10 + 50 * 3, 0, 0, WHITE, BLACK);
	sprintf(sbuf, "功率因数： %-#8.3f  ", Power / (CurrentRMS * VoltageRMS));
	DrawStringHorizontal(DrawingDC, FG, sbuf, 10, 10 + 50 * 4, 0, 0, WHITE, BLACK);
	if (LoadRecogniseCharacteristicProvider_CheckStable())
	{
		DrawStringHorizontal(DrawingDC, FG, "稳态", 10, 10 + 50 * 5, 0, 0, BLACK, GREEN);
	}
	else
	{
		DrawStringHorizontal(DrawingDC, FG, "瞬态", 10, 10 + 50 * 5, 0, 0, WHITE, RED);
	}

	if (Learn)
	{
		if (LearnStep % 2 == 0)
		{
			DrawStringHorizontal(DrawingDC, FG, "断开用电器后选择下一步菜单", 10, 10 + 50 * 6, 0, 0, WHITE, BLACK);
		}
		else
		{
			DrawStringHorizontal(DrawingDC, FG, "接通用电器后选择下一步菜单", 10, 10 + 50 * 6, 0, 0, WHITE, BLACK);
		}
	}
	else
	{
		DrawStringHorizontal(DrawingDC, FG, "                            ", 10, 10 + 50 * 6, 0, 0, WHITE, BLACK);
	}

	for (u8 i = 0; i < LoadCount; i++)
	{
		sprintf(sbuf, "负载%d", i);
		DrawLoadBox(DrawingDC, 142 * i, 10 + 50 * 7 + 30, 140, 70, sbuf, LoadRecogniseEngine_GetState(i));
	}
	/*
		GUIPOS DrawWidth = DrawingDC->GetWidth();
		GUIPOS 	DrawHeight = DrawingDC->GetHeight();

		for (u32 i = 0; i < LoadRecogniseFFTSize / 2; i += 1)
		{
			DrawingDC->SetPixel(i * DrawWidth * 2 / LoadRecogniseFFTSize, DrawHeight * (0.8 - log(FFTBuffer[2 * i] * FFTBuffer[2 * i] + FFTBuffer[2 * i + 1] * FFTBuffer[2 * i + 1]) / 40), RED);
		}


		for (u32 i = 0; i < LoadRecogniseSampleBufferSize; i += 1)
		{
			DrawingDC->SetPixel(i * DrawWidth / LoadRecogniseSampleBufferSize, DrawHeight * (0.5 - SampleBuffer[0][i] / 5), RED);
		}*/
	FreeAndEraseReference(FG);
	FreeAndEraseReference(DrawingDC);
	return false;
}
