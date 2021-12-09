#include "Xunji.h"
#include "PID.h"
#include "UWControl.h"

u8 XunjiStatement = XUNJI_DOUBLE_LINE;
u8 XunjiBizhangDirection = XUNJI_NONE;

u16 XunjiBizhangIntergration = 0;

void A(void){
	XunjiStatement = XUNJI_DOUBLE_LINE;
}

void XunjiCFG(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void Xunji(void){
	switch(XunjiStatement){
		case XUNJI_DOUBLE_LINE:
			if(Out1 == 0 && Out4 == 0){
				PIDMotorControl(PID_FORWARD, SPEED);
			}else if(Out1 == 1 && Out4 == 0){
				PIDMotorControl(PID_TURNLEFT, SPEEDT);
			}else if(Out1 == 0 && Out4 == 1){
				PIDMotorControl(PID_TURNRIGHT, SPEEDT);
			}
			break;
			
		case XUNJI_SINGLE_LINE:
			if(Out2 == 0 && Out3 == 0){
				PIDMotorControl(PID_FORWARD, SPEED);
			}else if(Out2 == 1 && Out3 == 0){
				PIDMotorControl(PID_TURNRIGHT, SPEEDT);
			}else if(Out2 == 0 && Out3 == 1){
				PIDMotorControl(PID_TURNLEFT, SPEEDT);
			}
			break;	
			
		case XUNJI_DOUBLE_TO_SINGLE_ONE:
			if(XunjiBizhangDirection == XUNJI_LEFT){
				PIDMotorControl(PID_TURNRIGHT, SPEEDT);
			}else if(XunjiBizhangDirection == XUNJI_RIGHT){
				PIDMotorControl(PID_TURNLEFT, SPEEDT);
			}
			break;	
			
		case XUNJI_DOUBLE_TO_SINGLE_TWO:
			PIDMotorControl(PID_FORWARD, SPEED);
			break;	
		
		case XUNJI_SINGLE_TO_DOUBLE_ONE:
			if(XunjiBizhangDirection == XUNJI_LEFT){
				PIDMotorControl(PID_TURNLEFT, SPEEDT);
			}else if(XunjiBizhangDirection == XUNJI_RIGHT){
				PIDMotorControl(PID_TURNRIGHT, SPEEDT);
			}
			break;	
			
		case XUNJI_SINGLE_TO_DOUBLE_TWO:
			PIDMotorControl(PID_FORWARD, SPEED);
			break;
		
		case XUNJI_STOP:
			PIDMotorControl(PID_FORWARD, 0);
			break;
	}
}

void XunjiStateTransform(void){
	switch(XunjiStatement){
		case XUNJI_DOUBLE_LINE:
			if(XunjiBizhangIntergration == 3){
				if(GetUWDistance(UWLeft) < 150){
					XunjiStatement = XUNJI_DOUBLE_TO_SINGLE_ONE;
					XunjiBizhangDirection = XUNJI_LEFT;
				}else if(GetUWDistance(UWRight) < 150){
					XunjiStatement = XUNJI_DOUBLE_TO_SINGLE_ONE;
					XunjiBizhangDirection = XUNJI_RIGHT;
				}
				XunjiBizhangIntergration = 0;
			}else{
				if(GetUWDistance(UWLeft) < 150){
					XunjiBizhangIntergration = XunjiBizhangIntergration + 1;
				}else if(GetUWDistance(UWRight) < 150){
					XunjiBizhangIntergration = XunjiBizhangIntergration + 1;
				}
			}
			break;
			
		case XUNJI_SINGLE_LINE:
			//waiting for idea
			XunjiBizhangIntergration = XunjiBizhangIntergration + 1;
			if(XunjiBizhangIntergration > 300){
				XunjiStatement = XUNJI_SINGLE_TO_DOUBLE_ONE;
				XunjiBizhangIntergration = 0;
			}
			break;	
			
		case XUNJI_DOUBLE_TO_SINGLE_ONE:
			if((XunjiBizhangDirection == XUNJI_LEFT && GetUWDistance(UWLeft) > 400) 
				|| (XunjiBizhangDirection == XUNJI_RIGHT && GetUWDistance(UWRight) > 400)){
				XunjiStatement = XUNJI_DOUBLE_TO_SINGLE_TWO;
			}
			break;
			
		case XUNJI_DOUBLE_TO_SINGLE_TWO:
			if((XunjiBizhangDirection == XUNJI_LEFT && Out2 == 1) 
				|| (XunjiBizhangDirection == XUNJI_RIGHT && Out3 == 1)){
				XunjiStatement = XUNJI_SINGLE_LINE;
				XunjiBizhangIntergration = 0;
			}
			break;	
		
		case XUNJI_SINGLE_TO_DOUBLE_ONE:
			XunjiBizhangIntergration = XunjiBizhangIntergration + 1;
			if(XunjiBizhangIntergration > 75){
				XunjiStatement = XUNJI_SINGLE_TO_DOUBLE_TWO;
				XunjiBizhangIntergration = 0;
			}
			break;	
			
		case XUNJI_SINGLE_TO_DOUBLE_TWO:
			if((XunjiBizhangDirection == XUNJI_LEFT && Out4 == 1) 
				|| (XunjiBizhangDirection == XUNJI_RIGHT && Out1 == 1)){
				XunjiStatement = XUNJI_DOUBLE_LINE;
				XunjiBizhangIntergration = 0;
			}
			break;
		
	}
}

u8 GetXunjiSate(void){
	return XunjiStatement;
}

void Start(void){
	XunjiStatement = XUNJI_DOUBLE_LINE;
}

void Stop(void){
	XunjiStatement = XUNJI_STOP;
}
