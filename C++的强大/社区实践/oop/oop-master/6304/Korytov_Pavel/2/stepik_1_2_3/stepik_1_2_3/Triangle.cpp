#include "stdafx.h"
#include "Triangle.h"

Triangle::Triangle() : Shape(3) {}
Triangle::Triangle(Point a, Point b, Point c, Color clr) : Shape(3, clr){
    pts[0] = a;
    pts[1] = b;
    pts[2] = c;
}

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3, Color clr)
    :Triangle(Point(x1, y1), Point(x2, y2), Point(x3, y3), clr) {}