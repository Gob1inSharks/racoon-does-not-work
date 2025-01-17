#include "main.h"
#include "JAR-Template/PID.h"
#include "Racoons/ladybrown.h"

#define INTAKE_POSITION 100
#define GUARD_POSITION 180
#define EJECT_POSITION 440
#define DESCORE_POSITION 470

int ladybrown_macro_angle = 0;
bool ladybrown_macro_active = false;
bool ladybrown_manual_active = false;
bool ladybrown_manual_reverse = false;

void ladybrown_task(void* param){

	LB.set_encoder_units(MOTOR_ENCODER_DEGREES);
	LB.tare_position();
	LB.set_zero_position(LB.get_position());

	while(1){

		if(ladybrown_macro_active){

			ladybrown_turn_to_with_motor_encoder(ladybrown_macro_angle);
			
		}else if (ladybrown_manual_active){
			if (ladybrown_manual_reverse){
				LB.move_velocity(-81);
			}else{
				LB.move_velocity(80);
			}
		}else{
			LB.brake();
		}

		if(LB.get_position() <= 4){
			LB.set_zero_position(LB.get_position());
			pros::delay(50);
		}

		pros::delay(2);
	}
}

bool mogo_clamper_active = false;

void mogo_clamper_task(void* param){

	bool mogo_clamped = false;
	
	while(1){

		if(mogo_clamper_active){

			CL.set_value(!mogo_clamped);
		    pros::delay(100);
			mogo_clamped = !mogo_clamped;
			mogo_clamper_active = false;		

		}

		pros::delay(2);
	}
}

bool ladybrown_at_loading_position = false;

void ladybrown_control(void* param){

	bool hold_down_l2 = false;
	bool hold_down_l1 = false;

	while(1){

		if (MASTER.get_digital(DIGITAL_L2)){
			pros::delay(100);
			if(MASTER.get_digital(DIGITAL_L1)){
				ladybrown_macro_angle = INTAKE_POSITION;
				ladybrown_at_loading_position = true;
				ladybrown_macro_active = true;
			} else {
				ladybrown_manual_reverse = false;
				ladybrown_at_loading_position = false;
				ladybrown_manual_active = true;
			}
		}else if (MASTER.get_digital(DIGITAL_L1)){
			pros::delay(100);
			if(MASTER.get_digital(DIGITAL_L2)){
				ladybrown_macro_angle = EJECT_POSITION;
				ladybrown_at_loading_position = false;
				ladybrown_macro_active = true;
			} else {
				ladybrown_manual_reverse = true;
				ladybrown_at_loading_position = false;
				ladybrown_manual_active = true;
			}
		}else if (MASTER.get_digital(DIGITAL_A)){
			ladybrown_macro_angle = GUARD_POSITION;
			ladybrown_at_loading_position = false;
			ladybrown_macro_active = true;
		} else if (MASTER.get_digital(DIGITAL_UP)){
			ladybrown_macro_angle = DESCORE_POSITION;
			ladybrown_at_loading_position = false;
			ladybrown_macro_active = true;
		}else if (!hold_down_l1 && !hold_down_l2){
			ladybrown_manual_active = false;
			ladybrown_macro_active = false;
			ladybrown_manual_active = false;
		}
		hold_down_l1 = MASTER.get_digital(DIGITAL_L1);
		hold_down_l2 = MASTER.get_digital(DIGITAL_L2);

		pros::delay(20);
	}
		
}

bool intake_active = false;
bool intake_reversed = false;

void intake_voltage_control(void* param){

	float velocity = 0;
	float past_position = 0;
	while(1){

		
		float velocity = (IN.get_position()-past_position)/2000;

		if(IN.get_voltage() > 3000){
			if(IN.get_actual_velocity() < 20){
				
				IN.move(-127);
				pros::delay(40);
				IN.move(0);
				pros::delay(20);
				IN.move(-127);

			}
		}
		past_position = IN.get_position();
		pros::delay(2);

	}
}

void intake_in(){
	IN.move(-128);
}

void intake_out(){
	IN.move(127);
}

void intake_task(void* param){

	while(1){

		if(intake_active){

			if(intake_reversed){
				IN.move(127);
			}else{
				IN.move(-128);
			}
		}else{
			IN.move(0);
		}

		pros::delay(2);

	}

}

void debug_task(void* param) {

	while(1){

		MASTER.clear_line(0);
		MASTER.print(0, 0,"LB: %d", LB.get_position());

		pros::delay(1000);

	}

}

int dir = 0;
int turn = 0;

void aracade_drive_task(void* param){

	while(1){
	
		dir = MASTER.get_analog(ANALOG_LEFT_Y);
		turn = MASTER.get_analog(ANALOG_RIGHT_X);

		LM.move(dir + turn);
		RM.move(dir - turn);

		pros::delay(2);
	}
}

void opcontrol() {

	set_motors_to_default();

    bool clamped = false;
	bool hold_down_b = false;

	pros::Task aracade_drive(aracade_drive_task);
	pros::Task ladybrown_macro_task(ladybrown_task);
	pros::Task mogo_clamper_toggle_task(mogo_clamper_task);
	pros::Task intake_voltage_control_task(intake_voltage_control);
	pros::Task intake_control_task(intake_task);
	pros::Task ladybrown_control_task(ladybrown_control);
	//pros::Task debugging(debug_task); //for debugging

	while (1) {

		if (MASTER.get_digital(DIGITAL_R1)) {
			intake_reversed = false;
      		intake_active = true;
    	}
    	else if(MASTER.get_digital(DIGITAL_R2)) {
	  		intake_reversed = true;
	  		intake_active = true;
    	}
    	else {
      		intake_active = false;
    	}

		if (MASTER.get_digital(DIGITAL_B) && !hold_down_b) {
			mogo_clamper_active = true;
    	}
    	hold_down_b = MASTER.get_digital(DIGITAL_B);

		pros::delay(2);
	}
}
