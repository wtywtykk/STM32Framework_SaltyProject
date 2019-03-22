#include "HAL\HCommon.h"
#include "Kernel\Common\KCommon.h"
#include "Kernel\GUI\Window\Window.h"
#include "Kernel\GUI\Window\ScreenWindow.h"
#include "Kernel\GUI\Window\WinEvent.h"
#include "Kernel\GUI\Window\WindowManager.h"
#include "Kernel\GUI\Menu\Menu.h"
#include "Kernel\GUI\Menu\GlobalMenu.h"
#include "Kernel\GUI\Text\DrawString.h"
#include "HAL\StandardSPIPort.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Kernel\GUI\InputBox\InputBox.h"
#include "Driver\AD9959.h"
#include "MultiInstDriver\ADF4351.h"
#include "MultiInstDriver\PE43711.h"
#include "User\BodePlotterScanEngine.h"
#include "User\BodePlotterDataStore.h"
#include "User\BodePlotterGraphic.h"
#include "User\BodePlotterFPGAAbstrast.h"
#include "Kernel\GUI\Shape\Line.h"
#include "User\BodePlotterCalibration.h"
#include "User\BodePlotterCursor.h"
#include <arm_math.h>

const float BodePlotter_FreqLowerLimit = 10.0e3;
const float BodePlotter_FreqUpperLimit = 230.0e6;
const float BodePlotter_AmplitudeLowerLimit = 1e-3;
const float BodePlotter_AmplitudeUpperLimit = 200e-3;
const float BodePlotter_MinPointLimit = 3;
const float BodePlotter_MaxPointLimit = 2048;
const u32 BodePlotter_CursorCount = 5;

const float BodePlotter_PllRef = 21.3456e6;
const float BodePlotter_PllPD = BodePlotter_PllRef;

WINDOW* BodePlotter_Win = NULL;

MenuStruct BodePlotterTopMenu;
MenuItemStruct BodePlotterTopMenuItem[4];

MenuStruct BodePlotterFreqMenu;
MenuItemStruct BodePlotterFreqMenuItem[4];

MenuStruct BodePlotterScanMenu;
MenuItemStruct BodePlotterScanMenuItem[3];

MenuStruct BodePlotterAmptMenu;
MenuItemStruct BodePlotterAmptMenuItem[4];

MenuStruct BodePlotterCursorMenu;
MenuItemStruct BodePlotterCursorMenuItem[5];

typedef enum
{
	Linear,
	Logarithmic,
}BodePlotter_AsixType;

char BodePlotter_FreqCenterBuf[32];
char BodePlotter_FreqStartBuf[32];
char BodePlotter_FreqEndBuf[32];
char BodePlotter_FreqSpanBuf[32];

char BodePlotter_FreqStepBuf[32];
char BodePlotter_FreqPointBuf[32];
char BodePlotter_FreqAxisBuf[32];

char BodePlotter_AmptitudeBuf[32];
char BodePlotter_AmptitudeBaseBuf[32];
char BodePlotter_AmptitudeDivBuf[32];
char BodePlotter_AmptitudeAxisBuf[32];

char BodePlotter_CursorTableBuf[32];
char BodePlotter_CursorSelBuf[32];
char BodePlotter_CursorFuncBuf[32];
char BodePlotter_CursorCustonBuf0[32];
char BodePlotter_CursorCustonBuf1[32];


float BodePlotter_FreqStart;
float BodePlotter_FreqEnd;

u32 BodePlotter_FreqPoint;
BodePlotter_AsixType BodePlotter_FreqAxis;

float BodePlotter_Amptitude;
float BodePlotter_AmptitudeBase;
float BodePlotter_AmptitudeDiv;
BodePlotter_AsixType BodePlotter_AmptitudeAxis;

bool BodePlotter_CursorTable;
u32 BodePlotter_CursorSel;
BodePlotter_Cursor BodePlotter_Cursors[BodePlotter_CursorCount];

BodePlotterScanEngine BodePlotter_ScanEngine;

BodePlotterDataStore* LastFullScanData = NULL;
BodePlotterDataStore* CurrentScanData = NULL;

BodePlotterGraphic BodePlotter_Graphic;

BodePlotterFPGAAbstrast BodePlotter_FPGA;

ADF4351_Handle BodePlotter_ADF4351Handle;

PE43711_Handle BodePoltter_Out0PE43711Handle;
PE43711_Handle BodePoltter_Out1PE43711Handle;

pcstr BodePlotter_FreqSetOptions[] = {
	"Hz",
	"kHz",
	"MHz",
	"取消",
};

pcstr BodePlotter_AmplitudeSetOptions[] = {
	"mVrms",
	"Vrms",
	"dBm",
	"-dBm",
	"取消",
};

pcstr BodePlotter_NumberSetOptions[] = {
	"确定",
	"取消",
};

pcstr BodePlotter_RatioSetOptions[] = {
	"线性",
	"dB",
	"-dB",
	"取消",
};

arm_linear_interp_instance_f32 BodePlotter_InputCaliInterp;

void BodePlotter_UpdateAllMenus(void);
void BodePlotter_StartScan(void);

class BodePlotter_EVENT :public WINEVENT
{
private:
	//Override those methods to handle messages
	virtual bool OnKeyPress(WINDOW* Win, KEYCODE Key);
	virtual bool OnPaint(WINDOW* Win);
};

bool BodePlotter_InputFrequency(float* Val, float LowerBound, float UpperBound)
{
	char Buf[255];
	float TempVal = 0.0;
	u32 SelOption = 0;
	InputBox(Buf, 255, BodePlotter_FreqSetOptions, sizeof(BodePlotter_FreqSetOptions) / sizeof(BodePlotter_FreqSetOptions[0]), &SelOption);
	if (SelOption == 3)
	{
		return false;
	}
	sscanf(Buf, "%f", &TempVal);
	switch (SelOption)
	{
	case 0://Hz
		TempVal *= 1.0;
		break;
	case 1://kHz
		TempVal *= 1.0e3;
		break;
	case 2://MHz
		TempVal *= 1.0e6;
		break;
	case 3://Cancel
		break;
	}
	if (TempVal < LowerBound)
	{
		TempVal = LowerBound;
	}
	if (TempVal > UpperBound)
	{
		TempVal = UpperBound;
	}
	*Val = TempVal;
	return true;
}

