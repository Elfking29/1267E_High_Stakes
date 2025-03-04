#include "main.h"

void rush_auto(){
    color_value=-1;
    DrivePID drive(0.4,0,0.1,1.2,0,0.4);
    Hook.move_relative(-250,200);
    Arm.move_relative(-100,200);
    delay(100);
    Arm.set_brake_mode(E_MOTOR_BRAKE_COAST);
    Arm.brake();
    drive.prepare(-12);
    while (!drive.is_finished()){
        drive.go();
    }
    delay(250);
    drive.prepare(-40,1);
    while (!drive.is_finished()){
        drive.go();
    }
    delay(250);
    drive.prepare(-11);
    while (!drive.is_finished()){
        drive.go();
    }
    delay(250);
    drive.prepare(-7);
    while (!drive.is_finished()){
        drive.go();
    }
    Clamp.toggle();
    Intake.move(127);
    Hook.move(127);
    //Stuff
    delay(1500);
    drive.prepare(-40,1);
    while (!drive.is_finished()){
        drive.go();
    }
    Lift.extend();
    delay(250);
    drive.prepare(24);
    while (!drive.is_finished()){
        drive.go();
    }
    delay(1500);
    Lift.toggle();
    drive.q_go(150,1);
    delay(250);
    drive.q_go(40);
    Lift.toggle();
    Intake.move(127);
    Hook.move(127);
    delay(5000);
}
