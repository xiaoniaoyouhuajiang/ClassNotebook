#ifndef POINT_H
#define POINT_H

#include <iostream>
using namespace std;

class Point
{
public:
    double X;
    double Y;

    Point() : X(0), Y(0){}
    Point(double y, double x) : X(x), Y(y){}
    ~Point(){}

    Point operator+(const Point&);
    Point operator-(const Point&);
    Point& operator=(const Point&);
    friend void operator<<(ostream&, const Point&);
};

#endif // POINT_H
