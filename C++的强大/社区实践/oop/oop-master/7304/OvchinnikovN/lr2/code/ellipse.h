#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape
{
private:
    Point f1;
    Point f2;
    double height;
    double width;

public:
    Ellipse(){}
    Ellipse(rgb color, double x, double y, double height, double width);

    void show();

    void move(double x, double y);

    void turn(double deg);

    void scale(double coeff);

    std::ostream& printShape(std::ostream &out, Shape &shape);

    Ellipse(const Ellipse &other);

    Ellipse operator +(double value);
};

#endif // ELLIPSE_H
