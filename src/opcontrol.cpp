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
	int total_time = 60;
	int left_x; //Turn
	int left_y; //Forwards & Backwards
	int right_x; //Strafe
	//int right_y;
	if (auton_value == 4){
		total_time = 60;
	}
	SmartCon OPPrint(total_time);
	uint32_t sleep_time = millis();
	int print_counter = 0;
	while (true) {
		//Drivetrain Movement
		//The convention I am choosing that I will stick to is:
		//Move - Forward: Positive, Backward: Negative
		//Turn - Left: Negative, Right: Positive
		//Strafe - Left: Negative, Right: Positive

		left_y = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),15);
		left_x = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_LEFT_X),15);
		right_x = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_RIGHT_X),15);
		int L_value = left_y+left_x+right_x;

		int R_value = left_y-left_x-right_x;

		move_drive_motors(L_value,R_value);

		//End Drivetrain

		//Everything below is printing
		if (print_counter%5 == 0){ //This ensures that it only prints after 50 msecs have passed
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