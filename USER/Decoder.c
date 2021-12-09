#include "Decoder.h"

short SpeedResultRight;
short SpeedResultLeft;

void Timer1_Init(void){  //10ms pulse
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
  NVIC_InitTypeDef NVIC_InitStructure;  
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);  
  
  TIM_TimeBaseStructure.TIM_Period = 10000; 
  TIM_TimeBaseStructure.TIM_Prescaler =72;  
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); 
  TIM_ClearFlag(TIM1, TIM_FLAG_Update); 
  
  TIM_ITConfig(TIM1, TIM_IT_Update | TIM_IT_Trigger, ENABLE);  
        
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;    
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
  NVIC_Init(&NVIC_InitStructure);   
  
  TIM_Cmd(TIM1, ENABLE); 
}  

void IRQHandlerTenMsDecoder(void){
	SpeedResultRight = TIM4->CNT;
	TIM4->CNT = 0;
		
	SpeedResultLeft = TIM5->CNT;
	TIM5->CNT = 0;
	
	if(SpeedResultRight > 0x90){
		SpeedResultRight = SpeedResultRight - 0xfff;
	}
	if(SpeedResultLeft > 0x90){
		SpeedResultLeft = SpeedResultLeft - 0xfff;
	}
}

void Decoder_CFG(void){
	GPIO_InitTypeDef GPIO_InitStructure;  
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
    TIM_ICInitTypeDef TIM_ICInitStructure;  
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);  
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  
  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  
    TIM_DeInit(TIM4);  
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);  
  
    TIM_TimeBaseStructure.TIM_Period = 0xffff;  
    TIM_TimeBaseStructure.TIM_Prescaler = 0;  
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  
    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge,  
            TIM_ICPolarity_BothEdge);  
    TIM_ICStructInit(&TIM_ICInitStructure);  
    TIM_ICInitStructure.TIM_ICFilter = 6;  
    TIM_ICInit(TIM4, &TIM_ICInitStructure);  
  
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);  
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);  
    //Reset counter  
    TIM4->CNT = 0;  
    TIM_Cmd(TIM4, ENABLE); 
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);  
  
	//GPIO_PinRemapConfig(GPIO_Remap_TIM5, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);  
    TIM_DeInit(TIM5);  
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);  
  
    TIM_TimeBaseStructure.TIM_Period = 0xffff;  
    TIM_TimeBaseStructure.TIM_Prescaler = 0;  
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
  
    TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge,  
            TIM_ICPolarity_BothEdge);  
    TIM_ICStructInit(&TIM_ICInitStructure);  
    TIM_ICInitStructure.TIM_ICFilter = 6;  
    TIM_ICInit(TIM5, &TIM_ICInitStructure);  
  
    TIM_ClearFlag(TIM5, TIM_FLAG_Update);  
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);  
    //Reset counter  
    TIM5->CNT = 0;  
    TIM_Cmd(TIM5, ENABLE);
}

short GetVelocity(u8 position){
	if(position == DECODER_LEFT){
		return SpeedResultLeft;
	}else if(position == DECODER_RIGHT){
		return SpeedResultRight;
	}else{
		return 0;
	}
}

