#ifndef SHAPE_H
#define SHAPE_H
#include "point.h"
#include "color.h"
#include <cmath>
class Shape
{
protected:
    Point centre;
    Color color;
    int angles;
    double angle;
    double scaled;
    int ID;
    static int nextID;
    friend void operator<<(ostream&, Shape&);

public:
    Shape() : color(0, 0, 0)
    {
        ID = nextID++;
    }
    ~Shape(){}

    virtual void MoveTo(const Point) = 0;
    virtual void RotateOn(double) = 0;
    virtual void ScaleOn(double) = 0;
    virtual void Information(ostream&) = 0;

    void getColor();
    void setColor(Color);
    void getInfo(ostream&);
};

#endif // SHAPE_H
