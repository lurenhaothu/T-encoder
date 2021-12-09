#include "UWControl.h"

u16 UWCounterLeft = 0;
u16 UWCounterRight = 0;

u16 UWCounterStateLeft;
u16 UWCounterStateRight;

u16 UWCountResultLeft = 5000;
u16 UWCountResultRight = 5000;

void GPIO_CFG(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC  | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);     
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	UWCounterStateLeft = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0);
	UWCounterStateRight = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1);
}

void UW_PWM_CFG(void){
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = 6000 - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 720 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 1;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_Cmd(TIM3, ENABLE);
}

void NVIC_EXIT_CFG(void){
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	//EXIT0-PD0
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//EXTI1-PD1
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	
	EXTI_ClearITPendingBit(EXTI_Line0);
	EXTI_ClearITPendingBit(EXTI_Line1);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource1);
	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

void UW_CFG(void){
	GPIO_CFG();
	UW_PWM_CFG();
	NVIC_EXIT_CFG();
}

u16 GetUWDistance(u8 position){
	if(position == UWLeft){
		return UWCountResultLeft * 17 / 10;
	}else if(position == UWRight){
		return UWCountResultRight * 17 / 10;
	}
	return 0;
}

void EXTI0_IRQHandler(void){
	u8 Data = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0);
	EXTI_ClearITPendingBit(EXTI_Line0);
	if(UWCounterStateLeft == Data){
		return;
	}else{
		UWCounterStateLeft = Data;
		if(UWCounterStateLeft == 0){
			UWCountResultLeft = TIM3->CNT - UWCounterLeft;
			UWCounterLeft = 0;
		}else{
			UWCounterLeft = TIM3->CNT;
		}
	}
}

void EXTI1_IRQHandler(void){
	u8 Data = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1);
	EXTI_ClearITPendingBit(EXTI_Line1);
	if(UWCounterStateRight == Data){
		return;
	}else{
		UWCounterStateRight = Data;
		if(UWCounterStateRight == 0){
			UWCountResultRight = TIM3->CNT - UWCounterRight;
			UWCounterRight = 0;
		}else{
			UWCounterRight = TIM3->CNT;
		}
	}
}