bool BodePlotter_InputAmplitude(float* Val, float LowerBound, float UpperBound)
{
	char Buf[255];
	float TempVal = 0.0;
	u32 SelOption = 0;
	InputBox(Buf, 255, BodePlotter_AmplitudeSetOptions, sizeof(BodePlotter_AmplitudeSetOptions) / sizeof(BodePlotter_AmplitudeSetOptions[0]), &SelOption);
	if (SelOption == 4)
	{
		return false;
	}
	sscanf(Buf, "%f", &TempVal);
	switch (SelOption)
	{
	case 0://mVrms
		TempVal *= 1.0e-3;
		break;
	case 1://Vrms
		TempVal *= 1.0;
		break;
	case 2://dBm
		TempVal = sqrt((pow(10, TempVal / 10) * 1.0e-3) * 50);
		break;
	case 3://-dBm
		TempVal = sqrt((pow(10, -TempVal / 10) * 1.0e-3) * 50);
		break;
	case 4://Cancel
		break;
	}
	if (TempVal < LowerBound)
	{
		TempVal = LowerBound;
	}
	if (TempVal > UpperBound)
	{
		TempVal = UpperBound;
	}
	*Val = TempVal;
	return true;
}

bool BodePlotter_InputNumber(float* Val, float LowerBound, float UpperBound)
{
	char Buf[255];
	float TempVal = 0.0;
	u32 SelOption = 0;
	InputBox(Buf, 255, BodePlotter_NumberSetOptions, sizeof(BodePlotter_NumberSetOptions) / sizeof(BodePlotter_NumberSetOptions[0]), &SelOption);
	if (SelOption == 1)
	{
		return false;
	}
	sscanf(Buf, "%f", &TempVal);
	if (TempVal < LowerBound)
	{
		TempVal = LowerBound;
	}
	if (TempVal > UpperBound)
	{
		TempVal = UpperBound;
	}
	*Val = TempVal;
	return true;
}

bool BodePlotter_InputRatio(float* Val, float LowerBound, float UpperBound)
{
	char Buf[255];
	float TempVal = 0.0;
	u32 SelOption = 0;
	InputBox(Buf, 255, BodePlotter_RatioSetOptions, sizeof(BodePlotter_RatioSetOptions) / sizeof(BodePlotter_RatioSetOptions[0]), &SelOption);
	if (SelOption == 3)
	{
		return false;
	}
	sscanf(Buf, "%f", &TempVal);
	switch (SelOption)
	{
	case 0://Linear
		break;
	case 1://dB
		TempVal = pow(10, TempVal / 20);
		break;
	case 2://-dB
		TempVal = pow(10, -TempVal / 20);
		break;
	case 3://Cancel
		break;
	}
	if (TempVal < LowerBound)
	{
		TempVal = LowerBound;
	}
	if (TempVal > UpperBound)
	{
		TempVal = UpperBound;
	}
	*Val = TempVal;
	return true;
}

void BodePlotter_TopMenuCallback(struct MenuItemStruct* MenuItem, MenuItemMessage Msg, u32 Param)
{
	if (Msg == ItemPress)
	{
		MENU * GlobalMenu = GetGlobalMenu();
		switch (MenuItem->Tag)
		{
		case 0:
			GlobalMenu->EnterMenu(&BodePlotterFreqMenu);
			break;
		case 1:
			GlobalMenu->EnterMenu(&BodePlotterScanMenu);
			break;
		case 2:
			GlobalMenu->EnterMenu(&BodePlotterAmptMenu);
			break;
		case 3:
			GlobalMenu->EnterMenu(&BodePlotterCursorMenu);
			break;
		default:
			break;
		}
		FreeAndEraseReference(GlobalMenu);
	}
}

void BodePlotter_FreqMenuCallback(struct MenuItemStruct* MenuItem, MenuItemMessage Msg, u32 Param)
{
	if (Msg == ItemPress)
	{
		switch (MenuItem->Tag)
		{
		case 0:
		{
			float NewCenter = 0;
			if (BodePlotter_InputFrequency(&NewCenter, BodePlotter_FreqLowerLimit, BodePlotter_FreqUpperLimit))
			{
				float Span = BodePlotter_FreqEnd - BodePlotter_FreqStart;
				BodePlotter_FreqStart = NewCenter - Span / 2;
				BodePlotter_FreqEnd = NewCenter + Span / 2;
				if (BodePlotter_FreqStart < BodePlotter_FreqLowerLimit)
				{
					BodePlotter_FreqStart = BodePlotter_FreqLowerLimit;
				}
				if (BodePlotter_FreqEnd > BodePlotter_FreqUpperLimit)
				{
					BodePlotter_FreqEnd = BodePlotter_FreqUpperLimit;
				}
				BodePlotter_StartScan();
			}
		}
		break;
		case 1:
			if (BodePlotter_InputFrequency(&BodePlotter_FreqStart, BodePlotter_FreqLowerLimit, BodePlotter_FreqEnd))
			{
				BodePlotter_StartScan();
			}
			break;
		case 2:
			if (BodePlotter_InputFrequency(&BodePlotter_FreqEnd, BodePlotter_FreqStart, BodePlotter_FreqUpperLimit))
			{
				BodePlotter_StartScan();
			}
			break;
		case 3:
		{
			float NewSpan = 0;
			if (BodePlotter_InputFrequency(&NewSpan, BodePlotter_FreqLowerLimit, BodePlotter_FreqUpperLimit))
			{
				float Center = (BodePlotter_FreqStart + BodePlotter_FreqEnd) / 2;
				BodePlotter_FreqStart = Center - NewSpan / 2;
				BodePlotter_FreqEnd = Center + NewSpan / 2;
				if (BodePlotter_FreqStart < BodePlotter_FreqLowerLimit)
				{
					BodePlotter_FreqStart = BodePlotter_FreqLowerLimit;
				}
				if (BodePlotter_FreqEnd > BodePlotter_FreqUpperLimit)
				{
					BodePlotter_FreqEnd = BodePlotter_FreqUpperLimit;
				}
				BodePlotter_StartScan();
			}
		}
		break;
		}
		BodePlotter_UpdateAllMenus();
	}
}

