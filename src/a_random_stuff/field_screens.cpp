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