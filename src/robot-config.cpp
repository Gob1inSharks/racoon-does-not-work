#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain  Brain;

motor RF = motor(PORT20,ratio6_1,true);
motor RM = motor(PORT19,ratio6_1,true);
motor RE = motor(PORT18,ratio6_1,true);

motor LF = motor(PORT20,ratio6_1,true);
motor LM = motor(PORT19,ratio6_1,true);
motor LE = motor(PORT18,ratio6_1,true);

motor IN = motor(PORT20,ratio6_1,true);
motor HT = motor(PORT19,ratio6_1,true);

motor LB = motor(PORT18,ratio6_1,true);

digital_out CL = digital_out(Brain.ThreeWirePort.A);

rotation Rotation = rotation(PORT2);
rotation Odom = rotation(PORT2);

controller Controller1 = controller();

inertial Gyro = inertial(PORT1);

void vexcodeInit( void ) {
  Gyro.calibrate();
}

void elegantCalibrate ( void ) {

  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Gyro.calibrate();
  int WAIT_TIME = 5000; //DO NOT CHANGE THIS VALUE
  wait(WAIT_TIME,msec);
  int foo = 0;
  while(foo < 5000){
    Controller1.Screen.print(Gyro.angle());
    Controller1.Screen.newLine();
    Controller1.Screen.print(Gyro.heading());
    Controller1.Screen.newLine();
    Controller1.Screen.print(Gyro.acceleration(yaxis)); 
    
    wait(10,msec);
    foo += 10;
  }
}