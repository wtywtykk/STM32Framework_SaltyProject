#include "HCommon.h"

__weak void GPIO_EXTI0_Callback(void);
__weak void GPIO_EXTI1_Callback(void);
__weak void GPIO_EXTI2_Callback(void);
__weak void GPIO_EXTI3_Callback(void);
__weak void GPIO_EXTI4_Callback(void);
__weak void GPIO_EXTI5_Callback(void);
__weak void GPIO_EXTI6_Callback(void);
__weak void GPIO_EXTI7_Callback(void);
__weak void GPIO_EXTI8_Callback(void);
__weak void GPIO_EXTI9_Callback(void);
__weak void GPIO_EXTI10_Callback(void);
__weak void GPIO_EXTI11_Callback(void);
__weak void GPIO_EXTI12_Callback(void);
__weak void GPIO_EXTI13_Callback(void);
__weak void GPIO_EXTI14_Callback(void);
__weak void GPIO_EXTI15_Callback(void);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch (GPIO_Pin)
	{
	case GPIO_PIN_0:
		GPIO_EXTI0_Callback();
		break;
	case GPIO_PIN_1:
		GPIO_EXTI1_Callback();
		break;
	case GPIO_PIN_2:
		GPIO_EXTI2_Callback();
		break;
	case GPIO_PIN_3:
		GPIO_EXTI3_Callback();
		break;
	case GPIO_PIN_4:
		GPIO_EXTI4_Callback();
		break;
	case GPIO_PIN_5:
		GPIO_EXTI5_Callback();
		break;
	case GPIO_PIN_6:
		GPIO_EXTI6_Callback();
		break;
	case GPIO_PIN_7:
		GPIO_EXTI7_Callback();
		break;
	case GPIO_PIN_8:
		GPIO_EXTI8_Callback();
		break;
	case GPIO_PIN_9:
		GPIO_EXTI9_Callback();
		break;
	case GPIO_PIN_10:
		GPIO_EXTI10_Callback();
		break;
	case GPIO_PIN_11:
		GPIO_EXTI11_Callback();
		break;
	case GPIO_PIN_12:
		GPIO_EXTI12_Callback();
		break;
	case GPIO_PIN_13:
		GPIO_EXTI13_Callback();
		break;
	case GPIO_PIN_14:
		GPIO_EXTI14_Callback();
		break;
	case GPIO_PIN_15:
		GPIO_EXTI15_Callback();
		break;
	}
}

__weak void GPIO_EXTI0_Callback(void)
{
}

__weak void GPIO_EXTI1_Callback(void)
{
}

__weak void GPIO_EXTI2_Callback(void)
{
}

__weak void GPIO_EXTI3_Callback(void)
{
}

__weak void GPIO_EXTI4_Callback(void)
{
}

__weak void GPIO_EXTI5_Callback(void)
{
}

__weak void GPIO_EXTI6_Callback(void)
{
}

__weak void GPIO_EXTI7_Callback(void)
{
}

__weak void GPIO_EXTI8_Callback(void)
{
}

__weak void GPIO_EXTI9_Callback(void)
{
}

__weak void GPIO_EXTI10_Callback(void)
{
}

__weak void GPIO_EXTI11_Callback(void)
{
}

__weak void GPIO_EXTI12_Callback(void)
{
}

__weak void GPIO_EXTI13_Callback(void)
{
}

__weak void GPIO_EXTI14_Callback(void)
{
}

__weak void GPIO_EXTI15_Callback(void)
{
}
