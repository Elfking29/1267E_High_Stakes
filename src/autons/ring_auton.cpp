#include "main.h"
void ring_auton(int color_value){
    DrivePID drive(0.2,0,0.1,15,0,0.4);
    delay(100);
    drive.prepare(-12);
    while (!drive.is_finished()){
        drive.go();
    }
    drive.prepare(-90*color_value,1);
    while (!drive.is_finished()){
        drive.go();
    }
    delay(500);
    drive.prepare(-3.8);
    while (!drive.is_finished()){
        drive.go();
    }
    Intake.move_relative(1000,127);
    delay(1000);
    Intake.move_relative(-500,64);
    delay(250);
    drive.prepare(4);
    while (!drive.is_finished()){
        drive.go();
    }
    drive.prepare(-135*color_value,1);
    while (!drive.is_finished()){
        drive.go();
    }
    delay(250);
    drive.prepare(-30);
    while (!drive.is_finished()){
        drive.go();
    }
    delay(500);
    drive.prepare(-7);
    while (!drive.is_finished()){
        drive.go();
    }   
    Clamp.toggle();
    delay(500);
    drive.prepare(-145*color_value,1);
    while (!drive.is_finished()){
        drive.go();
    }   
    }
    