#include "main.h"
void rush_auto(){
    DrivePID drive(0.2,0,0.1,1,0,0.2);
    delay(100);
    drive.prepare(-30);
    while (!drive.is_finished()){
        drive.go();
    }
    delay(500);
    drive.prepare(-6);
    while (!drive.is_finished()){
        drive.go();
        drive.timeout(3000);
    }
    Clamp.toggle();
    delay(1000);
    Intake.move(127);
}