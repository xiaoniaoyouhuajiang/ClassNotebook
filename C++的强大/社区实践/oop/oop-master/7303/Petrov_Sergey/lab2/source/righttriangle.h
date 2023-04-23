#pragma once
#include "triangle.h"

class RightTriangle: public Triangle{
public:
    RightTriangle(const Point& p, double a, double b, const Color& color);
    RightTriangle(const Point& p1, const Point& p2, const Point& p3, const Color& color);
    RightTriangle(const RightTriangle& other);

    friend std::ostream& operator<<(std::ostream& os, RightTriangle& s);
};
