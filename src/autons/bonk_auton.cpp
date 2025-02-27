#include "main.h"
void bonk_auto(){
    color_value=1;
    delay(50);
    Con1.clear_line(0);
    DrivePID drive(0.2,0,0.1,0.1,0,0.05);
    drive.prepare(90,1);
    while (!drive.is_finished()){
        drive.go();
    }
    delay(3000);
}