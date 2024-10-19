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
	int right_y; //Forwards & Backwards
	int right_x; //Strafe
	//int right_y;
	if (auton_value == 4){
		total_time = 60;
	}
	SmartCon OPPrint(total_time);
	Con1.clear();
	uint32_t sleep_time = millis();
	int print_counter = 0;
	while (true) {
		//Drivetrain Movement
		//The convention I am choosing that I will stick to is:
		//Move - Forward: Positive, Backward: Negative
		//Turn - Left: Negative, Right: Positive
		//Strafe - Left: Negative, Right: Positive

		right_y = Con1.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
		right_x = Con1.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
		
		int L_value = right_y;
		int R_value = right_y;

		move_drive_motors(L_value,R_value);

		//End Drivetrain

		//Ramp Control
		int button_a = Con1.get_digital(E_CONTROLLER_DIGITAL_A);
		int button_b = Con1.get_digital(E_CONTROLLER_DIGITAL_B);
		if (button_a == 1 && button_b != 1){
			Ramp.move(127);
		}
		else if (button_b == 1 && button_a != 1){
			Ramp.move(-127);
		}
		else{
			Ramp.set_brake_mode(E_MOTOR_BRAKE_COAST);
			Ramp.brake();
		}

		//Everything below is printing
		if (print_counter%50 == 0){ //This ensures that it only prints after 50 msecs have passed
		//without needing a long wait period, which can cause input lag
			rumble_pattern = "";
			batteries = "Bat:" + std::to_string(battery::get_capacity()) + "%, " + std::to_string(Con1.get_battery_level()) + "%";
			sensor_value = "";
			match_time = OPPrint.get_time();
			//OPPrint.print(batteries,match_time,sensor_value,rumble_pattern,std::make_tuple(3,2,1));
			int l = 1000*(FL.get_torque()+ML.get_torque()+BL.get_torque())/3;
			int r = 1000*(FR.get_torque()+MR.get_torque()+BR.get_torque())/3;
			Con1.clear();
			Con1.print(1,0,"%d, %d",l,r);
		}
		print_counter += 1;
		//End printing
		pros::Task::delay_until(&sleep_time, 10);
	}
}