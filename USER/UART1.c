#include "Uart1.h"

char SendBuffer[256];
u8 SendHead = 0, SendTail = 0;
char ReceiveBuffer[256];
u8 ReceivePosition = 0;

void NVIC_Configuration(void){
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel=DEBUG_USART_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;

    NVIC_Init(&NVIC_InitStructure);
}

void USART_Config(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK,ENABLE);
    DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin=DEBUG_USART_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT,&GPIO_InitStructure);
	
	GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE); 

    USART_InitStructure.USART_BaudRate=DEBUG_USART_BAUDRATE;
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;
    USART_InitStructure.USART_StopBits=USART_StopBits_1;
    USART_InitStructure.USART_Parity=USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
    USART_Init(DEBUG_USARTx,&USART_InitStructure);

    NVIC_Configuration();

    USART_ITConfig(DEBUG_USARTx,USART_IT_RXNE,ENABLE);

    USART_Cmd(DEBUG_USARTx,ENABLE);
}

u8 SendString(char* str){
	u8 i = 0, u = 1;
	if(SendTail == SendHead) u = 0;
	for(i = 0; str[i] != '\0'; i++){
		SendBuffer[SendTail] = str[i];
		SendTail++;
		if(SendTail == SendHead){
			return 0;
		}
	}
	if(u == 0){
		USART_SendData(DEBUG_USARTx, SendBuffer[SendHead]);
		SendHead++;
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	}
	return 1;
}

void DeleteReceiveData(void){
	u8 num;
	ReceivePosition = 0;
	for(num = 0; ; num++){
		ReceiveBuffer[num] = '\0';
		if(num == 0xff){
			break;
		}
	}
}

char* getReceiveBuffer(void){
	return ReceiveBuffer;
}

u8 getReceivePostion(void){
	return ReceivePosition;
}

void DEBUG_USART_IRQHandler(void){
    if(USART_GetITStatus(DEBUG_USARTx,USART_IT_TXE) == SET){
		if(SendHead != SendTail){
			USART_SendData(DEBUG_USARTx, SendBuffer[SendHead]);
			SendHead++;
		}else{
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
		}
    }
	
	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE) != RESET){
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		ReceiveBuffer[ReceivePosition] = USART_ReceiveData(DEBUG_USARTx);
		ReceiveBuffer[ReceivePosition + 1] = '\0';
		ReceivePosition++;
	}
}
