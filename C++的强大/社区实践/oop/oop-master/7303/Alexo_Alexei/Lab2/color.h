#ifndef COLOR_H
#define COLOR_H

struct Color{
    unsigned short R;
    unsigned short G;
    unsigned short B;
    Color(unsigned short R, unsigned short G ,unsigned short B){
        this->R = R % 256;
        this->G = G % 256;
        this->B = B % 256;
    }
    Color& operator = (const Color& color){
        R = color.R;
        G = color.G;
        B = color.B;
        return *this;
    }
};

#endif // COLOR_H
