#ifndef RIGHTTRIANGLE_H
#define RIGHTTRIANGLE_H

#include "shape.h"

class rightTriangle : public Shape
{
public:
    rightTriangle();
    rightTriangle(Point& center ,Point& p1, Point& p2, Point& p3);
    rightTriangle(rightTriangle& other);
    rightTriangle(Color& color);
    void scale(double coefficient);
    void rotate(double angle);
    void move(const Point& center);
    friend std::ostream& operator << (std::ostream &print, rightTriangle& rightTriangle);
private:
    Point p1, p2, p3;
    Point center;
    double coefficient = 1;
    double a;
    double b;
    double c;
};

#endif // RIGHTTRIANGLE_H