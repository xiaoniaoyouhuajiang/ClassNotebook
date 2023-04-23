#include "point2d.h"

double Point2d::distance(const Point2d &p) const
{
    double dx = p.x - x;
    double dy = p.y - y;

    return sqrt(dx*dx + dy*dy);
}


void Point2d::rotate(double angle)
{
    double old_x = x, old_y = y;

    x = old_x * cos(angle) - old_y * sin(angle);
    y = old_x * sin(angle) + old_y * cos(angle);
}


void Point2d::translate2d(const Point2d &dp)
{
    x += dp.x;
    y += dp.y;
}


void Point2d::scale(double scale)
{
    x *= scale;
    y *= scale;
}


Point2d Point2d::operator+(const Point2d& p)
{
    return Point2d(x + p.x, y + p.y);
}
