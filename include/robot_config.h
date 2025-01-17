#include "main.h"

extern pros::MotorGroup LM;
extern pros::MotorGroup RM;

extern pros::Motor IN;

extern pros::Motor LB;

extern pros::ADIDigitalOut CL;

extern pros::Controller MASTER;

extern pros::Imu IMU;

extern pros::Rotation ROT;

void set_motors_to_default(void);

void calibrate(void);