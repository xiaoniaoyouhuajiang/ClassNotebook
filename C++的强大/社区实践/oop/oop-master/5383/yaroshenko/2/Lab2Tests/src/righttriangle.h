#ifndef RIGHTTRIANGLE_H
#define RIGHTTRIANGLE_H

#include "triangle.h"

class RightTriangle : public Triangle
{
public:
    RightTriangle(const Point2d& vertex, double leftSide, double downSide, double angle = 0);
    // создает случайную фигуру
    RightTriangle(double random_range);

    double area() const;

protected:
    void print(std::ostream &os) const override;
};

#endif // RIGHTTRIANGLE_H
