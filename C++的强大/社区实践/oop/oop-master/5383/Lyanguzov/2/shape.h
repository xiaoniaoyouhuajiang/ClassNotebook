#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <limits>

#include "point.h"

const double eps = 0.0001;
const double epsStep = eps / 10;

struct Color
{
    size_t red;
    size_t green;
    size_t blue;

    Color(size_t r = 0, size_t g = 0, size_t b = 0) :
        red(r), green(g), blue(b) {}
};

class Shape
{
private:
    static unsigned int counter;


protected:
    const unsigned int id;
    Point center_coordinates;
    double current_angle;
    double current_scale;
    Color current_color;

    Shape(double x, double y, double angle = 0, double scale = 1, Color color = Color(0, 0, 0)) :
        id(counter++),
        current_angle(angle),
        current_scale(scale),
        current_color(color)
    {
        center_coordinates.x = x;
        center_coordinates.y = y;
    }
    virtual void print(std::ostream &os) = 0;

    // метод для вычисления количества точек пересечения фигур
    virtual int intersect(Shape& s2) const = 0;

public:
    virtual ~Shape(){}
    void setColor(Color color);
    Color getColor() const;
    Point getPosition() const;
    void setPosition(Point p);
    double getAngle() const;
    void setAngle(double angle);
    unsigned int getId() const;

    virtual void scale(double scale) = 0;
    virtual double getPerimetr() const = 0;
    virtual double getArea() = 0;

    friend std::ostream &operator << (std::ostream &os, Shape &f);

    virtual bool isPointOnBorder(const Point &p) const = 0;
};

#endif // SHAPE_H
