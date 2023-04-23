#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
protected:
    Point LowerLeftCorner;
    Point UpperRightCorner;

public:
    Rectangle(Point LLC, Point URC);
    ~Rectangle(){}

    void Turn(double value);
    void toScale(double k);
    void Moving(Point dot);
    void info(ostream& os);
};

#endif // RECTANGLE_H
