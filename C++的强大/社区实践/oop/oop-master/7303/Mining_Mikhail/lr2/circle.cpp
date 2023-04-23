#include "circle.h"


void Circle::set_crd()
{
    crd.clear();
    crd.push_back({centre.x - radius, centre.y});
    crd.push_back({centre.x, centre.y - radius});
    crd.push_back({centre.x + radius, centre.y});
    crd.push_back({centre.x, centre.y + radius});
}

Circle::Circle(double new_radius, Point center) : Shape(center)
{
    radius = new_radius;
    set_crd();
}

void Circle::move(Point new_center)
{
    centre.x = new_center.x;
    centre.y = new_center.y;
    set_crd();
}

void Circle::rotate(double)
{

}

void Circle::scale(double s)
{
    radius *= s;
    set_crd();
}

void Circle::print(std::ostream& out)
{
    out << "Stape type: circle\n";
    out << "Radius: " << radius << std::endl;
}

Circle::~Circle()
{
    radius = 0;
}
