#include "main.h"
void rush_auton(int color_value){
            DrivePID drive(0.2,0,0.1,0.4,0,0);
            drive.prepare(-10);
    while (!drive.is_finished()){
        drive.go();

    }
}
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

