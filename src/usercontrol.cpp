#include "vex.h"

bool ladybrown_running = false;

void usercontrol(void) {

  bool clamped = true;

  while (1) {

    chassis.control_arcade();

    if(Controller1.ButtonL1.pressing()) {
      IN.spin(forward, 127, pct);
      HK.spin(forward, 127, pct);
    } else if(Controller1.ButtonL2.pressing()) {
      IN.spin(reverse, 127, pct);
      HK.spin(reverse, 127, pct);
    } else {
      IN.stop(hold);
      HK.stop(hold);
    }
    
    if(Controller1.ButtonR1.pressing()) {
      LB.spin(forward, 127, pct);
    } else if(Controller1.ButtonR2.pressing()) {
      LB.spin(reverse, 127, pct);
    } else {
      LB.stop(hold);
    }

    if (Controller1.ButtonB.pressing() && !clamp) {
      CL.set(!(CL.value()));
      wait(80,msec);
    }
    clamp = Controller1.ButtonB.pressing();

    if(Controller1.ButtonX.pressed() && !ladybrown_running) {
      ladybrown_running = true;
      task(ladybrown_task());
    }

    wait(20, msec);
  }
}

void ladybrown_task(void){

  while(ladybrown_running){
    
  }
}