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
	SmartCon OPPrint(60);
	Con1.clear();
	uint32_t sleep_time = millis();
	int print_counter = 0;
	Arm.set_brake_mode(E_MOTOR_BRAKE_COAST);
	Ramp.set_brake_mode(E_MOTOR_BRAKE_COAST);
	while (true) {
		//Drivetrain Movement
		int left_x = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_LEFT_X),15); //Turn2
		int left_y = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),15); //FB
		int right_x = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_RIGHT_X),15); //Nothing
		int right_y = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y),15); //Turn1
		int Left_value = left_y+left_x-right_y;
		int Right_value = left_y-left_x+right_y;
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
		if (button_up){
			Arm.move(127);
		}
		else if (button_down and !button_up){
			Arm.move(-127);
		}
		else {
			Arm.brake();
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