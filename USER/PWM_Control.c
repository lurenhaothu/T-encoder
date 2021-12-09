#include "PWM_Control.h"

void PWM_CFG(void){
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(MOTOR_PWM_RCC_CLK, ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
	GPIO_InitStructure.GPIO_Pin = MOTOR_LEFT_PWM_PIN | MOTOR_RIGHT_PWM_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MOTOR_PWM_GPIO, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(MOTOR_CONTROL_RCC_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = MOTOR_LEFT_CONTROL_PIN | MOTOR_RIGHT_CONTROL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MOTOR_CONTROL_GPIO, &GPIO_InitStructure);
	
	RCC_APB1PeriphClockCmd(MOTOR_TIMER_RCC_CLK, ENABLE);
	TIM_TimeBaseStructure.TIM_Period = 100 - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 36 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(MOTOR_TIMER, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_LEFT_OCInit(MOTOR_TIMER, &TIM_OCInitStructure);
	TIM_LEFT_OCPLCFG(MOTOR_TIMER, TIM_OCPreload_Enable);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_RIGHT_OCInit(MOTOR_TIMER, &TIM_OCInitStructure);
	TIM_RIGHT_OCPLCFG(MOTOR_TIMER, TIM_OCPreload_Enable);
	
	TIM_SetCompare1(MOTOR_TIMER, 0);
	TIM_SetCompare2(MOTOR_TIMER, 0);
	GPIO_ResetBits(MOTOR_CONTROL_GPIO, MOTOR_LEFT_CONTROL_PIN | MOTOR_RIGHT_CONTROL_PIN);
	
	TIM_Cmd(MOTOR_TIMER, ENABLE);
}

void PWM_Control(u8 MotorPosition, u8 MotorVelocity, u8 Direction){
	if(Direction == MOTOR_FORWARD){
		if(MotorPosition == MOTOR_LEFT){
			GPIO_ResetBits(MOTOR_CONTROL_GPIO, MOTOR_LEFT_CONTROL_PIN);
			TIM_PWM_SETTER_LEFT(MOTOR_TIMER, MotorVelocity);
		}else if(MotorPosition == MOTOR_RIGHT){
			GPIO_ResetBits(MOTOR_CONTROL_GPIO, MOTOR_RIGHT_CONTROL_PIN);
			TIM_PWM_SETTER_RIGHT(MOTOR_TIMER, MotorVelocity);
		}
	}else if(Direction == MOTOR_BACKWARD){
		if(MotorPosition == MOTOR_LEFT){
			GPIO_SetBits(MOTOR_CONTROL_GPIO, MOTOR_LEFT_CONTROL_PIN);
			TIM_PWM_SETTER_LEFT(MOTOR_TIMER, 100 - MotorVelocity);
		}else if(MotorPosition == MOTOR_RIGHT){
			GPIO_SetBits(MOTOR_CONTROL_GPIO, MOTOR_RIGHT_CONTROL_PIN);
			TIM_PWM_SETTER_RIGHT(MOTOR_TIMER, 100 - MotorVelocity);
		}
	}
}
