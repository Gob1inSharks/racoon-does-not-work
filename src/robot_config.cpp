#include "main.h"

pros::MotorGroup LM ({-11,-12,13});
pros::MotorGroup RM ({-18,19,20});

pros::Motor IN(-15);
pros::Motor LB(16);

pros::ADIDigitalOut CL('H');

pros::Controller MASTER(CONTROLLER_MASTER);

pros::Imu IMU(10);

pros::Rotation ROT(9);

void set_motors_to_default(){
    LM.set_brake_mode(MOTOR_BRAKE_BRAKE);
    LM.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
    LM.set_zero_position(LM.get_position());
    RM.set_brake_mode(MOTOR_BRAKE_BRAKE);
    RM.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
    RM.set_zero_position(RM.get_position());
    IN.set_brake_mode(MOTOR_BRAKE_HOLD);
    IN.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
    IN.set_zero_position(IN.get_position());
    LB.set_brake_mode(MOTOR_BRAKE_HOLD);
    LB.set_encoder_units(MOTOR_ENCODER_DEGREES);
    LB.set_zero_position(LB.get_position());
}

void calibrate(){
    IMU.reset();
    IMU.set_rotation(0);
    ROT.reset();
    ROT.reset_position();
    ROT.set_position(0);
}