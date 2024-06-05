int joystick_math(int joystick_value, int deadzone);
void move_drive_motors(int FL_value, int BL_value, int FR_value, int BR_value, int ML_value, int MR_value);
void brake_drive(int type = 0);
int get_sign(double value);
