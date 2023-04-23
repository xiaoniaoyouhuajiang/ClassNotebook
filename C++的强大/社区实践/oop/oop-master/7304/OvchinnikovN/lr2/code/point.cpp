#include "point.h"

void Point::setPoint(double otherX, double otherY)
{
    x = otherX;
    y = otherY;
}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

void Point::setX(double X)
{
    x = X;
}

void Point::setY(double Y)
{
    y = Y;
}

Point Point::operator +(const Point &other)
{
    Point tmp;
    tmp.x = (this->x + other.x)/2;
    tmp.y = (this->y + other.y)/2;
    return tmp;
}

Point Point::operator +(double value)
{
    Point tmp;
    tmp.x = this->x + value;
    tmp.y = this->y + value;
    return tmp;
}
