#include "main.h"
void full_auto(){
    color_value=-1;
    DrivePID drive(0.2,0,0.1,1,0,0.2);
    Colory.set_led_pwm(100); //R 10+-10 B 210+-10
    delay(100);
    drive.prepare(-18);
    while(!drive.is_finished()){
        drive.go();
    }
    delay(250);
    drive.prepare(-5);
    while(!drive.is_finished()){
        drive.go();
    }
    delay(100);
    Clamp.toggle();
    delay(250);
    drive.prepare(25,1);
    while (!drive.is_finished()){
        drive.go();
    }
    while (1==1){}
    
}  