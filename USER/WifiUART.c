#include "WifiUART.h"
#include "UART1.h"
#include "Xunji.h"

u8 WifiState = SENDING_STATE_1_SENDING;
u8 SendMotorState = SENDING_MOTOR_STATE_1_SENDING;
u8 SendMotorNumber = 0;

void WIFI_IRQ_Handler(void){
	u8 NumForWhile;
	char* RecBuff = getReceiveBuffer();
	char state[4] = "abcd";
	switch(WifiState){
		case SENDING_NONE:
			
			break;
		
		case SENDING_STATE_1_SENDING:
			SendString(COMMAND_1);
			WifiState = SENDING_STATE_1_RECEING;
			break;
		
		case SENDING_STATE_1_RECEING:
			for(NumForWhile = 0; ; NumForWhile++){
				if((RecBuff[NumForWhile] == 'r') 
					&& (RecBuff[NumForWhile + 1] == 'e')
					&& (RecBuff[NumForWhile + 2] == 'a')
					&& (RecBuff[NumForWhile + 3] == 'd')
					&& (RecBuff[NumForWhile + 4] == 'y')){
					WifiState = SENDING_STATE_2_SENDING;
					DeleteReceiveData();
				}
					/*
				if((RecBuff[NumForWhile] == 'O') 
					&& (RecBuff[NumForWhile + 1] == 'K')){
					WifiState = SENDING_STATE_2_SENDING;
					DeleteReceiveData();
				}*/
				if(NumForWhile == 0xff){
					break;
				}
			}
			break;
			
		case SENDING_STATE_2_SENDING:
			SendString(COMMAND_2);
			WifiState = SENDING_STATE_2_RECEING;
			break;
		
		case SENDING_STATE_2_RECEING:
			for(NumForWhile = 0; ; NumForWhile++){
				if((RecBuff[NumForWhile] == 'O') 
					&& (RecBuff[NumForWhile + 1] == 'K')){
					WifiState = SENDING_STATE_3_SENDING;
					DeleteReceiveData();
				}
				if(NumForWhile == 0xff){
					break;
				}
			}
			break;
			
		case SENDING_STATE_3_SENDING:
			SendString(COMMAND_3);
			WifiState = SENDING_STATE_3_RECEING;
			break;
		
		case SENDING_STATE_3_RECEING:
			for(NumForWhile = 0; ; NumForWhile++){
				if((RecBuff[NumForWhile] == 'r') 
					&& (RecBuff[NumForWhile + 1] == 'e')
					&& (RecBuff[NumForWhile + 2] == 'a')
					&& (RecBuff[NumForWhile + 3] == 'd')
					&& (RecBuff[NumForWhile + 4] == 'y')){
					WifiState = SENDING_STATE_4_SENDING;
					DeleteReceiveData();
				}
					/*
				if((RecBuff[NumForWhile] == 'O') 
					&& (RecBuff[NumForWhile + 1] == 'K')){
					WifiState = SENDING_STATE_4_SENDING;
					DeleteReceiveData();
				}*/
				if(NumForWhile == 0xff){
					break;
				}
			}
			break;
			
		case SENDING_STATE_4_SENDING:
			SendString(COMMAND_4);
			WifiState = SENDING_STATE_4_RECEING;
			break;
		
		case SENDING_STATE_4_RECEING:
			for(NumForWhile = 0; ; NumForWhile++){
				if((RecBuff[NumForWhile] == 'O') 
					&& (RecBuff[NumForWhile + 1] == 'K')){
					WifiState = SENDING_STATE_5_SENDING;
					DeleteReceiveData();
				}
				if(NumForWhile == 0xff){
					break;
				}
			}
			break;
			
		case SENDING_STATE_5_SENDING:
			SendString(COMMAND_5);
			WifiState = SENDING_STATE_5_RECEING;
			break;
		
		case SENDING_STATE_5_RECEING:
			for(NumForWhile = 0; ; NumForWhile++){
				if((RecBuff[NumForWhile] == 'O') 
					&& (RecBuff[NumForWhile + 1] == 'K')){
					WifiState = SENDING_WAITING_CONNECTION;
					DeleteReceiveData();
				}
				if(NumForWhile == 0xff){
					break;
				}
			}
			break;
			
		case SENDING_WAITING_CONNECTION:
			for(NumForWhile = 0; ; NumForWhile++){
				if((RecBuff[NumForWhile] == '0') 
					&& (RecBuff[NumForWhile + 1] == ',')
					&& (RecBuff[NumForWhile + 2] == 'C')
					&& (RecBuff[NumForWhile + 3] == 'O')
					&& (RecBuff[NumForWhile + 4] == 'N')
					&& (RecBuff[NumForWhile + 5] == 'N')
					&& (RecBuff[NumForWhile + 6] == 'E')
					&& (RecBuff[NumForWhile + 7] == 'C')
					&& (RecBuff[NumForWhile + 8] == 'T')){
					WifiState = SENDING_MOTOR_STATE;
					DeleteReceiveData();
				}
				if(NumForWhile == 0xff){
					break;
				}
			}
			break;
			
			//command from computer:
			//Motor Start: <KAISHI!>
			//Motor Stop: <TINGZHI>
		case SENDING_MOTOR_STATE:
			for(NumForWhile = 0; ; NumForWhile++){
				
				if((RecBuff[NumForWhile] == '<') 
					&& (RecBuff[NumForWhile + 1] == 'K')
					&& (RecBuff[NumForWhile + 2] == 'A')
					&& (RecBuff[NumForWhile + 3] == 'I')
					&& (RecBuff[NumForWhile + 4] == 'S')
					&& (RecBuff[NumForWhile + 5] == 'H')
					&& (RecBuff[NumForWhile + 6] == 'I')
					&& (RecBuff[NumForWhile + 7] == '!')
					&& (RecBuff[NumForWhile + 8] == '>')){
					//Start
					Start();
					SendMotorState = SENDING_MOTOR_STATE_1_SENDING;
				}else if((RecBuff[NumForWhile] == '<') 
					&& (RecBuff[NumForWhile + 1] == 'T')
					&& (RecBuff[NumForWhile + 2] == 'I')
					&& (RecBuff[NumForWhile + 3] == 'N')
					&& (RecBuff[NumForWhile + 4] == 'G')
					&& (RecBuff[NumForWhile + 5] == 'Z')
					&& (RecBuff[NumForWhile + 6] == 'H')
					&& (RecBuff[NumForWhile + 7] == 'I')
					&& (RecBuff[NumForWhile + 8] == '>')){
					//Stop
					Stop();
					SendMotorState = SENDING_MOTOR_STATE_1_SENDING;
				}
				if(NumForWhile == 0xff){
					break;
				}
			}
			switch(SendMotorState){
				case SENDING_MOTOR_STATE_1_SENDING:
					SendString(COMMAND_6);
					SendMotorState = SENDING_MOTOR_STATE_2_RECEIVEING;
					break;
				
				case SENDING_MOTOR_STATE_2_RECEIVEING:
					for(NumForWhile = 0; ; NumForWhile++){
						if(RecBuff[NumForWhile] == '>'){
							SendMotorState = SENDING_MOTOR_STATE_3_SENDING;
							DeleteReceiveData();
						}
						if(NumForWhile == 0xff){
							break;
						}
					}
					break;
					
				case SENDING_MOTOR_STATE_3_SENDING:
					state[2] = GetXunjiSate();
					SendString(state);
					SendMotorState = SENDING_MOTOR_STATE_4_RECEIVEING;
					break;
				
				case SENDING_MOTOR_STATE_4_RECEIVEING:
					for(NumForWhile = 0; ; NumForWhile++){
						if((RecBuff[NumForWhile] == 'O')
							||(RecBuff[NumForWhile] == 'K')){
							SendMotorState = SENDING_MOTOR_STATE_1_SENDING;
							//WifiState = SENDING_MOTOR_STATE_WAITING;
							DeleteReceiveData();
						}
						if(NumForWhile == 0xff){
							break;
						}
					}
					break;
			}
			break;
			
		case SENDING_MOTOR_STATE_WAITING:
			SendMotorNumber++;
			if(SendMotorNumber != 10) break;
			SendMotorNumber = 0;
			WifiState = SENDING_MOTOR_STATE;
			break;
	}
}

void TIM6_CFG(void){
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
	NVIC_InitTypeDef NVIC_InitStructure;  
  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);  
  
	TIM_TimeBaseStructure.TIM_Period = 1000; 
	TIM_TimeBaseStructure.TIM_Prescaler =720;  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); 
	TIM_ClearFlag(TIM6, TIM_FLAG_Update); 
  
	TIM_ITConfig(TIM6, TIM_IT_Update | TIM_IT_Trigger, ENABLE);  
        
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;    
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
 	NVIC_Init(&NVIC_InitStructure);   
  
	TIM_Cmd(TIM6, ENABLE); 
}

void TIM6_IRQHandler(void){
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) 
    {  
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
		WIFI_IRQ_Handler();
    }
}
