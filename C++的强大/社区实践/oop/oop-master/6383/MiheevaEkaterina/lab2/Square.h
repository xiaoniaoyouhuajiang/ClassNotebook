//
// Created by katier on 07.03.18.
//

#ifndef UNTITLED_SQUARE_H
#define UNTITLED_SQUARE_H

#include "Rectangle.h"

class Square: public Rectangle{
public:
    Square(Colour colour,Point p1,Point p2,Point p3,Point p4);
    explicit Square(Colour colour);
    void print (std::ostream& os) override ;
    bool isSquare();
};


#endif //UNTITLED_SQUARE_H
