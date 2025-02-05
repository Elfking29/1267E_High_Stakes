#include "main.h"
void rush_auto(){
    color_value=-1;
    DrivePID drive(0.2,0,0.1,1,0,0.2);
     //R 10+-10 B 210+-10 for Colory
    delay(100);
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
    drive.prepare(-4);
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
    drive.prepare(30,1);
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