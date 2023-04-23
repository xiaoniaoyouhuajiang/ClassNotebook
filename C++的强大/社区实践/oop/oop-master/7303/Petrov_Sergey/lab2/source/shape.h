#pragma once
#include <iostream>

struct Point{
    Point():x(0), y(0){}
    Point(int _x, int _y):x(_x), y(_y){}
    Point(const Point& other):x(other.x), y(other.y){}

    void set(double _x, double _y){
        x = _x;
        y = _y;
    }

    double x;
    double y;
};

struct Color{
    Color():red(0),green(0),blue(0){}
    Color(unsigned char r, unsigned char g, unsigned char b):red(r),green(g),blue(b){}
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

class Shape{
public:
    void set_color(const Color& color);
    Color get_color() const;
    Point get_pos() const;
    void set_pos(const Point& p);
    unsigned long long get_id() const;
    double get_angle() const;

    friend std::ostream& operator<<(std::ostream& os, Shape& s);

    virtual void move(const Point& p) = 0;
    virtual void scale(double scale) = 0;
    virtual void turn(double angle) = 0;

    static unsigned long long global_id;

protected:
    Shape(const Point& position, const Color& color);
    Point pos;
    Color color;
    double angle;
    unsigned long long id;
};
