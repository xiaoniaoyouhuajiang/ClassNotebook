#pragma once

#include <iostream>
#include <vector>
#include <cmath>



struct Point {
    Point(double x = 0, double y = 0): x(x), y(y) {}
    Point(const Point& other):x(other.x), y(other.y){}


    double x;
    double y;
};

std::ostream& operator<<(std::ostream& out, Point& p);

struct Color{

    Color(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0):red(r),green(g),blue(b){}
    Color(const Color& other):red(other.red),green(other.green),blue(other.blue){}

    void set(unsigned char r, unsigned char g, unsigned char b){
        red = r;
        green = g;
        blue = b;
    }

    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

std::ostream& operator<<(std::ostream& out, Color& n);


class Shape{
public:

    virtual void move(const Point& p);

    virtual void scale(double scale);


    virtual void turn(double angle);

    friend std::ostream& operator<<(std::ostream& out, Shape& shape);

    void setColor(Color color);

    Color getColor();

    static unsigned int id_counter;

protected:
    Shape(const Point& position);
    Point pos;
    Color color;
    unsigned int id;
    double angle = 0;
    double Scale = 1;
    std::vector<Point> points;

};



