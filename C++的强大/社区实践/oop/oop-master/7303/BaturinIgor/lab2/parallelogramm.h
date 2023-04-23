#ifndef POINT_H
#define POINT_H

#define pi 3.14159265359

class Point
{
public:
    double x;
    double y;
    Point();
    Point(double x, double y);
    double length(Point& point);
    void rotate(double angle);
};

#endif // POINT_H