void draw_tiles();
void draw_donut(int x, int y, bool color);
void draw_mogo(int x, int y);
void draw_stakes();
void draw_ladder();

//On-Screen Buttons
class ScreenButton{
    private:
        int x;
        int y;
        int length;
        int height;
        int color_one;
        int color_two;
        bool toggle;
        bool enable;
        std::string str_one;
        std::string str_two;
        int border_one;
        int border_two;
        void draw_button();
    public:
        ScreenButton(int x, int y, int length, int width, int color_one, int color_two, std::string str_one, std::string str_two, int border_one=0x000000, int border_two=0xFFFFFF, bool toggled = 0);
        bool toggled();
        void poll(int touch_x, int touch_y);
        void enabled(bool enable);
};