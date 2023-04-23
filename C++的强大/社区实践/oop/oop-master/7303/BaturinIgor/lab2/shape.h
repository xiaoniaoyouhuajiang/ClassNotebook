#ifndef SPAHE_H
#define SPAHE_H

#include "color.h"
#include "point.h"
#include <iostream>

class Shape
{
public:
    Shape();
    Shape(Color &color);
    Color getColor();
    void setColor(const Color& newColor);
    int getID() const;
    virtual void move(const Point& center) = 0;
    virtual void rotate(double angle = 0) = 0;
    virtual void scale(double coefficient = 1) = 0;
    Color color;
    static int global_id;
private:
    int id;
    int count = 0;
};

#endif // SPAHE_H