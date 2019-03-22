#include "HAL\HCommon.h"
#include "HAL\UniGPIO.h"
#include "Driver\ZLG7290_Reg.h"
#include "Driver\Encoder_Reg.h"

/*Modify those if you want to use other IIC ports*/
/************************************************************************************/
#define KeyBoard_IIC_CLOCK_ENABLE __HAL_RCC_I2C2_CLK_ENABLE
#define KeyBoard_IIC_INSTANCE I2C2
#define KeyBoard_IIC_AF GPIO_AF4_I2C2
#define KeyBoard_IIC_CLOCK_SPEED 100000//100KHz
#define KeyBoard_IIC_TIMEOUT 2
#define KeyBoard_IIC_SCL_PORT GPIOB
#define KeyBoard_IIC_SCL_PIN	GPIO_PIN_10
#define KeyBoard_IIC_SDA_PORT GPIOB
#define KeyBoard_IIC_SDA_PIN GPIO_PIN_11
#define KeyBoard_INT_PORT GPIOA
#define KeyBoard_INT_PIN GPIO_PIN_8
#define KeyBoard_INT_ROUTINE_NAME GPIO_EXTI8_Callback
/************************************************************************************/

#define EncoderPushL_KeyVal 254
#define EncoderPushR_KeyVal 255

I2C_HandleTypeDef KeyBoard_IIC_Handle;
UniGPIO_Handle KeyBoard_INT;
bool KeyBoard_Initialized = false;

u8 LastVal = 0;
u8 LastCnt = 0;
s32 EncoderVal[2] = { 0,0 };

STATUS KeyBoard_IICInit(void);
STATUS KeyBoard_ResetIICBusAndInitIICPins(void);

STATUS KeyBoard_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	if (KeyBoard_Initialized)
	{
		return S_OK;
	}

	if (KeyBoard_IICInit() != S_OK)
	{
		return S_FAIL;
	}

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = 0;
	GPIO_InitStruct.Pin = KeyBoard_INT_PIN;
	GPIO_32_InitPin(KeyBoard_INT_PORT, &GPIO_InitStruct, &KeyBoard_INT);

	KeyBoard_Initialized = true;

	return S_OK;
}

void KeyBoard_INT_ROUTINE_NAME(void)
{
}

STATUS KeyBoard_GetEncoderRegs(s8 Val[3])
{
	if (HAL_I2C_Master_Receive(&KeyBoard_IIC_Handle, ENCODER_I2C_SLAVE_ADDRESS, (u8*)Val, 3, KeyBoard_IIC_TIMEOUT) == HAL_OK)
	{
		return S_OK;
	}
	return S_FAIL;
}

STATUS KeyBoard_GetRegs(u8* KeyVal, u8* RepeatCount)
{
	if (HAL_I2C_Mem_Read(&KeyBoard_IIC_Handle, ZLG7290_I2C_SLAVE_ADDRESS, ZLG7290_REG_Key, I2C_MEMADD_SIZE_8BIT, KeyVal, 1, KeyBoard_IIC_TIMEOUT) == HAL_OK &&
		HAL_I2C_Mem_Read(&KeyBoard_IIC_Handle, ZLG7290_I2C_SLAVE_ADDRESS, ZLG7290_REG_RepeatCnt, I2C_MEMADD_SIZE_8BIT, RepeatCount, 1, KeyBoard_IIC_TIMEOUT) == HAL_OK)
	{
		s8 EncVal[3] = { 0,0,0 };
		if (*KeyVal == 0)
		{
			//Encoder is optional......
			if (KeyBoard_GetEncoderRegs(EncVal) == S_OK)
			{
				EncoderVal[0] += EncVal[0];
				EncoderVal[1] += EncVal[1];
				switch (EncVal[2])
				{
				case 1:
					*KeyVal = EncoderPushL_KeyVal;
					break;
				case 2:
					*KeyVal = EncoderPushR_KeyVal;
					break;
				default:
					break;
				}
			}
		}
		return S_OK;
	}
	else
	{
		//Maybe there's something wrong with the IIC state machine.We need to reset it.
		KeyBoard_IICInit();
		return S_FAIL;
	}
}

