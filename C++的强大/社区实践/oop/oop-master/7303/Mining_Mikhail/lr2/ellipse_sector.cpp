#include <math.h>
#include "ellipse_sector.h"

void Ellipse_Sector::set_crd()
{
    crd.clear();

    Point p;
    p.x = radius1.radius * cos(radius1.angle) + centre.x;
    p.y = radius1.radius * sin(radius1.angle) + centre.y;
    crd.push_back(p);
    p.x = radius2.radius * cos(radius2.angle) + centre.x;
    p.y = radius2.radius * sin(radius2.angle) + centre.y;
    crd.push_back(p);

}

Ellipse_Sector::Ellipse_Sector(Radius new_radius1, Radius new_radius2, Point center) : Shape(center)
{
    radius1 = new_radius1;
    radius2 = new_radius2;
    set_crd();
}

void Ellipse_Sector::move(Point new_center)
{
    centre.x = new_center.x;
    centre.y = new_center.y;
    set_crd();
}

void Ellipse_Sector::rotate(double new_angle)
{
    radius1.angle += new_angle;
    radius2.angle += new_angle;
    set_crd();
}

void Ellipse_Sector::scale(double s)
{
    radius1.radius *= s;
    radius2.radius *= s;
    set_crd();
}

void Ellipse_Sector::print(std::ostream& out)
{
    out << "Stape type: ellipse sector\n";
    out << "Radius 1: " << radius1.radius << ", angle: " << radius1.angle << std::endl;
    out << "Radius 2: " << radius2.radius << ", angle: " << radius2.angle << std::endl;
}

Ellipse_Sector::~Ellipse_Sector()
{
    radius1.radius = 0;
    radius1.angle = 0;
    radius2.radius = 0;
    radius2.angle = 0;
}
