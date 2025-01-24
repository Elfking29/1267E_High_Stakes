#include "main.h"
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */

void button_update(){
    screen_touch_status_s_t status = screen::touch_status();
    int touch_x = status.x;
    int touch_y = status.y;
    //button::poll(touch_x,touch_y);
}

SmartCon Initprint(0);
int auton_value = 0;
int color_value = 0;

//Define Buttons
ScreenButton color_type(15,10,220,150,0xD22630,0x0077c8,"Red","Blue",0x000000,0x000000);
ScreenButton full_auton(250,10,220,50,0x004e38,0x004e38,"Full","Full");
ScreenButton mogo_auton(250,100,220,50,0xCFFF04,0xCFFF04,"Mogo","Mogo");
ScreenButton skills_tst(15,175,220,50,0xff580f,0xff580f,"Sklz Auto","Sklz Auto");
ScreenButton rush_auton(250,175,220,50,0xFF13F0,0xFF13F0,"Rush", "Rush");

// competition_initaialize is the same as pre_auton.
void competition_initialize() {
    //Initalize Buttons
    color_type.enabled(1);
    full_auton.enabled(1);
    mogo_auton.enabled(1);
    skills_tst.enabled(1);
    rush_auton.enabled(1);
    pros::screen_touch_status_s_t status;
    int x;
    int y;
    bool wait = false;
    bool hold = true;
    while (hold==true){
        //Track Touches & Update Buttons
        status = pros::screen::touch_status();
        //Get touchscreen status
        if (status.touch_status==TOUCH_RELEASED and wait==false){
            //If screen is pressed and not locked
            x = status.x; //Get x value
            y = status.y; //Get y value
            color_type.poll(x,y);
            full_auton.poll(x,y);
            mogo_auton.poll(x,y);
            skills_tst.poll(x,y);
            rush_auton.poll(x,y);
            wait=true; //Lock input
        }
        else if (status.touch_status!=TOUCH_RELEASED){
            wait=false; //Release lock
        }

        //Set Variables
        //This just sets variables for auton
        if (skills_tst.toggled()){
            auton_value = 4;
        }
        else if (full_auton.toggled()){
            auton_value = 1;
        }
        else if (mogo_auton.toggled()){
            auton_value = 2;
        }
        else if (rush_auton.toggled()){
            auton_value = 3;
        }

        
        if (color_type.toggled()==1){
            color_value = -1;
        }
        else{
            color_value = 1;
        }
        
        pros::Task::delay(1); //Delay before repeat

        //if (pneu_tests.toggled() == true){
            //hold = false;
        //}

    }
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    color_type.enabled(0);
    full_auton.enabled(0);
    mogo_auton.enabled(0);
    skills_tst.enabled(0);
    rush_auton.enabled(0);
    logo();
    //Select Auton
    //auton_value = 1;
    //color_value = 1;
    if (auton_value==4{
        skills_auton();
    }
    else if (auton_value==0){
        ring_auton(-color_value);
    }
    else if (auton_value==1){
        ring_auton(color_value);
    }
}
