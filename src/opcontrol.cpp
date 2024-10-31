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
std::string rumble_pattern = "";
std::string batteries = "";
std::string match_time = "";
std::string sensor_value = "";

void opcontrol() {
	logo();
	bool clamp_lock = false;
	double dunk_pos;
	SmartCon OPPrint(60);
	Con1.clear();
	uint32_t sleep_time = millis();
	int print_counter = 0;
	while (true) {
		//Drivetrain Movement
		//The convention I am choosing that I will stick to is:
		//Move - Forward: Positive, Backward: Negative
		//Turn - Left: Negative, Right: Positive
		int left_x = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_LEFT_X),15); //Turn2
		int left_y = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),15); //FB
		int right_x = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_RIGHT_X),15); //Nothing
		int right_y = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y),15); //Turn1
		int Left_value = left_y+left_x-right_y+right_x;
		int Right_value = left_y-left_x+right_y-right_x;
		move_drive_motors(Left_value,Right_value);
		//End Drivetrain

		//Buttons
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
			Ramp.set_brake_mode(E_MOTOR_BRAKE_COAST);
			Ramp.brake();
		}

		//Dunker (<50 & >500)
		Dunk.set_brake_mode(E_MOTOR_BRAKE_COAST);
		//First, manual
		if (button_up && !button_down){
			Dunk.move(127);
		}
		else if (button_down && !button_up){
			Dunk.move(-127);
		}
		else {
			Dunk.brake();
		}
		//Now, automatic-ish
		dunk_pos = Dunk.get_position();
		if (button_l1){
			Dunk.move(127);
		}
		else {
			if (dunk_pos > 50){
				Dunk.move(-127);
			}
			else {
				Dunk.brake();
			}
		}



		//Clamp
		if (button_a && !clamp_lock){
			Clamp.toggle();
			clamp_lock = true;
		}
		else if (!button_a){
			clamp_lock = false;
		}

		//Everything below is printing
		if (print_counter%50 == 0){ //This ensures that it only prints after 50 msecs have passed
		//without needing a long wait period, which can cause input lag
			rumble_pattern = "";
			batteries = "Bat:" + std::to_string(battery::get_capacity()) + "%, " + std::to_string(Con1.get_battery_level()) + "%";
			sensor_value = "";
			match_time = OPPrint.get_time();
			OPPrint.print(batteries,match_time,sensor_value,rumble_pattern,std::make_tuple(3,2,1));
		}
		print_counter += 1;
		//End printing
		pros::Task::delay_until(&sleep_time, 10);
	}
}