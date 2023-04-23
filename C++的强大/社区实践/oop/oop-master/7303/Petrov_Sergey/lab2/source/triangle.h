#pragma once
#include <cmath>
#include <vector>
#include "shape.h"

class Triangle: public Shape{
public:
    Triangle(const Point& p1, const Point& p2, const Point& p3, const Color& color);
    Triangle(const Triangle& other);

    std::vector<double> sides();

    void move(const Point& p);
    void scale(double scale);
    void turn(double angle);

    Point operator[](int ind);

    friend std::ostream& operator<<(std::ostream& os, Triangle& s);

protected:
    std::vector<Point> points;
    double a;
    double b;
    double c;
};
