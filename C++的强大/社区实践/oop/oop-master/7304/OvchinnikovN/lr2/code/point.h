#ifndef POINT_H
#define POINT_H

class Point
{
protected:
    double x;
    double y;

public:
    Point(int x=0, int y=0) : x(x), y(y){}
    void setPoint(double otherX, double otherY);
    double getX() const;
    double getY() const;
    void setX(double X);
    void setY(double Y);
    Point operator +(const Point &other);
    Point operator +(double value);
};

#endif // POINT_H
