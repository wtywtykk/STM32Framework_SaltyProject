#include "HAL\HCommon.h"
#include "ILI9806G.h"
#include "HAL/Tick.h"
#include "HAL/UniGPIO.h"

#define LCD_HardwareWidth 854
#define LCD_HardwareHeight 480

u16 LCD_Width;
u16 LCD_Height;

bool LCD_Initialized = false;

static void LCD_Fill_internal(u16 XStart, u16 YStart, u16 XEnd, u16 YEnd, u16 Color);

#define DataPort GPIO_PORT_P3
#define DataPortAddr 0x40004c20
#define CSPort GPIO_PORT_P2//
#define CSPin GPIO_PIN0//
#define RSPort GPIO_PORT_P2//
#define RSPin GPIO_PIN2//
#define RDPort GPIO_PORT_P8//
#define RDPin GPIO_PIN0//
#define WRPort GPIO_PORT_P2//
#define WRPin GPIO_PIN3//
#define RSTPort GPIO_PORT_P8//
#define RSTPin GPIO_PIN1//

UniGPIO_Handle CS_Handle;
UniGPIO_Handle RS_Handle;
UniGPIO_Handle RD_Handle;
UniGPIO_Handle WR_Handle;
UniGPIO_Handle RS_Handle;
UniGPIO_Handle RST_Handle;

STATUS LCD_IO_Init(void)
{
	GPIO_InitTypeDef GPIOInit;

	GPIOInit.FuncSel = 0;
	GPIOInit.HighDrive = true;
	GPIOInit.InterruptEnable = false;
	GPIOInit.InterruptLowToHigh = false;
	GPIOInit.Output = true;
	GPIOInit.Pin = 0xFF;
	GPIOInit.Pull = false;

	GPIO_32_InitPin(DataPort, &GPIOInit, NULL);
	GPIO_setAsOutputPin(DataPort, 0xFF);

	GPIOInit.Pin = CSPin;
	GPIO_32_InitPin(CSPort, &GPIOInit, &CS_Handle);
	UniGPIO_SetLow(&CS_Handle);

	GPIOInit.Pin = RSPin;
	GPIO_32_InitPin(RSPort, &GPIOInit, &RS_Handle);
	UniGPIO_SetHigh(&RS_Handle);

	GPIOInit.Pin = RDPin;
	GPIO_32_InitPin(RDPort, &GPIOInit, &RD_Handle);
	UniGPIO_SetHigh(&RD_Handle);

	GPIOInit.Pin = WRPin;
	GPIO_32_InitPin(WRPort, &GPIOInit, &WR_Handle);
	UniGPIO_SetHigh(&WR_Handle);

	GPIOInit.Pin = RSTPin;
	GPIO_32_InitPin(RSTPort, &GPIOInit, &RST_Handle);
	UniGPIO_SetHigh(&RST_Handle);

	return S_OK;
}

void WriteComm(u16 CMD)
{
	//UniGPIO_SetLow(&CS_Handle);
	UniGPIO_SetLow(&RS_Handle);
	HWREG16(DataPortAddr + OFS_PAOUT) = CMD;
	UniGPIO_SetLow(&WR_Handle);
	UniGPIO_SetHigh(&WR_Handle);
	//UniGPIO_SetHigh(&CS_Handle);
}

void WriteData8(u8 Data)
{
	//UniGPIO_SetLow(&CS_Handle);
	UniGPIO_SetHigh(&RS_Handle);
	HWREG16(DataPortAddr + OFS_PAOUT) = Data;
	UniGPIO_SetLow(&WR_Handle);
	UniGPIO_SetHigh(&WR_Handle);
	//UniGPIO_SetHigh(&CS_Handle);
}

void WriteData16(u16 Data)
{
	WriteData8(Data >> 8);
	WriteData8(Data & 0xFF);
}

u16 ReadData16(void)
{
	return 0;
}

