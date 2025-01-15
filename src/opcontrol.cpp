#include "main.h"
#include "JAR-Template/PID.h"

#define ANGLE_MIN_THRESHOLD 0.
#define ANGLE_MAX_THRESHOLD 250.

#define DEFAULT_POSITION 179

#define INTAKE_POSITION 20 + DEFAULT_POSITION
#define GUARD_POSITION 86 + DEFAULT_POSITION
#define EJECT_POSITION 146 + DEFAULT_POSITION

#define LADYBROWN_KP .35
#define LADYBROWN_KI 0
#define LADYBROWN_KD .13
#define LADYBROWN_STARTI 0

#define LADYBROWN_SETTLE_ERROR 1
#define LADYBROWN_SETTLE_TIME 1000
#define LADYBROWN_TIMEOUT 1000

int ladybrown_macro_angle = 0;
bool ladybrown_macro_active = false;

void ladybrown_macro(void* param){

	while(1){

		if(ladybrown_macro_active){

			float current_position = (double)ROT.get_position()/100;
			int desired_position = ladybrown_macro_angle;

			PID turnPID(reduce_negative_180_to_180(current_position-desired_position),LADYBROWN_KP,LADYBROWN_KI, LADYBROWN_KD, LADYBROWN_STARTI, LADYBROWN_SETTLE_ERROR, LADYBROWN_SETTLE_TIME, LADYBROWN_TIMEOUT);
			while( !turnPID.is_settled() ){
	
				float current_position = (double)ROT.get_position()/100;
    			float error = reduce_negative_180_to_180(current_position-desired_position);
    			float output = turnPID.compute(error);

    			output = clamp(output, -127, 127);
    			LB.move(output);

    			pros::delay(10);
    		}

			ladybrown_macro_active = false;
		}
		pros::delay(10);
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
