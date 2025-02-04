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

//Intake
extern Motor Intake;
//Dunker
extern Motor Arm;
//Pneumatics
extern pros::adi::Pneumatics Clamp;
extern pros::adi::Pneumatics Corner;
//Sensors
extern Optical Colory;
extern Rotation Rotaty;
extern Rotation Armaty;

//Define global variables here
extern int color_value;

