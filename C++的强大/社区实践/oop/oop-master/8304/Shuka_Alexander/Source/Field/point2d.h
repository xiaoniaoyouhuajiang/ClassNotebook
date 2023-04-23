#ifndef POINT2D_H
#define POINT2D_H

#include <cstddef>


class Point2D
{
public:
    explicit Point2D();
    explicit Point2D(int x, int y);

    Point2D(const Point2D& point);

    Point2D& operator=(const Point2D& point);

    int x;
    int y;
};

#endif // POINT2D_H
