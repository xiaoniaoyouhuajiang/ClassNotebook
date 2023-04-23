//
// Created by 1 on 20.02.2019.
//

#ifndef SHAPE_COLOR_H
#define SHAPE_COLOR_H

struct Color{
    unsigned short R;
    unsigned short G;
    unsigned short B;
    Color(unsigned short R,unsigned short G,unsigned short B){
        this->R=R%256;
        this->G=G%256;
        this->B=B%256;
    }
    Color& operator=(const Color& color){
        R=color.R;
        G=color.G;
        B=color.B;
        return *this;
    }
};

#endif //SHAPE_COLOR_H