u8 KeyBoard_GetKey_Single(void)
{
	u8 KeyVal = 0;
	u8 RepeatCount = 0;
	if (KeyBoard_GetRegs(&KeyVal, &RepeatCount) == S_OK)
	{
		if (LastVal != KeyVal || RepeatCount == 255)
		{
			LastVal = KeyVal;
			LastCnt = RepeatCount;
			return KeyVal;
		}
	}
	return 0;
}

u8 KeyBoard_GetKey_Repeat(void)
{
	u8 KeyVal = 0;
	u8 RepeatCount = 0;
	if (KeyBoard_GetRegs(&KeyVal, &RepeatCount) == S_OK)
	{
		if (LastVal != KeyVal || LastCnt != RepeatCount || RepeatCount == 255)
		{
			u8 Zero = 0;
			if (RepeatCount >= 200)
			{
				HAL_I2C_Mem_Write(&KeyBoard_IIC_Handle, ZLG7290_I2C_SLAVE_ADDRESS, ZLG7290_REG_RepeatCnt, I2C_MEMADD_SIZE_8BIT, &Zero, 1, KeyBoard_IIC_TIMEOUT);
			}
			LastVal = KeyVal;
			LastCnt = RepeatCount;
			return KeyVal;
		}
	}
	return 0;
}

s32 KeyBoard_GetEncoderVal(u8 Index)
{
	if (Index < sizeof(EncoderVal) / sizeof(EncoderVal[0]))
	{
		s32 Ret = EncoderVal[Index];
		EncoderVal[Index] = 0;
		return Ret;
	}
	return 0;
}

STATUS KeyBoard_IICInit(void)
{
	KeyBoard_IIC_CLOCK_ENABLE();

	KeyBoard_IIC_Handle.Instance = KeyBoard_IIC_INSTANCE;
	KeyBoard_IIC_Handle.Init.ClockSpeed = KeyBoard_IIC_CLOCK_SPEED;
	KeyBoard_IIC_Handle.Init.DutyCycle = I2C_DUTYCYCLE_2;
	KeyBoard_IIC_Handle.Init.OwnAddress1 = 0;
	KeyBoard_IIC_Handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	KeyBoard_IIC_Handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	KeyBoard_IIC_Handle.Init.OwnAddress2 = 0;
	KeyBoard_IIC_Handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	KeyBoard_IIC_Handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	//Reset IIC state machine
	KeyBoard_IIC_Handle.Instance->CR1 |= I2C_CR1_SWRST;
	KeyBoard_IIC_Handle.Instance->CR1 &= ~I2C_CR1_SWRST;

	HAL_I2C_DeInit(&KeyBoard_IIC_Handle);
	if (HAL_I2C_Init(&KeyBoard_IIC_Handle) != HAL_OK)
	{
		return S_FAIL;
	}

	KeyBoard_ResetIICBusAndInitIICPins();

	return S_OK;
}

STATUS KeyBoard_ResetIICBusAndInitIICPins(void)
{
	UniGPIO_Handle SCL;
	UniGPIO_Handle SDA;
	GPIO_InitTypeDef GPIO_InitStruct;
	u32 i;

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	GPIO_InitStruct.Pin = KeyBoard_IIC_SCL_PIN;
	GPIO_32_InitPin(KeyBoard_IIC_SCL_PORT, &GPIO_InitStruct, &SCL);
	GPIO_InitStruct.Pin = KeyBoard_IIC_SDA_PIN;
	GPIO_32_InitPin(KeyBoard_IIC_SDA_PORT, &GPIO_InitStruct, &SDA);

	UniGPIO_SetHigh(&SCL);
	UniGPIO_SetHigh(&SDA);

	//Toggle SCK 9 times to reset iic bus
	for (i = 0; i < 9; i++)
	{
		HAL_Delay(1);
		UniGPIO_SetLow(&SCL);
		HAL_Delay(1);
		UniGPIO_SetHigh(&SCL);
	}

	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Alternate = KeyBoard_IIC_AF;
	GPIO_InitStruct.Pin = KeyBoard_IIC_SCL_PIN;
	GPIO_32_InitPin(KeyBoard_IIC_SCL_PORT, &GPIO_InitStruct, &SCL);
	GPIO_InitStruct.Pin = KeyBoard_IIC_SDA_PIN;
	GPIO_32_InitPin(KeyBoard_IIC_SDA_PORT, &GPIO_InitStruct, &SDA);

	return S_OK;
}
