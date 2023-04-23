#include "ellipse.h"

Ellipse::Ellipse(Point LF, Point RF, double space) : LeftFocus(LF), RightFocus(RF), length(space)
{
    centre.X = (LF.X + RF.X) / 2;
    centre.Y = (LF.Y + RF.Y) / 2;
    angle = 0;
}

void Ellipse::Turn(double value)
{
    double TempX = LeftFocus.X, TempY = LeftFocus.Y;
    LeftFocus.X = centre.X + (TempX - centre.X)*cos(value) - (TempY - centre.Y)*sin(value);
    LeftFocus.Y = centre.Y + (TempY - centre.Y)*cos(value) + (TempX - centre.X)*sin(value);

    TempX = RightFocus.X, TempY = RightFocus.Y;
    RightFocus.X = centre.X + (TempX - centre.X)*cos(value) - (TempY - centre.Y)*sin(value);
    RightFocus.Y = centre.Y + (TempY - centre.Y)*cos(value) + (TempX - centre.X)*sin(value);
}

void Ellipse::toScale(double k)
{
    if(k > 1)
    {
        if(RightFocus.X > LeftFocus.X)
        {
            RightFocus.X += length/2 * (k-1);
            LeftFocus.X -= length/2 * (k-1);
            length *= k;
        }
        else
        {
            RightFocus.X -= length/2 * (k-1);
            LeftFocus.X += length/2 * (k-1);
            length *= k;
        }
    }
    else
    {
        double delta = (length - length*k)/2;
        if(RightFocus.X > LeftFocus.X)
        {
            RightFocus.X -= delta;
            LeftFocus.X += delta;
            length *= k;
        }
        else
        {
            RightFocus.X += delta;
            LeftFocus.X -= delta;
            length *= k;
        }
    }
}

void Ellipse::Moving(Point dot)
{
    Point Delta1 = RightFocus - centre;
    Point Delta2 = LeftFocus - centre;

    centre = dot;

    RightFocus = centre + Delta1;
    LeftFocus = centre + Delta2;
}

void Ellipse::info(ostream& os)
{
    os << "This is Ellipse!" << endl;
    os << "ID: " << ID << endl;
    os << "Count angle: " << angle << endl;
    os << "Centre: (" << centre.X << "; " << centre.Y << ")" << endl;
    os << "First focus: (" << LeftFocus.X << "; "  << LeftFocus.Y << ")" << endl;
    os << "Second focus: (" << RightFocus.X << "; "  << RightFocus.Y << ")" << endl;
    os << "Length: " << length << endl;
    os << endl;
}
