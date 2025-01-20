#include "main.h"
void skills_auton(){
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
    Intake.move(127);

}