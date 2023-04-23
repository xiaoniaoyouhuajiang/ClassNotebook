#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include <cmath>
using namespace std;
class Shape
{
protected:
    double Xcentre;
    double Ycentre;
    int local_id;
    int Rcolor;
    int Gcolor;
    int Bcolor;

public:
    static int id;
    Shape(double x, double y)
    {
        local_id = ++id;
        Xcentre = x;
        Ycentre = y;
        Rcolor = Gcolor = Bcolor = 0;
    }
    virtual ~Shape() {}
    virtual void MoveCentre(double x, double y) = 0;
    virtual double rotate(double radian) = 0;
    virtual bool scale(double i) = 0;
    void set_color(int red, int green, int blue)
    {
        Rcolor = red;
        Gcolor = green;
        Bcolor = blue;
    }
    friend ostream& operator<<(ostream& out, const Shape &s)
    {
        return out << "Center: (" << s.Xcentre << ", " << s.Ycentre << ")" << endl;
    }
};
#endif // SHAPE_H
