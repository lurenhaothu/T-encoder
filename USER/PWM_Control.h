#ifndef __PWM_CONTROL_H
#define __PWM_CONTROL_H

#include "stm32f10x.h"

#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1

#define MOTOR_FORWARD 0
#define MOTOR_BACKWARD 1

#define MOTOR_PWM_RCC_CLK	      RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO
#define MOTOR_LEFT_PWM_PIN        GPIO_Pin_2
#define MOTOR_RIGHT_PWM_PIN       GPIO_Pin_3
#define MOTOR_PWM_GPIO            GPIOA
#define MOTOR_TIMER			      TIM2
#define MOTOR_TIMER_RCC_CLK       RCC_APB1Periph_TIM2
#define TIM_LEFT_OCInit		      TIM_OC3Init
#define TIM_LEFT_OCPLCFG		  TIM_OC3PreloadConfig
#define TIM_PWM_SETTER_LEFT		  TIM_SetCompare3
#define TIM_RIGHT_OCInit		  TIM_OC4Init
#define TIM_RIGHT_OCPLCFG		  TIM_OC4PreloadConfig
#define TIM_PWM_SETTER_RIGHT	  TIM_SetCompare4


#define MOTOR_LEFT_CONTROL_PIN    GPIO_Pin_14
#define MOTOR_RIGHT_CONTROL_PIN   GPIO_Pin_15
#define MOTOR_CONTROL_GPIO        GPIOD
#define MOTOR_CONTROL_RCC_CLK     RCC_APB2Periph_GPIOD

void PWM_CFG(void);
void PWM_Control(u8 MotorPosition, u8 MotorVelocity, u8 Direction);

#endif
