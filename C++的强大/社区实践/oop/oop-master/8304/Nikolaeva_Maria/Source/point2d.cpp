#include "point2d.h"


Point2D::Point2D()
{
    x = 0;
    y = 0;
}


Point2D::Point2D(int x, int y)
{
    this->x = x;
    this->y = y;
}


Point2D* Point2D::clone()
{
    return new Point2D(this->x, this->y);
}
