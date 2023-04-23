#include "point.h"

Point Point::operator+(const Point& argument)
{
    Point result;
    result.X = X + argument.X;
    result.Y = Y + argument.Y;
    return result;
}

Point Point::operator-(const Point& argument)
{
    Point result;
    result.X = X - argument.X;
    result.Y = Y - argument.Y;
    return result;
}

Point& Point::operator=(const Point& argument)
{
    X = argument.X;
    Y = argument.Y;
    return *this;
}

void operator<<(ostream& os, const Point& dot)
{
    os << endl << "  Y = " << dot.Y << endl;
    os << "  X = " << dot.X << endl << endl;
}
