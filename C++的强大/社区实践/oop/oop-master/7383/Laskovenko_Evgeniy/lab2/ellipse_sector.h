#include "shape.h"

#ifndef ELLIPSE_SECTOR_H
#define ELLIPSE_SECTOR_H


class Ellipse_Sector : public Shape
{
    struct Radius
    {
        double radius;
        double angle;
    } radius_1, radius_2;
    void set_crd();

public:
    Ellipse_Sector(Radius, Radius, Point);
    void move(Point);
    void rotate(double);
    void scale(double);
    void print(std::ostream&);
    ~Ellipse_Sector();
};

#endif // ELLIPSE_SECTOR_H
