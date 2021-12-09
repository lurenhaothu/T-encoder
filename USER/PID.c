#include "PID.h"
#include "Decoder.h"
#include "PWM_Control.h"

short TargetVelocityLeft = 0;
short DeltaofLastMomentLeft;
short SigmaLeft;

short TargetVelocityRight = 0;
short DeltaofLastMomentRight;
short SigmaRight;

void PIDControl(u8 position, short velocity){
	if(position == PID_LEFT){
		SigmaLeft = 0;
		TargetVelocityLeft = velocity;
	}else if(position == PID_RIGHT){
		SigmaRight = 0;
		TargetVelocityRight = velocity;
	}
}

void PIDMotorControl(u8 direction, short velocity){
	if(velocity > 47){
		velocity = 47;
	}else if(velocity < -47){
		velocity = -47;
	}
	switch(direction){
		case PID_FORWARD:
			PIDControl(PID_LEFT, velocity);
			PIDControl(PID_RIGHT, velocity);
			break;
		
		case PID_BACKWARD:
			PIDControl(PID_LEFT, -velocity);
			PIDControl(PID_RIGHT, -velocity);
			break;
		
		case PID_TURNRIGHT:
			PIDControl(PID_LEFT, velocity);
			PIDControl(PID_RIGHT, -velocity);
			break;
		
		case PID_TURNLEFT:
			PIDControl(PID_LEFT, -velocity);
			PIDControl(PID_RIGHT, velocity);
			break;
	}
}

void IRQHandlerPID(void){
	float PController, IController, DController, Controller;
	
	short velocity = GetVelocity(DECODER_LEFT);
	short delta = TargetVelocityLeft - velocity;
	PController = P * delta;
	SigmaLeft = SigmaLeft + delta;
	IController = P / Ti * SigmaLeft;
	DController = P * Td * (delta - DeltaofLastMomentLeft);
	DeltaofLastMomentLeft = delta;
	Controller = PController + IController + DController;
	if(Controller >= 0){
		if(Controller > 100) Controller = 100;
		PWM_Control(MOTOR_LEFT, (int) Controller, MOTOR_FORWARD);
	}else{
		if(Controller < -100) Controller = -100;
		PWM_Control(MOTOR_LEFT, (int) (-Controller), MOTOR_BACKWARD);
	}
	
	velocity = GetVelocity(DECODER_RIGHT);
	delta = TargetVelocityRight - velocity;
	PController = P * delta;
	SigmaRight = SigmaRight + delta;
	IController = P / Ti * SigmaRight;
	DController = P * Td * (delta - DeltaofLastMomentRight);
	DeltaofLastMomentRight = delta;
	Controller = PController + IController + DController;
	if(Controller >= 0){
		if(Controller > 100) Controller = 100;
		PWM_Control(MOTOR_RIGHT, (int) Controller, MOTOR_FORWARD);
	}else{
		if(Controller < -100) Controller = -100;
		PWM_Control(MOTOR_RIGHT, (int) (-Controller), MOTOR_BACKWARD);
	}
}
