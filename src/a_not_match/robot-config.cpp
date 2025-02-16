#include "main.h"
using namespace pros;

/*
This is my robot-config file.
I used to use the VEX Code VSCode extention,
and this is where I defined all my devices.
I am recreating it here in PROS to both
make transitioning easier and to make the
code less messy.
*/

//Controller Definition
Controller Con1 (CONTROLLER_MASTER); 

/* Motors:
Port Number (Negative for reverse)
MOTOR_GEAR_{100/200/600}
*/
Motor BR (20,v5::MotorGears::blue);
Motor MR (19,v5::MotorGears::blue);
Motor FR (-18,v5::MotorGears::blue);

Motor BL (-17,v5::MotorGears::blue);
Motor ML (-16,v5::MotorGears::blue);
Motor FL (15,v5::MotorGears::blue);

//Intake Motor
Motor Hook (-13,v5::MotorGears::green);
Motor Intake (-12,v5::MotorGears::green);
//Dunker
Motor Arm (-11,v5::MotorGears::red);
//Pneumatics
pros::adi::Pneumatics Clamp ('h',false);
pros::adi::Pneumatics Cornerer ('g',false);
pros::adi::Pneumatics Sorter ('f',false);

//Sensors
Optical Colory (6);
Rotation Rotaty (7);
Rotation Armaty (8);
