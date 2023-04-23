#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>

#include "point.h"
#include "color.h"


class Shape{
public:
    Shape(Point cent = Pzero, Color clr = Black): center(cent), col(clr) {
        angle = 0;
        mult = 1;
    }
    virtual ~Shape() {}
    virtual void move(const Point & delta){ center = center + delta; }
    virtual void moveTo(const Point & newCenter){ center = newCenter; }
    virtual void resize(double size){ mult *= size; }
    virtual void rotate(double newAngle) { angle += newAngle; }

    Point getCenter(){ return center; }
    virtual double square() {return 0; }

    friend ostream& operator<<(ostream& os, const Shape& dt){
        os << "C: " << dt.center;
        return os;
    }

    Color getColor() {return col; }
    void setColor(Color clr) { col = clr; }
protected:
    Color col;
    double angle;
    double mult;
    Point center;
};

#endif