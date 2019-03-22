#include "HAL\HCommon.h"
#include "HAL\FSMC.h"
#include "ILI9806G.h"

#define LCD_HardwareWidth 854
#define LCD_HardwareHeight 480

__IO u16* const LCD_Command = (u16*)(FSMC_Base3);
__IO u16* const LCD_Data16 = (u16*)(FSMC_Base3 + 4);
__IO u32* const LCD_Data32 = (u32*)(FSMC_Base3 + 4);

u16 LCD_Width;
u16 LCD_Height;

bool LCD_Initialized = false;
SRAM_HandleTypeDef LCD_FSMC_Handle;

static void LCD_Fill_internal(u16 XStart, u16 YStart, u16 XEnd, u16 YEnd, u16 Color);

STATUS LCD_FSMC_Init(void)
{
	FSMC_NORSRAM_TimingTypeDef Timing;
	FSMC_NORSRAM_TimingTypeDef ExtTiming;

	FSMC_Init();
	LCD_FSMC_Handle.Instance = FSMC_NORSRAM_DEVICE;
	LCD_FSMC_Handle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;

	LCD_FSMC_Handle.Init.NSBank = FSMC_NORSRAM_BANK3;
	LCD_FSMC_Handle.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
	LCD_FSMC_Handle.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
	LCD_FSMC_Handle.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
	LCD_FSMC_Handle.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
	LCD_FSMC_Handle.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
	LCD_FSMC_Handle.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
	LCD_FSMC_Handle.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
	LCD_FSMC_Handle.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
	LCD_FSMC_Handle.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
	LCD_FSMC_Handle.Init.ExtendedMode = FSMC_EXTENDED_MODE_ENABLE;
	LCD_FSMC_Handle.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
	LCD_FSMC_Handle.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
	LCD_FSMC_Handle.Init.PageSize = FSMC_PAGE_SIZE_NONE;

	Timing.AddressSetupTime = 0;
	Timing.AddressHoldTime = 1;
	Timing.DataSetupTime = 6;
	Timing.BusTurnAroundDuration = 0;
	Timing.CLKDivision = 2;
	Timing.DataLatency = 2;
	Timing.AccessMode = FSMC_ACCESS_MODE_A;

	ExtTiming.AddressSetupTime = 0;
	ExtTiming.AddressHoldTime = 1;
	ExtTiming.DataSetupTime = 1;
	ExtTiming.BusTurnAroundDuration = 0;
	ExtTiming.CLKDivision = 2;
	ExtTiming.DataLatency = 2;
	ExtTiming.AccessMode = FSMC_ACCESS_MODE_A;

	if (HAL_SRAM_Init(&LCD_FSMC_Handle, &Timing, &ExtTiming) != HAL_OK)
	{
		return S_FAIL;
	}

	return S_OK;
}

void WriteComm(u16 CMD)
{
	*LCD_Command = CMD;
}

void WriteData16(u16 Data)
{
	*LCD_Data16 = Data;
}

void WriteData32(u32 Data)
{
	*LCD_Data32 = Data;
}

