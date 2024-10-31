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
Motor FL (2,v5::MotorGears::blue);
Motor ML (-5,v5::MotorGears::blue);
Motor BL (-4,v5::MotorGears::blue);

Motor FR (-12,v5::MotorGears::blue);
Motor MR (13,v5::MotorGears::blue);
Motor BR (14,v5::MotorGears::blue);

//Ramp Motor
Motor Ramp (-10,v5::MotorGears::green);
//Dunker
Motor Dunk (9,v5::MotorGears::green);
//Clamp
pros::adi::Pneumatics Clamp ('h',false);
//Tracking Wheels
Rotation track_left(19);
Rotation track_right(20);
