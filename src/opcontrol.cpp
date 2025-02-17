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
	bool cornerer_lock = false;
	bool arm_lock=false;
	bool lift_lock=false;
	int sort_state;
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


		//Intake
		if (button_r1){
			Intake.move(127);
			Hook.move(127);
		}
		else if (!button_r1 and button_left){
			Intake.move(-127);
			Hook.move(-127);
		}
		else {
			Intake.brake();
			Hook.brake();
		}

		//Arm
		/*
		if (button_right and !arm_lock){
			if (arm_state!=4){arm_state=4;}//Manual Control
			else {arm_state=0;}//Auto
			arm_lock=true;
		}
		else if (arm_state==4){
			arm_lock=false;
		}

		//Manual Control
		if (arm_state==4){
			if (button_up){Arm.move(127);}
			else if (button_down){Arm.move(-127);}
			else {Arm.brake();}
		}

		//Auto Control
		if (button_l2 and arm_state==0){
			Arm.move_absolute(100,200); //Intake Level
			arm_state=1;
			arm_lock=true;
		}
		else if (button_l2 and arm_state==1 and arm_lock){}
		else if (button_l2 and (arm_state==1 or arm_state==2)){
			Arm.move_absolute(500,200); //Stake Level
			arm_state=2;
			arm_lock=true;
		}
		else if (button_l2 and arm_state==2 and arm_lock){}
		else if (button_l2 and (arm_state==2 or arm_state==3)){
			Arm.move_absolute(0,200); //Lowered
			arm_state=3;
			arm_lock=true;
		}
		else{
			if (arm_state==3){arm_state=0;}
			arm_lock=false;
		}
		*/

		if (button_up){
			Arm.move(64);
		}
		else if (button_down){
			Arm.move(-64);
		}
		else {
			Arm.brake();
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
		if (button_a && !lift_lock){
			Lift.toggle();
			lift_lock = true;
			pneu_use+=1;
		}
		else if (!button_a){lift_lock=false;}

		//Sorter

		//Manual Sort
		//Complicated because only one variable used
		if (button_b and sort_state<2){sort_state=2;}
		else if (button_b and sort_state==2){}
		else if (sort_state==2){sort_state=3;}
		else if (sort_state==3){Sorter.retract();}
		else if (button_b and sort_state==3){sort_state=1;}
		else if (button_b and sort_state==1){}
		else {sort_state=0;}

		//Auto Sort
		if (sort_state<2){
			if (within(Colory.get_hue(),color_alt,10)){
				Sorter.extend();
				extra_extend=0;
			}
			else if (Sorter.is_extended() and extra_extend<50){extra_extend+=1;} //Change 50 for another number later
			else {Sorter.retract();}
		}

		//Printing
		if (!print_counter%250){ //Line 0
			Con1.print(0,0,"Pneu Use: %i", pneu_use/2);
		}
		if (!print_counter%200){ //Line 1
			Con1.print(1,0,"Arm Use: %s",arm_state==4?"Manual":"Auto");
		}
		if (!print_counter%150){ //Line 2
			Con1.print(2,0,"Auto Sort: %s",sort_state<2?"On":"Off");
		}
		if (!print_counter%100){ //Line 3
			Con1.print(3,0,"%d", int(Arm.get_position()));
			//Con1.print(3,0,"Main: %d Con: %d",)
		}
		else if (!print_counter%50){Con1.clear();} //Clear

		print_counter += 1;
		//End printing

		pros::Task::delay_until(&sleep_time, 10);
	}
}