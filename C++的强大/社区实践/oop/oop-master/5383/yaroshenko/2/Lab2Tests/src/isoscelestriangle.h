#ifndef ISOSCELESTRIANGLE_H
#define ISOSCELESTRIANGLE_H

#include "triangle.h"

class IsoscelesTriangle : public Triangle
{
public:
    IsoscelesTriangle(const Point2d& vertex, double side, double phi, double angle = 0);
    IsoscelesTriangle(double random_range);

    void scale(double scale = 1);

protected:
    double h;

    void print(std::ostream &os) const override;
};

#endif // ISOSCELESTRIANGLE_H
