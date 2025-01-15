#include "main.h"
#include "JAR-Template/PID.h"

#define LADYBROWN_KP .35
#define LADYBROWN_KI 0
#define LADYBROWN_KD .13
#define LADYBROWN_STARTI 0

#define LADYBROWN_SETTLE_ERROR 1
#define LADYBROWN_SETTLE_TIME 1000
#define LADYBROWN_TIMEOUT 1000

#define LADYBROWN_KP_MOTOR .3
#define LADYBROWN_KI_MOTOR 0
#define LADYBROWN_KD_MOTOR .05
#define LADYBROWN_STARTI_MOTOR 0

#define LADYBROWN_SETTLE_ERROR_MOTOR 1
#define LADYBROWN_SETTLE_TIME_MOTOR 1000
#define LADYBROWN_TIMEOUT_MOTOR 1000


void ladybrown_turn_to(int desired_position){
    ladybrown_turn_to(desired_position,LADYBROWN_KP,LADYBROWN_KI, LADYBROWN_KD, LADYBROWN_STARTI, LADYBROWN_SETTLE_ERROR, LADYBROWN_SETTLE_TIME, LADYBROWN_TIMEOUT);
}

void ladybrown_turn_to(int desired_position,int kp, int ki, int kd, int starti, int settle_error, int settle_time, int timeout){
    ladybrown_turn_to_with_rotary_encoder(desired_position,kp, ki, kd, starti, settle_error, settle_time, timeout);
}

void ladybrown_turn_to_with_rotary_encoder(int desired_position){
    ladybrown_turn_to_with_rotary_encoder(desired_position,LADYBROWN_KP,LADYBROWN_KI, LADYBROWN_KD, LADYBROWN_STARTI, LADYBROWN_SETTLE_ERROR, LADYBROWN_SETTLE_TIME, LADYBROWN_TIMEOUT);
}
 
void ladybrown_turn_to_with_rotary_encoder(int desired_position,int kp, int ki, int kd, int starti, int settle_error, int settle_time, int timeout){

	float current_position = (double)ROT.get_position()/100;

	PID turnPID(reduce_negative_180_to_180(current_position-desired_position),kp,ki, kd, starti, settle_error, settle_time, timeout);
	while(!turnPID.is_settled()){
	
		float current_position = (double)ROT.get_position()/100;
    	float error = reduce_negative_180_to_180(current_position-desired_position);
    	float output = turnPID.compute(error);

    	output = clamp(output, -127, 127);
    	LB.move(output);

    	pros::delay(10);
    }
}

void ladybrown_turn_to_with_motor_encoder(int desired_position){
    ladybrown_turn_to_with_motor_encoder(desired_position,LADYBROWN_KP_MOTOR,LADYBROWN_KI_MOTOR, LADYBROWN_KD_MOTOR, LADYBROWN_STARTI_MOTOR, LADYBROWN_SETTLE_ERROR_MOTOR, LADYBROWN_SETTLE_TIME_MOTOR, LADYBROWN_TIMEOUT_MOTOR);
}

void ladybrown_turn_to_with_motor_encoder(int desired_position,int kp, int ki, int kd, int starti, int settle_error, int settle_time, int timeout){

	float current_position = (double)LB.get_position()/100;

	PID turnPID(reduce_negative_180_to_180(current_position-desired_position),kp,ki, kd, starti, settle_error, settle_time, timeout);
	while(!turnPID.is_settled()){
	
		float current_position = (double)LB.get_position()/100;
    	float error = reduce_negative_180_to_180(current_position-desired_position);
    	float output = turnPID.compute(error);

    	output = clamp(output, -127, 127);
    	LB.move(output);

    	pros::delay(10);
    }
}