STATUS LCD_Init(void)
{
	if (LCD_Initialized)
	{
		return S_OK;
	}

	if (LCD_FSMC_Init() != S_OK)
	{
		return S_FAIL;
	}

	WriteComm(0x01);//Software reset
	HAL_Delay(5);
	WriteComm(0x11);//Sleep out
	HAL_Delay(5);

	WriteComm(0xFF);//EXTC Command Set enable register
	WriteData16(0xFF);
	WriteData16(0x98);
	WriteData16(0x06);

	LCD_SetDirection(0);

	WriteComm(0x38);//Idle Mode Off

	WriteComm(0x3A);//Interface Pixel Format
	WriteData16(0x55);//16 bit/Pixel

	LCD_SetBrightness(0);

	WriteComm(0x53);//Write CTRL Display Value
	WriteData16(0x2C);

	WriteComm(0x55);//Write Content Adaptive Brightness Control Value
	WriteData16(0xB1);

	WriteComm(0x5E);//Write CABC Minimum Brightness
	WriteData16(0);

	WriteComm(0xB1);//Frame Rate Control 1 (In Normal Mode/Full Colors)
	WriteData16(0x00);
	WriteData16(0x10);
	WriteData16(0x12);

	WriteComm(0xB2);//Frame Rate Control 2 (In Idle Mode/8 colors)
	WriteData16(0x00);
	WriteData16(0x1F);
	WriteData16(0x20);

	WriteComm(0xB1);//Frame Rate control 3 (In Partial Mode/Full Colors)
	WriteData16(0x00);
	WriteData16(0x10);
	WriteData16(0x12);

	WriteComm(0xB4);//Display Inversion Control
	WriteData16(0x00);
	WriteData16(0x00);
	WriteData16(0x00);

	WriteComm(0xB8);//DBI Type B Interface Setting
	WriteData16(0x40);

	WriteComm(0xC0); //Power Control 1
	WriteData16(0xE3);
	WriteData16(0x0B);
	WriteData16(0x00);

	WriteComm(0xC1); //Power Control 2
	WriteData16(0x17);
	WriteData16(0X85);
	WriteData16(0x85);
	WriteData16(0x20);

	WriteComm(0xC7); //VCOM Control 1
	WriteData16(0x1E);

	WriteComm(0xED);//VGMP / VGMN /VGSP / VGSN Voltage Measurement Set
	WriteData16(0x7F);
	WriteData16(0x0F);
	WriteData16(0x00);

	WriteComm(0xC8);//Backlight Control 1
	WriteData16(0xA0);
	WriteComm(0xCF);//Backlight Control 8
	WriteData16(0x00);

	WriteComm(0xDF); //Engineering Setting
	WriteData16(0x00);
	WriteData16(0x00);
	WriteData16(0x00);
	WriteData16(0x00);
	WriteData16(0x00);
	WriteData16(0x20);

	WriteComm(0xF1);//Panel Timing Control 1
	WriteData16(0x29);
	WriteData16(0x8A);
	WriteData16(0x07);

	WriteComm(0xF2);//Panel Timing Control 2
	WriteData16(0x40);
	WriteData16(0xD2);
	WriteData16(0x50);
	WriteData16(0x28);

	WriteComm(0xF3);//DVDD Voltage Setting
	WriteData16(0x74);

	WriteComm(0xF7);//Panel Resolution Selection Set
	WriteData16(0x81);//480x854

	WriteComm(0xFC);//LVGL Voltage Setting
	WriteData16(0x08);

	WriteComm(0xBC);//GIP 1
	WriteData16(0x03);
	WriteData16(0x0F);
	WriteData16(0x63);
	WriteData16(0x69);
	WriteData16(0x01);
	WriteData16(0x01);
	WriteData16(0x1B);
	WriteData16(0x11);
	WriteData16(0x70);
	WriteData16(0x73);
	WriteData16(0xFF);
	WriteData16(0xFF);
	WriteData16(0x08);
	WriteData16(0x09);
	WriteData16(0x05);
	WriteData16(0x00);
	WriteData16(0xEE);
	WriteData16(0xE2);
	WriteData16(0x01);
	WriteData16(0x00);
	WriteData16(0xC1);

	WriteComm(0xBD); // GIP 2
	WriteData16(0x01);
	WriteData16(0x23);
	WriteData16(0x45);
	WriteData16(0x67);
	WriteData16(0x01);
	WriteData16(0x23);
	WriteData16(0x45);
	WriteData16(0x67);

	WriteComm(0xBE); // GIP 3
	WriteData16(0x00);
	WriteData16(0x22);
	WriteData16(0x27);
	WriteData16(0x6A);
	WriteData16(0xBC);
	WriteData16(0xD8);
	WriteData16(0x92);
	WriteData16(0x22);
	WriteData16(0x22);

	WriteComm(0xE0);//Positive Gamma Control
	WriteData16(0x00);
	WriteData16(0x0C);
	WriteData16(0x15);
	WriteData16(0x0D);
	WriteData16(0x0F);
	WriteData16(0x0C);
	WriteData16(0x07);
	WriteData16(0x05);
	WriteData16(0x07);
	WriteData16(0x0B);
	WriteData16(0x10);
	WriteData16(0x10);
	WriteData16(0x0D);
	WriteData16(0x17);
	WriteData16(0x0F);
	WriteData16(0x00);

	WriteComm(0xE1);//Negative Gamma Correction
	WriteData16(0x00);
	WriteData16(0x0D);
	WriteData16(0x15);
	WriteData16(0x0E);
	WriteData16(0x10);
	WriteData16(0x0D);
	WriteData16(0x08);
	WriteData16(0x06);
	WriteData16(0x07);
	WriteData16(0x0C);
	WriteData16(0x11);
	WriteData16(0x11);
	WriteData16(0x0E);
	WriteData16(0x17);
	WriteData16(0x0F);
	WriteData16(0x00);

	WriteComm(0x35);//Tearing Effect Line ON
	WriteData16(0x00);

	LCD_Fill_internal(0, 0, LCD_Width, LCD_Height, 0x0000);

	WriteComm(0x29);//Display On

	LCD_SetBrightness(255);

	LCD_Initialized = true;

	return S_OK;
}

