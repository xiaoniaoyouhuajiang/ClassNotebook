#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

class Triangle : public Shape
{
protected:
    Point one;
    Point two;
    Point three;

public:
    Triangle(){}
    Triangle(rgb color, double x1, double y1, double x2, double y2, double x3, double y3);
    void setCenter();
    void show() override;
    void move(double x, double y) override;
    void turn(double deg) override;
    void scale(double coeff) override;
    std::ostream& printShape(std::ostream &out, Shape &shape) override;
    Triangle(const Triangle &other);
    Triangle operator +(const Triangle& other);
    Triangle operator +(double value);
};

#endif // TRIANGLE_H
