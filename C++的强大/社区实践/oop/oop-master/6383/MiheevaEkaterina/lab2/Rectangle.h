//
// Created by katier on 07.03.18.
//

#ifndef UNTITLED_RECTANGLE_H
#define UNTITLED_RECTANGLE_H

#include "Shape.h"

class Rectangle: public Shape{
public:
    Rectangle(Colour colour,Point p1, Point p2, Point p3, Point p4);
    Rectangle(Colour colour, double k1, double k2);

    bool isRectangle()  ;
    void print (std::ostream& os) override ;
    void scale(double k) override;
    void move(Point newCoord) override;
    void rotate (double angle) override;

protected:
    Point p1;
    Point p2;
    Point p3;
    Point p4;
};


#endif //UNTITLED_RECTANGLE_H