void BodePlotter_ScanMenuCallback(struct MenuItemStruct* MenuItem, MenuItemMessage Msg, u32 Param)
{
	if (Msg == ItemPress)
	{
		switch (MenuItem->Tag)
		{
		case 0:
		{
			float NewStep = 0;
			if (BodePlotter_InputFrequency(&NewStep, BodePlotter_FreqLowerLimit, BodePlotter_FreqUpperLimit))
			{
				BodePlotter_FreqPoint = (BodePlotter_FreqEnd - BodePlotter_FreqStart) / NewStep + 1;
				if (BodePlotter_FreqPoint < BodePlotter_MinPointLimit)
				{
					BodePlotter_FreqPoint = BodePlotter_MinPointLimit;
				}
				if (BodePlotter_FreqPoint > BodePlotter_MaxPointLimit)
				{
					BodePlotter_FreqPoint = BodePlotter_MaxPointLimit;
				}
				BodePlotter_StartScan();
			}
		}
		break;
		case 1:
		{
			float NewPoint = 0;
			if (BodePlotter_InputNumber(&NewPoint, BodePlotter_MinPointLimit, BodePlotter_MaxPointLimit))
			{
				BodePlotter_FreqPoint = NewPoint;
				if (BodePlotter_FreqPoint < BodePlotter_MinPointLimit)
				{
					BodePlotter_FreqPoint = BodePlotter_MinPointLimit;
				}
				if (BodePlotter_FreqPoint > BodePlotter_MaxPointLimit)
				{
					BodePlotter_FreqPoint = BodePlotter_MaxPointLimit;
				}
				BodePlotter_StartScan();
			}
		}
		break;
		case 2:
			if (BodePlotter_FreqAxis == Linear)
			{
				BodePlotter_FreqAxis = Logarithmic;
			}
			else
			{
				BodePlotter_FreqAxis = Linear;
			}
			break;
		}
		BodePlotter_UpdateAllMenus();
	}
}

void BodePlotter_AmptMenuCallback(struct MenuItemStruct* MenuItem, MenuItemMessage Msg, u32 Param)
{
	if (Msg == ItemPress)
	{
		switch (MenuItem->Tag)
		{
		case 0:
			BodePlotter_InputAmplitude(&BodePlotter_Amptitude, BodePlotter_AmplitudeLowerLimit, BodePlotter_AmplitudeUpperLimit);
			break;
		case 1:
			BodePlotter_InputRatio(&BodePlotter_AmptitudeBase, 0.00001, 10000);
			break;
		case 2:
			BodePlotter_InputRatio(&BodePlotter_AmptitudeDiv, 0.00001, 10000);
			break;
		case 3:
			if (BodePlotter_AmptitudeAxis == Linear)
			{
				BodePlotter_AmptitudeAxis = Logarithmic;
			}
			else
			{
				BodePlotter_AmptitudeAxis = Linear;
			}
			break;
		}
		BodePlotter_UpdateAllMenus();
	}
}

void BodePlotter_CursorMenuCallback(struct MenuItemStruct* MenuItem, MenuItemMessage Msg, u32 Param)
{
	if (Msg == ItemPress)
	{
		switch (MenuItem->Tag)
		{
		case 0:
			break;
		case 1:
			BodePlotter_CursorSel++;
			if (BodePlotter_CursorSel > BodePlotter_CursorCount)
			{
				BodePlotter_CursorSel = 0;
			}
			break;
		case 2:
			switch (BodePlotter_Cursors[BodePlotter_CursorSel].Type)
			{
			default:
			case Unused:
				BodePlotter_Cursors[BodePlotter_CursorSel].Type = Normal;
				break;
			case Normal:
				BodePlotter_Cursors[BodePlotter_CursorSel].Type = Delta;
				break;
			case Delta:
				BodePlotter_Cursors[BodePlotter_CursorSel].Type = Unused;
				break;
			}
			break;
		case 3:
		case 4:
			switch (BodePlotter_Cursors[BodePlotter_CursorSel].Type)
			{
			case Unused:
				break;
			case Normal:
				switch (MenuItem->Tag)
				{
				case 3:
					break;
				case 4:
					break;
				}
				break;
			case Delta:
				switch (MenuItem->Tag)
				{
				case 3:
					BodePlotter_Cursors[BodePlotter_CursorSel].DeltaData.Cursors[0]++;
					if (BodePlotter_Cursors[BodePlotter_CursorSel].DeltaData.Cursors[0] > BodePlotter_CursorCount)
					{
						BodePlotter_Cursors[BodePlotter_CursorSel].DeltaData.Cursors[0] = 0;
					}
					break;
				case 4:
					BodePlotter_Cursors[BodePlotter_CursorSel].DeltaData.Cursors[1]++;
					if (BodePlotter_Cursors[BodePlotter_CursorSel].DeltaData.Cursors[1] > BodePlotter_CursorCount)
					{
						BodePlotter_Cursors[BodePlotter_CursorSel].DeltaData.Cursors[1] = 0;
					}
					break;
				}
				break;
			}
			break;
		}
		BodePlotter_UpdateAllMenus();
	}
}

void BodePlotter_ConvertDispFreq(pstr Buf, float Val)
{
	pcstr UnitTable[] = { "Hz","kHz","MHz" };
	u8 i = 0;
	while (Val >= 1000.0)
	{
		Val /= 1000.0;
		i++;
		if (i + 1 == sizeof(UnitTable) / sizeof(UnitTable[0]))
		{
			break;
		}
	}
	sprintf(Buf, "%4.2f %s", Val, UnitTable[i]);
}

void BodePlotter_ConvertDispVoltage(pstr Buf, float Val)
{
	if (BodePlotter_AmptitudeAxis == Linear)
	{
		pcstr UnitTable[] = { "mV","V" };
		u8 i = 0;
		Val *= 1000.0;
		while (Val >= 1000.0)
		{
			Val /= 1000.0;
			i++;
			if (i + 1 == sizeof(UnitTable) / sizeof(UnitTable[0]))
			{
				break;
			}
		}
		sprintf(Buf, "%4.2f %s", Val, UnitTable[i]);
	}
	else
	{
		float dBVal = 10 * log10(Val * Val / 50.0 / 1e-3);
		sprintf(Buf, "%4.2f dBm", dBVal);
	}
}

void BodePlotter_ConvertDispRatio(pstr Buf, float Val)
{
	if (BodePlotter_AmptitudeAxis == Linear)
	{
		sprintf(Buf, "%4.2f", Val);
	}
	else
	{
		float dBVal = 10 * log10(Val * Val);
		sprintf(Buf, "%4.2f dB", dBVal);
	}
}

void BodePlotter_ConvertDispAsix(pstr Buf, BodePlotter_AsixType Val)
{
	switch (Val)
	{
	default:
	case Linear:
		strcpy(Buf, "线性");
		break;
	case Logarithmic:
		strcpy(Buf, "对数");
		break;
	}
}

