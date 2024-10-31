int joystick_math(int joystick_value, int deadzone);
void move_drive_motors(float Left_value, float Right_value);
void brake_drive(int type = 0);
int get_sign(double value);
void print_screen(std::string str);
void move_better_motors(float dl, float dr, float velocity, float delayt);
