#ifndef DECODER_H
#define DECODER_H

#include "stm32f10x.h"

#define DECODER_LEFT 0
#define DECODER_RIGHT 1

void Decoder_CFG(void);
void Timer1_Init(void);
void IRQHandlerTenMsDecoder(void);
short GetVelocity(u8 position);

#endif
