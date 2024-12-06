using namespace pros;
//I am aware that using the extern keyword in C++ is not
//good practice, however, it is what VEXCode uses, and
//many other teams using PROS use extern as well

extern pros::Controller Con1;

//Motors
extern Motor FL;
extern Motor BL;

extern Motor FR;
extern Motor BR;

extern Motor ML;
extern Motor MR;

//Ramp
extern Motor Ramp;
//Dunker
extern Motor Arm;
//Clamp
extern pros::adi::Pneumatics Clamp;
//Sensors
extern Distance Checker;

//Define global variables here
extern double robot_angle;

