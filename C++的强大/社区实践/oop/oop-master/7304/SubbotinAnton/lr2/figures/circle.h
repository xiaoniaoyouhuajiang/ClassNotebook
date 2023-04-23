#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape
{
public:
    double radius;

    Circle(const Point, double);
    ~Circle(){}

    void MoveTo(const Point);
    void RotateOn(double);
    void ScaleOn(double);
    void Information(ostream&);
};

#endif // CIRCLE_H
