#ifndef HX_UTL_COLOUR_H
#define HX_UTL_COLOUR_H

struct Colour {
    int r;
    int g;
    int b;
    int a;

    Colour();
    Colour(int r, int g, int b);
    // predefined colours
    static const Colour Black;
    static const Colour White;
    static const Colour Grey25;
    static const Colour Grey50;
    static const Colour Grey75;

    static const Colour Red;
    static const Colour Green;
    static const Colour Blue;
    static const Colour Yellow;
    static const Colour Cyan;
    static const Colour Magenta;

    void set(float r, float g, float b);
    void set(float r, float g, float b, float a);
    void set(int r, int g, int b);
    void set(int r, int g, int b, int a);
    float getRf();
    float getGf();
    float getBf();
    float getAf();
    void fillArray(float *array);
    void fillArray(int *array);
    int clamp(int channel);
    float clamp(float channel);
};

#endif
