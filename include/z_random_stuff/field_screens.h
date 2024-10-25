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