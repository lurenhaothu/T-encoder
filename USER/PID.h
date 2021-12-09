#ifndef PID_H
#define PID_H

#include "stm32f10x.h"

#define PID_LEFT 0
#define PID_RIGHT 1

#define P 0.7
#define Td 0
#define Ti 1

#define PID_FORWARD 0
#define PID_BACKWARD 1
#define PID_TURNRIGHT 2
#define PID_TURNLEFT 3

void PIDControl(u8 position, short velocity);
void PIDMotorControl(u8 direction, short velocity);

void IRQHandlerPID(void);

#endif
