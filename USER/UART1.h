#ifndef _UART1_H_
#define _UART1_H_
		
#include "stm32f10x.h"
	
#define DEBUG_USARTx                        USART1
#define DEBUG_USART_CLK                     RCC_APB2Periph_USART1
#define DEBUG_USART_APBxClkCmd              RCC_APB2PeriphClockCmd
#define DEBUG_USART_BAUDRATE                115200

//USART GPIO
#define DEBUG_USART_GPIO_CLK                (RCC_APB2Periph_GPIOB)
#define DEBUG_USART_GPIO_APBxClkCmd         RCC_APB2PeriphClockCmd

#define DEBUG_USART_TX_GPIO_PORT            GPIOB
#define DEBUG_USART_TX_GPIO_PIN             GPIO_Pin_6
#define DEBUG_USART_RX_GPIO_PORT            GPIOB
#define DEBUG_USART_RX_GPIO_PIN             GPIO_Pin_7

#define DEBUG_USART_IRQ                     USART1_IRQn
#define DEBUG_USART_IRQHandler              USART1_IRQHandler

void NVIC_Configuration(void);
void USART_Config(void);
u8 SendString(char* str);
void DeleteReceiveData(void);
char* getReceiveBuffer(void);
u8 getReceivePostion(void);
		
#endif
