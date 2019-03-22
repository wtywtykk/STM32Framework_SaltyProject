#pragma once

#define WINBOND_ID 0xEF
#define W25Q80_DeviceID 0x12
#define W25Q16_DeviceID 0x13
#define W25Q32_DeviceID 0x15
#define W25Q64_DeviceID 0x16
#define W25Q128_DeviceID 0x17

#define W25Qxx_CMD_WriteEnable 0x06
#define W25Qxx_CMD_VolatileSRWriteEnable 0x06
#define W25Qxx_CMD_WriteDisable 0x04
#define W25Qxx_CMD_ReadStatusReg1 0x05
#define W25Qxx_CMD_WriteStatusReg1 0x01
#define W25Qxx_CMD_ReadStatusReg2 0x35
#define W25Qxx_CMD_WriteStatusReg2 0x31
#define W25Qxx_CMD_ReadStatusReg3 0x15
#define W25Qxx_CMD_WriteStatusReg3 0x11
#define W25Qxx_CMD_ChipErase 0xC7//or 0x60
#define W25Qxx_CMD_EraseProgramSuspend 0x75
#define W25Qxx_CMD_EraseProgramResume 0x7A
#define W25Qxx_CMD_PowerDown 0xB9
#define W25Qxx_CMD_ReleasePowerDown_ID 0xAB
#define W25Qxx_CMD_Manufacturer_DeviveID 0x90
#define W25Qxx_CMD_JEDECID 0x9F
#define W25Qxx_CMD_GlobalBlockLock 0x7E
#define W25Qxx_CMD_GlobalBlockUnlock 0x98
#define W25Qxx_CMD_EnterQPIMode 0x38
#define W25Qxx_CMD_EnableReset 0x66
#define W25Qxx_CMD_ResetDevice 0x99

#define W25Qxx_CMD_ReadUniqueID 0x4B
#define W25Qxx_CMD_PageProgram 0x02
#define W25Qxx_CMD_QuadPageProgram 0x32
#define W25Qxx_CMD_SectorErase 0x20 //Sector 4k Erase
#define W25Qxx_CMD_BlockErase32 0x52 //Block 32k Erase
#define W25Qxx_CMD_BlockErase64 0xD8 //Block 64k Erase
#define W25Qxx_CMD_ReadData 0x03
#define W25Qxx_CMD_FastRead 0x0B
#define W25Qxx_CMD_FastReadDualOutput 0x3B
#define W25Qxx_CMD_FastReadQuadOutput 0x6B
#define W25Qxx_CMD_ReadSFDPRegister 0x5A
#define W25Qxx_CMD_EraseSecurityRegister 0x44
#define W25Qxx_CMD_ProgramSecurityRegister 0x42
#define W25Qxx_CMD_ReadSecurityRegister 0x48
#define W25Qxx_CMD_IndividualBlockLock 0x36
#define W25Qxx_CMD_IndividualBlockUnlock 0x39
#define W25Qxx_CMD_ReadBlockLock 0x3D

#define W25Qxx_CMD_FastReadDualIO 0xBB
#define W25Qxx_CMD_Mftr_DeviceIDDualIO 0xBB

#define W25Qxx_CMD_SetBurstWithWarp 0x77
#define W25Qxx_CMD_FastReadQuadIO 0xEB
#define W25Qxx_CMD_WordReadQuadIO 0xE7
#define W25Qxx_CMD_OctalWordReadQuadIO 0xE3
#define W25Qxx_CMD_Mftr_DeviceIDQuadIO 0x94

#define W25Qxx_DUMMY_BYTE 0xFF

#define W25Qxx_SR1_SRP0 (1<<7)
#define W25Qxx_SR1_SEC (1<<6)
#define W25Qxx_SR1_TB (1<<5)
#define W25Qxx_SR1_BP2 (1<<4)
#define W25Qxx_SR1_BP1 (1<<3)
#define W25Qxx_SR1_BP0 (1<<2)
#define W25Qxx_SR1_WEL (1<<1)
#define W25Qxx_SR1_BUSY (1<<0)

#define W25Qxx_SR2_SUS (1<<7)
#define W25Qxx_SR2_CMP (1<<6)
#define W25Qxx_SR2_LB3 (1<<5)
#define W25Qxx_SR2_LB2 (1<<4)
#define W25Qxx_SR2_LB1 (1<<3)
#define W25Qxx_SR2_RESERVED (1<<2)
#define W25Qxx_SR2_QuadEnable (1<<1)
#define W25Qxx_SR2_SRP1 (1<<0)

#define W25Qxx_SR3_HOLD_RST (1<<7)
#define W25Qxx_SR3_DRV1 (1<<6)
#define W25Qxx_SR3_DRV0 (1<<5)
#define W25Qxx_SR3_RESERVED3 (1<<4)
#define W25Qxx_SR3_RESERVED2 (1<<3)
#define W25Qxx_SR3_WPS (1<<2)
#define W25Qxx_SR3_RESERVED1 (1<<1)
#define W25Qxx_SR3_RESERVED0 (1<<0)

#define W25Qxx_PageSize 256
#define W25Qxx_SectorSize 4096
