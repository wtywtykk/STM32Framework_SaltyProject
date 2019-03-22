//#include "HAL\HCommon.h"
//#include "HAL\UniGPIO.h"
//#include "FT5336.h"
//#include "FT5336_Reg.h"
//#include <string.h>
//
//UniGPIO_Handle CTP_INT;
//UniGPIO_Handle RTP_CLK;
//UniGPIO_Handle RTP_MOSI;
//UniGPIO_Handle RTP_MISO;
//
//#define FT5336_MAX_POINTS 5
//
//typedef struct
//{
//	u8 XH;
//	u8 XL;
//	u8 YH;
//	u8 YL;
//	u8 WEIGHT;
//	u8 MISC;
//}FT5336_POINT_REG;
//
//static bool Touch_Initialized = false;
////static u16 MaxWidth;
////static u16 MaxHeight;
//static I2C_HandleTypeDef Touch_IIC_Handle;
//TouchRawData RawData[FT5336_MAX_POINTS];
//
//static STATUS Touch_ResetIICBusAndInitIICPins();
//
//static STATUS Touch_ReadPoints(FT5336_POINT_REG* Point, u8 Count);
//static STATUS Touch_PhasePoint(const FT5336_POINT_REG* Point, TouchRawData* PhasedPoint);
//
//static STATUS Touch_CheckID(void);
//
//static STATUS Touch_ReadReg(u8 RegAddr, void* Buffer, u8 Length);
//static STATUS Touch_WriteReg(u8 RegAddr, void* Buffer, u8 Length);
//
//STATUS Touch_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStruct;
//
//	if (Touch_Initialized)
//	{
//		return S_OK;
//	}
//
//	//CTP interrupt pin
//	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//	GPIO_InitStruct.Pull = GPIO_PULLUP;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//	GPIO_InitStruct.Alternate = 0;
//
//	GPIO_InitStruct.Pin = GPIO_PIN_15;
//	GPIO_32_InitPin(GPIOG, &GPIO_InitStruct, &CTP_INT);
//
//	//Not used by CTP,configure them as analog input to avoid unnecessary current consumption
//	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//	GPIO_InitStruct.Alternate = 0;
//
//	GPIO_InitStruct.Pin = GPIO_PIN_3;
//	GPIO_32_InitPin(GPIOB, &GPIO_InitStruct, &RTP_CLK);
//	GPIO_InitStruct.Pin = GPIO_PIN_4;
//	GPIO_32_InitPin(GPIOB, &GPIO_InitStruct, &RTP_MISO);
//	GPIO_InitStruct.Pin = GPIO_PIN_5;
//	GPIO_32_InitPin(GPIOB, &GPIO_InitStruct, &RTP_MOSI);
//
//	__HAL_RCC_I2C2_CLK_ENABLE();
//
//	Touch_IIC_Handle.Instance = I2C2;
//	Touch_IIC_Handle.Init.ClockSpeed = 400000;//400kHz
//	Touch_IIC_Handle.Init.DutyCycle = I2C_DUTYCYCLE_2;
//	Touch_IIC_Handle.Init.OwnAddress1 = 0;
//	Touch_IIC_Handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
//	Touch_IIC_Handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
//	Touch_IIC_Handle.Init.OwnAddress2 = 0;
//	Touch_IIC_Handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
//	Touch_IIC_Handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
//
//	//Reset IIC state machine
//	Touch_IIC_Handle.Instance->CR1 |= I2C_CR1_SWRST;
//	Touch_IIC_Handle.Instance->CR1 &= ~I2C_CR1_SWRST;
//
//	if (HAL_I2C_Init(&Touch_IIC_Handle) != HAL_OK)
//	{
//		return S_FAIL;
//	}
//
//	Touch_ResetIICBusAndInitIICPins(&Touch_IIC_Handle);
//
//	if (Touch_CheckID() != S_OK)
//	{
//		return S_FAIL;
//	}
//
//	u8 b = 2;
//	Touch_WriteReg(FT5336_PERIODACTIVE_REG, &b, 1);
//	Touch_WriteReg(FT5336_PERIODMONITOR_REG, &b, 1);
//
//	memset(RawData, 0, sizeof(RawData));
//
//	Touch_Initialized = true;
//
//	return S_OK;
//}
//
//void Touch_SetUpdateMode(TouchUpdateMode NewMode)
//{/*
//	uint8_t regValue = 0;
//	regValue = (FT5336_G_MODE_INTERRUPT_TRIGGER << FT5336_G_MODE_INTERRUPT_SHIFT) & FT5336_G_MODE_INTERRUPT_MASK;
//
//	//Set interrupt trigger mode in FT5336_GMODE_REG
//	Touch_WriteReg(FT5336_GMODE_REG, &regValue, sizeof(regValue));
//
//	//ft5336_TS_DisableIT
//	uint8_t regValue = 0;
//	regValue = (FT5336_G_MODE_INTERRUPT_POLLING << FT5336_G_MODE_INTERRUPT_SHIFT) & FT5336_G_MODE_INTERRUPT_MASK;
//
//	//Set interrupt polling mode in FT5336_GMODE_REG
//	Touch_WriteReg(FT5336_GMODE_REG, &regValue, sizeof(regValue));*/
//}
//
//void SetUpdateSpeed(u8 ActiveRate, u8 MonitorRate)
//{
//}
//
//void GPIO_EXTI15_Callback(void)
//{
//}
//
//STATUS Touch_Read(void)
//{
//	u8 PointCount;
//	FT5336_POINT_REG Points[FT5336_MAX_POINTS];
//	u8 i;
//
//	if (Touch_ReadReg(FT5336_TD_STAT_REG, &PointCount, sizeof(PointCount)) != S_OK)
//	{
//		return S_FAIL;
//	}
//
//	i = 0;
//	if (PointCount > 0 && PointCount <= FT5336_MAX_POINTS)
//	{
//		if (Touch_ReadPoints(Points, PointCount) != S_OK)
//		{
//			return S_FAIL;
//		}
//		for (; i < PointCount; i++)
//		{
//			Touch_PhasePoint(&Points[i], &RawData[i]);
//		}
//	}
//
//	for (; i < FT5336_MAX_POINTS; i++)
//	{
//		RawData[i].Weight = 0;
//	}
//
//	return S_OK;
//}
//
//static STATUS Touch_ResetIICBusAndInitIICPins()
//{
//	UniGPIO_Handle CTP_SCK;
//	UniGPIO_Handle CTP_SDA;
//	GPIO_InitTypeDef GPIO_InitStruct;
//	u32 i;
//
//	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
//	GPIO_InitStruct.Pull = GPIO_PULLUP;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//
//	GPIO_InitStruct.Pin = GPIO_PIN_10;
//	GPIO_32_InitPin(GPIOB, &GPIO_InitStruct, &CTP_SCK);
//	GPIO_InitStruct.Pin = GPIO_PIN_11;
//	GPIO_32_InitPin(GPIOB, &GPIO_InitStruct, &CTP_SDA);
//
//	UniGPIO_SetHigh(&CTP_SCK);
//	UniGPIO_SetHigh(&CTP_SDA);
//
//	//Toggle SCK 9 times to reset iic bus
//	for (i = 0; i < 9; i++)
//	{
//		HAL_Delay(1);
//		UniGPIO_SetLow(&CTP_SCK);
//		HAL_Delay(1);
//		UniGPIO_SetHigh(&CTP_SCK);
//	}
//
//	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
//	GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;
//	GPIO_InitStruct.Pin = GPIO_PIN_10;
//	GPIO_32_InitPin(GPIOB, &GPIO_InitStruct, &CTP_SCK);
//	GPIO_InitStruct.Pin = GPIO_PIN_11;
//	GPIO_32_InitPin(GPIOB, &GPIO_InitStruct, &CTP_SDA);
//
//	return S_OK;
//}
//
//static STATUS Touch_ReadPoints(FT5336_POINT_REG* Point, u8 Count)
//{
//	if (Touch_ReadReg(FT5336_P1_XH_REG, Point, sizeof(FT5336_POINT_REG) * Count) != S_OK)
//	{
//		return S_FAIL;
//	}
//	return S_OK;
//}
//
//static STATUS Touch_PhasePoint(const FT5336_POINT_REG* Point, TouchRawData* PhasedPoint)
//{
//	PhasedPoint->X = (Point->XL & FT5336_TOUCH_POS_LSB_MASK) >> FT5336_TOUCH_POS_LSB_SHIFT;
//	PhasedPoint->X |= ((Point->XH & FT5336_TOUCH_POS_MSB_MASK) >> FT5336_TOUCH_POS_MSB_SHIFT) << 8;
//
//	PhasedPoint->Y = (Point->YL & FT5336_TOUCH_POS_LSB_MASK) >> FT5336_TOUCH_POS_LSB_SHIFT;
//	PhasedPoint->Y |= ((Point->YH & FT5336_TOUCH_POS_MSB_MASK) >> FT5336_TOUCH_POS_MSB_SHIFT) << 8;
//
//	PhasedPoint->EventFlag = (Point->XH & FT5336_TOUCH_EVT_FLAG_MASK) >> FT5336_TOUCH_EVT_FLAG_SHIFT;
//
//	PhasedPoint->TouchID = (Point->YH & FT5336_TOUCH_ID_FLAG_MASK) >> FT5336_TOUCH_ID_FLAG_SHIFT;
//
//	PhasedPoint->Weight = (Point->WEIGHT & FT5336_TOUCH_WEIGHT_MASK) >> FT5336_TOUCH_WEIGHT_SHIFT;
//
//	PhasedPoint->Area = (Point->MISC & FT5336_TOUCH_AREA_MASK) >> FT5336_TOUCH_AREA_SHIFT;
//
//	return S_OK;
//}
//
//static STATUS Touch_CheckID(void)
//{
//	u8 ReadAttempts;
//	//At maximum 4 attempts to read ID : exit at first finding of the searched device ID
//	for (ReadAttempts = 0; ReadAttempts < 3; ReadAttempts++)
//	{
//		u8 DeviceID;
//
//		HAL_Delay(10);
//		//Read register FT5336_CHIP_ID_REG as DeviceID detection
//		if (Touch_ReadReg(FT5336_CHIP_ID_REG, &DeviceID, sizeof(DeviceID)) == S_OK && DeviceID == FT5336_ID_VALUE)
//		{
//			//Device found
//			return S_OK;
//		}
//	}
//	//Device NOT found
//	return S_FAIL;
//}
//
//static STATUS Touch_ReadReg(u8 RegAddr, void* Buffer, u8 Length)
//{
//	if (HAL_I2C_Mem_Read(&Touch_IIC_Handle, FT5336_I2C_SLAVE_ADDRESS, RegAddr, I2C_MEMADD_SIZE_8BIT, Buffer, Length, 5) != HAL_OK)
//	{
//		return S_FAIL;
//	}
//	return S_OK;
//}
//
//static STATUS Touch_WriteReg(u8 RegAddr, void* Buffer, u8 Length)
//{
//	if (HAL_I2C_Mem_Write(&Touch_IIC_Handle, FT5336_I2C_SLAVE_ADDRESS, RegAddr, I2C_MEMADD_SIZE_8BIT, Buffer, Length, 5) != HAL_OK)
//	{
//		return S_FAIL;
//	}
//	return S_OK;
//}
