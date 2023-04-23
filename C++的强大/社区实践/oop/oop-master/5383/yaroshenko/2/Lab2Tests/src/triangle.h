#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <array>
#include <algorithm>
#include "polygon.h"

class Triangle : public Polygon
{
public:
    Triangle(const Point2d& v1 = Point2d(), const Point2d& v2 = Point2d(), const Point2d& v3 = Point2d());

    double area() const;
    double perimeter() const;

    void scale(double scale = 1);

    double getA() const;
    double getB() const;
    double getC() const;

    bool operator==(const Triangle& other) const;

protected:
    double a, b, c;

    void print(std::ostream &os) const override;
};

#endif // TRIANGLE_H
