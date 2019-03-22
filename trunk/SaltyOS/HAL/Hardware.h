#pragma once

#define FSMC_Base 0x60000000L
#define FSMC_Base1 (FSMC_Base+(0L<<26))
#define FSMC_Base2 (FSMC_Base+(1L<<26))
#define FSMC_Base3 (FSMC_Base+(2L<<26))
#define FSMC_Base4 (FSMC_Base+(3L<<26))

#define SRAMBitBandBase  0x22000000
#define PeripheralBitBandBase 0x42000000
#define SRAMBase 0x20000000
#define PeripheralBase 0x40000000
#define BitBandAddr(BitBandBase,ByteOffset,BitNumber) (BitBandBase + ((ByteOffset) * 32) + ((BitNumber) * 4))
#define SRAMBitBandAddr(Addr,BitNumber) ((u32*)BitBandAddr(SRAMBitBandBase,(u32)(Addr)-SRAMBase,(BitNumber)))
#define PeripheralBitBandAddr(Addr,BitNumber) ((u32*)BitBandAddr(PeripheralBitBandBase,(u32)(Addr)-PeripheralBase,(BitNumber)))
