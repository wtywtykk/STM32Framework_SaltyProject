#pragma once

#define ZLG7290_I2C_SLAVE_ADDRESS	((uint8_t)0x70)

#define ZLG7290_REG_SystemReg ((uint8_t)0x00)
#define ZLG7290_REG_Key ((uint8_t)0x01)
#define ZLG7290_REG_RepeatCnt ((uint8_t)0x02)
#define ZLG7290_REG_FunctionKey ((uint8_t)0x03)

#define ZLG7290_REG_CmdBuf0 ((uint8_t)0x07)
#define ZLG7290_REG_CmdBuf1 ((uint8_t)0x08)
#define ZLG7290_REG_FlashOnOff ((uint8_t)0x0C)
#define ZLG7290_REG_ScanNum ((uint8_t)0x0D)
#define ZLG7290_REG_DpRam0 ((uint8_t)0x10)
#define ZLG7290_REG_DpRam1 ((uint8_t)0x11)
#define ZLG7290_REG_DpRam2 ((uint8_t)0x12)
#define ZLG7290_REG_DpRam3 ((uint8_t)0x13)
#define ZLG7290_REG_DpRam4 ((uint8_t)0x14)
#define ZLG7290_REG_DpRam5 ((uint8_t)0x15)
#define ZLG7290_REG_DpRam6 ((uint8_t)0x16)
#define ZLG7290_REG_DpRam7 ((uint8_t)0x17)

#define ZLG7290_SystemReg_KeyAvi ((uint8_t)1<<0)
