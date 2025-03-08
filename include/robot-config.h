using namespace pros;
//I am aware that using the extern keyword in C++ is not
//good practice, however, it is what VEXCode uses, and
//many other teams using PROS use extern as well

extern pros::Controller Con1;
extern pros::Controller Con2;

//Motors
extern Motor FL;
extern Motor BL;

extern Motor FR;
extern Motor BR;

extern Motor ML;
extern Motor MR;

//Intake
extern Motor Hook;
extern Motor Intake;
//Dunker
extern Motor Arm;
//Pneumatics
extern pros::adi::Pneumatics Clamp;
extern pros::adi::Pneumatics Cornerer;
extern pros::adi::Pneumatics Sorter;
extern pros::adi::Pneumatics Lift;
//Sensors
extern Optical Colory;
extern Rotation Rotaty;
extern Imu imu;
extern Rotation Armaty;

//Define global variables here
extern int color_value;

