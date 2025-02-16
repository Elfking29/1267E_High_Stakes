#include "main.h"
void rush_auto(){
    DrivePID drive(0.2,0,0.1,1,0,0.2);
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
    drive.prepare(-42,1);
    while (!drive.is_finished()){
        drive.go();
    }
    delay(250);
    drive.prepare(-10);
    while (!drive.is_finished()){
        drive.go();
    }
    delay(250);
    drive.prepare(-5);
    while (!drive.is_finished()){
        drive.go();
    }
    Clamp.toggle();
    Intake.move(127);
    Hook.move(127);
    
    delay(1500);
    drive.prepare(-75,1);
    while (!drive.is_finished()){
        drive.go();
    }
    //Clamp.toggle();
    delay(250);
    drive.prepare(24);
    while (!drive.is_finished()){
        drive.go();
    }
    delay(3000);
    drive.prepare(40,1);
    while (!drive.is_finished()){
        drive.go();
    }
    delay(500);
    Intake.brake();
    Hook.brake();
    drive.prepare(-40);
    while (!drive.is_finished()){
        drive.go();
    }
   
}