#include "main.h"

pros::MotorGroup LM ({-11,-12,13});
pros::MotorGroup RM ({-18,19,20});

pros::Motor IN(15);
pros::Motor LB(16);

pros::ADIDigitalOut CL('A');

pros::Controller MASTER(CONTROLLER_MASTER);

pros::Imu IMU(10);

pros::Rotation ROT(9);

void set_brake_modes(){
    LM.set_brake_mode(MOTOR_BRAKE_BRAKE);
    RM.set_brake_mode(MOTOR_BRAKE_BRAKE);
    IN.set_brake_mode(MOTOR_BRAKE_HOLD);
    LB.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void calibrate(){
    IMU.reset();
    ROT.reset();
    ROT.reset_position();
    ROT.set_position(0);
}