#include "main.h"
void ring_auton(int color_value){
    Con1.clear();
    delay(50);
    DrivePID drive(0.2,0,0.1,0.4,0,0);
    drive.prepare(90,1);
    while (!drive.is_finished()){
        drive.go();
    }
    delay(50);
    Con1.clear();


}