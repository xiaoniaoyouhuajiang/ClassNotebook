#ifndef SHAPE_H
#define SHAPE_H

#include "rgb.h"
#include "point.h"
#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPen>
#include <cmath>

#define PI 3.14159265359

class Shape
{
protected:
    unsigned long int id;
    Point center;
    rgb color;

public:
    static unsigned long int count;
    virtual void move(double x, double y) = 0;
    virtual void turn(double deg) = 0;
    virtual void scale(double coeff) = 0;
    virtual std::ostream& printShape(std::ostream &out, Shape &shape) = 0;
    virtual void show() = 0;

    Shape();
    Shape(rgb color);
    void setMainCenter(double x, double y);
    Point getMainCenter();
    rgb getShapeColor();
    unsigned long int getId();
    friend std::ostream& operator<< (std::ostream& out, Shape &shape)
    {
        return shape.printShape(out, shape);
    }
};

#endif // SHAPE_H
