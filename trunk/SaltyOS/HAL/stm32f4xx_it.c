/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
  /* Includes ------------------------------------------------------------------*/
#include "HCommon.h"
#include "PowerManagement.h"
#include "USB.h"

/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
	BeepAndReset(1);
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
	BeepAndReset(2);
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
	BeepAndReset(3);
}

/**
* @brief This function handles Pre-fetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
	BeepAndReset(4);
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
	BeepAndReset(5);
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
	/* USER CODE BEGIN SVCall_IRQn 0 */

	/* USER CODE END SVCall_IRQn 0 */
	/* USER CODE BEGIN SVCall_IRQn 1 */

	/* USER CODE END SVCall_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
	/* USER CODE BEGIN DebugMonitor_IRQn 0 */

	/* USER CODE END DebugMonitor_IRQn 0 */
	/* USER CODE BEGIN DebugMonitor_IRQn 1 */

	/* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
	/* USER CODE BEGIN PendSV_IRQn 0 */

	/* USER CODE END PendSV_IRQn 0 */
	/* USER CODE BEGIN PendSV_IRQn 1 */

	/* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
	/* USER CODE BEGIN SysTick_IRQn 0 */

	/* USER CODE END SysTick_IRQn 0 */
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
	/* USER CODE BEGIN SysTick_IRQn 1 */

	/* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */

void EXTI0_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void EXTI1_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}

void EXTI2_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}

void EXTI3_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
}

void EXTI4_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

void EXTI9_5_IRQHandler(void)
{
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_5))
	{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
	}
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_6))
	{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
	}
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_7))
	{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
	}
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_8))
	{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
	}
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_9))
	{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
	}
}

void EXTI15_10_IRQHandler(void)
{
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_10))
	{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
	}
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_11))
	{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
	}
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12))
	{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
	}
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13))
	{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
	}
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_14))
	{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
	}
	if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_15))
	{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
	}
}

void OTG_FS_IRQHandler(void)
{
	USB_IRQHandler();
}

void OTG_HS_IRQHandler(void)
{
	USB_IRQHandler();
}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
