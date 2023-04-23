#ifndef POINT_H
#define POINT_H

class Point{
public:
    Point(double x, double y);
    double getX() const;
    void setX(double x);
    double getY() const;
    void setY(double y);

private:
    double x;
    double y;
};

#endif // POINT_H
