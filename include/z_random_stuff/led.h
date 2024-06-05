class MyLED{
    private:
        int adi_port;
        int strip_length;
        int smart_port;

        int* color_buffer;

        bool lights_bool;

        struct{
            int r;
            int g;
            int b;
        } rgb;

        pros::ADILed lightstrip;

    public:
        MyLED(int adi_port, int strip_length, int smart_port = 22);
        void color_shift(int r, int g, int b);
        void clear();
        void clear_all();
        void clear_pixel(int pixel);
        int get_adi_port();
        int get_buffer_index(int index);
        int get_smart_port();
        int get_strip_length();
        void gradient(int start_color, int end_color, int fade_width, int start_pos, bool reversed);
        int interpolate_rgb(int start_color, int end_color, int step, int fade_width, int start_pos, bool reversed);
        std::tuple<int,int,int> hex_to_rgb(int color);
        int rgb_to_hex(int r, int g, int b);
        void rotate(int pixels);
        void set_all(int color);
        void set_buffer_all(int color);
        void set_buffer_pixel(int color, int pixel);
        void set_pixel(int color, int pixel);
        void turn_off();
        void turn_on();
        void update_lights();
};