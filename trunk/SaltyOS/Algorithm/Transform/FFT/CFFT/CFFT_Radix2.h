#pragma once

void CFFT_Radix2_BitReverse_Recursive(float* Buf, u8 Log2Length);
void CFFT_Radix2_BitReverse(float* Buf, u8 Log2Length);
void CFFT_Radix2_ReOrder(float* Buf, u8 Log2Length);
