//
// Created by katier on 07.03.18.
//
#ifndef UNTITLED_ELLIPSE_H
#define UNTITLED_ELLIPSE_H

#include "Shape.h"

class Ellipse: public Shape{
public:
    Ellipse (Colour colour,double angle, Point center,double a,double b);
    void scale(double k) override;
    void move (Point toNewCenter) override;
    void rotate(double angle) override;
    void print (std::ostream& os) override;
    void roteteAroundZero(double angle);
private:
    double a;
    double b;
    Point center;
    double angle;
};


#endif //UNTITLED_ELLIPSE_H
