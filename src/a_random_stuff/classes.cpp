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
DrivePID::DrivePID(double kp_fb,double ki_fb,double kd_fb, double kp_tu,double ki_tu,double kd_tu, double dt){
    this->kp_fb = kp_fb;
    this->ki_fb = ki_fb;
    this->kd_fb = kd_fb;

    this->kp_tu = kp_tu;
    this->ki_tu = ki_tu;
    this->kd_tu = kd_tu;

    this->finish=false;
    this->breakpoint=5;
    this->dt=dt;

    this->li=0;
    this->ri=0;
    this->loe=0;
    this->roe=0;

}

void DrivePID::prepare(double distangle, bool turn, bool rev){
    this->turn=turn;
    if (!this->turn){
        this->target = rev==0?distangle:(360*distangle)/(4*3.1416)*(1/1);
        //360 - Convert into revolutions
        //distance (inches)
        //wheel diameter (inches)
        //pi
        //gear ratio (motor/wheel)
    }
    else {
        float r = 1; //Radius of drivetrain
        this->target = rev==0?distangle:(2*r*distangle/4)*(1/1);
        //This is a form of the arc length equation
        //See page 149 of notebook for details
    }

	//set correct encoder units
	FL.set_encoder_units(MOTOR_ENCODER_DEGREES);
    ML.set_encoder_units(MOTOR_ENCODER_DEGREES);
	BL.set_encoder_units(MOTOR_ENCODER_DEGREES);
	FR.set_encoder_units(MOTOR_ENCODER_DEGREES);
    MR.set_encoder_units(MOTOR_ENCODER_DEGREES);
	BR.set_encoder_units(MOTOR_ENCODER_DEGREES);

	FL.tare_position();
    ML.tare_position();
	BL.tare_position();
	FR.tare_position();
    MR.tare_position();
	BR.tare_position();
	//Set motor position to 0
	std::uint32_t time = millis();
}
void DrivePID::move(){
	this->l_encode = (FL.get_position()+ML.get_position()+BL.get_position())/3;
	this->r_encode = (FL.get_position()+MR.get_position()+BR.get_position())/3;
	//This averages all three motors, which is more accurate

	//Error for both sides
	this->l_error = this->target-this->l_encode;
	this->r_error = this->target-this->r_encode;

	//Proportional for both sides
	this->lp = this->kp_fb*this->l_error;
	this->rp = this->kp_fb*this->r_error;

	//Integral for both sides
	//Use the ternery operator to keep it compact
	//If error is 0, we want the integral at 0
	//Also, if error > +-100, then it should be 0
	float arb_num = 100;
	this->li = this->l_error>std::abs(arb_num)?0:this->l_error==0?0:this->ki_fb*(this->li+this->dt*this->l_error);
	this->ri = this->r_error>std::abs(arb_num)?0:this->r_error==0?0:this->ki_fb*(this->ri+this->dt*this->r_error);

	//Derivative for both sides
	this->ld = this->kd_fb*(this->l_error-this->loe)/this->dt;
	this->rd = this->kd_fb*(this->r_error-this->roe)/this->dt;

	//Set previous error to error
	this->loe = this->l_error;
	this->roe = this->r_error;

	//Motor values
    if (!this->turn){
        this->l_motor = this->lp+this->li+this->ld;
        this->r_motor = this->rp+this->ri+this->rd;
    }
    else {
        this->l_motor = (this->lp+this->li+this->ld+this->rp+this->ri+this->rd)/2;
        this->r_motor = -this->l_motor;
    }
	//Move motors
	move_drive_motors(this->l_motor,this->r_motor);

	//Calculate whether loop should end
	if (fabs(this->l_motor)<=this->breakpoint and fabs(this->r_motor)<=this->breakpoint){
		this->finish = true;
	}
    Task::delay_until(&this->time,this->dt);
}

bool DrivePID::is_finished(){
    return this->finish;
}

/*
How to use PIDmove:
    pid_prepare(distance);
    while(!is_finished()){
        pid_move();
    }
*/

/*
void DrivePID::turn(double distance, bool rev){
    Turns using tracking wheels

    //These three values may not be needed, but can be tweaked
    double error_prior = 0;
    double integral_prior = 0;
    double bias = 0;  

    double kp = this->kp_tu;
    double ki = this->ki_tu;
    double kd = this->kd_tu;

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
*/

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
            //pros::Controller(pros::E_CONTROLLER_MASTER).rumble(this->return_string.c_str());
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
            pros::Controller(pros::E_CONTROLLER_MASTER).clear_line(line); //Might need this
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