//Use multiple inertial sensors
class MultiIMU{
    private:
        pros::Imu imu_one;
        pros::Imu imu_two;
        pros::Imu imu_three;
    public:
        MultiIMU(int port_one,int port_two,int port_three);
        void calibrate();
        void reset();
        float one_data_point(float value_one, float value_two, float value_three);
        float get_rotation();
        float get_heading();
        void tare_rotation();
        void tare_heading();
        void set_heading(int heading);
        void set_rotation(int rotation);

};

//PID Loops for Drivetrain
class DrivePID{
    private:
    //Forward & Backward
        double kp_fb;
        double ki_fb;
        double kd_fb;
        //Turn with tracking wheels
        double kp_tu_w;
        double ki_tu_w;
        double kd_tu_w;
        //Strafe
        double kp_st;
        double ki_st;
        double kd_st;
        double ks_st;

        int side_zero;
        int side_one;
        int side_two;
        int side_three;

        double iteration_time;
    public:
        DrivePID(double kp_fb,double ki_fb,double kd_fb, double kp_tu_w,double ki_tu_w,double kd_tu_w, double kp_st,double ki_st,double kd_st,double ks_st, double iteration_time);
        void move(double distance, double kp_opt = 1267, double ki_opt = 1267, double kd_opt = 1267);
        void strafe(double distance, double kp_opt = 1267, double ki_opt = 1267, double kd_opt = 1267, double ks_opt = 1267);
        void turn_wheels(double revolutions, double kp_opt = 1267, double ki_opt = 1267, double kd_opt = 1267);
};

//Smart Controller Printing
class SmartCon{
    private:
    std::string first_check;
    std::string second_check;
    std::string third_check;
    std::string return_string;
    int return_num;
    int line;
    bool debug;
    int raw_ticks;
    int raw_sec;
    int total_time;
    int return_min;
    int return_sec;
    public:
    SmartCon(int total_time);
    std::tuple<int,std::string> print(std::string line_one, std::string line_two, std::string line_three, std::string rumble, std::tuple<int,int,int> order); 
    std::string get_time();
};


//Pneumatics Wrapper
class PneumaticsWrapper{
    private:
        int adi_port;
        int smart_port;
        bool current_state;
        enum pneu_states{
            off = 0,
            disabled = 0,
            retracted = 0,
            on = 1,
            enabled = 1,
            expanded = 1,
        };
    public:
        PneumaticsWrapper(int adi_port, int smart_port = 22);
        //This requires a function overload because you can't
        //have an int (really a real bool) as the name part of an enum
        bool set_value(pneu_states possibilities);
        bool set_value(bool possibilities);
        bool swap_state();      
};

//On-Screen Buttons
class ScreenButton{
    private:
        int x;
        int y;
        int length;
        int height;
        int color;
        bool toggle;
        bool enable;
        void draw_button();
    public:
        ScreenButton(int x, int y, int length, int width, int color, bool toggled = 0);
        bool toggled();
        void poll(int touch_x, int touch_y);
        void enabled(bool enable);
};