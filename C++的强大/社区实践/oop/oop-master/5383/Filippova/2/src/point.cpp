
#include <cmath>
#include "point.h"


Point::Point():
    X(0), Y(0) {}

Point::Point(double xx, double yy) :
    X(xx), Y(yy){}

double Point::distance(const Point &other) const
{
    double dx = other.X - X;
    double dy = other.Y - Y;
    return sqrt(dx*dx + dy*dy);
}

void Point::rotate(double angle)
{
    double old_x = X;
    double old_y = Y;
    
    X = old_x * cos(angle) - old_y * sin(angle);
    Y = old_x * sin(angle) + old_y * cos(angle);
}