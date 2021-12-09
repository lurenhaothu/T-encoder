#ifndef _WIFIUART_H_
#define _WIFIUART_H_

#include "stm32f10x.h"

#define COMMAND_1 "AT+RST\r\n"
#define COMMAND_2 "AT+CWMODE=3\r\n"
#define COMMAND_3 "AT+RST\r\n"
#define COMMAND_4 "AT+CIPMUX=1\r\n"
#define COMMAND_5 "AT+CIPSERVER=1\r\n"
#define COMMAND_6 "AT+CIPSEND=0,4\r\n"

#define SENDING_STATE_1_SENDING 0
#define SENDING_STATE_2_SENDING 1
#define SENDING_STATE_3_SENDING 2
#define SENDING_STATE_4_SENDING 3
#define SENDING_STATE_5_SENDING 4

#define SENDING_STATE_1_RECEING 5
#define SENDING_STATE_2_RECEING 6
#define SENDING_STATE_3_RECEING 7
#define SENDING_STATE_4_RECEING 8
#define SENDING_STATE_5_RECEING 9

#define SENDING_NONE 10

#define SENDING_WAITING_CONNECTION 16
#define SENDING_MOTOR_STATE 11
#define SENDING_MOTOR_STATE_WAITING 17

#define SENDING_MOTOR_STATE_1_SENDING 12
#define SENDING_MOTOR_STATE_2_RECEIVEING 13
#define SENDING_MOTOR_STATE_3_SENDING 14
#define SENDING_MOTOR_STATE_4_RECEIVEING 15

void WIFI_IRQ_Handler(void);
void TIM6_CFG(void);

#endif