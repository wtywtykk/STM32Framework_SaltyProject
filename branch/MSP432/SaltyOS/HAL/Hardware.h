#pragma once

#define SRAMBitBandBase  0x22000000
#define PeripheralBitBandBase 0x42000000
#define SRAMBase 0x20000000
#define PeripheralBase 0x40000000
#define BitBandAddr(BitBandBase,ByteOffset,BitNumber) (BitBandBase + ((ByteOffset) * 32) + ((BitNumber) * 4))
#define SRAMBitBandAddr(Addr,BitNumber) ((u32*)BitBandAddr(SRAMBitBandBase,(u32)(Addr)-SRAMBase,(BitNumber)))
#define PeripheralBitBandAddr(Addr,BitNumber) ((u8*)BitBandAddr(PeripheralBitBandBase,(u32)(Addr)-PeripheralBase,(BitNumber)))
