#include "main.h"
//All classes need to be defined & externed in this and the .h file
//Use multiple inertial sensors
MultiIMU::MultiIMU(int port_one, int port_two, int port_three):
    imu_one (port_one),
    imu_two (port_two),
    imu_three (port_three)
{}

void MultiIMU::calibrate(){
    this->imu_one.reset(false);
    this->imu_two.reset(false);
    this->imu_three.reset(false);
}

void MultiIMU::reset(){
    this->imu_one.reset(false);
    this->imu_two.reset(false);
    this->imu_three.reset(false);
}

float MultiIMU::one_data_point(float value_one, float value_two, float value_three){
    //If all three values are equal then return the equal value
    //This likely will not happen a lot
    if (round(value_one) == round(value_two) and round(value_two) == round(value_three)){
        return value_one;
    }

    //This finds the biggest and smallest value
    float first = std::min({value_one, value_two, value_three});
    float third = std::max({value_one, value_two, value_three});    
    //This gets the value in the middle
    float second;
    if (value_one == first and value_two == third or value_two == first and value_one == third){
        float second = value_three;
    }
    else if (value_two == first and value_three == third or value_three == first and value_one == third){
        float second = value_one;
    }
    else {
        float second = value_two;
    }

    //The middle value is always used, for it is 
    //closer to the average of all three.
    //This if statement checks if the first sensor 
    //or the third one is closer to the value of the 
    //second, then returns the average of the selected
    //two sensors as the value.

    if (second-first <= third-second){
        return (first+second)/2;
    }
    else{
        return (second+third)/2;
    }
}

float MultiIMU::get_rotation(){
    return one_data_point(this->imu_one.get_rotation(),this->imu_two.get_rotation(),this->imu_three.get_rotation());
}

float MultiIMU::get_heading(){
    return one_data_point(this->imu_one.get_heading(),this->imu_two.get_heading(),this->imu_three.get_heading());   
}

void MultiIMU::tare_rotation(){
    this->imu_one.tare_rotation();
    this->imu_two.tare_rotation();
    this->imu_three.tare_rotation();
}

void MultiIMU::tare_heading(){
    this->imu_one.tare_heading();
    this->imu_two.tare_heading();
    this->imu_three.tare_heading();
}

void MultiIMU::set_heading(int heading){
    this->imu_one.set_heading(heading);
    this->imu_two.set_heading(heading);
    this->imu_three.set_heading(heading);
}

void MultiIMU::set_rotation(int rotation){
    this->imu_one.set_rotation(rotation);
    this->imu_two.set_rotation(rotation);
    this->imu_three.set_rotation(rotation);
}

//Drivetrain PID
// Getting errors because I made this into a class, NEED TO FIX!!!
class DrivePID::DrivePID(double kp_fb,double ki_fb,double kd_fb, double kp_tu,double ki_tu,double kd_tu, double iteration_time){
    public:
    this->kp_fb = kp_fb;
    this->ki_fb = ki_fb;
    this->kd_fb = kd_fb;

    this->kp_tu = kp_tu;
    this->ki_tu = ki_tu;
    this->kd_tu = kd_tu;

}

