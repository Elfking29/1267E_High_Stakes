#include "main.h"
void bonk_auto(){
    color_value=1;
    DrivePID drive(0.4,0,0.1,0.8,0,0.3);
    Lift.extend();
    Intake.move(127);
    delay(750);
    Hook.move(127);
    Intake.move(0);
    delay(500);
    Hook.brake();
    Intake.move(-127);
    delay(250);
    drive.q_go(-80,1);
    delay(250);
    Intake.move(127);
    drive.q_go(7);
    drive.q_go(-30,1);
    Arm.move_relative(1225,200);
    delay(1500);
    Intake.move(-127);
    drive.q_go(-6);

}