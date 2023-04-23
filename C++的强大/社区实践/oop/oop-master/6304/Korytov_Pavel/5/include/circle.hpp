#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

#define M_PI 3.14159265358979323846

class Circle : public Shape
{
public:
    Circle(Point cent = Pzero, double rad = 0, Color clr = Black) : Shape(cent, clr), radius(rad){}
    double getRadius(){ return radius * mult; }
    void setRadius(double rad) { mult = 1;  radius = rad; }
    double square() { return M_PI * getRadius() * getRadius(); }
    bool onCircle(const Point & p){
        Point temp = p - center;
        return (temp.GetR() == getRadius());
    }
    friend ostream& operator<<(ostream& os, const Circle& dt){
        os << "C: " << dt.center << " R:" << dt.radius;
        return os;
    }
private:
    double radius;
};

#endif