void LCD_SetDirection(uint Direction)
{
	WriteComm(0x36);//Memory Access Control
	switch (Direction)
	{
	default:
	case 0:
		WriteData16(0x22);
		LCD_Width = LCD_HardwareWidth;
		LCD_Height = LCD_HardwareHeight;
		break;
	case 1:
		WriteData16(0x31);
		LCD_Width = LCD_HardwareWidth;
		LCD_Height = LCD_HardwareHeight;
		break;
	case 2:
		WriteData16(0x00);
		LCD_Width = LCD_HardwareHeight;
		LCD_Height = LCD_HardwareWidth;
		break;
	case 3:
		WriteData16(0x13);
		LCD_Width = LCD_HardwareHeight;
		LCD_Height = LCD_HardwareWidth;
		break;
	}
}

void LCD_SetBrightness(u8 Brightness)
{
	WriteComm(0x51);//Write Display Brightness Value
	WriteData16(Brightness);
}

void LCD_SetCurrentPoint(u16 X, u16 Y)
{
	WriteComm(0x2A);
	WriteData32(X >> 8 | (X & 0xFF) << 16);

	WriteComm(0x2B);
	WriteData32(Y >> 8 | (Y & 0xFF) << 16);
}

void LCD_ClipArea(u16 XStart, u16 YStart, u16 XEnd, u16 YEnd)
{
	WriteComm(0x2A);
	WriteData32(XStart >> 8 | (XStart & 0xFF) << 16);
	WriteData32((XEnd - 1) >> 8 | ((XEnd - 1) & 0xff) << 16);

	WriteComm(0x2B);
	WriteData32(YStart >> 8 | (YStart & 0xFF) << 16);
	WriteData32((YEnd - 1) >> 8 | ((YEnd - 1) & 0xFF) << 16);
}

void LCD_EnterReadMode(void)
{
	WriteComm(0x2E);//Start read,reset address counter
	UNUSED(*LCD_Data16);//dummy read
}

void LCD_EnterWriteMode(void)
{
	WriteComm(0x2C);//Start write,reset address counter
}

u16 LCD_Read(void)
{
	u16 Part1;
	u16 Part2;
	WriteComm(0x3E);//Continue read
	UNUSED(*LCD_Data16);//dummy read
	Part1 = *LCD_Data16;
	Part2 = *LCD_Data16;
	return (Part1 & 0xF800) | ((Part1 & 0x00FC) << 3) | (Part2 >> 11);
}

#ifndef ExpandReadWriteFunctions

void LCD_Write(u16 Dat)
{
	*LCD_Data16 = Dat;
}

#endif

static void LCD_Fill_internal(u16 XStart, u16 YStart, u16 XEnd, u16 YEnd, u16 Color)
{
	u32 i;
	u16 Width = XEnd - XStart;
	u16 Height = YEnd - YStart;
	LCD_ClipArea(XStart, YStart, XEnd, YEnd);
	LCD_EnterWriteMode();
	for (i = 0; i < Width * Height; i++)
	{
		WriteData16(Color);
	}
	LCD_ClipArea(0, 0, LCD_Width, LCD_Height);
}
