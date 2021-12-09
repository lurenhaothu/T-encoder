#ifndef UWCONTROL_H
#define UWCONTROL_H

#include "stm32f10x.h"

/*
int UWCounterLeft = 0;
int UWCounterRight = 0;

int UWCounterStateLeft;
int UWCounterStateRight;

int UWCountResultLeft = 0;
int UWCountResultRight = 0;
*/

#define UWLeft 0
#define UWRight 1

void GPIO_CFG(void);
void UW_PWM_CFG(void);
void NVIC_EXIT_CFG(void);
void UW_CFG(void);
u16 GetUWDistance(u8 position);

#endif
