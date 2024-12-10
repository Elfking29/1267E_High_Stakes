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
Motor FL (11,v5::MotorGears::blue);
Motor ML (-12,v5::MotorGears::blue);
Motor BL (-13,v5::MotorGears::blue);

Motor FR (-14,v5::MotorGears::blue);
Motor MR (15,v5::MotorGears::blue);
Motor BR (16,v5::MotorGears::blue);

//Ramp Motor
Motor Ramp (-18,v5::MotorGears::red);
//Dunker
Motor Arm (19,v5::MotorGears::red);
//Clamp
pros::adi::Pneumatics Clamp ('h',false);
//Sensors
Distance Checker (10);
