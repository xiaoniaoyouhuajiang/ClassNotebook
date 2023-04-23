#include "shape.h"

class Circle : public Shape
{
    double radius;
    void set_crd();

public:
    Circle(double, Point);
    void move(Point);
    void rotate(double);
    void scale(double);
    void print(std::ostream&);
    ~Circle();
};
