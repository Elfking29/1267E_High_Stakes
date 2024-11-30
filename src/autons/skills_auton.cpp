#include "main.h"
void skills_auton(){
    Arm.move_relative(520,127); //Dunk ring
    delay(750); //wait
    Arm.move(-64); //Retract dunker
    delay(1000); //wait
    Arm.set_brake_mode(E_MOTOR_BRAKE_COAST);
    Arm.brake(); //stop dunker
    move_better_motors(400,400,200,1000);
    move_better_motors(-465,-465,200,1000);
    move_better_motors(3000,3000,600,3000);

}