void BodePlotter_ConvertDispOnOff(pstr Buf, bool Val)
{
	if (Val)
	{
		strcpy(Buf, "打开");
	}
	else
	{
		strcpy(Buf, "关闭");
	}
}

void BodePlotter_ConvertDispCursorFunc(pstr Buf, BodePlotter_CursorType Val)
{
	switch (Val)
	{
	default:
	case Unused:
		strcpy(Buf, "关闭");
		break;
	case Normal:
		strcpy(Buf, "普通");
		break;
	case Delta:
		strcpy(Buf, "差值");
		break;
	}
}

void BodePlotter_InitADF4351(void)
{
	UniGPIO_Handle MOSIPin;
	UniGPIO_Handle SCKPin;
	UniGPIO_Handle LEPin;
	UniGPIO_Handle CEPin;
	UniGPIO_Handle LDPin;
	UniGPIO_Handle PDBRFPin;
	UniGPIO_Handle MuxOutPin;

	GPIO_CPLD_InitPin(1, 6, true, &MOSIPin);
	GPIO_CPLD_InitPin(1, 8, true, &SCKPin);
	GPIO_CPLD_InitPin(1, 0, true, &LEPin);
	GPIO_CPLD_InitPin(1, 1, true, &CEPin);
	GPIO_CPLD_InitPin(1, 3, false, &LDPin);
	GPIO_CPLD_InitPin(1, 4, true, &PDBRFPin);
	GPIO_CPLD_InitPin(1, 7, false, &MuxOutPin);
	ADF4351_Init(&BodePlotter_ADF4351Handle, 5.1, &MOSIPin, &SCKPin, &LEPin, &CEPin, &LDPin, &PDBRFPin, &MuxOutPin);
	ADF4351_SetPDFrequency(&BodePlotter_ADF4351Handle, BodePlotter_PllRef, BodePlotter_PllPD);
	ADF4351_PFD_ChargePump_Param CPParam;
	CPParam.AntibacklashPulseWidth = ABP_6ns_FRAC_N;
	CPParam.BandSelect = true;
	CPParam.ChargeCancelation = false;
	CPParam.ClkDividerMode = FastLockEnable;
	CPParam.ClockDivider = 10;
	CPParam.CSREnable = false;
	CPParam.Current = 0.3;
	CPParam.FeedBackSelect = FeedBack_Fundamental;
	CPParam.Polarity = true;
	CPParam.TriState = false;
	ADF4351_SetPFD_ChargePumpParam(&BodePlotter_ADF4351Handle, &CPParam);
	ADF4351_SetMuxOut(&BodePlotter_ADF4351Handle, DGND);
	ADF4351_SetModulus(&BodePlotter_ADF4351Handle, 4095);
	ADF4351_SetOutputAFrequency(&BodePlotter_ADF4351Handle, BodePlotter_PllRef, 100e6, true);
	ADF4351_SetOutputPower(&BodePlotter_ADF4351Handle, Pos5);
	ADF4351_SetAuxOutput(&BodePlotter_ADF4351Handle, false, AuxOut_Divided, Neg4);
	ADF4351_Misc_Param MiscParam;
	MiscParam.LowNoiseSpur = LowNoiseMode;
	MiscParam.MuteTillLockDetect = false;
	MiscParam.Perscaler = Prescaler89;
	ADF4351_SetMiscParam(&BodePlotter_ADF4351Handle, &MiscParam);
	ADF4351_Update(&BodePlotter_ADF4351Handle);
}

void BodePlotter_InitPE43711(PE43711_Handle* Handle, u8 Port)
{
	UniGPIO_Handle SIPin;
	UniGPIO_Handle CLKPin;
	UniGPIO_Handle LEPin;

	GPIO_CPLD_InitPin(Port, 1, true, &SIPin);
	GPIO_CPLD_InitPin(Port, 5, true, &CLKPin);
	GPIO_CPLD_InitPin(Port, 7, true, &LEPin);

	PE43711_Init(Handle, &SIPin, &CLKPin, &LEPin);
}

void BodePlotter_InitHardware(void)
{
	AD9959_SetChannelFrequency(0, BodePlotter_PllRef);
	BodePlotter_InitADF4351();
	BodePlotter_InitPE43711(&BodePoltter_Out0PE43711Handle, 2);
	BodePlotter_InitPE43711(&BodePoltter_Out1PE43711Handle, 3);
}

void BodePlotter_InitTopMenu(void)
{
	BodePlotterTopMenu.ItemCount = sizeof(BodePlotterTopMenuItem) / sizeof(BodePlotterTopMenuItem[0]);
	BodePlotterTopMenu.Items = BodePlotterTopMenuItem;
	BodePlotterTopMenu.MenuCaption = "简易幅频特性测试仪";
	BodePlotterTopMenu.CallBack = NULL;

	BodePlotterTopMenuItem[0].Caption = "频率";
	BodePlotterTopMenuItem[0].Enabled = true;
	BodePlotterTopMenuItem[0].CallBack = BodePlotter_TopMenuCallback;
	BodePlotterTopMenuItem[0].Style = SubMenuItem;
	BodePlotterTopMenuItem[0].SubCaption = NULL;
	BodePlotterTopMenuItem[0].Tag = 0;

	BodePlotterTopMenuItem[1] = BodePlotterTopMenuItem[0];
	BodePlotterTopMenuItem[1].Caption = "扫描";
	BodePlotterTopMenuItem[1].Tag = 1;

	BodePlotterTopMenuItem[2] = BodePlotterTopMenuItem[0];
	BodePlotterTopMenuItem[2].Caption = "幅度";
	BodePlotterTopMenuItem[2].Tag = 2;

	BodePlotterTopMenuItem[3] = BodePlotterTopMenuItem[0];
	BodePlotterTopMenuItem[3].Caption = "光标";
	BodePlotterTopMenuItem[3].Tag = 3;
}

