#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#ifndef SHAPE_H
#define SHAPE_H

enum Color {NOCOLOR, WHITE, RED, GREEN, BLUE, BLACK};

struct Point
{
    double x;
    double y;
};

class Shape
{
protected:
    static unsigned id;
    Color clr;
    Point centre;
    std::vector<Point> crd;

private:
    //Pure-virtual (non-used) functions:
    virtual void set_crd() = 0;

public:
    Shape(Point center);
    Color get_color() const;
    void set_color(Color color);

    //Pure-virtual functions:
    virtual void move(Point) = 0;
    virtual void rotate(double) = 0;
    virtual void scale(double) = 0;
    virtual void print(std::ostream&) = 0;

    //Virtual functions:
    virtual ~Shape();

    //Friend functions:
    friend std::ostream& operator<<(std::ostream&, Shape&);
};

#endif // SHAPE_H
