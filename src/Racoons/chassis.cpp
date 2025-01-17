#include "main.h"
#include "JAR-Template/PID.h"
#include "JAR-Template/util.h"

#define INERTIAL_RATIO 348.5

#define WHEEL_DIAMETER 2.75
#define WHEEL_RATIO .8

#define DRIVE_KP 1.0
#define DRIVE_KI 0.01
#define DRIVE_KD 2.0
#define DRIVE_STARTI 0

#define DRIVE_SETTLE_ERROR 1
#define DRIVE_SETTLE_TIME 800
#define DRIVE_TIMEOUT 2000

#define TURN_KP 0.4
#define TURN_KI 0.01
#define TURN_KD 1.4
#define TURN_STARTI 0

#define TURN_SETTLE_ERROR 0.25
#define TURN_SETTLE_TIME 800
#define TURN_TIMEOUT 2000

void drive_with_voltage(float leftVoltage, float rightVoltage){
    LM.move_voltage((int)leftVoltage*1000);
    RM.move_voltage((int)rightVoltage*1000);
}

float get_drive_position(void ){

    float position_left = (float)LM.get_position()*M_PI*WHEEL_DIAMETER*WHEEL_RATIO;
    float position_right = (float)RM.get_position()*M_PI*WHEEL_DIAMETER*WHEEL_RATIO;

    return (position_left + position_right)/2;

}

void drive_to_distance(float desired_position, float drive_max_voltage, float turn_settle_error, int turn_settle_time, int turn_timeout){

    drive_to_distance(desired_position, drive_max_voltage, DRIVE_KP, DRIVE_KI, DRIVE_KD, DRIVE_STARTI, turn_settle_error, turn_settle_time, turn_timeout);
}

void drive_to_distance(float desired_position){

    drive_to_distance(desired_position, 12, DRIVE_KP, DRIVE_KI, DRIVE_KD, DRIVE_STARTI, DRIVE_SETTLE_ERROR, DRIVE_SETTLE_TIME, DRIVE_TIMEOUT);
}

void drive_to_distance(float desired_position, float drive_max_voltage){

    drive_to_distance(desired_position, drive_max_voltage, DRIVE_KP, DRIVE_KI, DRIVE_KD, DRIVE_STARTI, DRIVE_SETTLE_ERROR, DRIVE_SETTLE_TIME, DRIVE_TIMEOUT);
}

void drive_to_distance(float desired_position, float drive_max_voltage, float drive_kp, float drive_ki, float drive_kd){

    drive_to_distance(desired_position, drive_max_voltage, drive_kp, drive_ki, drive_kd, DRIVE_STARTI, DRIVE_SETTLE_ERROR, DRIVE_SETTLE_TIME, DRIVE_TIMEOUT);
}

void drive_to_distance(float desired_position, float drive_max_voltage, float drive_kp, float drive_ki, float drive_kd, float drive_starti, float drive_settle_error, int drive_settle_time, int drive_timeout){

    float current_angle = IMU.get_rotation();
    float desired_angle = current_angle;

    LM.set_zero_position(LM.get_position());
    RM.set_zero_position(RM.get_position());

    float start_position = get_drive_position();
    float current_position = start_position;

    PID drivePID(desired_position, drive_kp, drive_ki, drive_kd, drive_starti, drive_settle_error, drive_settle_time, drive_timeout,2);

    PID headingPID(reduce_negative_180_to_180(desired_position - current_position), .2, 0, .4, 0, drive_settle_error, drive_settle_time, drive_timeout,2);
    
    while(drivePID.is_settled() == false){
    
        current_position = get_drive_position();
        current_angle = IMU.get_rotation(); 

        float drive_error = desired_position+start_position-current_position;
        float turn_error = reduce_negative_180_to_180(desired_angle - current_angle);

        float drive_output = drivePID.compute(drive_error);
        float turn_output = headingPID.compute(turn_error);

        drive_output = clamp(drive_output, -1000*drive_max_voltage, 1000*drive_max_voltage);
        turn_output = clamp(turn_output, 0, 0);

        drive_with_voltage(drive_output+turn_output, drive_output-turn_output);
        pros::delay(2);
    }

    LM.brake();
    RM.brake();

    pros::delay(10);
}

void turn_to_angle(float desired_position, float turn_max_voltage, float turn_settle_error, int turn_settle_time, int turn_timeout){
    turn_to_angle(desired_position, turn_max_voltage, TURN_KP, TURN_KI, TURN_KD, TURN_STARTI, turn_settle_error, turn_settle_time, turn_timeout);
}

void turn_to_angle(float desired_position){

    turn_to_angle(desired_position, 12, TURN_KP, TURN_KI, TURN_KD, TURN_STARTI, TURN_SETTLE_ERROR, TURN_SETTLE_TIME, TURN_TIMEOUT);
}

void turn_to_angle(float desired_position, float turn_max_voltage){
    
    turn_to_angle(desired_position, turn_max_voltage, TURN_KP, TURN_KI, TURN_KD, TURN_STARTI, TURN_SETTLE_ERROR, TURN_SETTLE_TIME, TURN_TIMEOUT);

}

void turn_to_angle(float desired_position, float turn_max_voltage, float turn_kp, float turn_ki, float turn_kd, float turn_starti){

    turn_to_angle(desired_position, turn_max_voltage, turn_kp, turn_ki, turn_kd, turn_starti, TURN_SETTLE_ERROR, TURN_SETTLE_TIME, TURN_TIMEOUT);
}

void turn_to_angle(float desired_position, float turn_max_voltage, float turn_kp, float turn_ki, float turn_kd, float turn_starti, float turn_settle_error, int turn_settle_time, int turn_timeout){
    float current_position = IMU.get_rotation();

    PID turnPID(reduce_negative_180_to_180(desired_position - current_position), turn_kp, turn_ki, turn_kd, turn_starti, turn_settle_error, turn_settle_time, turn_timeout);
    
    while( !turnPID.is_settled() ){

        current_position = IMU.get_rotation();

        float error = reduce_negative_180_to_180(desired_position - current_position);
        float output = turnPID.compute(error);
        output = clamp(output, -turn_max_voltage*1000, turn_max_voltage*1000);
        drive_with_voltage(output, -output);

        pros::delay(10);
    }

    LM.brake();
    RM.brake();
    pros::delay(10);
}

void timed_drive(float voltage_left, float voltage_right, int time){

    LM.move(voltage_left);
    RM.move(voltage_right);

    pros::delay(time);

    LM.brake();
    RM.brake();
}