void BodePlotter_InitFreqMenu(void)
{
	BodePlotterFreqMenu.ItemCount = sizeof(BodePlotterFreqMenuItem) / sizeof(BodePlotterFreqMenuItem[0]);
	BodePlotterFreqMenu.Items = BodePlotterFreqMenuItem;
	BodePlotterFreqMenu.MenuCaption = "频率设定";
	BodePlotterFreqMenu.CallBack = NULL;

	BodePlotterFreqMenuItem[0].Caption = "中心频率";
	BodePlotterFreqMenuItem[0].Enabled = true;
	BodePlotterFreqMenuItem[0].CallBack = BodePlotter_FreqMenuCallback;
	BodePlotterFreqMenuItem[0].Style = PopupItem;
	BodePlotterFreqMenuItem[0].SubCaption = BodePlotter_FreqCenterBuf;
	BodePlotter_ConvertDispFreq(BodePlotter_FreqCenterBuf, (BodePlotter_FreqStart + BodePlotter_FreqEnd) / 2);
	BodePlotterFreqMenuItem[0].Tag = 0;

	BodePlotterFreqMenuItem[1] = BodePlotterFreqMenuItem[0];
	BodePlotterFreqMenuItem[1].Caption = "起始频率";
	BodePlotterFreqMenuItem[1].SubCaption = BodePlotter_FreqStartBuf;
	BodePlotter_ConvertDispFreq(BodePlotter_FreqStartBuf, BodePlotter_FreqStart);
	BodePlotterFreqMenuItem[1].Tag = 1;

	BodePlotterFreqMenuItem[2] = BodePlotterFreqMenuItem[0];
	BodePlotterFreqMenuItem[2].Caption = "终止频率";
	BodePlotterFreqMenuItem[2].SubCaption = BodePlotter_FreqEndBuf;
	BodePlotter_ConvertDispFreq(BodePlotter_FreqEndBuf, BodePlotter_FreqEnd);
	BodePlotterFreqMenuItem[2].Tag = 2;

	BodePlotterFreqMenuItem[3] = BodePlotterFreqMenuItem[0];
	BodePlotterFreqMenuItem[3].Caption = "扫宽";
	BodePlotterFreqMenuItem[3].SubCaption = BodePlotter_FreqSpanBuf;
	BodePlotter_ConvertDispFreq(BodePlotter_FreqSpanBuf, BodePlotter_FreqEnd - BodePlotter_FreqStart);
	BodePlotterFreqMenuItem[3].Tag = 3;
}

void BodePlotter_UpdateFreqMenu(void)
{
	BodePlotter_ConvertDispFreq(BodePlotter_FreqCenterBuf, (BodePlotter_FreqStart + BodePlotter_FreqEnd) / 2);
	BodePlotter_ConvertDispFreq(BodePlotter_FreqStartBuf, BodePlotter_FreqStart);
	BodePlotter_ConvertDispFreq(BodePlotter_FreqEndBuf, BodePlotter_FreqEnd);
	BodePlotter_ConvertDispFreq(BodePlotter_FreqSpanBuf, BodePlotter_FreqEnd - BodePlotter_FreqStart);
}

void BodePlotter_InitScanMenu(void)
{
	BodePlotterScanMenu.ItemCount = sizeof(BodePlotterScanMenuItem) / sizeof(BodePlotterScanMenuItem[0]);
	BodePlotterScanMenu.Items = BodePlotterScanMenuItem;
	BodePlotterScanMenu.MenuCaption = "扫描设定";
	BodePlotterScanMenu.CallBack = NULL;

	BodePlotterScanMenuItem[0].Caption = "频率步进";
	BodePlotterScanMenuItem[0].Enabled = true;
	BodePlotterScanMenuItem[0].CallBack = BodePlotter_ScanMenuCallback;
	BodePlotterScanMenuItem[0].Style = PopupItem;
	BodePlotterScanMenuItem[0].SubCaption = BodePlotter_FreqStepBuf;
	BodePlotter_ConvertDispFreq(BodePlotter_FreqStepBuf, (BodePlotter_FreqEnd - BodePlotter_FreqStart) / (BodePlotter_FreqPoint - 1));
	BodePlotterScanMenuItem[0].Tag = 0;

	BodePlotterScanMenuItem[1] = BodePlotterScanMenuItem[0];
	BodePlotterScanMenuItem[1].Caption = "扫描点数";
	BodePlotterScanMenuItem[1].SubCaption = BodePlotter_FreqPointBuf;
	sprintf(BodePlotter_FreqPointBuf, "%ld", BodePlotter_FreqPoint);
	BodePlotterScanMenuItem[1].Tag = 1;

	BodePlotterScanMenuItem[2] = BodePlotterScanMenuItem[0];
	BodePlotterScanMenuItem[2].Caption = "X坐标系";
	BodePlotterScanMenuItem[2].Style = ButtonItem;
	BodePlotterScanMenuItem[2].SubCaption = BodePlotter_FreqAxisBuf;
	BodePlotter_ConvertDispAsix(BodePlotter_FreqAxisBuf, BodePlotter_FreqAxis);
	BodePlotterScanMenuItem[2].Tag = 2;
}

void BodePlotter_UpdateScanMenu(void)
{
	BodePlotter_ConvertDispFreq(BodePlotter_FreqStepBuf, (BodePlotter_FreqEnd - BodePlotter_FreqStart) / (BodePlotter_FreqPoint - 1));
	sprintf(BodePlotter_FreqPointBuf, "%ld", BodePlotter_FreqPoint);
	BodePlotter_ConvertDispAsix(BodePlotter_FreqAxisBuf, BodePlotter_FreqAxis);
}

void BodePlotter_InitAmptMenu(void)
{
	BodePlotterAmptMenu.ItemCount = sizeof(BodePlotterAmptMenuItem) / sizeof(BodePlotterAmptMenuItem[0]);
	BodePlotterAmptMenu.Items = BodePlotterAmptMenuItem;
	BodePlotterAmptMenu.MenuCaption = "幅度设定";
	BodePlotterAmptMenu.CallBack = NULL;

	BodePlotterAmptMenuItem[0].Caption = "输出幅度";
	BodePlotterAmptMenuItem[0].Enabled = true;
	BodePlotterAmptMenuItem[0].CallBack = BodePlotter_AmptMenuCallback;
	BodePlotterAmptMenuItem[0].Style = PopupItem;
	BodePlotterAmptMenuItem[0].SubCaption = BodePlotter_AmptitudeBuf;
	BodePlotter_ConvertDispVoltage(BodePlotter_AmptitudeBuf, BodePlotter_Amptitude);
	BodePlotterAmptMenuItem[0].Tag = 0;

	BodePlotterAmptMenuItem[1] = BodePlotterAmptMenuItem[0];
	BodePlotterAmptMenuItem[1].Caption = "参考电平";
	BodePlotterAmptMenuItem[1].SubCaption = BodePlotter_AmptitudeBaseBuf;
	BodePlotter_ConvertDispRatio(BodePlotter_AmptitudeBaseBuf, BodePlotter_AmptitudeBase);
	BodePlotterAmptMenuItem[1].Tag = 1;

	BodePlotterAmptMenuItem[2] = BodePlotterAmptMenuItem[0];
	BodePlotterAmptMenuItem[2].Caption = "刻度";
	BodePlotterAmptMenuItem[2].SubCaption = BodePlotter_AmptitudeDivBuf;
	BodePlotter_ConvertDispRatio(BodePlotter_AmptitudeDivBuf, BodePlotter_AmptitudeDiv);
	BodePlotterAmptMenuItem[2].Tag = 2;

	BodePlotterAmptMenuItem[3] = BodePlotterAmptMenuItem[0];
	BodePlotterAmptMenuItem[3].Caption = "Y坐标系";
	BodePlotterAmptMenuItem[3].Style = ButtonItem;
	BodePlotterAmptMenuItem[3].SubCaption = BodePlotter_AmptitudeAxisBuf;
	BodePlotter_ConvertDispAsix(BodePlotter_AmptitudeAxisBuf, BodePlotter_AmptitudeAxis);
	BodePlotterAmptMenuItem[3].Tag = 3;
}

