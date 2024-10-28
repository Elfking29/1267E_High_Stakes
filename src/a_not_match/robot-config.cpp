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
Motor FL (3,v5::MotorGears::blue);
Motor ML (-4,v5::MotorGears::blue);
Motor BL (-5,v5::MotorGears::blue);

Motor FR (-6,v5::MotorGears::blue);
Motor MR (7,v5::MotorGears::blue);
Motor BR (8,v5::MotorGears::blue);

//Ramp Motor
Motor Ramp (10,v5::MotorGears::green);

//Tracking Wheels
Rotation track_left(19);
Rotation track_right(20);
