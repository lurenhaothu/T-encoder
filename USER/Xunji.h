#ifndef __XUNJI_H
#define __XUNJI_H

#include "stm32f10x.h"

#define  Out1 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)
#define  Out2 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)
#define  Out3 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8)
#define  Out4 GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9)
#define SPEED 20
#define SPEEDT 20

#define XUNJI_STOP 6
#define XUNJI_DOUBLE_LINE 0
#define XUNJI_SINGLE_LINE 1
#define XUNJI_DOUBLE_TO_SINGLE_ONE 2
#define XUNJI_DOUBLE_TO_SINGLE_TWO 3
#define XUNJI_SINGLE_TO_DOUBLE_ONE 4
#define XUNJI_SINGLE_TO_DOUBLE_TWO 5

#define XUNJI_LEFT 6
#define XUNJI_RIGHT 7
#define XUNJI_NONE 8

void A(void);

void XunjiCFG(void);
void Xunji(void);
void XunjiStateTransform(void);

u8 GetXunjiSate(void);
void Start(void);
void Stop(void);

#endif
