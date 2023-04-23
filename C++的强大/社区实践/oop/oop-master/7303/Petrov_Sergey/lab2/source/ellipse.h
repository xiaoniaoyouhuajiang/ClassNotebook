#pragma once
#include "shape.h"

class Ellipse : public Shape{
public:
    Ellipse(const Point& center, double a, double b, const Color& c);
    Ellipse(const Ellipse& other);

    void move(const Point& p);
    void scale(double scale);
    void turn(double angle);

    double get_radius1() const;
    double get_radius2() const;

    friend std::ostream& operator<<(std::ostream& os, Ellipse& s);

protected:
    double a;
    double b;
};
