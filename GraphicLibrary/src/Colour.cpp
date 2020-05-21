#include "Colour.h"
#include <cmath>

// predefined colours
const Colour Colour::Black (   0,   0,   0);
const Colour Colour::White ( 255, 255, 255);
const Colour Colour::Grey25(  64,  64,  64);
const Colour Colour::Grey50( 128, 128, 128);
const Colour Colour::Grey75( 192, 192, 192);

const Colour Colour::Red     ( 255,   0,   0);
const Colour Colour::Yellow  ( 255, 255,   0);
const Colour Colour::Green   (   0, 255,   0);
const Colour Colour::Cyan    (   0, 255, 255);
const Colour Colour::Blue    (   0,   0, 255);
const Colour Colour::Magenta ( 255,   0, 255);

Colour::Colour(){
    r = 255;
    g = 255;
    b = 255;
    a = 255;
}
Colour::Colour(int r, int g, int b){
    this->r = clamp(r);
    this->g = clamp(g);
    this->b = clamp(b);
    a = 255;
}

void Colour::set(float r, float g, float b){
    this->r = clamp((int)rint(r*255));
    this->g = clamp((int)rint(g*255));
    this->b = clamp((int)rint(b*255));
    a = 255;
}
void Colour::set(float r, float g, float b, float a){
    this->r = clamp((int)rint(r*255));
    this->g = clamp((int)rint(g*255));
    this->b = clamp((int)rint(b*255));
    this->a = clamp((int)rint(a*255));
}
void Colour::set(int r, int g, int b){
    this->r = clamp(r);
    this->g = clamp(g);
    this->b = clamp(b);
    a = 255;
}
void Colour::set(int r, int g, int b, int a){
    this->r = clamp(r);
    this->g = clamp(g);
    this->b = clamp(b);
    this->a = clamp(a);
}
float Colour::getRf(){
    return (((float)r)/255.f);
}
float Colour::getGf(){
    return (((float)g)/255.f);
}
float Colour::getBf(){
    return (((float)b)/255.f);
}
float Colour::getAf(){
    return (((float)a)/255.f);
}

void Colour::fillArray(float *array){
    array[0] = getRf();
    array[1] = getGf();
    array[2] = getBf();
    array[3] = getAf();
}
void Colour::fillArray(int *array){
    array[0] = r;
    array[1] = g;
    array[2] = b;
    array[3] = a;
}

int Colour::clamp(int channel){
    if (channel < 0){
        channel = 0;
    } else if (channel > 255){
        channel = 255;
    }
    return channel;
}
float Colour::clamp(float channel){
    if (channel < 0.f){
        channel = 0.f;
    } else if (channel > 1.f){
        channel = 1.f;
    }
    return channel;
}
