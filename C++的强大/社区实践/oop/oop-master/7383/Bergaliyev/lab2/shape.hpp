#pragma once
#include <cmath>
#include <iostream>
#define eps 0.000000000001

struct Color{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    Color(unsigned char red, unsigned char green, unsigned char blue)
     : red(red), green(green), blue(blue) {}
};

std::ostream & operator<<(std::ostream & ostream, Color const & color);

struct Point{
    double x;
    double y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    double distance(Point const & p) const {
	return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y-p.y));
    }
};

std::ostream & operator<<(std::ostream & ostream, Point const & p);

class Shape{
public:
    void scale(double scale_ratio);
    void relocate(Point p);
    void rotate(double angle);
    virtual std::ostream & print(std::ostream & ostream) const = 0;
    Color get_color() const {
	return color;
    }
    void set_color(Color new_color){
	color = new_color;
    }
    unsigned int get_id() const{
	return id;
    }
    Point get_v1() const{
	return v1;
    }
    Point get_v2() const{
	return v2;
    }
    Point get_v3() const{
	return v3;
    }
    Point get_v4() const{
	return v4;
    }
    virtual ~Shape() {
	--count;
    }
protected:
    Shape(Color color, Point v1, Point v2, Point v3, Point v4) : color(color), v1(v1), v2(v2), v3(v3), v4(v4), id(count) {
	++count;
    }
    Color color;
    Point center; //точка пересечения диагоналей
    Point v1;
    Point v2;
    Point v3;
    Point v4;
private:
    unsigned int id;
    static unsigned int count;
};

std::ostream & operator<<(std::ostream & ostream, Shape const & shape);
