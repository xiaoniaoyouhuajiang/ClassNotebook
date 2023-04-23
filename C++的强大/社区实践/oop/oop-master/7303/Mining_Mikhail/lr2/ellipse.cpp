#include <math.h>
#include "ellipse.h"

void Ellipse::set_crd()
{
    crd.clear();
    crd.push_back({centre.x - a / 2, centre.y});
    crd.push_back({centre.x, centre.y + b / 2});
    crd.push_back({centre.x + a / 2, centre.y});
    crd.push_back({centre.x, centre.y - b / 2});
    rotate(angle);
}

Ellipse::Ellipse(double new_a, double new_b, Point center, double new_angle) : Shape(center)
{
    a = new_a;
    b = new_b;
    angle = new_angle;
    set_crd();
}

void Ellipse::move(Point new_centre)
{
    centre.x = new_centre.x;
    centre.y = new_centre.y;
    set_crd();
}

void Ellipse::rotate(double new_angle)
{
    angle = new_angle;

    double new_x, new_y;
    for(unsigned i=0; i<crd.size(); ++i)
    {
        new_x = crd[i].x;
        new_y = crd[i].y;
        crd[i].x = (new_x - centre.x) * cos(angle) - (new_y - centre.y) * sin(angle) + centre.x;
        crd[i].y = (new_x - centre.x) * sin(angle) + (new_y - centre.y) * cos(angle) + centre.y;
    }

}

void Ellipse::scale(double s)
{
    a *= s;
    b *= s;
    set_crd();
}

void Ellipse::print(std::ostream& out)
{
    out << "Stape type: ellipse\n";
    out << "a: " << a << std::endl;
    out << "b: " << b << std::endl;
}

Ellipse::~Ellipse()
{
    a = 0;
    b = 0;
}
