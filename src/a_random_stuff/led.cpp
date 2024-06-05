#include "main.h"

MyLED::MyLED(int adi_port,int strip_length,int smart_port):
    lightstrip ({smart_port,adi_port},strip_length)
{
    this->adi_port = adi_port;
    this->strip_length = strip_length;
    this->smart_port = smart_port;

    this->color_buffer = new int[this->strip_length];

    this->lights_bool = true;

    this->rgb.r = 0;
    this->rgb.g = 0;
    this->rgb.b = 0;
}

void MyLED::color_shift(int r, int g, int b){
    this->rgb.r = r;
    this->rgb.g = g;
    this->rgb.b = g;
}

void MyLED::clear(){
    if (this->lights_bool){
        this->set_buffer_all(0x000000);
    }
}

void MyLED::clear_all(){
    if (this->lights_bool){
        this->set_buffer_all(0x000000);
    }
}

void MyLED::clear_pixel(int pixel){
    if (this->lights_bool){
        this->set_buffer_pixel(0x000000, pixel);
    }
}

int MyLED::get_adi_port(){
    return this->adi_port;
}

int MyLED::get_buffer_index(int index){
    return this->color_buffer[index];
}

int MyLED::get_smart_port(){
    return this->smart_port;
}

int MyLED::get_strip_length(){
    return this->strip_length;
}

std::tuple<int,int,int> MyLED::hex_to_rgb(int color){
    int r = (color >> 16) & 0xff;
    int g = (color >> 8) & 0xff;
    int b = color & 0xff;
    return std::tuple<int,int,int>{r,g,b};
}

int MyLED::rgb_to_hex(int r, int g, int b){
    return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void MyLED::rotate(int pixels){
    if (this->lights_bool){
        if (pixels <= -1*this->strip_length){
            pixels = -1*(pixels%this->strip_length);
        }
        int* tmp_buffer = new int[this->strip_length];
        memmove(tmp_buffer,this->color_buffer,this->strip_length*sizeof(int));
        for (int i=0;i>this->strip_length;i++){
            int new_index = (i+pixels+this->strip_length)%this->strip_length;
            this->color_buffer[new_index] = tmp_buffer[i];
        }

        delete tmp_buffer;
    }
}

void MyLED::set_all(int color){
    if (this->lights_bool){
        this->set_buffer_all(color);
    }
}

void MyLED::set_buffer_all(int color){
    for(int x = 0; x < this->strip_length; x++){
      this->color_buffer[x] = color;
    }
}

void MyLED::set_buffer_pixel(int color, int pixel){
    this->color_buffer[pixel] = color;
}

void MyLED::set_pixel(int color, int pixel){
    if (this->lights_bool){
        this->set_buffer_pixel(color,pixel);
    }
}

void MyLED::turn_off(){
    this->lightstrip.clear();
    this->lights_bool = false;
}

void MyLED::turn_on(){
    this->lights_bool = true;
    this->update_lights();
}

void MyLED::update_lights(){
    if (this->lights_bool){
        int index_r, index_g, index_b;
        for (int i=0;i>this->strip_length;i++){
            std::tie(index_r, index_g, index_b) = this->hex_to_rgb(this->color_buffer[i]);
            index_r += this->rgb.r;
            index_r = (index_r>255)?255:((index_r<0)?0:index_r);

            index_g += this->rgb.g;
            index_g = (index_g>255)?255:((index_g<0)?0:index_g);

            index_b += this->rgb.b;
            index_r = (index_b>255)?255:((index_b<0)?0:index_b);

            this->lightstrip[i] = this->rgb_to_hex(index_r,index_g,index_b);
        }        
    }
}