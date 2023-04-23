#include "shape.h"
#ifndef HEXAGON_H
#define HEXAGON_H

class Hexagon: public Shape{
    double a, radius;
public:
    Hexagon(Colour,std::vector <Point>,double,double);
    void scale(double) override;
    double perimetr() override;
    double area() override;
    void print(std::ostream& out) override;
};

#endif // HEXAGON_H
