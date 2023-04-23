#ifndef POINT_H
#define POINT_H

class Point
{
public:
    double X;
    double Y;

    Point() : X(0), Y(0){}
    Point(double x, double y) : X(x), Y(y){}
    ~Point(){}

    Point operator + (const Point&);
    Point operator - (const Point&);
    Point& operator = (const Point&);
};

#endif // POINT_H
