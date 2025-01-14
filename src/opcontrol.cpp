#include "main.h"

void opcontrol() {

    set_brake_modes();

    bool clamped = false;
	bool hold_down_b = false;

	while (1) {

		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);

		int dir = MASTER.get_analog(ANALOG_LEFT_Y);
		int turn = MASTER.get_analog(ANALOG_RIGHT_X);
		LM.move(dir + turn);
		RM.move(dir - turn);

		if (MASTER.get_digital(DIGITAL_L1)) {
      		IN.move(127); // This is 100 because it's a 100rpm motor
    	}
    	else if(MASTER.get_digital(DIGITAL_L2)) {
      		IN.move(-128);
    	}
    	else {
      		IN.brake();
    	}

		if (MASTER.get_digital(DIGITAL_R1)) {
      		LB.move_velocity(127); // This is 100 because it's a 100rpm motor
    	}
    	else if (MASTER.get_digital(DIGITAL_R2)) {
      		LB.move_velocity(-128);
    	}
    	else {
      		LB.brake();
    	}

		if (MASTER.get_digital(DIGITAL_B) && !hold_down_b) {
	  		CL.set_value(!clamped);
			clamped = !clamped;
      		pros::delay(100);
    	}
    	hold_down_b = MASTER.get_digital(DIGITAL_B);

		pros::delay(10);
	}
}