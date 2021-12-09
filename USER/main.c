#include "stm32f10x.h"
#include "PWM_Control.h"
#include "Decoder.h"
#include "LEDalive.h"
#include "PID.h"
#include "Xunji.h"
#include "UWControl.h"
#include "Uart1.h"
#include "WifiUART.h"  

u8 TimerCounter = 0;

int main(void){
	
	SystemInit();
	LED_ALIVE();
	Decoder_CFG();
	Timer1_Init();
	PWM_CFG();
	XunjiCFG();
	UW_CFG();
	USART_Config();
	TIM6_CFG();
	
	while(1){
		
	}
}

void TIM1_UP_IRQHandler(void)   //10MS
{       
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) 
    {  
		TimerCounter++;
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		//
		XunjiStateTransform();
		
		//10MS
		IRQHandlerTenMsDecoder();
		IRQHandlerPID();
		
		//50MS
		if(TimerCounter % 5 == 0){
			Xunji();
		}
    }
}
