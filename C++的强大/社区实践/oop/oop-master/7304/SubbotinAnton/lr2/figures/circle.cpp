#include "circle.h"

Circle::Circle(const Point dot, double r)
{
    radius = r;
    centre = dot;
    angles = 0;
    angle = 0;
    scaled = 1;
}

void Circle::MoveTo(const Point dot)
{
    centre = dot;
}

void Circle::RotateOn(double ang){
    angle = fmod(ang, 360.0);
}

void Circle::ScaleOn(double k)
{
    scaled *= k;
    radius *= k;
}

void Circle::Information(ostream& os)
{
    os << "----------------------------" << endl;
    os << "This is Circle." << endl;
    getInfo(os);
    os << "Radius: " << radius << endl << endl;
}
