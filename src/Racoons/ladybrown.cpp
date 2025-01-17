#include "main.h"
#include "JAR-Template/PID.h"

#define LADYBROWN_KP 1.
#define LADYBROWN_KI 0
#define LADYBROWN_KD 3.
#define LADYBROWN_STARTI 0

#define LADYBROWN_SETTLE_ERROR 1
#define LADYBROWN_SETTLE_TIME 1000
#define LADYBROWN_TIMEOUT 1000

#define LADYBROWN_KP_MOTOR 0.9
#define LADYBROWN_KI_MOTOR 0
#define LADYBROWN_KD_MOTOR 1.5
#define LADYBROWN_STARTI_MOTOR 0

#define LADYBROWN_SETTLE_ERROR_MOTOR 1
#define LADYBROWN_SETTLE_TIME_MOTOR 1000
#define LADYBROWN_TIMEOUT_MOTOR 2000

void ladybrown_turn_to(float desired_position){
    ladybrown_turn_to(desired_position,LADYBROWN_KP,LADYBROWN_KI, LADYBROWN_KD, LADYBROWN_STARTI, LADYBROWN_SETTLE_ERROR, LADYBROWN_SETTLE_TIME, LADYBROWN_TIMEOUT);
}

void ladybrown_turn_to(float desired_position,float kp, float ki, float kd, float starti, float settle_error, int settle_time, int timeout){
    ladybrown_turn_to_with_rotary_encoder(desired_position,kp, ki, kd, starti, settle_error, settle_time, timeout);
}

void ladybrown_turn_to_with_rotary_encoder(float desired_position){
    ladybrown_turn_to_with_rotary_encoder(desired_position,LADYBROWN_KP,LADYBROWN_KI, LADYBROWN_KD, LADYBROWN_STARTI, LADYBROWN_SETTLE_ERROR, LADYBROWN_SETTLE_TIME, LADYBROWN_TIMEOUT);
}
 
void ladybrown_turn_to_with_rotary_encoder(float desired_position,float kp, float ki, float kd, float starti, float settle_error, int settle_time, int timeout){

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

void ladybrown_turn_to_with_motor_encoder(float desired_position){
    ladybrown_turn_to_with_motor_encoder(desired_position,LADYBROWN_KP_MOTOR,LADYBROWN_KI_MOTOR, LADYBROWN_KD_MOTOR, LADYBROWN_STARTI_MOTOR, LADYBROWN_SETTLE_ERROR_MOTOR, LADYBROWN_SETTLE_TIME_MOTOR, LADYBROWN_TIMEOUT_MOTOR);
}

void ladybrown_turn_to_with_motor_encoder(float desired_position,float kp, float ki, float kd, float starti, float settle_error, int settle_time, int timeout){

	float current_position = LB.get_position();

	PID turnPID(desired_position-current_position,kp, ki, kd, starti, settle_error, settle_time, timeout, 2);
	
	while(!turnPID.is_settled()){
	
		float current_position = LB.get_position();
    	float error = desired_position-current_position;
    	float output = turnPID.compute(error);

    	output = clamp(output, -127, 127);
    	LB.move(output);

    	pros::delay(2);
    }
}