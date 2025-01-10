#include "main.h"
void ring_auton(int color_value){
	Arm.set_encoder_units(MOTOR_ENCODER_DEGREES);
    DrivePID drive(0.2,0,0.1,0.4,0,0);
    delay(100);
    drive.prepare(-7);
    //Ramp.move(127);
    while (!drive.is_finished()){
        drive.go();
    }
    drive.prepare(-85,1);
    while (!drive.is_finished()){
        drive.go();
    }
    delay(1000);
    Arm.move_absolute(300,100);
    delay(1000);
    drive.prepare(-4.5);
    while (!drive.is_finished()){
        drive.go();
    }
    Arm.move_absolute(0,100);
    delay(4000);
    drive.prepare(30);
    while (!drive.is_finished()){
        drive.go();
    }
    



}