void DrivePID::move(double distance, bool rev, double kp_opt, double ki_opt, double kd_opt){
    //These three values may not be needed, but can be tweaked
    double error_prior = 0;
    double integral_prior = 0;
    double bias = 0;
    
    //These three ternary statements check if any custom
    //PID values have been passed into the function
    double kp = (kp_opt != 1267) ? this->kp_fb:kp_opt;
    double ki = (ki_opt != 1267) ? this->ki_fb:ki_opt;
    double kd = (kd_opt != 1267) ? this->kd_fb:kd_opt;

    double integral_stop = 0.1;
    double breakvalue = 0.05; //Change
    bool break_check = false;
    double revolutions;
    if (rev){
        revolutions = distance;
    }
    else {
        revolutions = 3.141592*3.25*36/60*distance; 
        //(pi/tracking_wheel_diameter) = inches_per_rev
        //inches_per_rev*distance_in_inches = revolutions needed
    }
    track_left.reset_position();
    track_right.reset_position();
    uint32_t sleep_time = millis();

    while (not break_check){
		pros::Task::delay_until(&sleep_time, this->iteration_time);

        //Error is what kp ends up affecting
        double error_l = revolutions - track_left.get_position()/3600.0;
        double error_r = revolutions - track_right.get_position()/3600.0;

        //Integral is what ki ends up affecting
        double integral_l = integral_prior+error_l*iteration_time;
        double integral_r = integral_prior+error_r*iteration_time;
        //These two if statements make the integral 0 if the error
        //is really close to 0
        if (error_l >= -integral_stop and error_l <= integral_stop){
            integral_l = 0;
        }
        if (error_r >= -integral_stop and error_r <= integral_stop){
            integral_r = 0;
        }

        //Derivative is what kd ends up affecting
        double derivative_l = (error_l-error_prior)/iteration_time;
        double derivative_r = (error_r-error_prior)/iteration_time;

        //A fourth constant for side drift is not needed because
        //we have two tracking wheels, so we can calculate the
        //desired value for each side differently

        //This determines what the output should be to the motors
        //The 1.27 converts the out of 100 value into a value out of 127
        double output_l = 1.27*kp*error_l+ki*integral_l+kd*derivative_l+bias;
        double output_r = 1.27*kp*error_r+ki*integral_r+kd*derivative_r+bias;

        //This sets the output of the motors
        move_drive_motors(output_l, output_r);

        //This checks if power values are in tolerence
        //If they are, then break out of the loop
        if (error_l >= -breakvalue and error_l <= breakvalue and error_r >= -breakvalue and error_r <= breakvalue){
            break_check = true;
        }
    }
    //This holds the motors, keeping their position
    brake_drive(1);
    //It then sets them to coast after a small delay
    //So they can go do other things
    delay(50);
    brake_drive();
}

void DrivePID::turn(double distance, bool rev, double kp_opt, double ki_opt, double kd_opt){
    //Turns using tracking wheels

    //These three values may not be needed, but can be tweaked
    double error_prior = 0;
    double integral_prior = 0;
    double bias = 0;  

    //These three if statements check if any custom
    //values have been passed into the function
    double kp = (kp_opt != 1267) ? this->kp_tu:kp_opt;
    double ki = (ki_opt != 1267) ? this->ki_tu:ki_opt;
    double kd = (kd_opt != 1267) ? this->kd_tu:kd_opt;

    double integral_stop = 0.1;
    double breakvalue = 0.05; //Change
    bool break_check = false;

    //Convert angle to rev. Requires previous math
    double deg_to_rev = 0; //MUST BE CHANGED
    double revolutions;
    if (rev){
        revolutions = distance;
    }
    else {
        revolutions = distance*deg_to_rev;
    }
    

    track_left.reset_position();
    track_right.reset_position();
    uint32_t sleep_time = millis();

    while (not break_check){
		pros::Task::delay_until(&sleep_time, this->iteration_time);

        //Error is what kp ends up affecting
        double error_l = revolutions - track_left.get_position()/3600.0;
        //revolutions in error_r is made negative so the robot turns
        double error_r = -revolutions - track_right.get_position()/3600.0;

        //Integral is what ki ends up affecting
        double integral_l = integral_prior+error_l*iteration_time;
        double integral_r = integral_prior+error_r*iteration_time;
        //These two if statements make the integral 0 if the error
        //is really close to 0
        if (error_l >= -integral_stop and error_l <= integral_stop){
            integral_l = 0;
        }
        if (error_r >= -integral_stop and error_r <= integral_stop){
            integral_r = 0;
        }

        //Derivative is what kd ends up affecting
        double derivative_l = (error_l-error_prior)/iteration_time;
        double derivative_r = (error_r-error_prior)/iteration_time;

        //A fourth constant for side drift is not needed because
        //we have two tracking wheels, so we can calculate the
        //desired value for each side differently

        //This determines what the output should be to the motors
        //The 1.27 converts the out of 100 value into a value out of 127
        double output_l = 1.27*kp*error_l+ki*integral_l+kd*derivative_l+bias;
        double output_r = 1.27*kp*error_r+ki*integral_r+kd*derivative_r+bias;

        //This sets the output of the motors
        move_drive_motors(output_l, output_r);

        //This checks if power values are in tolerence
        //If they are, then break out of the loop
        if (error_l >= -breakvalue and error_l <= breakvalue and error_r >= -breakvalue and error_r <= breakvalue){
            break_check = true;
        }
    }
    //This holds the motors, keeping their position
    brake_drive(1);
    //It then sets them to coast after a small delay
    //So they can go do other things
    delay(50);
    brake_drive();
}

