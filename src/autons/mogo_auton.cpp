#include "main.h"
void mogo_auton(int color_value){
        move_better_motors(-550,-550,300,1000);
        move_better_motors(-500,500,300,750);
        move_better_motors(-160,-160,500,500);
        Dunk.move_relative(520,127);
        delay(750);
        Dunk.move(-127);
        delay(500);
        Dunk.set_brake_mode(E_MOTOR_BRAKE_COAST);
        Dunk.brake();
        Ramp.set_brake_mode(E_MOTOR_BRAKE_COAST);
        move_better_motors(200,200,300,500);
        move_better_motors(600,-600,300,1000);
        /*
        // plans for mogo_auton: (all current values are rought estimates)
        // red version

        // about a 4ft rush to middle mogo on an angle (assuming the line is the starting point)
        move(48, false, 0, 0, 0); // fix pid values

        // clamp onto mogo 


        // rotate about 90 degrees left for rings behind the mogo
        turn(-90, false, 0, 0, 0); // fix pid values

        // drive and intake bottom ring of stack


        // rotate towards ladder
        turn(-45, false, 0, 0, 0); // fix pid values

        // drive into ladder, end auto
        move(36, false, 0, 0, 0); // fix pid values
    } else {
        // blue version

        // about a 4ft rush to middle mogo on an angle (assuming the line is the starting point)
        move(48, false, 0, 0, 0); // fix pid values

        // clamp onto mogo 


        // rotate about 90 degrees left for rings behind the mogo
        turn(90, false, 0, 0, 0); // fix pid values

        // drive and intake bottom ring of stack


        // rotate towards ladder
        turn(45, false, 0, 0, 0); // fix pid values

        // drive into ladder, end auto
        move(36, false, 0, 0, 0); // fix pid values
        */

}