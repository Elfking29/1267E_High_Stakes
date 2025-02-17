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
    this->breakpoint=15;
    this->dt=dt;

    this->li=0;
    this->ri=0;
    this->loe=0;
    this->roe=0;

}

void DrivePID::prepare(double distangle, bool turn, bool rev){
    this->turn=turn;
    this->finish = false;
    if (this->turn == false){
        this->target = (360*distangle*60)/(3.25*3.1416*36);
        //360 - Convert into revolutions
        //distance (inches)
        //wheel diameter (inches)
        //pi
        //gear ratio (motor/wheel)
    }
    else {
        //this->target = (2*6.5*distangle/3.25)*(60/36);
        this->target = color_value*distangle*1900/315;
        //This is a form of the arc length equation
        //See page 149 of notebook for details
    }
    //Set correct k constants
    this->kp=this->turn==0?this->kp_fb:this->kp_tu;
    this->ki=this->turn==0?this->ki_fb:this->ki_tu;
    this->kd=this->turn==0?this->kd_fb:this->kd_tu;

	//Set correct encoder units (degrees)
	FL.set_encoder_units(MOTOR_ENCODER_DEGREES);
    ML.set_encoder_units(MOTOR_ENCODER_DEGREES);
	BL.set_encoder_units(MOTOR_ENCODER_DEGREES);
	FR.set_encoder_units(MOTOR_ENCODER_DEGREES);
    MR.set_encoder_units(MOTOR_ENCODER_DEGREES);
	BR.set_encoder_units(MOTOR_ENCODER_DEGREES);

	//Set motor position to 0
	FL.tare_position();
    ML.tare_position();
	BL.tare_position();
	FR.tare_position();
    MR.tare_position();
	BR.tare_position();

    //Set time
	this->time = millis();
    this->st = this->time;
}

void DrivePID::go(){

	this->l_encode = (FL.get_position()+ML.get_position()+BL.get_position())/3;
	this->r_encode = (FR.get_position()+MR.get_position()+BR.get_position())/3;
    if (this->turn==1){
        this->r_encode = -this->r_encode;
    }
	//This averages all three motors, which is more accurate

	//Error for both sides
	this->l_error = this->target-this->l_encode;
	this->r_error = this->target-this->r_encode;

	//Proportional for both sides
	this->lp = this->kp*this->l_error;
	this->rp = this->kp*this->r_error;

	//Integral for both sides
	//Use the ternery operator to keep it compact
	//If error is 0, we want the integral at 0
	//Also, if error > +-100, then it should be 0
	float arb_num = 100;
	this->li = this->l_error>std::abs(arb_num)?0:this->l_error==0?0:this->ki*(this->li+this->dt*this->l_error);
	this->ri = this->r_error>std::abs(arb_num)?0:this->r_error==0?0:this->ki*(this->ri+this->dt*this->r_error);

	//Derivative for both sides
	this->ld = this->kd*(this->l_error-this->loe)/this->dt;
	this->rd = this->kd*(this->r_error-this->roe)/this->dt;

	//Set previous error to error
	this->loe = this->l_error;
	this->roe = this->r_error;

	//Motor values
    if (this->turn == 0){
        this->l_motor = this->lp+this->li+this->ld;
        this->r_motor = this->rp+this->ri+this->rd;
    }
    else {
        this->l_motor = (this->lp+this->li+this->ld+this->rp+this->ri+this->rd)/2;
        this->r_motor = -this->l_motor;
    }

    //gaeb was here ;P

	//Move motors
	move_drive_motors(this->l_motor,this->r_motor);

    Con1.print(0,0,"%i,%i",int(this->l_motor), int(this->r_motor));

	//Calculate whether loop should end
	if (fabs(this->l_motor)<=this->breakpoint and fabs(this->r_motor)<=this->breakpoint){
		this->finish = true;
        FL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
        BL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

        FR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
        BR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

        ML.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
        MR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

        FL.brake();
        BL.brake();

        FR.brake();
        BR.brake();

        ML.brake();
        MR.brake();
	}


    //Delay for 10 msec
    Task::delay_until(&this->time,this->dt);
}



bool DrivePID::is_finished(){
    return this->finish;
}

void DrivePID::timeout(int t){
    if (t!=0){
        if (this->time+this->st >= this->st+t){
            this->finish = true;
        }
    }
}

void DrivePID::q_go(double distangle, bool turn, int t){
    this->prepare(distangle,turn);
    while (!this->is_finished()){
        this->go();
        this->timeout(t);
    }
}

/*
How to use PIDmove:
    prepare(distance, turn {0/1});
    while(!is_finished()){
        other_stuff_first();
        move();
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