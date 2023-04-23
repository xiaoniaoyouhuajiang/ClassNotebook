#ifndef PARALLELOGRAM_H
#define PARALLELOGRAM_H

#include "shape.h"

class Parallelogram : public Shape
{
public:
    Point RightHigh;
    Point RightLow;

    Parallelogram(Point, Point, Point);
    ~Parallelogram(){}

    void MoveTo(const Point);
    void RotateOn(double);
    void ScaleOn(double);
    void Information(ostream&);
};

#endif // PARALLELOGRAM_H
