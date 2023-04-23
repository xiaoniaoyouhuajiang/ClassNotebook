#ifndef CIRCLE_H
#define CIRCLE_H
#include <iostream>
#include <cmath>
#include "shape.h"
using namespace std;
class Circle : public Shape
{
private:
    double radius;

public:
    Circle(double radius, double x, double y) : Shape(x, y), radius(radius) {

    }
    ~Circle() {}
    void MoveCentre(double x, double y)
    {
        Xcentre = x;
        Ycentre = y;
    }
    double rotate(double radian) {}
    bool scale(double i)
    {
        if (i != 0.0)
        {
            radius *= i;
            return true;
        }
        return false;
    }

    bool operator ==(Circle s1)
    {
        if(s1.Xcentre == Xcentre && s1.Ycentre == Ycentre)
            return s1.radius == radius;
        else
            return false;
    }

    friend ostream& operator<<(ostream& out, const Circle &s)
    {
        return out << "Circle" << "   id:" << s.local_id << endl << "Center: (" << s.Xcentre << ", " << s.Ycentre << ")" << endl << "Radius: " << s.radius << endl;
    }


};
#endif // CIRCLE_H
