#include "main.h"
#include "JAR-Template/PID.h"

#define DEFAULT_POSITION 0

#define INTAKE_POSITION 60 + DEFAULT_POSITION
#define GUARD_POSITION 120 + DEFAULT_POSITION
#define EJECT_POSITION 438 + DEFAULT_POSITION

int ladybrown_macro_angle = 0;
bool ladybrown_macro_active = false;

void ladybrown_macro(void* param){

	while(1){

		if(ladybrown_macro_active){

			ladybrown_turn_to_with_motor_encoder(ladybrown_macro_angle);

		}
		pros::delay(8);
	}
}

void opcontrol() {

    set_brake_modes();

    bool clamped = false;
	bool hold_down_b = false;

	pros::Task macro(ladybrown_macro);

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

		if (MASTER.get_digital(DIGITAL_DOWN)){
			ladybrown_macro_angle = INTAKE_POSITION;
			ladybrown_macro_active = true;
		} else if (MASTER.get_digital(DIGITAL_UP)){
			ladybrown_macro_angle = EJECT_POSITION;
			ladybrown_macro_active = true;
		} else if (MASTER.get_digital(DIGITAL_RIGHT)){
			ladybrown_macro_angle = GUARD_POSITION;
			ladybrown_macro_active = true;
		}

		pros::delay(10);
	}
}
