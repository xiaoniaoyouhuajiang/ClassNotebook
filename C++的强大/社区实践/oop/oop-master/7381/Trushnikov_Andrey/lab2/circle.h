#include <shape.h>
#ifndef CIRCLE_H
#define CIRCLE_H

class Circle: public Shape{
    double radius;
public:
    Circle(std::vector <Point>,double, Colour);
    void scale(double) override;
    double perimetr() override;
    double area() override;
    void print(std::ostream&) override;
};

#endif // CIRCLE_H
