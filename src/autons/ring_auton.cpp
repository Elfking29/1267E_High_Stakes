#include "main.h"
void ring_auton(int color_value){
        move_better_motors(2000,2000,600,5000);
        move_drive_motors(0,0);
        /*
        // plans for ring_auton: (all values are rough estimates)
        // red version

        // drive into mogo
        move(24, false, 0, 0, 0); // fix pid values

        // clamp mogo


        // rotate and move toward middle rings
        turn(90, false, 0, 0, 0); // fix pid values
        move(24, false, 0, 0, 0); // fix pid values

        // intake middle ring one


        // move + rotate for midddle ring two?


        // intake middle ring two?


        // rotate for ring stack behind


        // drive to + intake ring


        // drive to ladder?


    } else {
        // blue version

        // drive into mogo
        move(24, false, 0, 0, 0); // fix pid values

        // clamp mogo


        // rotate and move toward middle rings
        turn(-90, false, 0, 0, 0); // fix pid values
        move(24, false, 0, 0, 0); // fix pid values

        // intake middle ring one


        // move + rotate for midddle ring two?


        // intake middle ring two?


        // rotate for ring stack behind


        // drive to + intake ring


        // drive to ladder?
        */

}