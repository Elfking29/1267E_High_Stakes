#include "main.h"
void bonk_auto(){
    DrivePID drive(0.2,0,0.1,0.4,0,0);
    drive.prepare(-10);
    while (!drive.is_finished()){
        drive.go();
    }
}