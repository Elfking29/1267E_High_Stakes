#include "main.h"
void bonk_auto(){
    //color_value=1;
    DrivePID drive(0.4,0,0.1,0.3,0.05,0.05);
    Lift.extend();
    Intake.move(127);
    delay(750);
    Hook.move(127);
    Intake.move(0);
    delay(500);
    Hook.brake();
    Intake.move(-127);
    delay(250);
    drive.q_go(8);
    drive.q_go(-109.5,1);
    Lift.toggle();
    delay(250);
    Arm.move_absolute(1225,200);
    drive.q_go(9.25);
    delay(1500);
    Arm.move_absolute(0,200);
    drive.q_go(-6);
    drive.q_go(44,1);
    delay(100);
    drive.q_go(-20);
    delay(250);
    drive.q_go(-3);
    drive.q_go(-12);
    Clamp.toggle();
    drive.q_go(-5);
    delay(100);
    Hook.move(127);
    delay(1000);
    drive.q_go(-80,1);
    delay(250);
    drive.q_go(-45,1);
    delay(100);
    Lift.toggle();
    Intake.move(127);
    delay(250);
    drive.q_go(28);
    delay(1000);
    drive.q_go(10,1);
    Arm.move_absolute(300,200);
    Intake.move(0);
    drive.q_go(-45);
    Arm.move_absolute(0,200);
    
}