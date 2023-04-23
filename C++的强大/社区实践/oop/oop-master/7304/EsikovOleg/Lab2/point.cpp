#include "point.h"

Point Point::operator + (const Point& element)
{
    Point result;
    result.X = X + element.X;
    result.Y = Y + element.Y;
    return result;
}

Point Point::operator - (const Point& element)
{
    Point result;
    result.X = X - element.X;
    result.Y = Y - element.Y;
    return result;
}

Point& Point::operator = (const Point& element)
{
    X = element.X;
    Y = element.Y;
    return *this;
}
