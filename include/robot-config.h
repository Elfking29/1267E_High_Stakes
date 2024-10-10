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

//Tracking Wheels
extern Rotation track_left;
extern Rotation track_right;
extern Rotation track_back;

//Inertial
extern IMU inertial;

//Auton Stuff
extern adi::Potentiometer selector;
extern adi::DigitalIn changer;

//Light Strip

//Define global variables here
extern int color_value;
extern int auton_value;
extern double robot_angle;

