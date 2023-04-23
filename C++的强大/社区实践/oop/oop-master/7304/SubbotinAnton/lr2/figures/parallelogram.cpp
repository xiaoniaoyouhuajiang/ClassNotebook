#include "parallelogram.h"

Parallelogram::Parallelogram(Point dot, Point RH, Point RL)
{
    centre = dot;
    RightHigh = RH;
    RightLow = RL;
    angles = 4;
    angle = 0;
    scaled = 1;
}

void Parallelogram::MoveTo(const Point dot)
{
    RightHigh = RightHigh - centre;
    RightLow = RightLow - centre;
    centre = dot;
    RightHigh = RightHigh + centre;
    RightLow = RightLow + centre;

}

void Parallelogram::RotateOn(double ang)
{
    ang = fmod(ang, 360.0);
    angle += ang;
    if(angle >= 360.0)
        angle -= 360.0;
    ang = ang * M_PI / 180;
    Point def = RightHigh - centre;
    RightHigh.X = centre.X + def.X * cos(ang) - def.Y * sin(ang);
    RightHigh.Y = centre.Y + def.Y * cos(ang) + def.X * sin(ang);

    def = RightLow - centre;
    RightLow.X = centre.X + def.X * cos(ang) - def.Y * sin(ang);
    RightLow.Y = centre.Y + def.Y * cos(ang) + def.X * sin(ang);
}

void Parallelogram::ScaleOn(double k)
{
    RightHigh = RightHigh - centre;
    RightHigh.X *= k;
    RightHigh.Y *= k;
    RightHigh = RightHigh + centre;
    RightLow = RightLow - centre;
    RightLow.X *= k;
    RightLow.Y *= k;
    RightLow = RightLow + centre;
    scaled *= k;
}

void Parallelogram::Information(ostream& os)
{
    os << "----------------------------" << endl;
    os << "This is Parallelogram." << endl;
    getInfo(os);
    os << "RightHigh: " << RightHigh;
    os << "RightLow: " << RightLow;
}
