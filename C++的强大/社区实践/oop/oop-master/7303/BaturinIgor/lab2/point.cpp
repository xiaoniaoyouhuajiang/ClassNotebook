#include "point.h"
#include <math.h>
Point::Point() : x(0), y(0)
{

}

Point::Point(double x, double y)
    : x(x)
    , y(y)
{

}

double Point::length(Point& point) {
    return sqrt((x-point.x)*(x-point.x) + (y-point.y)*(y-point.y));
}

void Point::rotate(double angle) {
    double newX = x;
    double newY = y;
    x = newX * cos(angle*pi/180) - newY * sin(angle*pi/180);
    y = newX * sin(angle*pi/180) + newY * cos(angle*pi/180);
}
     
17  7303/BaturinIgor/lab2/point.h
@@ -0,0 +1,17 @@
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