STATUS LCD_Init(void)
{
	if (LCD_Initialized)
	{
		return S_OK;
	}

	if (LCD_IO_Init() != S_OK)
	{
		return S_FAIL;
	}

	WriteComm(0x01);//Software reset
	HAL_Delay(5);
	WriteComm(0x11);//Sleep out
	HAL_Delay(5);

	WriteComm(0xFF);//EXTC Command Set enable register
	WriteData8(0xFF);
	WriteData8(0x98);
	WriteData8(0x06);

	LCD_SetDirection(2);

	WriteComm(0x38);//Idle Mode Off

	WriteComm(0x3A);//Interface Pixel Format
	WriteData8(0x55);//16 bit/Pixel

	LCD_SetBrightness(0);

	WriteComm(0x53);//Write CTRL Display Value
	WriteData8(0x2C);

	WriteComm(0x55);//Write Content Adaptive Brightness Control Value
	WriteData8(0xB1);

	WriteComm(0x5E);//Write CABC Minimum Brightness
	WriteData8(0);

	WriteComm(0xB1);//Frame Rate Control 1 (In Normal Mode/Full Colors)
	WriteData8(0x00);
	WriteData8(0x10);
	WriteData8(0x12);

	WriteComm(0xB2);//Frame Rate Control 2 (In Idle Mode/8 colors)
	WriteData8(0x00);
	WriteData8(0x1F);
	WriteData8(0x20);

	WriteComm(0xB1);//Frame Rate control 3 (In Partial Mode/Full Colors)
	WriteData8(0x00);
	WriteData8(0x10);
	WriteData8(0x12);

	WriteComm(0xB4);//Display Inversion Control
	WriteData8(0x00);
	WriteData8(0x00);
	WriteData8(0x00);

	WriteComm(0xB8);//DBI Type B Interface Setting
	WriteData8(0x40);

	WriteComm(0xC0); //Power Control 1
	WriteData8(0xE3);
	WriteData8(0x0B);
	WriteData8(0x00);

	WriteComm(0xC1); //Power Control 2
	WriteData8(0x17);
	WriteData8(0X85);
	WriteData8(0x85);
	WriteData8(0x20);

	WriteComm(0xC7); //VCOM Control 1
	WriteData8(0x1E);

	WriteComm(0xED);//VGMP / VGMN /VGSP / VGSN Voltage Measurement Set
	WriteData8(0x7F);
	WriteData8(0x0F);
	WriteData8(0x00);

	WriteComm(0xC8);//Backlight Control 1
	WriteData8(0xA0);
	WriteComm(0xCF);//Backlight Control 8
	WriteData8(0x00);

	WriteComm(0xDF); //Engineering Setting
	WriteData8(0x00);
	WriteData8(0x00);
	WriteData8(0x00);
	WriteData8(0x00);
	WriteData8(0x00);
	WriteData8(0x20);

	WriteComm(0xF1);//Panel Timing Control 1
	WriteData8(0x29);
	WriteData8(0x8A);
	WriteData8(0x07);

	WriteComm(0xF2);//Panel Timing Control 2
	WriteData8(0x40);
	WriteData8(0xD2);
	WriteData8(0x50);
	WriteData8(0x28);

	WriteComm(0xF3);//DVDD Voltage Setting
	WriteData8(0x74);

	WriteComm(0xF7);//Panel Resolution Selection Set
	WriteData8(0x81);//480x854

	WriteComm(0xFC);//LVGL Voltage Setting
	WriteData8(0x08);

	WriteComm(0xBC);//GIP 1
	WriteData8(0x03);
	WriteData8(0x0F);
	WriteData8(0x63);
	WriteData8(0x69);
	WriteData8(0x01);
	WriteData8(0x01);
	WriteData8(0x1B);
	WriteData8(0x11);
	WriteData8(0x70);
	WriteData8(0x73);
	WriteData8(0xFF);
	WriteData8(0xFF);
	WriteData8(0x08);
	WriteData8(0x09);
	WriteData8(0x05);
	WriteData8(0x00);
	WriteData8(0xEE);
	WriteData8(0xE2);
	WriteData8(0x01);
	WriteData8(0x00);
	WriteData8(0xC1);

	WriteComm(0xBD); // GIP 2
	WriteData8(0x01);
	WriteData8(0x23);
	WriteData8(0x45);
	WriteData8(0x67);
	WriteData8(0x01);
	WriteData8(0x23);
	WriteData8(0x45);
	WriteData8(0x67);

	WriteComm(0xBE); // GIP 3
	WriteData8(0x00);
	WriteData8(0x22);
	WriteData8(0x27);
	WriteData8(0x6A);
	WriteData8(0xBC);
	WriteData8(0xD8);
	WriteData8(0x92);
	WriteData8(0x22);
	WriteData8(0x22);

	WriteComm(0xE0);//Positive Gamma Control
	WriteData8(0x00);
	WriteData8(0x0C);
	WriteData8(0x15);
	WriteData8(0x0D);
	WriteData8(0x0F);
	WriteData8(0x0C);
	WriteData8(0x07);
	WriteData8(0x05);
	WriteData8(0x07);
	WriteData8(0x0B);
	WriteData8(0x10);
	WriteData8(0x10);
	WriteData8(0x0D);
	WriteData8(0x17);
	WriteData8(0x0F);
	WriteData8(0x00);

	WriteComm(0xE1);//Negative Gamma Correction
	WriteData8(0x00);
	WriteData8(0x0D);
	WriteData8(0x15);
	WriteData8(0x0E);
	WriteData8(0x10);
	WriteData8(0x0D);
	WriteData8(0x08);
	WriteData8(0x06);
	WriteData8(0x07);
	WriteData8(0x0C);
	WriteData8(0x11);
	WriteData8(0x11);
	WriteData8(0x0E);
	WriteData8(0x17);
	WriteData8(0x0F);
	WriteData8(0x00);

	WriteComm(0x35);//Tearing Effect Line ON
	WriteData8(0x00);

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
		WriteData8(0x22);
		LCD_Width = LCD_HardwareWidth;
		LCD_Height = LCD_HardwareHeight;
		break;
	case 1:
		WriteData8(0x31);
		LCD_Width = LCD_HardwareWidth;
		LCD_Height = LCD_HardwareHeight;
		break;
	case 2:
		WriteData8(0x00);
		LCD_Width = LCD_HardwareHeight;
		LCD_Height = LCD_HardwareWidth;
		break;
	case 3:
		WriteData8(0x13);
		LCD_Width = LCD_HardwareHeight;
		LCD_Height = LCD_HardwareWidth;
		break;
	}
}