void BodePlotter_UpdateAmptMenu(void)
{
	BodePlotter_ConvertDispVoltage(BodePlotter_AmptitudeBuf, BodePlotter_Amptitude);
	BodePlotter_ConvertDispRatio(BodePlotter_AmptitudeBaseBuf, BodePlotter_AmptitudeBase);
	BodePlotter_ConvertDispRatio(BodePlotter_AmptitudeDivBuf, BodePlotter_AmptitudeDiv);
	BodePlotter_ConvertDispAsix(BodePlotter_AmptitudeAxisBuf, BodePlotter_AmptitudeAxis);
}

void BodePlotter_InitCursorMenu(void)
{
	BodePlotterCursorMenu.ItemCount = sizeof(BodePlotterCursorMenuItem) / sizeof(BodePlotterCursorMenuItem[0]);
	BodePlotterCursorMenu.Items = BodePlotterCursorMenuItem;
	BodePlotterCursorMenu.MenuCaption = "光标";
	BodePlotterCursorMenu.CallBack = NULL;

	BodePlotterCursorMenuItem[0].Caption = "光标表";
	BodePlotterCursorMenuItem[0].Enabled = true;
	BodePlotterCursorMenuItem[0].CallBack = BodePlotter_CursorMenuCallback;
	BodePlotterCursorMenuItem[0].Style = ButtonItem;
	BodePlotterCursorMenuItem[0].SubCaption = BodePlotter_CursorTableBuf;
	BodePlotter_ConvertDispOnOff(BodePlotter_CursorTableBuf, BodePlotter_CursorTable);
	BodePlotterCursorMenuItem[0].Tag = 0;

	BodePlotterCursorMenuItem[1] = BodePlotterCursorMenuItem[0];
	BodePlotterCursorMenuItem[1].Caption = "光标选择";
	BodePlotterCursorMenuItem[1].SubCaption = BodePlotter_CursorSelBuf;
	sprintf(BodePlotter_CursorSelBuf, "%ld", BodePlotter_CursorSel);
	BodePlotterCursorMenuItem[1].Tag = 1;

	BodePlotterCursorMenuItem[2] = BodePlotterCursorMenuItem[0];
	BodePlotterCursorMenuItem[2].Caption = "光标功能";
	BodePlotterCursorMenuItem[2].SubCaption = BodePlotter_CursorFuncBuf;
	BodePlotter_ConvertDispCursorFunc(BodePlotter_CursorFuncBuf, BodePlotter_Cursors[BodePlotter_CursorSel].Type);
	BodePlotterCursorMenuItem[2].Tag = 2;

	BodePlotterCursorMenuItem[3] = BodePlotterCursorMenuItem[0];
	BodePlotterCursorMenuItem[3].Enabled = false;
	BodePlotterCursorMenuItem[3].Caption = NULL;
	BodePlotterCursorMenuItem[3].Style = BlankItem;
	BodePlotterCursorMenuItem[3].SubCaption = NULL;
	BodePlotterCursorMenuItem[3].Tag = 3;

	BodePlotterCursorMenuItem[4] = BodePlotterCursorMenuItem[3];
	BodePlotterCursorMenuItem[4].Tag = 4;
}

void BodePlotter_UpdateCursorMenu(void)
{
	BodePlotter_ConvertDispOnOff(BodePlotter_CursorTableBuf, BodePlotter_CursorTable);
	sprintf(BodePlotter_CursorSelBuf, "%ld", BodePlotter_CursorSel);
	BodePlotter_ConvertDispCursorFunc(BodePlotter_CursorFuncBuf, BodePlotter_Cursors[BodePlotter_CursorSel].Type);

	switch (BodePlotter_Cursors[BodePlotter_CursorSel].Type)
	{
	default:
	case Unused:
		BodePlotterCursorMenuItem[3].Caption = NULL;
		BodePlotterCursorMenuItem[3].Enabled = false;
		BodePlotterCursorMenuItem[3].Style = BlankItem;
		BodePlotterCursorMenuItem[3].SubCaption = NULL;

		BodePlotterCursorMenuItem[4].Caption = NULL;
		BodePlotterCursorMenuItem[4].Enabled = false;
		BodePlotterCursorMenuItem[4].Style = BlankItem;
		BodePlotterCursorMenuItem[4].SubCaption = NULL;
		break;
	case Normal:
		BodePlotterCursorMenuItem[3].Caption = "频率";
		BodePlotterCursorMenuItem[3].Enabled = false;
		BodePlotterCursorMenuItem[3].Style = ButtonItem;
		BodePlotter_ConvertDispFreq(BodePlotter_CursorCustonBuf0, BodePlotter_Cursors[BodePlotter_CursorSel].NormalData.Freq);
		BodePlotterCursorMenuItem[3].SubCaption = BodePlotter_CursorCustonBuf0;

		BodePlotterCursorMenuItem[4].Caption = NULL;
		BodePlotterCursorMenuItem[4].Enabled = false;
		BodePlotterCursorMenuItem[4].Style = BlankItem;
		BodePlotterCursorMenuItem[4].SubCaption = NULL;
		break;
	case Delta:
		BodePlotterCursorMenuItem[3].Caption = "光标1";
		BodePlotterCursorMenuItem[3].Enabled = true;
		BodePlotterCursorMenuItem[3].Style = ButtonItem;
		sprintf(BodePlotter_CursorCustonBuf0, "%ld", BodePlotter_Cursors[BodePlotter_CursorSel].DeltaData.Cursors[0]);
		BodePlotterCursorMenuItem[3].SubCaption = BodePlotter_CursorCustonBuf0;

		BodePlotterCursorMenuItem[4].Caption = "光标2";
		BodePlotterCursorMenuItem[4].Enabled = true;
		BodePlotterCursorMenuItem[4].Style = ButtonItem;
		BodePlotterCursorMenuItem[4].SubCaption = BodePlotter_CursorCustonBuf1;
		sprintf(BodePlotter_CursorCustonBuf1, "%ld", BodePlotter_Cursors[BodePlotter_CursorSel].DeltaData.Cursors[1]);
		break;
	}
}

