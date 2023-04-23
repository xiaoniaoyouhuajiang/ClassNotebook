#include "shape.h"

class Ellipse_Sector : public Shape
{
    struct Radius
    {
        double radius;
        double angle;
    } radius1, radius2;
    void set_crd();

public:
    Ellipse_Sector(Radius, Radius, Point);
    void move(Point);
    void rotate(double);
    void scale(double);
    void print(std::ostream&);
    ~Ellipse_Sector();
};
