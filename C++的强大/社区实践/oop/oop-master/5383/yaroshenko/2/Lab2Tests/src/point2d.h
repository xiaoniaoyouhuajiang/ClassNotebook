#ifndef POINT2D_H
#define POINT2D_H

#include <cmath>

struct Point2d
{
    double x;
    double y;

    Point2d(double _x = 0, double _y = 0) : x(_x), y(_y) {}

    double distance(const Point2d& p) const;
    void rotate(double angle = 0);
    void translate2d(const Point2d& dp);
    void scale(double scale = 1);

    Point2d operator-() const { return Point2d(-x, -y); }
    Point2d operator+(const Point2d& p);
};

#endif // POINT2D_H
