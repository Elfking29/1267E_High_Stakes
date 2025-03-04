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
	Lift.extend();
	logo();
	bool clamp_lock = false;
	bool cornerer_lock = false;
	bool arm_lock=false;
	bool lift_lock=false;
	bool sort_lock=false;
	bool sort_state=false;
	bool fun_bool=false;
	bool a_lock=false;
	int arm_state = 0;
	int pneu_use = 1;
	int extra_extend=0;
	SmartCon OPPrint(60);
	Con1.clear();
	uint32_t sleep_time = millis();
	int print_counter = 0;
	int color_main=color_value==1?10:210; //Red,Blue
	int color_alt=color_value==1?210:10; //Blue,Red
	Arm.set_brake_mode(MOTOR_BRAKE_BRAKE);
	Arm.set_encoder_units(MOTOR_ENCODER_DEGREES);
	Intake.set_brake_mode(MOTOR_BRAKE_COAST);
	Hook.set_brake_mode(MOTOR_BRAKE_BRAKE);
	while (true) {
		//Drivetrain Movement
		int left_x = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_LEFT_X),15); //Turn
		int left_y = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),15); //Nothing
		int right_x = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_RIGHT_X),15); //Nothing
		int right_y = joystick_math(Con1.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y),15); //FB
		int Left_value = right_y+left_x +left_y;
		int Right_value = right_y-left_x +left_y;
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


		//Intake
		if (button_r1){
			Intake.move(127);
			Hook.move(127);
		}
		else if (!button_r1 and button_r2){
			Intake.move(-127);
			Hook.move(-127);
		}
		else {
			Intake.brake();
			if (!fun_bool){Hook.brake();}
		}

		//Arm
		if (button_l2 and arm_state==0){
			Arm.move_absolute(95,200); //Intake Level
			arm_state=1;
			arm_lock=true;
		}
		else if (button_l2 and arm_state==1 and arm_lock){}
		else if (button_l2 and (arm_state==1)){
			Hook.move_relative(-250,200);
			fun_bool=true;
			Arm.move_absolute(1225,200); //Stake Level
			arm_state=2;
			arm_lock=true;
		}
		else if (button_l2 and arm_state==2 and arm_lock){}
		else if (button_l2 and (arm_state==2)){
			Arm.move_absolute(0,200); //Lowered
			arm_state=3;
			arm_lock=true;
		}
		else if (button_l2){}
		else{
			if (arm_state==3){arm_state=0;}
			arm_lock=false;
			fun_bool=false;
		}

		//Manual Control
		if (button_up or button_down or button_right){
			arm_lock=true;
			if (button_up){Arm.move(127);}
			if (button_down){Arm.move(-127);}
			if (button_right){arm_lock=false;}
			else {Arm.brake();}
		}

		//Clamp
		if (button_l1 && !clamp_lock){
			Clamp.toggle();
			clamp_lock = true;
			pneu_use += 1;
			}
		else if (!button_l1){clamp_lock = false;}

		//Cornerer
		if (button_x && !cornerer_lock){
			Cornerer.toggle();
			cornerer_lock = true;
			pneu_use+=1;
		}
		else if (!button_x){cornerer_lock=false;}

		//Intake Lift
		if (button_left && !lift_lock){
			Lift.toggle();
			lift_lock = true;
			pneu_use+=1;
		}
		else if (!button_left){lift_lock=false;}

		//Sorter

		//Off/On
		if (button_b && !sort_lock){
			sort_state=!sort_state;
			sort_lock=true;
		}
		else if (!button_b){sort_lock=false;}

		//Auto Sort
		if (!sort_state){
			if (within(Colory.get_hue(),color_alt,10)){
				Sorter.extend();
				extra_extend=0;
			}
			else if (fun_bool and extra_extend<=5000){extra_extend+=1;} //Change 50 for another number later
			else {Sorter.retract();}
		}

		if (button_b){rush_auto();}
		if (button_a){bonk_auto();}


		//Printing
		/*
		if (!print_counter%250==0){ //Line 0
			Con1.print(0,0,"Pneu Use: %i", pneu_use/2);
		}
		if (!print_counter%200==0){ //Line 1
			Con1.print(1,0,"Arm Use: %s",arm_state==4?"Manual":"Auto");
		}
		if (!print_counter%150==0){ //Line 2
			Con1.print(2,0,"Auto Sort: %s",sort_state<2?"On":"Off");
		}
		if (print_counter%100==0){ //Line 3
			Con1.print(3,0,"%d", int(Arm.get_position()));
			//Con1.print(3,0,"Main: %d Con: %d",int(Con1.get_battery_level()),int(get_capacity))
		}
		else if (!print_counter%50==0){Con1.clear();} //Clear
		*/
	if (print_counter%50==0){
		//Con1.print(0,0,"%f", Arm.get_actual_velocity());
		Con1.print(0,0,"%f",pneu_use);
	}

		print_counter += 10;
		//End printing

		pros::Task::delay_until(&sleep_time, 10);
	}
}