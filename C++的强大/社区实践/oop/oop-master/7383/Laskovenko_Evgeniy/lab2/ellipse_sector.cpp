#include <math.h>
#include "ellipse_sector.h"

void Ellipse_Sector::set_crd()
{
    crd.clear();

    Point p;
    p.x = radius_1.radius * cos(radius_1.angle) + centre.x;
    p.y = radius_1.radius * sin(radius_1.angle) + centre.y;
    crd.push_back(p);
    p.x = radius_2.radius * cos(radius_2.angle) + centre.x;
    p.y = radius_2.radius * sin(radius_2.angle) + centre.y;
    crd.push_back(p);

}

Ellipse_Sector::Ellipse_Sector(Radius rad_1, Radius rad_2, Point cntr) : Shape(cntr)
{
    radius_1 = rad_1;
    radius_2 = rad_2;
    set_crd();
}

void Ellipse_Sector::move(Point new_cntr)
{
    centre.x = new_cntr.x;
    centre.y = new_cntr.y;
    set_crd();
}

void Ellipse_Sector::rotate(double angl)
{
    radius_1.angle += angl;
    radius_2.angle += angl;
    set_crd();
}

void Ellipse_Sector::scale(double k)
{
    radius_1.radius *= k;
    radius_2.radius *= k;
    set_crd();
}

void Ellipse_Sector::print(std::ostream& out)
{
    out << "Stape type: ellipse sector\n";
    out << "Radius 1: " << radius_1.radius << ", angle: " << radius_1.angle << std::endl;
    out << "Radius 2: " << radius_2.radius << ", angle: " << radius_2.angle << std::endl;
}

Ellipse_Sector::~Ellipse_Sector()
{
    radius_1.radius = 0;
    radius_1.angle = 0;
    radius_2.radius = 0;
    radius_2.angle = 0;
}
