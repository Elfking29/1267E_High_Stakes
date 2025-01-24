#include "main.h"
void full_auto(){
    DrivePID drive(0.2,0,0.1,1,0,0.2);
    delay(100);
    drive.prepare(-11);
    while (!drive.is_finished()){
        drive.go();
    }
    drive.prepare(90,1);
    while (!drive.is_finished()){
        drive.go();
    }
    delay(500);
    drive.prepare(-3.8);
    while (!drive.is_finished()){
        drive.go();
        drive.timeout(1500);
    }
    Intake.move_relative(1000,127);
    delay(1000);
    Intake.move_relative(-500,64);
    delay(250);
    drive.prepare(5);
    while (!drive.is_finished()){
        drive.go();
        //drive.timeout(1500);
    }
    drive.prepare(140,1);
    while (!drive.is_finished()){
        drive.go();
    }
    delay(500);
    drive.prepare(-30);
    while (!drive.is_finished()){
        drive.go();
    }
    delay(500);
    drive.prepare(-6);
    while (!drive.is_finished()){
        drive.go();
        //drive.timeout(2000);
    }   
    Clamp.toggle();
    delay(500);
    drive.prepare(130,1);
    while (!drive.is_finished()){
        drive.go();
    }   
    Intake.move(127);
    delay(500);
    drive.prepare(30);
    while(!drive.is_finished()){
        drive.go();
    }
    delay(3000);
    drive.prepare(-25,1); //Adjust
    while(!drive.is_finished()){
        drive.go();
    }
    Intake.brake();
    delay(250);
    drive.prepare(-36); //Adjust
    while(!drive.is_finished()){
        drive.go();
    }   
    
}  