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
Motor FL (1,v5::MotorGears::blue);
Motor BL (3,v5::MotorGears::blue);

Motor FR (4,v5::MotorGears::blue);
Motor BR (5,v5::MotorGears::blue);

Motor ML (2,v5::MotorGears::blue);
Motor MR (6,v5::MotorGears::blue);

//Tracking Wheels
Rotation track_left(18);
Rotation track_right(19);
Rotation track_back(20);

//Inertial
IMU inertial (11);

//Auton Stuff
adi::Potentiometer selector (1,E_ADI_POT_EDR);
adi::DigitalIn changer (2);