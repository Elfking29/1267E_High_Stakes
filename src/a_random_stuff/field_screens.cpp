#include "main.h"
void draw_tiles(){
    pros::screen::set_pen(0xFFFFFF);
    pros::screen::draw_rect(0,32,120,152);
    int gray;
    for (int y=32;y>152;y=y+20){ //Because of the status bar, might be able to be changed
        for (int x=0;x>120;x=x+20){
            if (gray == 0x333333){
                gray = 0x555555;
            }
            else {
                gray = 0x333333;
            }
            pros::screen::set_pen(gray);
            pros::screen::fill_rect(x,y,x+20,y+20);
        }
    }
}

void draw_donut(int x, int y, bool color){
    //0=Red, 1=Blue
    if (color){
        pros::screen::set_pen(0x0000FF);
    }
    else{
        pros::screen::set_pen(0xFF0000);
    }
    //This sets color of ring
    int r = 6; //Possibly change later
    pros::screen::fill_circle(x,y,r);
}

void draw_mogo(int x, int y){
    pros::screen::set_pen(0xFFFF00);
    int r = 8; //Possibly change later
    pros::screen::fill_circle(x,y,r);
}

void draw_stakes(){
    pros::screen::set_pen(0xFFFF00);
    int r = 3; //Possibly change later
    pros::screen::fill_circle(60,32,r);
    pros::screen::fill_circle(60,152,r);
    pros::screen::set_pen(0xFF0000);
    pros::screen::fill_circle(0,92,r);
    pros::screen::set_pen(0x0000FF);
    pros::screen::fill_circle(120,92,r);
}

void draw_ladder(){
    pros::screen::set_pen(0x9F9F00);
    int x=1;
    int y=1;
    pros::screen::draw_line(x,y,x,y);
}

//On-Screen Buttons
ScreenButton::ScreenButton(int x, int y, int length, int height, int color, bool toggled){
    this->x=x;
    this->y=y;
    this->length=length;
    this->height=height;
    this->color=color;
    this->toggle=toggled;
    this->enable=false;
}

void ScreenButton::draw_button(){
    int margin = 3;
    if (enable){
        //Draw toggled outline if needed
        if (toggle){
            screen::set_pen(0xffffff);
        }
        else {
            screen::set_pen(0x000000);
        }
        screen::fill_rect(this->x-margin,this->y-margin,this->x+this->length+margin,this->y+this->height+margin);
        //Draw actual button
        screen::set_pen(this->color);
        screen::fill_rect(this->x,this->y,this->x+this->length,this->y+this->height);
    }
    else {
        screen::set_pen(0x000000);
        screen::fill_rect(this->x-margin,this->y-margin,this->x+this->length+margin,this->y+this->height+margin);
    }
}

bool ScreenButton::toggled(){
    return this->toggle;
}

void ScreenButton::poll(int touch_x, int touch_y){
    //The reason for using parameters rather than
    //accessing the touch data dirctly is that
    //accessing the data only once is faster 

    //This function should be placed inside a screen::touch_callback
    //Example: screen::touch_callback(button::poll(),TOUCH_PRESSED)
    if (enable){
        if (touch_x >= this->x and touch_x <= this->x+this->length and touch_y >= this->y and touch_y <= this->y+this->height){
            this->toggle = !this->toggle;
            this->draw_button();
        }
    }
}

void ScreenButton::enabled(bool enable){
    //Enable whenever you want buttone to display and touch
    //Disable otherwise
    this->enable=enable;
    this->draw_button();
}