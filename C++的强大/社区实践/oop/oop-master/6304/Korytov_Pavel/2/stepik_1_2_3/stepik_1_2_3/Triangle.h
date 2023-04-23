#pragma once
#include "Shape.h"

class Triangle :
    public Shape
{
public:
    Triangle();
	~Triangle() = default;
    Triangle(Point a, Point b, Point c, Color clr = Black);
    Triangle(int x1, int y1, int x2, int y2, int x3, int y3, Color clr = Black);
};