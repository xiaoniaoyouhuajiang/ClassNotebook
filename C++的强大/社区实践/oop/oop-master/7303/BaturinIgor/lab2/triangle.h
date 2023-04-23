#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

class Triangle : public Shape
{
public:
    Triangle();
    Triangle(Point& center ,Point& p1, Point& p2, Point& p3);
    Triangle(Color& color);
    void scale(double coefficient);
    void rotate(double angle);
    void move(const Point& center);
    friend Triangle operator + (Triangle const & t_1, Triangle const & t_2) {
        Point point1;
        Point point2;
        Point point3;
        point1.x = (t_1.p1.x + t_2.p1.x)/2;
        point1.y = (t_1.p1.y + t_2.p1.y)/2;
        point2.x = (t_1.p2.x + t_2.p2.x)/2;
        point2.y = (t_1.p2.y + t_2.p2.y)/2;
        point3.x = (t_1.p3.x + t_2.p3.x)/2;
        point3.y = (t_1.p3.y + t_2.p3.y)/2;
        Point center;
        center.x = (point1.x + point2.x + point3.x)/3;
        center.y = (point1.y + point2.y + point3.y)/3;
        return Triangle(center, point1, point2, point3);
    }
    friend std::ostream& operator << (std::ostream &print, Triangle& triangle);
private:
    double coefficient = 1;
    double a;
    double b;
    double c;
    Point p1, p2, p3;
    Point center;
};

#endif // TRIANGLE_H