void BodePlotter_UpdateAllMenus(void)
{
	MENU* GlobalMenu = GetGlobalMenu();

	BodePlotter_UpdateFreqMenu();
	BodePlotter_UpdateScanMenu();
	BodePlotter_UpdateAmptMenu();
	BodePlotter_UpdateCursorMenu();

	GlobalMenu->UpdateItems();
	FreeAndEraseReference(GlobalMenu);
}

void BodePlotter_LoadParam(void)
{
	BodePlotter_FreqStart = BodePlotter_FreqLowerLimit;
	BodePlotter_FreqEnd = BodePlotter_FreqUpperLimit;

	BodePlotter_FreqPoint = 101;
	BodePlotter_FreqAxis = Linear;

	BodePlotter_Amptitude = 100e-3;
	BodePlotter_AmptitudeBase = 1;
	BodePlotter_AmptitudeDiv = 0.2;
	BodePlotter_AmptitudeAxis = Linear;

	BodePlotter_CursorTable = false;
	BodePlotter_CursorSel = 0;

	for (u32 i = 0; i < BodePlotter_CursorCount; i++)
	{
		BodePlotter_Cursors[i].Type = Unused;
		BodePlotter_Cursors[i].NormalData.Freq = 0.0;
		BodePlotter_Cursors[i].DeltaData.Cursors[0] = 0;
		BodePlotter_Cursors[i].DeltaData.Cursors[1] = 0;
	}
}

void BodePlotter_CreateMenu(void)
{
	MENU* GlobalMenu = GetGlobalMenu();

	BodePlotter_InitTopMenu();
	BodePlotter_InitFreqMenu();
	BodePlotter_InitScanMenu();
	BodePlotter_InitAmptMenu();
	BodePlotter_InitCursorMenu();

	BodePlotter_UpdateAllMenus();

	GlobalMenu->EnterMenu(&BodePlotterTopMenu);
	FreeAndEraseReference(GlobalMenu);
}

void BodePlotter_CreateWin(void)
{
	WINDOW* ScrWin = SCREENWINDOW::GetScreenWindow();
	GUIPOS ScrWidth = 0;
	GUIPOS ScrHeight = 0;
	ScrWin->GetWindowPos(NULL, NULL, &ScrWidth, &ScrHeight);
	FreeAndEraseReference(ScrWin);
	BodePlotter_Win = new_noexcpt WINDOW(NULL, 0, 0, ScrWidth - MENU::GetMenuWidth(), ScrHeight, true);
	WINEVENT* Event = new_noexcpt BodePlotter_EVENT();
	BodePlotter_Win->LinkEventHandler(Event);
	BodePlotter_Win->SetCaption("BodePlotterWin");

	DC* WinDC = BodePlotter_Win->GetDC();
	BodePlotter_Graphic.AssignDC(WinDC);
	FreeAndEraseReference(WinDC);
}

void BodePlotter_SetAmplitude(void)
{
	double TxFreq = BodePlotter_ScanEngine.GetTxFreq();
	u32 IndexL = 0;
	u32 IndexH = BodePlotter_TrackGenCaliDataNumber - 1;
	float Att = BodePlotter_TrackGenCaliAtt;
	float TargetAmpl = 10 * log10(BodePlotter_Amptitude * BodePlotter_Amptitude / 50.0 / 1e-3);
	float CaliInterpol;
	while ((IndexH - IndexL) > 1)
	{
		u32 IndexM = (IndexL + IndexH) / 2;
		if (BodePlotter_TrackGenCali[IndexM][0] < TxFreq)
		{
			IndexL = IndexM;
		}
		else
		{
			IndexH = IndexM;
		}
	}
	if (IndexH - IndexL)
	{
		CaliInterpol = (BodePlotter_TrackGenCali[IndexH][1] - BodePlotter_TrackGenCali[IndexL][1]) * (TxFreq - BodePlotter_TrackGenCali[IndexL][0]) / (BodePlotter_TrackGenCali[IndexH][0] - BodePlotter_TrackGenCali[IndexL][0]) + BodePlotter_TrackGenCali[IndexL][1];
	}
	else
	{
		CaliInterpol = BodePlotter_TrackGenCali[IndexH][1];
	}
	Att += CaliInterpol - TargetAmpl;
	if (Att > 31.75)
	{
		PE43711_SetAttenuation(&BodePoltter_Out1PE43711Handle, Att - 31.75);
		Att = 31.75;
	}
	else
	{
		PE43711_SetAttenuation(&BodePoltter_Out1PE43711Handle, 0);
	}
	PE43711_SetAttenuation(&BodePoltter_Out0PE43711Handle, Att);
	/*PE43711_SetAttenuation(&BodePoltter_Out0PE43711Handle, 20);
	PE43711_SetAttenuation(&BodePoltter_Out1PE43711Handle, 0);*/
}

void BodePlotter_StartScan(void)
{
	double SampleFreq;
	double NCOFreq;
	BodePlotter_ScanEngine.LoadPattern(BodePlotter_FreqStart, BodePlotter_FreqEnd, BodePlotter_FreqPoint);
	SampleFreq = BodePlotter_ScanEngine.GetSampleFreq();
	NCOFreq = BodePlotter_ScanEngine.GetNCOFreq();
	ADF4351_SetOutputAFrequency(&BodePlotter_ADF4351Handle, BodePlotter_PllRef, SampleFreq, true);
	ADF4351_Update(&BodePlotter_ADF4351Handle);
	BodePlotter_FPGA.SetNCO(NCOFreq, SampleFreq);
	AD9959_SetChannelFrequency(1, BodePlotter_ScanEngine.GetTxFreq());
	BodePlotter_SetAmplitude();

	if (CurrentScanData)
	{
		if (CurrentScanData->IsFinished())
		{
			if (LastFullScanData)
			{
				delete LastFullScanData;
			}
			LastFullScanData = CurrentScanData;
			CurrentScanData = new_noexcpt BodePlotterDataStore(&BodePlotter_ScanEngine);
		}
		else
		{
			delete CurrentScanData;
			CurrentScanData = new_noexcpt BodePlotterDataStore(&BodePlotter_ScanEngine);
		}
	}
	else
	{
		CurrentScanData = new_noexcpt BodePlotterDataStore(&BodePlotter_ScanEngine);
	}
}

