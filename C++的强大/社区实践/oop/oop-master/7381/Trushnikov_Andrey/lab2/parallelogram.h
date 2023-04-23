#include "shape.h"
#ifndef PARALLELOGRAM_H
#define PARALLELOGRAM_H

class Parallelogram: public Shape{
    double a , b, h;
public:
    Parallelogram(Colour,std::vector <Point>,double,double, double);
    void scale(double) override;
    double perimetr() override;
    double area() override;
    void print(std::ostream& out) override;
};

#endif // PARALLELOGRAM_H
