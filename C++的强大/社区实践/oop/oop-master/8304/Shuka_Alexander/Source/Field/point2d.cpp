#include "point2d.h"


Point2D::Point2D()
{
    this->x = 0;
    this->y = 0;
}


Point2D::Point2D(int x, int y)
{
    this->x = x;
    this->y = y;
}


Point2D::Point2D(const Point2D& point)
{
    this->x = point.x;
    this->y = point.y;
}


Point2D& Point2D::operator=(const Point2D& point)
{
    if (this == &point) {
        return *this;
    }

    this->x = point.x;
    this->y = point.y;

    return *this;
}