void BodePlotter_StoreData(void)
{
	s64 Val;
	double NormalizeData;
	bool OverRange;
	BodePlotter_FPGA.ReteriveValue(&Val, &OverRange);
	NormalizeData = arm_linear_interp_f32(&BodePlotter_InputCaliInterp, BodePlotter_ScanEngine.GetTxFreq());
	CurrentScanData->AddData(sqrt((double)Val) / NormalizeData);
}

void BodePlotter_DoScan(void)
{
	if (BodePlotter_ScanEngine.IsFinished())
	{
		BodePlotter_StoreData();
		BodePlotter_StartScan();
	}
	else
	{
		if (BodePlotter_ScanEngine.IsNextReady())
		{
			double SampleFreq;
			double NCOFreq;
			BodePlotter_StoreData();
			SampleFreq = BodePlotter_ScanEngine.GetSampleFreq();
			NCOFreq = BodePlotter_ScanEngine.GetNCOFreq();
			ADF4351_SetOutputAFrequency(&BodePlotter_ADF4351Handle, BodePlotter_PllRef, SampleFreq, true);
			ADF4351_Update(&BodePlotter_ADF4351Handle);
			BodePlotter_FPGA.SetNCO(NCOFreq, SampleFreq);
			AD9959_SetChannelFrequency(1, BodePlotter_ScanEngine.GetTxFreq());
			BodePlotter_SetAmplitude();
		}
	}
}

void BodePlotter_RefreshDisplay(void)
{
	static u32 NextTick = 0;
	if (NextTick < HAL_GetTick())
	{
		NextTick = HAL_GetTick() + 300;
		BodePlotter_Graphic.SetFreqParam(BodePlotter_FreqStart, BodePlotter_FreqEnd, BodePlotter_FreqAxis == Logarithmic ? true : false);
		BodePlotter_Graphic.SetAmptParam(BodePlotter_AmptitudeBase, BodePlotter_AmptitudeDiv, BodePlotter_AmptitudeAxis == Logarithmic ? true : false);
		PostMessage(BodePlotter_Win, WM_PAINT, 0, 0);
	}
}

u32 RefreshPause = 0;

void TaskLauncher(void)
{
	BodePlotter_LoadParam();
	BodePlotter_InitHardware();
	BodePlotter_CreateWin();
	BodePlotter_CreateMenu();
	BodePlotter_StartScan();
	BodePlotter_SetAmplitude();

	BodePlotter_InputCaliInterp.nValues = BodePlotter_InputCaliDataCount;
	BodePlotter_InputCaliInterp.pYData = (float*)BodePlotter_InputCali;
	BodePlotter_InputCaliInterp.x1 = BodePlotter_InputCaliLowerFreq;
	BodePlotter_InputCaliInterp.xSpacing = (BodePlotter_InputCaliUpperFreq - BodePlotter_InputCaliLowerFreq) / (BodePlotter_InputCaliDataCount - 1);
	while (1)
	{
		DoMessageLoop();
		if (HAL_GetTick() > RefreshPause)
		{
			BodePlotter_DoScan();
			BodePlotter_RefreshDisplay();
		}
	}
}

bool BodePlotter_EVENT::OnKeyPress(WINDOW * Win, KEYCODE Key)
{
	if (Key == KEY_ESC)
	{
		MENU* GlobalMenu = GetGlobalMenu();
		GlobalMenu->ExitAll();
		GlobalMenu->EnterMenu(&BodePlotterTopMenu);
		FreeAndEraseReference(GlobalMenu);
	}
	if (BodePlotter_Cursors[BodePlotter_CursorSel].Type == Normal)
	{
		if (Key == KEY_ENCL)
		{
			BodePlotter_Cursors[BodePlotter_CursorSel].NormalData.Freq -= (BodePlotter_FreqEnd - BodePlotter_FreqStart) / 500;
		}
		if (Key == KEY_ENCR)
		{
			BodePlotter_Cursors[BodePlotter_CursorSel].NormalData.Freq += (BodePlotter_FreqEnd - BodePlotter_FreqStart) / 500;
		}
		if (BodePlotter_Cursors[BodePlotter_CursorSel].NormalData.Freq < BodePlotter_FreqStart)
		{
			BodePlotter_Cursors[BodePlotter_CursorSel].NormalData.Freq = BodePlotter_FreqStart;
		}
		if (BodePlotter_Cursors[BodePlotter_CursorSel].NormalData.Freq > BodePlotter_FreqEnd)
		{
			BodePlotter_Cursors[BodePlotter_CursorSel].NormalData.Freq = BodePlotter_FreqEnd;
		}
		BodePlotter_UpdateAllMenus();
		PostMessage(BodePlotter_Win, WM_PAINT, 0, 0);
	}
	RefreshPause = HAL_GetTick() + 1000;
	return true;
}

bool BodePlotter_EVENT::OnPaint(WINDOW * Win)
{
	DC* DrawingDC = Win->GetDC();
	FONTGROUP* FG = NewReferenceSafe(new_noexcpt FONTGROUP("ASC24"));

	BodePlotter_Graphic.Draw(LastFullScanData, CurrentScanData);

	/*DrawLine(DrawingDC, CursorL, 0, CursorL, 600, RED);
	DrawLine(DrawingDC, CursorR, 0, CursorR, 600, GREEN);

	char Buf[128];
	float F1 = BodePlotter_FreqStart + (BodePlotter_FreqEnd - BodePlotter_FreqStart)*CursorL / 700;
	float F2 = BodePlotter_FreqStart + (BodePlotter_FreqEnd - BodePlotter_FreqStart)*CursorR / 700;
	sprintf(Buf, "L %f MHz R %f MHz Delta %fMHz", F1 / 1e6, F2 / 1e6, (F2 - F1) / 1e6);
	DrawStringHorizontal(DrawingDC, FG, Buf, 0, 400, 0, 0, WHITE, BLACK);*/

	FreeAndEraseReference(FG);
	FreeAndEraseReference(DrawingDC);
	return false;
}
