#include "main.h"

int joystick_math(int joystick_value, int deadzone){
    //https://www.vexforum.com/t/optimizing-exponential-drive/73719
    if (std::abs(joystick_value) < deadzone ){
        return 0;
    }
    else {
        return get_sign(joystick_value)*(1.2*pow(1.0356,std::abs(joystick_value))
        -1.2+0.2*std::abs(joystick_value));
    }
}

void print_screen(std::string str){
    screen::print(TEXT_MEDIUM,1,1,"%s",str);
}

void move_drive_motors(float Left_value, float Right_value){
    //Move all motors with given value [-127,127]
	FL.move(Left_value);
    ML.move(Left_value);
	BL.move(Left_value);
		
	FR.move(Right_value);
    MR.move(Right_value);
	BR.move(Right_value);
}

void move_better_motors(float dl, float dr, float velocity, float delayt){

    FL.move_relative(dl,velocity);
    ML.move_relative(dl,velocity);
    BL.move_relative(dl,velocity);

    FR.move_relative(dr,velocity);
    MR.move_relative(dr,velocity);
    BR.move_relative(dr,velocity);

    pros::delay(delayt);
}


void brake_drive(int type){
    if (type == 0){
        //Coast (Slowly turn to a stop)
        //Same as motor.move(0)

        FL.set_brake_mode(E_MOTOR_BRAKE_COAST);
        BL.set_brake_mode(E_MOTOR_BRAKE_COAST);

        FR.set_brake_mode(E_MOTOR_BRAKE_COAST);
        BR.set_brake_mode(E_MOTOR_BRAKE_COAST);

        ML.set_brake_mode(E_MOTOR_BRAKE_COAST);
        MR.set_brake_mode(E_MOTOR_BRAKE_COAST);
    }
    else if (type == 1){
        //Hold (Stop speedily and actively hold position)

        FL.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        BL.set_brake_mode(E_MOTOR_BRAKE_HOLD);

        FR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        BR.set_brake_mode(E_MOTOR_BRAKE_HOLD);

        ML.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        MR.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    }
    else if (type == 2){
        //Brake (Stop speedily but don't hold position)

        FL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
        BL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

        FR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
        BR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

        ML.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
        MR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
    }

    //Actually brake

    FL.brake();
    BL.brake();

    FR.brake();
    BR.brake();

    ML.brake();
    MR.brake();
}

int get_sign(double value){
    if (value == 0){
        return 1;
    }
    else {
        return value/fabs(value);
    }
}
