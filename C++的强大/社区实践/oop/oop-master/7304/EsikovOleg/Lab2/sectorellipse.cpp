#include "sectorellipse.h"

SectorEllipse::SectorEllipse(Point LF, Point RF, double space, double Angle1, double Angle2) : Ellipse(LF, RF, space)
{
    AngleWithX = Angle1;
    AngleSector = Angle2;
    angle = 1;
}

void SectorEllipse::Turn(double value)
{
    Ellipse::Turn(value);
    AngleWithX += value;
    AngleSector += value;
}

void SectorEllipse::info(ostream &os)
{
    os << "This is SectorEllipse!" << endl;
    os << "ID: " << ID << endl;
    os << "Count angle: " << angle << endl;
    os << "Centre: (" << centre.X << "; " << centre.Y << ")" << endl;
    os << "First focus: (" << LeftFocus.X << "; "  << LeftFocus.Y << ")" << endl;
    os << "Second focus: (" << RightFocus.X << "; "  << RightFocus.Y << ")" << endl;
    os << "Length: " << length << endl;
    os << "MinAngle: " << AngleWithX << endl;
    os << "MaxAngle: " << AngleSector << endl;
    os << endl;
}