void LCD_SetBrightness(u8 Brightness)
{
	WriteComm(0x51);//Write Display Brightness Value
	WriteData8(Brightness);
}

void LCD_SetCurrentPoint(u16 X, u16 Y)
{
	WriteComm(0x2A);
	WriteData16(X);

	WriteComm(0x2B);
	WriteData16(Y);
}

void LCD_ClipArea(u16 XStart, u16 YStart, u16 XEnd, u16 YEnd)
{
	WriteComm(0x2A);
	WriteData16(XStart);
	WriteData16(XEnd - 1);

	WriteComm(0x2B);
	WriteData16(YStart);
	WriteData16(YEnd - 1);
}

void LCD_EnterReadMode(void)
{
	volatile u32 i;
	WriteComm(0x2E);//Start read,reset address counter
	i = ReadData16();//dummy read
}

void LCD_EnterWriteMode(void)
{
	WriteComm(0x2C);//Start write,reset address counter
}

u16 LCD_Read(void)
{
	u16 Part1;
	u16 Part2;
	volatile u16 i;
	WriteComm(0x3E);//Continue read
	i = ReadData16();//dummy read
	Part1 = ReadData16();
	Part2 = ReadData16();
	return (Part1 & 0xF800) | ((Part1 & 0x00FC) << 3) | (Part2 >> 11);
}

void LCD_Write(u16 Dat)
{
	WriteData16(Dat);
}

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
