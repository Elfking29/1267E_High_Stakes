#include "main.h"
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
	logo();
	bool clamp_lock = false;
	float clamp_use = 0.5;
	int dunk_state = 0;
	bool arm_stop;
	bool ramp_stop;
	int ramp_pos;
	SmartCon OPPrint(60);
	Con1.clear();
	uint32_t sleep_time = millis();
	int print_counter = 0;
	Arm.set_brake_mode(MOTOR_BRAKE_HOLD);
	Arm.set_encoder_units(MOTOR_ENCODER_DEGREES);
	Ramp.set_brake_mode(MOTOR_BRAKE_BRAKE);
	while (true) {
		//Drivetrain Movement
		int left_x = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_LEFT_X),15); //Turn
		int left_y = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),15); //Nothing
		int right_x = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_RIGHT_X),15); //Nothing
		int right_y = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y),15); //FB
		int Left_value = right_y+left_x;
		int Right_value = right_y-left_x;
		move_drive_motors(Left_value,Right_value);
		//End Drivetrain

		//Buttons
		//Most of these don't do anything right now
		//However, they are nice to have
		int button_a = Con1.get_digital(E_CONTROLLER_DIGITAL_A);
		int button_b = Con1.get_digital(E_CONTROLLER_DIGITAL_B);
		int button_x = Con1.get_digital(E_CONTROLLER_DIGITAL_X);
		int button_y = Con1.get_digital(E_CONTROLLER_DIGITAL_Y);

		int button_up = Con1.get_digital(E_CONTROLLER_DIGITAL_UP);
		int button_down = Con1.get_digital(E_CONTROLLER_DIGITAL_DOWN);
		int button_left = Con1.get_digital(E_CONTROLLER_DIGITAL_LEFT);
		int button_right = Con1.get_digital(E_CONTROLLER_DIGITAL_RIGHT);

		int button_l1 = Con1.get_digital(E_CONTROLLER_DIGITAL_L1);
		int button_l2 = Con1.get_digital(E_CONTROLLER_DIGITAL_L2);
		int button_r1 = Con1.get_digital(E_CONTROLLER_DIGITAL_R1);
		int button_r2 = Con1.get_digital(E_CONTROLLER_DIGITAL_R2);


		//Ramp
		if (button_r1 == 1){
			Ramp.move(127);
		}
		else if (button_b == 1 && button_r1 != 1){
			Ramp.move(-127);
		}
		else{
			Ramp.brake();
		}

		//First, manual

		if (button_r2 and !dunk_state){
			dunk_state = 1;
		}
		else if (!button_r2){
			dunk_state = 0;
		}

		switch(dunk_state){
			case 1: //Step 0 :)
				//This just resets variables	
				arm_stop = false;
				ramp_stop = false;
				ramp_pos = 0;
				dunk_state = 2;
				break;
			//See notebook for steps
			case 2: //Steps 1 & 2
				//Arm code first
				Arm.move_absolute(500 /*change*/ ,100);
				//Intake code
				Ramp.move(127);

				//If statements
				if (Checker.get_distance()<20 /*change*/ ){
					Ramp.brake();
					ramp_stop = true;
				}
				if (Arm.get_position()<500+10 and Arm.get_position()>500-10){
					Arm.brake();
					arm_stop = true;
				}
				if (ramp_stop and arm_stop){
					ramp_pos = Ramp.get_position();
					dunk_state = 3;
				}

				break;
			case 3: //Step 3
				Ramp.move(127);
				if (Ramp.get_position() >= ramp_pos+500){
					//500 needs to be changed
					Ramp.brake();
					dunk_state = 4;
				}
				break;
			case 4: //Step 5
				Arm.move_absolute(0,100);
				if (Arm.get_position() < 15){
					Arm.brake();
					dunk_state = 1;
				}
				break;
		}




		//Clamp
		if (button_a && !clamp_lock){
			Clamp.toggle();
			clamp_lock = true;
			clamp_use += 0.5;
			}
		else if (!button_a){
			clamp_lock = false;
		}

		//Everything below is printing
		if (print_counter%50 == 0){
			Con1.print(0,0,"%d",int(clamp_use));
		}

		print_counter += 1;
		//End printing
		pros::Task::delay_until(&sleep_time, 10);
	}
}