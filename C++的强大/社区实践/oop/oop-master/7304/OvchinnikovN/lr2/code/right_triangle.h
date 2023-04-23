#ifndef RIGHT_TRIANGLE_H
#define RIGHT_TRIANGLE_H

#include "triangle.h"

class RightTriangle : public Triangle
{
private:
    double side1;
    double side2;

public:
    RightTriangle(){}
    RightTriangle(rgb color, double x, double y, double side1, double side2);

    std::ostream& printShape(std::ostream &out, Shape &shape);

    RightTriangle operator +(double value);
};

#endif // RIGHT_TRIANGLE_H
