#include "main.h"
int joystick_math(int joystick_value, int deadzone){
    if (fabs(joystick_value)>deadzone){
         return round((1/127)*joystick_value*fabs(joystick_value));
    } 
    return 0;
}

void move_drive_motors(int FL_value, int BL_value, int FR_value, int BR_value, int ML_value, int MR_value){
    //Move all motors with given value [-127,127]
	FL.move(FL_value);
	BL.move(BL_value);
		
	FR.move(FR_value);
	BR.move(BR_value);

    //Setting one of those two to '1267'
    //Does not run the motors at all.
    //This can be useful in some situations
    //Like strafing PID
	if (ML_value != 1267 and MR_value != 1267){
        ML.move(ML_value);
	    MR.move(MR_value);
    }
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
