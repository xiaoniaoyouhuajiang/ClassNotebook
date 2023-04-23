#include "regularhexagon.h"

RegularHexagon::RegularHexagon(Point dot, double r)
{
    centre = dot;
    radius = r;
    UpperA.X = centre.X;
    UpperA.Y = centre.Y + radius;
    angles = 6;
    angle = 0;
    scaled = 1;
}

void RegularHexagon::MoveTo(const Point dot)
{
    UpperA = UpperA - centre;
    centre = dot;
    UpperA = UpperA + centre;
}

void RegularHexagon::RotateOn(double ang)
{
    angle += ang;
    angle = fmod(angle, 360.0);
    double rad = angle * M_PI / 180;
    UpperA.X = centre.X - radius * sin(rad);
    UpperA.Y = centre.Y + radius * cos(rad);
}

void RegularHexagon::ScaleOn(double k)
{
    UpperA = UpperA - centre;
    UpperA.X *= k;
    UpperA.Y *= k;
    UpperA = UpperA + centre;
    scaled *= k;
}

void RegularHexagon::Information(ostream& os)
{
    os << "----------------------------" << endl;
    os << "This is Regular Hexagon." << endl;
    getInfo(os);
    os << "Upper Angle: " << UpperA;
}
