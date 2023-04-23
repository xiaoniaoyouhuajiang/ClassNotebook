#include "rectangle.h"

Rectangle::Rectangle(Point LLC, Point URC) : LowerLeftCorner(LLC), UpperRightCorner(URC)
{
    centre.X = (LowerLeftCorner.X + UpperRightCorner.X) / 2;
    centre.Y = (LowerLeftCorner.Y + UpperRightCorner.Y) / 2;
    angle = 4;
}

void Rectangle::Turn(double value)
{
    double TempX = LowerLeftCorner.X, TempY = LowerLeftCorner.Y;
    LowerLeftCorner.X = centre.X + (TempX - centre.X)*cos(value) - (TempY - centre.Y)*sin(value);
    LowerLeftCorner.Y = centre.Y + (TempY - centre.Y)*cos(value) + (TempX - centre.X)*sin(value);

    TempX = UpperRightCorner.X, TempY = UpperRightCorner.Y;
    UpperRightCorner.X = centre.X + (TempX - centre.X)*cos(value) - (TempY - centre.Y)*sin(value);
    UpperRightCorner.Y = centre.Y + (TempY - centre.Y)*cos(value) + (TempX - centre.X)*sin(value);
}

void Rectangle::toScale(double k)
{
    double side1 = UpperRightCorner.X - LowerLeftCorner.X;
    side1 = fabs(side1);
    double side2 = UpperRightCorner.Y - LowerLeftCorner.Y;
    side2 = fabs(side2);

    if(k > 1)
    {
        if(UpperRightCorner.X > LowerLeftCorner.X)
        {
            UpperRightCorner.X += side1/2 * (k-1);
            LowerLeftCorner.X -= side1/2 * (k-1);
            UpperRightCorner.Y += side2/2 * (k-1);
            LowerLeftCorner.Y -= side2/2 * (k-1);
        }
        else
        {
            UpperRightCorner.X -= side1/2 * (k-1);
            LowerLeftCorner.X += side1/2 * (k-1);
            UpperRightCorner.Y -= side2/2 * (k-1);
            LowerLeftCorner.Y += side2/2 * (k-1);
        }
    }
    else
    {
        double delta1 = (side1 - side1*k) / 2;
        double delta2 = (side2 - side2*k) / 2;
        if(UpperRightCorner.X > LowerLeftCorner.X)
        {
            UpperRightCorner.X -= delta1;
            LowerLeftCorner.X += delta1;
            UpperRightCorner.Y -= delta2;
            LowerLeftCorner.Y += delta2;
        }
        else
        {
            UpperRightCorner.X += delta1;
            LowerLeftCorner.X -= delta1;
            UpperRightCorner.Y += delta2;
            LowerLeftCorner.Y -= delta2;
        }
    }
}

void Rectangle::Moving(Point dot)
{
    Point DeltaUp = UpperRightCorner - centre;
    Point DeltaLow = LowerLeftCorner - centre;

    centre = dot;

    UpperRightCorner = centre + DeltaUp;
    LowerLeftCorner = centre + DeltaLow;
}

void Rectangle::info(ostream& os)
{
    os << "This is Rectangle!" << endl;
    os << "ID: " << ID << endl;
    os << "Count angle: " << angle << endl;
    os << "Centre: (" << centre.X << "; " << centre.Y << ")" << endl;
    os << "First point: (" << LowerLeftCorner.X << "; "  << LowerLeftCorner.Y << ")" << endl;
    os << "Second point: (" << UpperRightCorner.X << "; "  << UpperRightCorner.Y << ")" << endl;
    os << endl;
}
