#ifndef REGULARHEXAGON_H
#define REGULARHEXAGON_H

#include "shape.h"

class RegularHexagon : public Shape
{
public:
    Point UpperA;
    double radius;

    RegularHexagon(Point, double);
    ~RegularHexagon(){}

    void MoveTo(const Point);
    void RotateOn(double);
    void ScaleOn(double);
    void Information(ostream&);
};

#endif // REGULARHEXAGON_H
