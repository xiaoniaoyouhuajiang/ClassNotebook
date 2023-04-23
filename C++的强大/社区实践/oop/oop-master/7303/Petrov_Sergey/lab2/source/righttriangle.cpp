#include "righttriangle.h"

RightTriangle::RightTriangle(const Point& p1, const Point& p2, const Point& p3, const Color& color)
    :Triangle(p1, p2, p3, color){}

RightTriangle::RightTriangle(const Point& p, double a, double b, const Color& color)
    :Triangle(Point(p.x, p.y+a), p, Point(p.x+b, p.y), color){}

RightTriangle::RightTriangle(const RightTriangle& other)
    :Triangle(other.points[0], other.points[1], other.points[2], other.color){}

std::ostream& operator<<(std::ostream& os, RightTriangle& s){
    os << (Triangle&)s;
}
