#include "main.h"
#include "Racoons/chassis.h"
#include "robot_config.h"
#include "Racoons/ladybrown.h"

bool clamp_position = false;

void clamp_toggle(){
    clamp_position = !clamp_position;
    CL.set_value(clamp_position);
    pros::delay(100);
}


void test(){

    set_motors_to_default();
    calibrate();
    pros::delay(5000);

    drive_to_distance(-24);
    pros::delay(1500);
    turn_to_angle(180);
}

void ladybrown_turn_for(int voltage, int time){
    LB.move_voltage(voltage);
    pros::delay(time);
    LB.brake();
}

void auton_init(){
    CL.set_value(clamp_position);
}

void mogo_grab(){

    drive_to_distance(-7);
    timed_drive(-40,-40,500);
    pros::delay(300);
    clamp_toggle();

}

void score_ladybrown_red(){
    drive_to_distance(3);
    ladybrown_turn_for(12000,500);
    pros::delay(200); //for debugging
    drive_to_distance(-10);
    ladybrown_turn_for(-12000,600);
    pros::delay(100);
    turn_to_angle(-47.5,10,0.25,800,2000);
    pros::delay(10);
    IMU.set_rotation(0);
}

void score_ladybrown_blue(){
    drive_to_distance(3);
    ladybrown_turn_for(12000,600);
    pros::delay(300); //for debugging
    drive_to_distance(-9);
    ladybrown_turn_for(-12000,800);
    pros::delay(100);
    turn_to_angle(46.25,10,0.15,800,2000);
    pros::delay(10);
    IMU.set_rotation(0);
}

void skills(){
    auton_init();
    ladybrown_turn_for(12000,500);
    drive_to_distance(-10,2,1,2000,2000);
    clamp_toggle();
    ladybrown_turn_for(-12000,600);
    IMU.set_rotation(0);
    pros::delay(500);
    IN.move(-127);
    float angle = 0;
    while(1){

        turn_to_angle(angle);
        drive_to_distance(200,12.7,1,5000,5000);
        drive_to_distance(-200,12.7,1,5000,5000);

        angle += 5;

    }

}

void skills_square(){
    ladybrown_turn_for(12000,500);
    ladybrown_turn_for(-12000,600);
    turn_to_angle(35);

    while(1){
        for(int i = 1; i <= 4; i++){
        timed_drive(-127,-127,1500);
        turn_to_angle(-9*i);}
    }

}

void two_stake_awp_blue(){

    auton_init();
    score_ladybrown_blue();
    mogo_grab();
    turn_to_angle(100);
    IN.move(-127);
    drive_to_distance(60,12,1,1000,2500);
    pros::delay(1000);
    drive_to_distance(-80,12,1,1000,2500);

}

void two_stake_awp_red(){
    auton_init();
    score_ladybrown_red();
    mogo_grab();
    turn_to_angle(-100);
    IN.move(-127);
    drive_to_distance(60,12,1,1000,2500);
    pros::delay(1000);
    drive_to_distance(-80,12,1,1000,2500);
}

void autonomous() {

    int current_auton_selection = 5;

    switch(current_auton_selection){ 
        case 0:
            calibrate();
            pros::delay(5000);
            break;
        case 1:   
            mogo_grab();
            break;
        case 2:
            mogo_grab();
        case 3:
            two_stake_awp_blue();
        case 4:
            two_stake_awp_red();
        case 5:
            score_ladybrown_blue();
            mogo_grab();
            break;
        case 6:
            skills_square();
            break;

    }
}