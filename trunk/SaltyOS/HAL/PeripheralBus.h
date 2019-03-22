#pragma once

C_HEADER_BEGIN

#define ExpandReadWriteFunctions

STATUS PeripheralBus_Init(void);

#ifdef ExpandReadWriteFunctions
extern volatile u16* const PeripheralBusAddr;
#define PeripheralBus_Read(Addr) (*(volatile u16* const)(PeripheralBusAddr + (Addr)))
#define PeripheralBus_Write(Addr,Data) *(volatile u16* const)(PeripheralBusAddr + (Addr)) = (Data)
#else
u16 PeripheralBus_Read(u8 Addr);
void PeripheralBus_Write(u8 Addr, u16 Data);
#endif

//CPLD GPIO ports registers
#define PeripheralBus_GPIO0Base 00
#define PeripheralBus_GPIO1Base 08
#define PeripheralBus_GPIO2Base 16
#define PeripheralBus_GPIO3Base 24
#define PeripheralBus_GPIO4Base 32
#define PeripheralBus_GPIO5Base 40
#define PeripheralBus_GPIO6Base 48
#define PeripheralBus_GPIO7Base 56
#define PeripheralBus_GPIOxBase(x) ((x) * 8)

#define PeripheralBus_GPIOOffset_IOData 0
#define PeripheralBus_GPIOOffset_Set 1
#define PeripheralBus_GPIOOffset_Clear 2
#define PeripheralBus_GPIOOffset_Direction 3
#define PeripheralBus_GPIOOffset_Config 4

#define PeripheralBus_GPIO_ConfigBit_Reset (1<<0)
#define PeripheralBus_GPIO_ConfigBit_HiZ (1<<1)

//When reading from this address, the cpld captures the data on the pararrel port and automatically sends a clock to fpga
#define PeripheralBus_FPGARead 5

//CPLD global configure registers
#define PeripheralBus_Config 6
#define PeripheralBus_ConfigBit_Reset (1<<0)
#define PeripheralBus_ConfigBit_DedicatedFunctionUsed (1<<1)

//Read from this address will get the inverted value of the previously written value
#define PeripheralBus_CommTest 63

C_HEADER_END