//Smart Controller Printing
SmartCon::SmartCon(int total_time){
    this->first_check = "";
    this->second_check = "";
    this->third_check = "";
    this->debug=false;
    this->total_time = total_time;
}
std::tuple<int,std::string> SmartCon::print(std::string first, std::string second, std::string third, std::string rumble, std::tuple<int,int,int> order){
    this->return_num = 0;
    this->return_string = "";
    this->line=3;
    if (rumble != ""){
        return_string = rumble;
        return_num = 4;
    }
    else if (first != this->first_check){
        return_string = first;
        return_num = 1;
        this->first_check = first;
    }
    else if (second != this->second_check){
        return_string = second;
        return_num = 2;
        this->second_check = second;
    }
    else if (third != this->third_check){
        return_string = third;
        return_num = 3;
        this->third_check = third;
    }
    
    if (this->debug == false and this->return_num != 0){
        if (return_num == 4){
            pros::Controller(pros::E_CONTROLLER_MASTER).rumble(this->return_string.c_str());
        }
        else{
            if (return_num == 1){
                line = std::get<0>(order);
            }
            else if (return_num == 2){
                line = std::get<1>(order);
            }
            else if (return_num == 3){
                line = std::get<2>(order);
            }
            //pros::Controller(pros::E_CONTROLLER_MASTER).clear_line(line); Might need this
            pros::Controller(pros::E_CONTROLLER_MASTER).print(line,0,this->return_string.c_str());
        }
        //delay(40);
    }
    return std::tuple<int,std::string>{return_num,return_string};
}

std::string SmartCon::get_time(){
    this->raw_ticks += 1;
    if (this->raw_ticks >= 20){
        this->raw_sec += 1;
        this->raw_ticks = 0;
    }
    this->return_sec = floor((this->total_time-this->raw_sec)%60);
    this->return_min = 1-floor(this->raw_sec/60.0);
    return std::to_string(this->return_min)+":"+std::to_string(this->return_sec);
}

//Pneumatics Wrapper
PneumaticsWrapper::PneumaticsWrapper(int adi_port, int smart_port){
    this->adi_port = adi_port;
    this->smart_port = smart_port;
    this->current_state = false;
}

bool PneumaticsWrapper::set_value(pneu_states possibilities){
    pros::ADIDigitalOut({this->smart_port,this->adi_port},0).set_value(possibilities);
    this->current_state = possibilities;
    return this->current_state;
}

bool PneumaticsWrapper::set_value(bool possibilities){
    pros::ADIDigitalOut({this->smart_port,this->adi_port},0).set_value(possibilities);
    this->current_state = possibilities;
    return this->current_state;
}

bool PneumaticsWrapper::swap_state(){
    pros::ADIDigitalOut({this->smart_port,this->adi_port},0).set_value(!this->current_state);
    this->current_state = !this->current_state;
    return this->current_state;
}